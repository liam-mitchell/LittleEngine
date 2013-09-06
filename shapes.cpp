/*
 * shapes.cpp
 *
 *  Created on: Jul 6, 2013
 *      Author: Danyl
 */
#include <new>
#include "shapes.h"
#include <stdlib.h>

Image::Image() :width(1), height(1) {
	chars = new CHAR;
	colours = new COL;
	chars[0] = 255;
	colours[0] = 0;
}

Image::Image(const int w, const int h, const CHAR *chrs, const COL *cols) :width(w), height(h) {
	chars = new CHAR[w * h];
	colours = new COL[w * h];
	for (int i = 0; i < w * h; ++i) {
		chars[i] = chrs[i];
		colours[i] = cols[i];
	}
}

Image::Image(const Image &src) {
	width = src.width;
	height = src.height;
	chars = new CHAR[width * height];
	colours = new COL[width * height];
	for (int i = 0; i < width * height; ++i) {
		chars[i] = src.chars[i];
		colours[i] = src.colours[i];
	}
}

Image::~Image() {
	delete [] chars;
	delete [] colours;
}

Image &Image::operator=(const Image &src) {
	if (this != &src) {
		if (chars) delete [] chars;
		if (colours) delete [] colours;
		width = src.width;
		height = src.height;
		chars = new CHAR[width * height];
		colours = new COL[width * height];
		for (int i = 0; i < width * height; ++i) {
			chars[i] = src.chars[i];
			colours[i] = src.colours[i];
		}
	}
	return *this;
}

bool Image::operator==(const Image &src) {
	if (width == src.width && height == src.height) {
		for (int i = 0; i < width * height; ++i) {
			if (chars[i] != src.chars[i] || colours[i] != src.colours[i])
				return false;
		}

		return true;
	} else return false;
}

void Image::setWidth(int w) {
	width = w;
}

void Image::setHeight(int h) {
	height = h;
}

void Image::setChars(CHAR *chrs) {
	for (int i = 0; i < width * height; ++i) {
		chars[i] = chrs[i];
	}
}

void Image::setColours(COL *cols) {
	for (int i = 0; i < width * height; ++i) {
		colours[i] = cols[i];
	}
}

int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}

CHAR *Image::getChars() {
	return chars;
}

COL *Image::getColours() {
	return colours;
}

Image::Image(const char *filename) {
	std::ifstream inputFile;
	inputFile.open(filename, std::ios::in);

	if (inputFile.is_open()) {
		inputFile >> width;
		inputFile >> height;
		chars = new CHAR[width * height];
		colours = new CHAR[width * height];

		int temp, i;
		for (i = 0; (i < height * width) && inputFile.good(); ++i) {
			inputFile >> temp;
			chars[i] = (CHAR)temp;
		}

		for (i = 0; (i < width * height) && inputFile.good(); ++i) {
			inputFile >> temp;
			colours[i] = (CHAR)temp;
		}
	} else {
		width = 0;
		height = 0;
		chars = NULL;
		colours = NULL;
	}

	inputFile.close();
}

Cloud_s Cloud = {
		CLOUDW,
		CLOUDH,
		{
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,177,177,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,177,177,177,177,177,177,255,255,255,255,255,255,255,255,
			255,255,255,255,255,177,177,178,178,177,177,177,177,255,255,255,255,255,255,255,
			255,255,255,177,177,177,178,178,178,178,178,178,177,177,255,255,255,255,255,255,
			255,255,177,177,178,178,178,178,178,178,178,178,178,177,255,255,255,255,255,255,
			255,255,177,178,178,178,178,178,178,178,178,178,178,177,177,255,255,255,255,255,
			255,255,177,177,177,177,177,177,177,177,177,177,177,177,177,177,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
		},

		{
			  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			  0,  0,  0,  0,  0,  0,  0,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			  0,  0,  0,  0,  0,  0,  8,  8,  8,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,
			  0,  0,  0,  0,  0,  8,  8,  7,  7,  7,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,
			  0,  0,  0,  8,  8,  8,  7,  7,  7,  7,  7,  8,  8,  8,  0,  0,  0,  0,  0,  0,
			  0,  0,  8,  8,  7,  7,  7,  7,  7,  7,  7,  7,  8,  8,  0,  0,  0,  0,  0,  0,
			  0,  0,  8,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8,  8,  8,  0,  0,  0,  0,
			  0,  0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  0,  0,  0,  0,
			  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		}
};

Sun_s Sun =
{
  SUNW,
  SUNH,
  {
    255,255,255,255,255,255,255,177,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,177,255,255,255,177,255,255,255,177,255,255,255,
    255,255,255,255,177,255,255,255,255,255,177,255,255,255,255,
    255,255,255,255,255,255,177,177,177,255,255,255,255,255,255,
    255,255,255,255,255,177,178,219,178,177,255,255,255,255,255,
    255,255,255,255,177,178,219,219,219,178,177,255,255,255,255,
    177,255,177,255,177,219, 94,219, 94,219,177,255,177,255,177,
    255,255,255,255,177,178,219,126,219,178,177,255,255,255,255,
    255,255,255,255,255,177,178,219,178,177,255,255,255,255,255,
    255,255,255,255,255,255,177,177,177,255,255,255,255,255,255,
    255,255,255,255,177,255,255,255,255,255,177,255,255,255,255,
    255,255,255,177,255,255,255,177,255,255,255,177,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,177,255,255,255,255,255,255,255,
  },
  {
      0,  0,  0,  0,  0,  0,  0, 62,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0, 62,  0,  0,  0, 62,  0,  0,  0, 62,  0,  0,  0,
      0,  0,  0,  0, 62,  0,  0,  0,  0,  0, 62,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0, 62, 62, 62,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0, 62, 62, 14, 62, 62,  0,  0,  0,  0,  0,
      0,  0,  0,  0, 62, 62, 14, 14, 14, 62, 62,  0,  0,  0,  0,
     62,  0, 62,  0, 62, 14,224, 14,224, 14, 62,  0, 62,  0, 62,
      0,  0,  0,  0, 62, 62, 14,224, 14, 62, 62,  0,  0,  0,  0,
      0,  0,  0,  0,  0, 62, 62, 14, 62, 62,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0, 62, 62, 62,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0, 62,  0,  0,  0,  0,  0, 62,  0,  0,  0,  0,
      0,  0,  0, 62,  0,  0,  0, 62,  0,  0,  0, 62,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0, 62,  0,  0,  0,  0,  0,  0,  0,
  }
};

Rectangle_s WhtRectangle = {
		RECTW,
		RECTH,
		{
				254,254,254,
				254,254,254,
				254,254,254
		},
		{
				15,15,15,
				15,15,15,
				15,15,15
		}
};

Rectangle_s BluRectangle = {
		RECTW,
		RECTH,
		{
				219,219,219,
				219,219,219,
				219,219,219
		},
		{
				FOREGROUND_BLUE,FOREGROUND_BLUE,FOREGROUND_BLUE,
				FOREGROUND_BLUE,FOREGROUND_BLUE,FOREGROUND_BLUE,
				FOREGROUND_BLUE,FOREGROUND_BLUE,FOREGROUND_BLUE
		}
};


