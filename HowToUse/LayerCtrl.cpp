//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл LayerCtrl.cpp                                                         //
//                                                                            //
//                  *** TLAYERCTRL ОКНО УПРАВЛЕНИЯ СЛОЯМИ ***                 //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QDesktopWidget>
#include "LayerCtrl.h"
#include "Base.h"


TLayerCtrl::TLayerCtrl(QWidget *parent) : QDialog(parent)
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

  LayerGrid->setColumnWidth(1, 250);  //Поле для названия слоя должно быть такой ширины
}


TLayerCtrl::~TLayerCtrl()
{
  Placement->Save();
  delete Placement;
  FIniFileName = "";
}


void TLayerCtrl::IniFileName(std::string Value)
{
  FIniFileName = Value;
  Placement->Restore(FIniFileName, "WIN_LAYER_CTRL");
}


void TLayerCtrl::MoveToCenter()
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


void TLayerCtrl::GetData(int Index)
{
int q, i;
TMapData::TLayerList list;
  //Очистка "грида" от старых данных
  q = LayerGrid->rowCount();
  for(i=0; i<q; i++)
    LayerGrid->removeRow(0);

  list = (static_cast<TBase*>(OWNER))->ShellGIS->GetLayerList();

  //for(i=static_cast<int>(list.size()-1); i>=0; i--)
  for(i=0;i<static_cast<int>(list.size());i++)
  {
    LayerGrid->insertRow(0);

    if (list[static_cast<unsigned int>(i)].Visible == true)
      LayerGrid->setItem(0, 0, new QTableWidgetItem("видимый"));
    else
      LayerGrid->setItem(0, 0, new QTableWidgetItem("скрытый"));

    LayerGrid->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(list[static_cast<unsigned int>(i)].Name)));
  }
  LayerGrid->setCurrentCell(Index, 0);

  list.clear();
}


void TLayerCtrl::showEvent(QShowEvent *event)
{
  if(event->type() == QEvent::Show)
  {
    GetData(0);
  }
  else
  {
    QWidget::showEvent(event);
  }
}


void TLayerCtrl::hideEvent(QHideEvent *event)
{
int q, i;
  if(event->type() == QEvent::Hide)
  {
    //Очистка "грида" от старых данных
    q = LayerGrid->rowCount();
    for(i=0; i<q; i++)
      LayerGrid->removeRow(0);
  }
  else
  {
    QWidget::hideEvent(event);
  }
}


void TLayerCtrl::on_pushButton_clicked()
{
int Index;
std::string name;
  Index = LayerGrid->currentRow();
  if (Index >= 0)
  {
    name = LayerGrid->item(Index, 1)->text().toStdString();
    (static_cast<TBase*>(OWNER))->ShellGIS->ShowLayer(name);
    GetData(Index);
    (static_cast<TBase*>(OWNER))->ShellGIS->RePaint();
  }
}


void TLayerCtrl::on_pushButton_2_clicked()
{
int Index;
std::string name;
  Index = LayerGrid->currentRow();
  if (Index >= 0)
  {
    name = LayerGrid->item(Index, 1)->text().toStdString();
    (static_cast<TBase*>(OWNER))->ShellGIS->HideLayer(name);
    GetData(Index);
    (static_cast<TBase*>(OWNER))->ShellGIS->RePaint();
  }
}


void TLayerCtrl::on_pushButton_3_clicked()
{
bool res;
std::string name;
  (static_cast<TBase*>(OWNER))->LayerAdd->exec();
  name = (static_cast<TBase*>(OWNER))->LayerAdd->GetLayerName();

  if (name != "")
  {
    res = (static_cast<TBase*>(OWNER))->ShellGIS->AddLayer(name);
    if (res == true)
    {
      GetData(0);
    }
  }

  (static_cast<TBase*>(OWNER))->ShellGIS->RePaint();
}


void TLayerCtrl::on_pushButton_4_clicked()
{
int Index;
std::string name;
  Index = LayerGrid->currentRow();
  if (Index >= 0)
  {
    //if ((static_cast<TBase*>(OWNER))->CancelOK->WhatCanIDo() == true)
    //{
      name = LayerGrid->item(Index, 1)->text().toStdString();
      (static_cast<TBase*>(OWNER))->ShellGIS->DelLayer(name);
      Index = Index - 1;
      if (Index >= 0)
        GetData(Index);
      else
        GetData(0);
    //}
  }
}


void TLayerCtrl::on_CheckGrid15_clicked()
{
  if (CheckGrid15->checkState() == Qt::CheckState::Checked)
    (static_cast<TBase*>(OWNER))->ShellGIS->WhatIsShow(false, true);
  else
    (static_cast<TBase*>(OWNER))->ShellGIS->WhatIsShow(false, false);
}


void TLayerCtrl::on_pushButton_5_clicked()
{
int Index;
std::string name;
  Index = LayerGrid->currentRow();
  if (Index >= 0)
  {
    name = LayerGrid->item(Index, 1)->text().toStdString();
    (static_cast<TBase*>(OWNER))->ObjCtrl->Name = name;
    (static_cast<TBase*>(OWNER))->ObjCtrl->exec();
  }
}
