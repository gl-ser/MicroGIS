//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл ObjCtrl.cpp                                                           //
//                                                                            //
//              *** TOBJCTRL ОКНО УПРАВЛЕНИЯ ОБЪЕКТАМИ СЛОЯ ***               //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QDesktopWidget>
#include "ObjCtrl.h"
#include "Base.h"


TObjCtrl::TObjCtrl(QWidget *parent) : QDialog(parent)
{
  setupUi(this);

  #ifndef __unix__
  //Устанавливаю значки заголовка окна: "закрытие"
  setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
  #endif

  //Запрет изменения размеров окна пользователем
  setFixedSize(size());

  FIniFileName = "";
  Placement = new TPlacement(this);

  //До момента чтения положения окна из INI-файла окно размещается по центру экрана
  MoveToCenter();

  ObjGrid->setColumnWidth(1, 550);  //Поле для названия объекта должно быть такой ширины
  Name = "";
}


TObjCtrl::~TObjCtrl()
{
  Placement->Save();
  delete Placement;
  FIniFileName = "";
}


void TObjCtrl::IniFileName(std::string Value)
{
  FIniFileName = Value;
  Placement->Restore(FIniFileName, "WIN_OBJ_CTRL");
}


void TObjCtrl::MoveToCenter()
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


void TObjCtrl::showEvent(QShowEvent *event)
{
int q, i;
TLayer::THeadersObjects list;
  if(event->type() == QEvent::Show)
  {
    //Очистка "грида" от старых данных
    q = ObjGrid->rowCount();
    for(i=0; i<q; i++)
      ObjGrid->removeRow(0);

    list = (static_cast<TBase*>(OWNER))->ShellGIS->GetObjList(Name);

    for(i=0;i<static_cast<int>(list.size());i++)
    {
      ObjGrid->insertRow(0);

      ObjGrid->setItem(0, 0, new QTableWidgetItem(QString::number(list[static_cast<unsigned int>(i)].ID)));
      ObjGrid->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(list[static_cast<unsigned int>(i)].Name)));
    }
    ObjGrid->setCurrentCell(0, 0);

    list.clear();
  }
  else
  {
    QWidget::showEvent(event);
  }
}


void TObjCtrl::hideEvent(QHideEvent *event)
{
int q, i;
  if(event->type() == QEvent::Hide)
  {
    //Очистка "грида" от старых данных
    q = ObjGrid->rowCount();
    for(i=0; i<q; i++)
      ObjGrid->removeRow(0);
  }
  else
  {
    QWidget::hideEvent(event);
  }
}


void TObjCtrl::on_pushButton_clicked()
{
int Index, q, i;
unsigned int ID;
TLayer::THeadersObjects list;
  Index = ObjGrid->currentRow();
  if (Index >= 0)
  {
    //if ((static_cast<TBase*>(OWNER))->CancelOK->WhatCanIDo() == true)
    //{
      ID = static_cast<unsigned int>(std::stoi(ObjGrid->item(Index, 0)->text().toStdString()));
      (static_cast<TBase*>(OWNER))->ShellGIS->DelObjFromLayer(Name, ID);
      Index = Index - 1;

      //Очистка "грида" от старых данных
      q = ObjGrid->rowCount();
      for(i=0; i<q; i++)
        ObjGrid->removeRow(0);

      list = (static_cast<TBase*>(OWNER))->ShellGIS->GetObjList(Name);

      for(i=0;i<static_cast<int>(list.size());i++)
      {
        ObjGrid->insertRow(0);

        ObjGrid->setItem(0, 0, new QTableWidgetItem(QString::number(list[static_cast<unsigned int>(i)].ID)));
        ObjGrid->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(list[static_cast<unsigned int>(i)].Name)));
      }
      if (Index >= 0)
        ObjGrid->setCurrentCell(Index, 0);
      else
        ObjGrid->setCurrentCell(0, 0);

      list.clear();
    //}
  }
}
