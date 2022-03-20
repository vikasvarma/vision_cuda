/**
 * @file image.h
 * @author Vikas Varma (vikas.2110varma@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

/**
 * @brief IMAGE_H DOCUMENTATION
 *
 */

/*******************************************************************************
 * @brief IMAGE - Container class to store image pixel data.
 *
 *
 */
enum class ImageType
{
	UNKNOWN,
	PNG,
	JPEG,
	TIFF
};

class Image
{
public:
	/**
	 * @brief DATA - Row major interleaved scanline pixel intensities.
	 *
	 */
	uint8_t *data = nullptr;
	size_t bytes = 0;
	int W, H, C;

public:
	Image(const char *filename);
	Image(int w, int h, int c);
	Image(const Image &img);
	~Image();

	bool write(const char *filename);
	inline uint8_t &operator()(int x, int y, int c)
	{
		return data[get_index(x, y, c)];
	}
	inline uint8_t &operator()(int x, int y, int c) const
	{
		return data[get_index(x, y, c)];
	}

private:
	ImageType Image::get_type(const char *filename);
	int get_index(int x, int y, int c) const;
};

#endif // IMAGE_H