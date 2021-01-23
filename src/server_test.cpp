// -*- mode: c++; coding: utf-8-unix -*-
// Copyright (c) 2020 FunFun <fu.aba.dc5@gmail.com>

// Common Header
//#include "common/common.h"

// System Header
#include <fstream> // for TEST
#include <iostream> // for TEST
using namespace std; // for TEST

// Qt Header
#include <QApplication>

#include <QDateTime>

#include <QByteArray>
#include <QBuffer>
#include <QIODevice>

// Local Header
#include "server.h"

#include "rgb2yuv/rgb2yuv.h"

namespace qtbrynhildr {

void Server::testForMouse()
{
  QCursor::setPos(960, 540);
}

void Server::testForCapture()
{
#if QTB_TEST_DESKTOP_IMAGE_CAPTURE1 // for TEST Desktop Image Capture
  QScreen *screen = QGuiApplication::primaryScreen();
  if (screen != 0){
	cout << "primaryScreen(): OK" << endl << flush;
  }
  else {
	cout << "primaryScreen(): NG" << endl << flush;
  }
  const QWindow *window = windowHandle();
  if (window != 0){
	cout << "windowHandle(): OK" << endl << flush;
	screen = window->screen();
  }
  else {
	cout << "windowHandle(): NG" << endl << flush;
  }
  if (screen == 0){
	cout << "capture: NG" << endl << flush;
  }
  else {
	cout << "capture: OK" << endl << flush;
	QDateTime beginTime = QDateTime::currentDateTime();
	QPixmap pixmap;
	QImage image;
	for (int i = 0 ; i < 1; i++){
	  //                         windowID, x, y, width, height
	  pixmap = screen->grabWindow(0, 0, 0, -1, -1);	// 33 (ms)
	  //	  image = pixmap.toImage();
	  //	  image.convertToFormat(QImage::Format_RGB888); // 17 (ms)
	  // to JPEG file image
	  image = pixmap.toImage();

#if 0 // for TEST
	  {
		fstream file;

		file.open("result/image.dat", ios::out | ios::binary);
		if (file.is_open()){
		  file.write((const char*)image.bits(), image.width() * image.height() * 4);
		  file.close();
		}
	  }
#endif // 1 // for TEST

	  // image -> jpeg file image
	  //testForMJPG(image);

	  // image -> vp8
	  testForVP8(image);
	}
	QDateTime endTime = QDateTime::currentDateTime();
	qint64 diffSeconds = endTime.toMSecsSinceEpoch() - beginTime.toMSecsSinceEpoch();
	cout << "diff time = " << diffSeconds << " msecs." << endl << flush;
	pixmap.save("result/desktop.jpg", "jpg", 75);
  }
#endif // for TEST

  // image -> vp8
  //testForVP8FromFile();
}

// test for MJPG
void Server::testForMJPG(QImage &image)
{
  QByteArray ba;
  QBuffer buffer(&ba);

  // write jpeg file image
  buffer.open(QIODevice::WriteOnly);
  //         QIODevice*, format, quality
  image.save(&buffer,    "JPG",  50); // writes image into ba in JPG format
  buffer.close();

#if 1 // for TEST
  { // save jpeg file image binary to file
	fstream file;

	file.open("result/desktop_image.jpg", ios::out | ios::binary);
	if (file.is_open()){
	  file.write(ba.data(), ba.length());
	  file.close();
	}
  }
#endif // 1 // for TEST
}

// test for VP8 (MODE7)
void Server::testForVP8FromFile()
{
  // setup for rgb2yuv
  qtbrynhildr::width = 1280;
  qtbrynhildr::height = 800;

  setup();

  { // load rgb image for TEST
	fstream file;

	file.open("jpg/rgb.dat", ios::in | ios::binary);
	if (file.is_open()){
	  file.read((char*)rgb, qtbrynhildr::rgbImageSize);
	  file.close();
	  cout << "Read : jpg/rgb.dat to rgb : done. size = " << qtbrynhildr::rgbImageSize << " bytes " << endl << flush;
	}

	{
	  QImage *image = new QImage(rgb, qtbrynhildr::width, qtbrynhildr::height, IMAGE_FORMAT);
	  image->save("result/desktop_original.jpg", "jpg", 75);
	}

	// RGB convert to YUV
	qtbrynhildr::convertRGBtoYUV(rgb, ytop, utop, vtop, qtbrynhildr::height);

#if 1 // for TEST
	{
	  fstream file;

	  file.open("result/yuv_result.dat", ios::out | ios::binary);
	  if (file.is_open()){
		file.write((const char*)yuv, qtbrynhildr::yuvImageSize);
		file.close();
	  }
	}
#endif // 1 // for TEST

	// YUV convert to RGB (for TEST)
	qtbrynhildr::convertYUVtoRGB(ytop, utop, vtop, rgb, qtbrynhildr::height);

#if 1 // for TEST
	{
	  fstream file;

	  file.open("result/rgb_result.dat", ios::out | ios::binary);
	  if (file.is_open()){
		file.write((const char*)rgb, qtbrynhildr::rgbImageSize);
		file.close();
	  }
	}
#endif // 1 // for TEST

	{
	  QImage *image = new QImage(rgb, qtbrynhildr::width, qtbrynhildr::height, IMAGE_FORMAT);
	  image->save("result/desktop_final.jpg", "jpg", 75);

	  *image = image->convertToFormat(QImage::Format_RGB888);
	  {
		fstream file;

		file.open("result/rgb_888.dat", ios::out | ios::binary);
		if (file.is_open()){
		  file.write((const char*)image->bits(), image->width() * image->height() * 3);
		  file.close();
		}
	  }
	}
  }
}

// test for VP8
void Server::testForVP8(QImage &image)
{
  // setup for rgb2yuv
  qtbrynhildr::width = image.width();
  qtbrynhildr::height =image.height();

  setup();

  // RGB convert to YUV
  qtbrynhildr::convertRGBtoYUV(image.bits(), ytop, utop, vtop, qtbrynhildr::height);

  // YUV convert to RGB (for TEST)
  qtbrynhildr::convertYUVtoRGB(ytop, utop, vtop, rgb, qtbrynhildr::height);

  {
	QImage *image = new QImage(rgb, qtbrynhildr::width, qtbrynhildr::height, IMAGE_FORMAT);
	image->save("result/desktop_test.jpg", "jpg", 75);
  }
}

} // end of namespace qtbrynhildr
