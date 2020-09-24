// -*- mode: c++; coding: utf-8-unix -*-
// Copyright (c) 2020 FunFun <fu.aba.dc5@gmail.com>

#ifndef RGB2YUV_H
#define RGB2YUV_H
// Common Header
#include "common/common.h"

// System Header

// Qt Header

// Local Header


// desktop image format
#define FORMAT_RGB32 1
//#define FORMAT_RGB888 1

#if FORMAT_RGB32
// RGB32 (4bytes) format info.
#define IMAGE_FORMAT QImage::Format_RGB32
#define IMAGE_FORMAT_SIZE 4
#elif FORMAT_RGB888
// RGB888 (3bytes) format info.
#define IMAGE_FORMAT QImage::Format_RGB888
#define IMAGE_FORMAT_SIZE 3
#else  // FORMAT_RGB888
#error "unknown image format!"
#endif

namespace qtbrynhildr {

  // parameters
  extern int width;
  extern int height;
  extern int rgbImageSize;
  extern int yuvImageSize;

  extern uchar *rgb;
  extern uchar *yuv;
  extern uchar *ytop;
  extern uchar *utop;
  extern uchar *vtop;

  // initialize for yuv
  extern void initVPX();

  // setup for yuv, rgb
  extern bool setup();

  // RGB convert to YUV (qtbrynhildr::convertRGBtoYUV())
  extern void convertRGBtoYUV(uchar *rgbtop, uchar *ytop, uchar* utop, uchar *vtop, int height);

  // YUV convert to RGB (for TEST)
  extern void convertYUVtoRGB(uchar *ytop, uchar* utop, uchar *vtop, uchar *rgbtop, int height);

} // end of namespace qtbrynhildr

#endif // RGB2YUV_H
