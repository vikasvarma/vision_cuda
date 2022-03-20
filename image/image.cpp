// Define STB_IMAGE & STB_IMAGE_WRITE packages
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <stdint.h>
#include <string>
#include <map>
#include <cassert>
#include "image.h"

#include "stb_image.h"
#include "stb_image_write.h"

using namespace std;

/*******************************************************************************
 * @brief EXCEPTION_HANDLING
 *
 */
#define READ_FAILURE "ERR 001: Read failure.\n Unable to read image file."
#define IMASSERT(condition, message) \
    do                               \
    {                                \
        if (!(condition))            \
        {                            \
            printf((message));       \
        }                            \
        assert((condition));         \
    } while (false)

struct ImageException : public exception
{
public:
    ImageException(const string &msg) : msg_(msg) {}
    ~ImageException() {}
    string getMessage() const { return (msg_); }

private:
    string msg_;
};
// END: EXCEPTION_HANDLING

/*******************************************************************************
 * @brief IMAGE
 *
 */

static map<string, ImageType> const typemap{
    {".png", ImageType::PNG},
    {".jpg", ImageType::JPEG},
    {".jpeg", ImageType::JPEG},
    {".tif", ImageType::TIFF},
    {".tiff", ImageType::TIFF}};

/**
 * @brief Construct a new Image object by reading data from disk
 * 
 * @param filename 
 */
Image::Image(const char *filename)
{
    // Read the image:
    uint8_t *buffer;
    buffer = stbi_load(filename, &W, &H, &C, 0);
    bytes = W * H * C;

    if (buffer == NULL)
    {
        throw(ImageException(READ_FAILURE));
    }
}

/**
 * @brief Construct a new Image object using its dimension
 * 
 * @param w 
 * @param h 
 * @param c 
 */
Image::Image(int w, int h, int c) : W(w), H(h), C(c)
{
    // Initialize a new data buffer
    bytes = w * h * c;
    data = new uint8_t[bytes];
}

/**
 * @brief Construct a new Image object from another Image object
 * 
 * @param img 
 */
Image::Image(const Image &img) : W(img.W), H(img.H), C(img.C)
{
    // Copy data buffer from the source image.
    bytes = img.bytes;
    memcpy(data, img.data, bytes);
}

/**
 * @brief Destroy the Image object
 * 
 */
Image::~Image()
{
    if (data != nullptr)
    {
        stbi_image_free(data);
    }
}

/**
 * @brief Write data in the Image object to disk.
 * 
 * @param filename 
 * @return true 
 * @return false 
 */
bool Image::write(const char *filename)
{
    ImageType type = get_type(filename);
    int success = 0;
    switch (type)
    {
    case ImageType::PNG:
        success = stbi_write_png(filename, W, H, C, data, W * C);
        break;
    case ImageType::JPEG:
        success = stbi_write_jpg(filename, W, H, C, data, 100);
        break;
    default:
        success = 0;
        throw(ImageException("ERR02: Invalid file type.\nUnable to determine image format."));
        break;
    }
    if (success == 0)
    {
        printf("Failed to write %s.", filename);
    }
    return success == 0;
}

/**
 * @brief Utility Functions
 */
ImageType Image::get_type(const char *filename)
{
    const char *ext = strrchr(filename, '.');
    auto entry = typemap.find(ext);
    ImageType type;
    if (entry != typemap.end())
    {
        type = entry->second;
    }
    else
    {
        type = ImageType::UNKNOWN;
    }
    return type;
}

int Image::get_index(int x, int y, int c) const
{
    /**
     * Data is H scanlines each of size W*C.
     * Channel information is interleaved into each pixel. So for examples,
     * if the image has 3 channels (RGB), then the DATA buffer format is
     * (RGB)(RGB)(RGB)...(RGB)
     * (0,0)(1,0)(2,0)...(W-1,0)
     */
    IMASSERT((x >= 0) && (x < W), "X specified is out of W range.");
    IMASSERT((y >= 0) && (y < H), "Y specified is out of H range.");
    IMASSERT((c >= 0) && (c < C), "C specified is out of channel range.");
    return y * W + x * C + c;
}

// END: IMAGE