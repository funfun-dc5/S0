// -*- mode: c++; coding: utf-8-unix -*-
// Copyright (c) 2020 FunFun <fu.aba.dc5@gmail.com>

#ifndef SERVER_H
#define SERVER_H
// Common Header
//#include "common/common.h"

// System Header

// Qt Header
#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QSettings>
#include <QSystemTrayIcon>

// for TEST
#define QTB_TEST_DESKTOP_IMAGE_CAPTURE1	1

#if QTB_TEST_DESKTOP_IMAGE_CAPTURE1 // for TEST Desktop Image Capture
#include <QPixmap>
#include <QScreen>
#include <QWindow>
#include <QWidget>
#endif // for TEST

// mouse cursor
#include <QCursor>

// Local Header


namespace qtbrynhildr {

  class Server : public QMainWindow
{
  Q_OBJECT

  //-------------------------------------------------------------------------------
  // Variable
  //-------------------------------------------------------------------------------
private:
  // settings
  QSettings *settings;

  // tray icon
  QSystemTrayIcon *trayIcon;

  // menu for system tray
  QMenu *trayIconMenu;

  // ------------------------------------------------------------
  // QAction
  // ------------------------------------------------------------
  // minimize window
  QAction *minimize_Action;

  // restore window
  QAction *restore_Action;

  // reset
  QAction *reset_Action;

  // about
  QAction *about_Action;

  // exit
  QAction *exit_Action;

  // output log flag
  bool outputLog;

  //-------------------------------------------------------------------------------
  // Function
  //-------------------------------------------------------------------------------
public:
  // constructor
  Server();
  // destructor
  virtual ~Server();

  // test for Mouse
  void testForMouse();

  // test for Capture
  void testForCapture();

  // test for MJPG (MODE5,6)
  void testForMJPG(QImage &image);

  // test for VP8 (MODE7)
  void testForVP8FromFile();

  // test for VP8 (MODE7)
  void testForVP8(QImage &image);

protected:
  // set visible
  void setVisible(bool visible) override;

private:
  // build GUI
  void createActions();
  void createTrayIcon();

private slots:
  // minimize window
  void minimize();

  // restore window
  void restore();

  // reset application
  void reset();

  // about this appication
  void about();

  // exit appication
  void exit();

  //
  void iconActivated(QSystemTrayIcon::ActivationReason reason);
};

} // end of namespace qtbrynhildr

#endif // SERVER_H
