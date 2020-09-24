// -*- mode: c++; coding: utf-8-unix -*-
// Copyright (c) 2017 FunFun <fu.aba.dc5@gmail.com>

// Common Header
#include "common/common.h"

// System Header

// Qt Header

// Local Header
#include "rgb2yuv.h"

namespace qtbrynhildr {

// RGB convert to YUV macro
#define GET_Y(R, G, B)	((( 76*R + 150*G +  29*B) >> 8))
#define GET_U(R, G, B)	(((-43*R -  84*G + 128*B) >> 8) + 128)
#define GET_V(R, G, B)	(((128*R - 107*G -  20*B) >> 8) + 128)

// RGB convert to YUV (qtbrynhildr::convertRGBtoYUV())
void convertRGBtoYUV(uchar *rgbtop, uchar *ytop, uchar* utop, uchar *vtop, int height)
{
  int rgbNext = width * 4;
  uchar *rgbtop2 = rgbtop + rgbNext; // for yPos+1
  uchar *ytop2 = ytop + width; // for yPos+1

  for(int yPos = 0; yPos < height; yPos += 2){
	for(int xPos = 0; xPos < width; xPos += 2){
	  int r, g, b;
	  int y, u, v;

	  // calc y,u,v (xPos, yPos)
	  // set RGBA
	  b = *rgbtop++;
	  g = *rgbtop++;
	  r = *rgbtop++;
	  rgbtop++; // a

	  // calc y, u, v
	  y = GET_Y(r, g, b);
	  u = GET_U(r, g, b);
	  v = GET_V(r, g, b);

	  // store Y,U,V
	  *ytop++ = (uchar)y;
	  *utop++ = (uchar)u;
	  *vtop++ = (uchar)v;

	  // calc y (xPos+1, yPos)
	  // set RGBA
	  b = *rgbtop++;
	  g = *rgbtop++;
	  r = *rgbtop++;
	  rgbtop++; // a

	  // calc y
	  y = GET_Y(r, g, b);
	  // store Y
	  *ytop++ = (uchar)y;

	  // calc y (xPos, yPos+1)
	  // set RGBA
	  b = *rgbtop2++;
	  g = *rgbtop2++;
	  r = *rgbtop2++;
	  rgbtop2++; // a

	  // calc y
	  y = GET_Y(r, g, b);
	  // store Y
	  *ytop2++ = (uchar)y;

	  // calc y (xPos+1, yPos+1)
	  // set RGBA
	  b = *rgbtop2++;
	  g = *rgbtop2++;
	  r = *rgbtop2++;
	  rgbtop2++; // a

	  // calc y
	  y = GET_Y(r, g, b);
	  // store Y
	  *ytop2++ = (uchar)y;
	}
	rgbtop += rgbNext;
	rgbtop2 += rgbNext;
	ytop += width;
	ytop2 += width;
  }
  cout << "Done : convertRGBtoYUV()" << endl << flush;
}

} // end of namespace qtbrynhildr
