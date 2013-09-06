#ifndef SHAPES_H_
#define SHAPES_H_

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#define CHAR unsigned char
#define COL unsigned char

//#define PtrAdd( ptr, offset ) \
//  (((char *)ptr) + offset)
//
//#define CharAt( image, x, y ) \
//  (CHAR *)(PtrAdd( image->chars, ((y) * image->width + (x)) * sizeof( CHAR ) ))
//
//#define ColourAt( image, x, y ) \
//  (COL *)(PtrAdd( image->colours, ((y) * image->width + (x)) * sizeof( COL ) ))

typedef class Image {
public:
	Image();
	Image(const int w, const int h, const CHAR *chrs, const COL *cols);
	Image(const Image &src);
	Image(const char *filename);
	~Image();
	Image &operator=(const Image &src);
	bool operator==(const Image &src);

	void setWidth(int w);
	void setHeight(int h);
	int getWidth();
	int getHeight();
	void setChars(CHAR *chrs);
	void setColours(COL *cols);
	CHAR *getChars();
	CHAR *getColours();
private:
	int width;
	int height;
	unsigned char *chars;
	unsigned char *colours;
} _Image;

#define CLOUDW 20
#define CLOUDH 10

typedef struct _CLOUD {
	int width;
	int height;
	unsigned char chars[CLOUDW * CLOUDH];
	unsigned char colours[CLOUDW * CLOUDH];
} Cloud_s;

#define RECTW 3
#define RECTH 3

typedef struct _RECTANGLE {
	int width;
	int height;
	unsigned char chars[RECTW * RECTH];
	unsigned char colours[RECTW * RECTH];
} Rectangle_s;

#define SUNW 15
#define SUNH 15

typedef struct _SUN
{
  int width;
  int height;
  unsigned char chars[SUNW * SUNH];
  unsigned char colours[SUNW * SUNH];
} Sun_s;

Image *allocateImage(int width, int height);
void setImage(Image *image, CHAR *chars, CHAR *colours);
void deallocateImage(Image *image);

extern Cloud_s Cloud;
extern Rectangle_s WhtRectangle;
extern Rectangle_s BluRectangle;
extern Sun_s Sun;


#endif /* SHAPES_H_ */
