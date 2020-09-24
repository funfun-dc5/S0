// -*- mode: c++; coding: utf-8-unix -*-
// Copyright (c) 2020 FunFun <fu.aba.dc5@gmail.com>

// Common Header
//#include "common/common.h"

// System Header
#include <cstring>

// Qt Header

// Local Header
#include "rgb2yuv.h"

namespace qtbrynhildr {

// parameters
int width = 0;
int height = 0;
int rgbImageSize = 0;
int yuvImageSize = 0;

uchar *rgb = 0;
uchar *yuv = 0;
uchar *ytop = 0;
uchar *utop = 0;
uchar *vtop = 0;

// initialize for yuv
void initVPX()
{
  // initialize libvpx
}

// setup for yuv, rgb
bool setup()
{
  // calc YUV/RGB image size
  int size = width * height;
  yuvImageSize = size + size / 2;
  rgbImageSize = size * IMAGE_FORMAT_SIZE;

  // allocate yuv/rgb buffer
  if (yuv != 0){
	delete [] yuv;
  }
  yuv = new uchar[yuvImageSize];
  memset(yuv, 0, yuvImageSize);
  if (rgb != 0){
	delete [] rgb;
  }
  rgb = new uchar[rgbImageSize];
  memset(rgb, 0, rgbImageSize);

  // set parameters
  ytop = yuv;
  utop = ytop + size;
  vtop = utop + size / 4;

  return true;
}

// clip
inline int clip(int val)
{
  if (val < 0) return 0;
  if (val > 255) return 255;
  return val;
}

// YUV convert to RGB (for TEST)
#define GET_R(Y, V)           (Y                 + 1.402*(V-128))
#define GET_G(Y, U, V)        (Y - 0.344*(U-128) - 0.714*(V-128))
#define GET_B(Y, U)           (Y + 1.772*(U-128))
void convertYUVtoRGB(uchar *ytop, uchar* utop, uchar *vtop, uchar *rgbtop, int height)
{
  int uvNext = width / 2;

  for (int yPos = 0; yPos < height; yPos++) {
	for (int xPos = 0, uvOffset = 0; xPos < width; xPos += 2, uvOffset++) {
	  uchar u = *(utop + uvOffset);
	  uchar v = *(vtop + uvOffset);
	  for (int i = 0; i < 2; i++) {
		int r, g, b;
		uchar y = *ytop++;
		// R
		r = clip(GET_R(y, v));
		// G
		g = clip(GET_G(y, u, v));
		// B
		b = clip(GET_B(y, u));

		// B
		*rgbtop++ = (uchar)b;
		// G
		*rgbtop++ = (uchar)g;
		// R
		*rgbtop++ = (uchar)r;
		// A
		*rgbtop++ = 0xFF;
	  }
	}
	if (yPos % 2 == 1) {
	  utop += uvNext;
	  vtop += uvNext;
	}
  }
  cout << "Done : convertYUVtoRGB()" << endl << flush;
}

} // end of namespace qtbrynhildr
