//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл WinTuner.cpp                                                          //
//                                                                            //
//                       *** TWINTUNER ОКНО НАСТРОЕК ***                      //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QDesktopWidget>
#include <QFileDialog>
#include <QSqlRecord>
#include "WinTuner.h"
#include "Base.h"
#include "MainWin.h"


TWinTuner::TWinTuner(QWidget *parent) : QDialog(parent)
{
  setupUi(this);

  #ifndef __unix__
  //Устанавливаю значки заголовка окна: "закрытие"
  setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
  #endif

  //Запрет изменения размеров окна пользователем
  //setFixedSize(size());
  setFixedHeight(size().rheight());

  OWNER = NULL;
  FIniFileName = "";
  IsOK = false;
  IsChange = true;
  Placement = new TPlacement(this);

  TimerCloseWinTuner = new QBasicTimer();

  //До момента чтения положения окна из INI-файла окно размещается по центру экрана
  MoveToCenter();
}


TWinTuner::~TWinTuner(void)
{
  TimerCloseWinTuner->stop();
  Placement->Save();
  OWNER = NULL;
  IsOK = false;
  IsChange = false;
  delete TimerCloseWinTuner;
  delete Placement;
}


void TWinTuner::IniFileName(std::string Value)
{
  FIniFileName = Value;
  Placement->Restore(FIniFileName, "WIN_TUNER");
}


void TWinTuner::keyPressEvent(QKeyEvent *event)
{
  //Обработка нажатия на клавишу Esc
  if(event->key() == Qt::Key_Escape)
  {
    IsOK = false;
    close();
  }
  else
  {
    QWidget::keyPressEvent(event);
  }
}


void TWinTuner::showEvent(QShowEvent *event)
{
  if (event->type() == QEvent::Show)
  {
    if (IsChange == true)
    {
      CheckProto->setChecked(static_cast<TBase*>(OWNER)->CheckProto);
      CheckMap->setChecked(static_cast<TBase*>(OWNER)->CheckMap);
    }
    IsOK = false;
    CancelButton->setFocus();
  }
  else
  {
    QWidget::showEvent(event);
  }
}


void TWinTuner::hideEvent(QHideEvent *event)
{
QSettings *ConfigFile;  //INI-файл настроек приложения
QString str, name;

  if(event->type() == QEvent::Hide)
  {
    if (IsOK == true)
    {  //Сохранить изменения

    }
    else
    {  //Не сохранять изменения
      //Пользователь отменил всю свою работу по настройкам => надо все элементы управления вернуть в
      // первоначальное состояние
      CheckProto->setChecked(static_cast<TBase*>(OWNER)->CheckProto);

      CheckMap->setChecked(static_cast<TBase*>(OWNER)->CheckMap);

      IsChange = true;
    }

    //if ((pr1 == true) && (pr2 == true) && (pr3 == true) && (pr4 == true) && (pr5 == true) && (pr6 == true))
    //{
      static_cast<TBase*>(OWNER)->CheckProto = CheckProto->isChecked();

      static_cast<TBase*>(OWNER)->CheckMap = CheckMap->isChecked();

      //>>> Работа с INI-файлом >>>
      ConfigFile = new QSettings(QString::fromStdString(FIniFileName), QSettings::IniFormat);

      if (CheckProto->isChecked() == true)
        ConfigFile->setValue("USER/CheckProto", "1");
      else
        ConfigFile->setValue("USER/CheckProto", "0");

      if (CheckMap->isChecked() == true)
        ConfigFile->setValue("USER/CheckMap", "1");
      else
        ConfigFile->setValue("USER/CheckMap", "0");

      delete ConfigFile;
      //<<< Работа с INI-файлом <<<

      static_cast<TBase*>(OWNER)->AddToLogBook(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") +
                                               " Изменены параметры приложения");

      IsChange = true;

      if (CheckProto->isChecked() == true)
        static_cast<TBase*>(OWNER)->Log->show();

      if (CheckMap->isChecked() == true)
        static_cast<TBase*>(OWNER)->Map->show();
    //}
  }
  else
  {
    QWidget::hideEvent(event);
  }
}


void TWinTuner::timerEvent(QTimerEvent *event)
{
  if (event->timerId() == TimerCloseWinTuner->timerId())
  {
    TimerCloseWinTuner->stop();
    IsChange = false;
    this->exec();
  }
  else
  {
    QWidget::timerEvent(event);
  }
}


void TWinTuner::MoveToCenter()
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


void TWinTuner::on_OKButton_clicked()
{
  IsOK = true;
  close();
}


void TWinTuner::on_CancelButton_clicked()
{
  IsOK = false;
  close();
}
