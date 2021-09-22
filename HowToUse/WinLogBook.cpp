//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл WinLogBook.cpp                                                        //
//                                                                            //
//                      *** TWINLOGBOOK ОКНО ЖУРНАЛА ***                      //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QShowEvent>
#include <QDesktopWidget>
#include <QDateTime>
#include <QFileDialog>
#include <QTextStream>
#include "WinLogBook.h"


TWinLogBook::TWinLogBook(QWidget *parent) : QMainWindow(parent)
{
  setupUi(this);

  OWNER = NULL;

  FIniFileName = "";
  Placement = new TPlacement(this);

  //До момента чтения положения окна из INI-файла окно размещается по центру экрана
  MoveToCenter();

  TextProtocol->append(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") + " Протокол создан");

QFile F;
QString FN;
  FN = qApp->applicationDirPath() + "/" + "Astronomer.txt";
  F.setFileName(FN);
  QFileInfo FileInfo(F);

  if (FileInfo.size() > 1000000)
  {
    if (F.open(QIODevice::WriteOnly | QIODevice::Text) == true)
      F.close();

    TextProtocol->append(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") + " Очищен главный LOG-файл приложения");
  }
}


TWinLogBook::~TWinLogBook()
{
  Placement->Save();
  delete Placement;
  FIniFileName = "";

  OWNER = NULL;
}


void TWinLogBook::IniFileName(std::string Value)
{
  FIniFileName = Value;
  Placement->Restore(FIniFileName, "WIN_LOG_BOOK");
}


void TWinLogBook::SaveToFile(QString FilePathName, bool ReWrite)
{
bool IsOpen;
QFile File;            //Файл журнала
QTextStream Data;      //Содержимое файла журнала
QString Codec;         //Кодировка текстового файла

  if (FilePathName != "")
  {
    Codec = "utf-8";
    Data.setDevice(&File);  //Связать содержимое файла с самим файлом
    Data.setCodec(Codec.toStdString().c_str());  //Кодировка текстового файла

    //Задать имя файла
    File.setFileName(FilePathName);

    if (ReWrite == true)
    {
      //Создать в файловой системе новый (или очистить существующий) текстовый файл и открыть его за запись
      IsOpen = File.open(QIODevice::WriteOnly | QIODevice::Text);
    }
    else
    {
      //Дописать в конец файла
      IsOpen = File.open(QIODevice::Append | QIODevice::Text);
    }

    if (IsOpen == true)
    {
      if (ReWrite == true)
        TextProtocol->append(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") + " Протокол сохранен в файле пользователем");

      Data << TextProtocol->toPlainText() << endl << endl;  //Передача содержимого QTextEdit в QTextStream (в содержимое файла)

      File.close();  //Завершить запись в файл
    }

    #ifdef __unix__
    QFile f;
    f.setFileName(FilePathName);
    f.setPermissions(QFileDevice::ReadOwner | QFileDevice::ReadGroup | QFileDevice::ReadOther |
                     QFileDevice::WriteOwner | QFileDevice::WriteGroup | QFileDevice::WriteOther |
                     QFileDevice::ExeOwner | QFileDevice::ExeGroup | QFileDevice::ExeOther);
    #endif
  }
}


void TWinLogBook::MoveToCenter()
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


void TWinLogBook::showEvent(QShowEvent *event)
{
  if(event->type() == QEvent::Show)
  {

  }
  else
  {
    QWidget::showEvent(event);
  }
}


void TWinLogBook::hideEvent(QHideEvent *event)
{
  if( event->type() == QEvent::Hide)
  {

  }
  else
  {
    QWidget::hideEvent(event);
  }
}


void TWinLogBook::on_action_4_triggered()
{
QString FilePathName;  //Путь и имя к текстовому файлу

  FilePathName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить протокол в файле"),
                                              qApp->applicationDirPath(), QString::fromUtf8("*.txt"));
  if (FilePathName != "")
  {
    #ifdef __unix__
    FilePathName = FilePathName + ".txt";
    #endif

    SaveToFile(FilePathName, true);
  }
}


void TWinLogBook::on_action_5_triggered()
{
  TextProtocol->clear();
  TextProtocol->append(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") + " Протокол очищен пользователем");
}
