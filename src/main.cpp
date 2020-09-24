// -*- mode: c++; coding: utf-8-unix -*-
// Copyright (c) 2020 FunFun <fu.aba.dc5@gmail.com>

// Common Header

// System Header

// Qt Header
#include <QApplication>
#if !defined(QT_NO_SYSTEMTRAYICON)
#include <QSystemTrayIcon>
#include <QMessageBox>
#else // !defined(QT_NO_SYSTEMTRAYICON)
#error "QT_NO_SYSTEMTRAYICON"
#endif // !defined(QT_NO_SYSTEMTRAYICON)
#include <QLocale>
#include <QMainWindow>
#include <QTranslator>
#include <QWidget>

// Local Header
#include "server.h"

using namespace qtbrynhildr;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  // for Translation
  QTranslator appTranslator;
  appTranslator.load(":/translations/S0_"
					 + QLocale::system().name(),
					 //					 + "ja_JP",
					 qApp->applicationDirPath());
  app.installTranslator(&appTranslator);

#ifndef QT_NO_SYSTEMTRAYICON
  if (!QSystemTrayIcon::isSystemTrayAvailable()) {
	QMessageBox::critical(0, QObject::tr("Systray"),
						  QObject::tr("I couldn't detect any system tray "
									  "on this system."));
	return 1;
  }
  else {
	//
	QApplication::setQuitOnLastWindowClosed(false);
  }
#endif

  Server *mainWindow = new Server();

  mainWindow->setFocus(Qt::ActiveWindowFocusReason);
  mainWindow->show();

  mainWindow->testForCapture(); // for capture

  mainWindow->testForMouse(); // for mouse

  bool result = app.exec();

  delete mainWindow;

  return result;
}
