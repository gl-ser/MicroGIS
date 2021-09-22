//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл MainWin.cpp                                                           //
//                                                                            //
//                        *** TMAINWIN ГЛАВНОЕ ОКНО ***                       //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QMessageBox>
#include <QLabel>
#include <QDateTime>
#include <QDesktopWidget>
#include <QStyleFactory>
#include "MainWin.h"


TMainWin::TMainWin(QWidget *parent) : QMainWindow(parent)
{
  setupUi(this);

  QApplication::setStyle(QStyleFactory::create("windows"));

  //Устанавливаю значки заголовка окна: "минимизация" и "закрытие"
  setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

  //Запрет изменения размеров окна пользователем
  //setFixedSize(size());

  CurTimeText = new QLabel(this);
  this->statusBarMain->addWidget(CurTimeText);

  CurTimeText->setText("XXXXXXXXXXXXXXXXXXXXXXXXXX");

  CurTimeTimer = new QBasicTimer();

  TimerQuit = new QBasicTimer();  //Таймер выхода из приложения (по умолчанию он остановлен)

  TimerFirstStart = new QBasicTimer();

  FIniFileName = "";
  Placement = new TPlacement(this);

  //До момента чтения положения окна из INI-файла окно размещается по центру экрана
  MoveToCenter();

  //Создание главного модуля данных приложения
  Base = new TBase(this);

  if (Base->Result == false)
  {
    Base->Error->MessageGreen("Корректная работа приложения невозможна");
    TimerQuit->start(300, this);
  }
  CurTimeTimer->start(1000, this);

  progressBar->setMinimum(0);
  progressBar->setMaximum(100);
  progressBar->setValue(0);

  first = true;
}


TMainWin::~TMainWin(void)
{
  Placement->Save();
  CurTimeTimer->stop();
  delete Base;
  delete CurTimeTimer;
  delete CurTimeText;
  delete TimerQuit;
  delete TimerFirstStart;
  delete Placement;

  first = false;
}


void TMainWin::IniFileName(std::string Value)
{
  FIniFileName = Value;
  Placement->Restore(FIniFileName, "WIN_MAIN");
}


void TMainWin::FirstStart()
{
  TimerFirstStart->start(2000, this);
}


void TMainWin::on_action_triggered()
{  //Параметры приложения
  Base->Tuner->show();
}


void TMainWin::on_action_4_triggered()
{  //Выход
  close();
}


void TMainWin::MoveToCenter()
{
QRect Rect;
QPoint Center;

  //Прямоугольник с размерами экрана
  Rect = qApp->desktop()->availableGeometry(qApp->desktop()->primaryScreen());

  //Координаты центра экрана
  Center = Rect.center();

  //Учитывается половина ширины окна
  Center.setX(Center.x() - (width()/2));

  //Учитывается половина высоты окна
  Center.setY(Center.y() - (height()/2));

  //Смещение окна по указанным координатам
  move(Center);
}


void TMainWin::timerEvent(QTimerEvent *event)
{
bool r1, r2, r3;
double t, H;
TMultitude::TOnePoint PointSun, PointMoon, Moscow;
TVector RSunAbs, RSunOtn, RMoonAbs, RMoonOtn, DummyAbs, DummyOtn, Point, Moon2, Sun2;
  if (event->timerId() == CurTimeTimer->timerId())
  {
    if (first == true)
    {
      r1 = Base->ShellGIS->AddLayerDynamicPoint();

      if (r1 == true)
      {
        r2 = Base->ShellGIS->AddInDynamicPoint(1, "Солнце", PointSun, 16744448);
        r3 = Base->ShellGIS->AddInDynamicPoint(2, "Луна", PointMoon, 0);
        if ((r2 == true) && (r3 == true))
        {
          first = false;
          Base->ShellGIS->RePaint();
        }
      }
    }

    CurTimeText->setText(" тек. время " + QDateTime::currentDateTime().toString(Qt::SystemLocaleLongDate)+" ");

    t = TCalendar::QDateTimeToTDateTime(QDateTime::currentDateTime());
    Base->SunCoordinates2000(t, &RSunAbs);
    Base->MoonCoordinates2000(t, &RMoonAbs);

    Base->AbsToOtnPrecision(RSunAbs, DummyAbs, t, &RSunOtn, &DummyOtn);
    Base->AbsToOtnPrecision(RMoonAbs, DummyAbs, t, &RMoonOtn, &DummyOtn);

    TCartography::OtnToBLH(RSunOtn, &PointSun.B, &PointSun.L, &H);
    TCartography::OtnToBLH(RMoonOtn, &PointMoon.B, &PointMoon.L, &H);

    Base->ShellGIS->MoveInDynamicPoint(1, "Солнце", PointSun);
    Base->ShellGIS->MoveInDynamicPoint(2, "Луна", PointMoon);

    Moscow.B = 55.60989*M_PI/180.0;
    Moscow.L = 37.75286*M_PI/180.0;

    //Вычисление Гринвичских координат нашего района
    TCartography::BLHToOtn(Moscow.B, Moscow.L, 0.0, &Point);

    Base->Log->TextProtocol->clear();
    Base->AddToLogBook("МОСКВА:");

    Base->AddToLogBook("Склонение Луны: " + QString::fromStdString(TNumerical::GradToString(
                       Base->LunarHeight(t, Point)*180.0/M_PI)));

    Base->AddToLogBook("Азимут Луны: " + QString::fromStdString(TNumerical::GradToString(
                       TCartography::AzimuthOfEnd(Moscow.B, Moscow.L, 0.0, PointMoon.B, PointMoon.L, 0.0)*180.0/M_PI)));

    Base->AddToLogBook("Склонение Солнца: " + QString::fromStdString(TNumerical::GradToString(
                       Base->SolarHeight(t, Point)*180.0/M_PI)));

    Base->AddToLogBook("Азимут Солнца: " + QString::fromStdString(TNumerical::GradToString(
                       TCartography::AzimuthOfEnd(Moscow.B, Moscow.L, 0.0, PointSun.B, PointSun.L, 0.0)*180.0/M_PI)));

    //Вектор, направленный из нашего района на Луну
    Moon2 = RMoonOtn - Point;

    //Вектор, направленный из нашего района на Солнце
    Sun2 = RSunOtn - Point;

    //Угол между Луной и Солнцем над нашим районом
    Base->AddToLogBook("Видимый угол между Луной и Солнцем: " + QString::fromStdString(TNumerical::GradToString(
                       TMultitude::ArcCos((Moon2*Sun2)/(Moon2.getModul()*Sun2.getModul()))*180.0/M_PI)));
  }
  else
  {
    if (event->timerId() == TimerQuit->timerId())
    {
      TimerQuit->stop();
      close();
    }
    else
    {
      if (event->timerId() == TimerFirstStart->timerId())
      {
        TimerFirstStart->stop();
        Base->Tuner->exec();
      }
      else
      {
        QWidget::timerEvent(event);
      }
    }
  }
}


void TMainWin::on_action_2_triggered()
{  //Открыть журнал
  Base->Log->show();
}


void TMainWin::on_action_5_triggered()
{  //Открыть карту
  Base->Map->show();
}
