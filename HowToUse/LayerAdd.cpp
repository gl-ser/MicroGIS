//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл LayerAdd.cpp                                                          //
//                                                                            //
//                *** TLAYERADD ОКНО ДОБАВЛЕНИЯ НОВОГО СЛОЯ ***               //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include "LayerAdd.h"
#include <QShowEvent>
#include <QDesktopWidget>


TLayerAdd::TLayerAdd(QWidget *parent) : QDialog(parent)
{
  setupUi(this);

  #ifndef __unix__
  //Устанавливаю значки заголовка окна: "закрытие"
  setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
  #endif

  //Запрет изменения размеров окна пользователем
  setFixedSize(size());

  FIniFileName = "";
  FName = "";
  Placement = new TPlacement(this);

  //До момента чтения положения окна из INI-файла окно размещается по центру экрана
  MoveToCenter();
}


TLayerAdd::~TLayerAdd()
{
  Placement->Save();
  delete Placement;
  FIniFileName = "";
  FName = "";
}


void TLayerAdd::IniFileName(std::string Value)
{
  FIniFileName = Value;
  Placement->Restore(FIniFileName, "WIN_LAYER_ADD");
}


std::string TLayerAdd::GetLayerName()
{
  return FName;
}


void TLayerAdd::on_pushButton_clicked()
{  //OK
  FName = EditName->text().toStdString();

  if (FName != "")
    close();
}


void TLayerAdd::on_pushButton_2_clicked()
{  //Отмена
  FName = "";
  close();
}


void TLayerAdd::MoveToCenter()
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


void TLayerAdd::showEvent(QShowEvent *event)
{
  if( event->type() == QEvent::Show)
  {
    FName = "";
    EditName->setText("");
    EditName->setFocus();
  }
  else
  {
    QWidget::showEvent(event);
  }
}


void TLayerAdd::hideEvent(QHideEvent *event)
{
  if( event->type() == QEvent::Hide)
  {

  }
  else
  {
    QWidget::hideEvent(event);
  }
}
