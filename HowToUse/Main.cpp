//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл Main.cpp                                                              //
//                                                                            //
//                      *** ТОЧКА ВХОДА В ПРИЛОЖЕНИЕ ***                      //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include "MainWin.h"
#include <QApplication>


int main(int argc, char *argv[])
{
QApplication Application(argc, argv);
TMainWin* Coordination;  //Объект главного окна приложения
int res;

#ifndef __unix__
QStringList paths;
  paths = QCoreApplication::libraryPaths();
  paths.append(".");
  //paths.append("imageformats");
  paths.append("platforms");
  paths.append("sqldrivers");
  QCoreApplication::setLibraryPaths(paths);
#endif

  Coordination = new TMainWin();
  Coordination->show();
  res = Application.exec();
  delete Coordination;
  return res;
}

