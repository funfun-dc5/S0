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
#include <QIcon>
#include <QMessageBox>

// Local Header
#include "server.h"


namespace qtbrynhildr {

// constructor
Server::Server()
  :QMainWindow()
  ,settings(0)
  ,trayIcon(0)
  ,trayIconMenu(0)
  ,reset_Action(0)
  ,about_Action(0)
  ,exit_Action(0)
  // for DEBUG
  ,outputLog(true)
{
  // settings
  settings =
	new QSettings(QSettings::IniFormat, QSettings::UserScope, "mcz-xoxo", "Server");

  // restore geometry
  bool result = restoreGeometry(settings->value("geometry").toByteArray());
  if (!result){
	QPoint topLeft = QPoint(100,100);
	move(topLeft);
  }
  else {
	// restore window state
	restoreState(settings->value("windowState").toByteArray());
  }

  // create GUI
  createActions();
  createTrayIcon();

  if (QSystemTrayIcon::isSystemTrayAvailable()) {
	connect(trayIcon, &QSystemTrayIcon::activated, this, &Server::iconActivated);
  }
  else {
	cout << "QSystemTrayIcon::isSystemTrayAvailable() is false" << endl << flush;
  }

  QIcon icon = QIcon(":/images/S0.ico");
  trayIcon->setIcon(icon);
  trayIcon->show();
  // set window flags
  Qt::WindowFlags flags = windowFlags();
  //flags |= Qt::WindowStaysOnTopHint; // stay on top
  flags &= ~Qt::WindowMinimizeButtonHint; // disable Minimize Button
  flags &= ~Qt::WindowMaximizeButtonHint; // disable Maximize Button
  setWindowFlags(flags);

  setWindowTitle("S0 by Qt");
  setWindowIcon(icon);

  setWindowOpacity(0.98);
}

// destructor
Server::~Server()
{
}

// set visible
void Server::setVisible(bool visible)
{
  QMainWindow::setVisible(visible);
  minimize_Action->setEnabled(visible);
  restore_Action->setEnabled(!visible);
}

void Server::createActions()
{
  // minimize window
  minimize_Action = new QAction(tr("Minimize"), this);
  connect(minimize_Action, SIGNAL(triggered()), this, SLOT(minimize()));

  // restore window
  restore_Action = new QAction(tr("Restore"), this);
  connect(restore_Action, SIGNAL(triggered()), this, SLOT(restore()));

  // reset
  reset_Action = new QAction(tr("Reset"), this);
  connect(reset_Action, SIGNAL(triggered()), this, SLOT(reset()));

  // about
  about_Action = new QAction(tr("About"), this);
  connect(about_Action, SIGNAL(triggered()), this, SLOT(about()));

  // exit
  exit_Action = new QAction(tr("Exit"), this);
  connect(exit_Action, SIGNAL(triggered()), this, SLOT(exit()));
}

void Server::createTrayIcon()
{
  trayIconMenu = new QMenu(this);

  //  trayIconMenu->addSeparator();

  trayIconMenu->addAction(minimize_Action);
  minimize_Action->setEnabled(!isMinimized());

  trayIconMenu->addAction(restore_Action);
  restore_Action->setEnabled(isVisible());

  trayIconMenu->addAction(reset_Action);

  trayIconMenu->addSeparator();

  trayIconMenu->addAction(about_Action);

  trayIconMenu->addSeparator();

  trayIconMenu->addAction(exit_Action);

  trayIcon = new QSystemTrayIcon(this);
  trayIcon->setContextMenu(trayIconMenu);
}

//---------------------------------------------------------------------------
// private slots
//---------------------------------------------------------------------------
// minimize window
void Server::minimize()
{
  cout << "minimize()" << endl << flush;
  hide();
}

// restore window
void Server::restore()
{
  cout << "restore()" << endl << flush;
  showNormal();
}

// reset application
void Server::reset()
{
  cout << "reset()" << endl << flush;
}

// about this appication
void Server::about()
{
  cout << "about()" << endl << flush;

  // display About Message Box
  QMessageBox::about(this,
					 "About " "S0 by Qt",
					 "<h2>"
					 "S0 by Qt"
					 " Ver. "
					 "0.0.1"
					 "</h2>"
					 "<p>Copyright &copy;"
					 " "
					 "2020"
					 " "
					 "FunFun"
					 " @ "
					 "mcz-xoxo"
					 " powered by MCZ."
					 "<br><br>"
					 "<a href=\"http://mcz-xoxo.cocolog-nifty.com/blog/\">http://mcz-xoxo.cocolog-nifty.com/blog/</a>"
					 );
}

// exit appication
void Server::exit()
{
  cout << "exit()" << endl << flush;

  qApp->quit();
}

//
void Server::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  switch(reason){
  case QSystemTrayIcon::Trigger:
  case QSystemTrayIcon::DoubleClick:
	if (!isVisible()){
	  showNormal();
	}
	break;
  case QSystemTrayIcon::MiddleClick:
	//cout << "iconActivated(): MiddleClick" << endl << flush;
	break;
  default:
	//cout << "iconActivated(): Others" << endl << flush;
	break;
  }
}

} // end of namespace qtbrynhildr
