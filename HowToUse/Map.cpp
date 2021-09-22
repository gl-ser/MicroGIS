//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл Map.cpp                                                               //
//                                                                            //
//                           *** TMAP ОКНО КАРТЫ ***                          //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QShowEvent>
#include <QDesktopWidget>
#include "Map.h"
#include "Base.h"


TMap::TMap(QWidget *parent) : QMainWindow(parent)
{
  setupUi(this);

  OWNER = NULL;

  /*#ifndef __unix__
  //Устанавливаю значки заголовка окна: "закрытие"
  setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
  #endif*/

  CurrentScale = new QLabel(this);
  this->statusBarMain->addWidget(CurrentScale);

  Ruler = new QLabel(this);
  this->statusBarMain->addWidget(Ruler);

  CurCoord = new QLabel(this);
  this->statusBarMain->addWidget(CurCoord);

  FIniFileName = "";
  Placement = new TPlacement(this);

  //До момента чтения положения окна из INI-файла окно размещается по центру экрана
  MoveToCenter();
}


TMap::~TMap()
{
  Placement->Save();
  delete Placement;
  FIniFileName = "";
  delete CurCoord;
  delete CurrentScale;
  delete Ruler;

  OWNER = NULL;
}


void TMap::IniFileName(std::string Value)
{
  FIniFileName = Value;
  Placement->Restore(FIniFileName, "WIN_MAP");
}


void TMap::MoveToCenter()
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


void TMap::showEvent(QShowEvent *event)
{
  if(event->type() == QEvent::Show)
  {

  }
  else
  {
    QWidget::showEvent(event);
  }
}


void TMap::hideEvent(QHideEvent *event)
{
  if( event->type() == QEvent::Hide)
  {

  }
  else
  {
    QWidget::hideEvent(event);
  }
}


void TMap::on_action_triggered()
{
  if (action->isChecked() == true)
  {
    (static_cast<TBase*>(OWNER))->ShellGIS->SetProjection(TGISLib::CYLINDRICAL);
    action_2->setChecked(false);
    action_3->setChecked(false);
    action_9->setChecked(false);
    action_10->setChecked(false);
  }
  else
  {
    action->setChecked(true);
  }
}


void TMap::on_action_2_triggered()
{
  if (action_2->isChecked() == true)
  {
    (static_cast<TBase*>(OWNER))->ShellGIS->SetProjection(TGISLib::NORTHPOLE);
    action->setChecked(false);
    action_3->setChecked(false);
    action_9->setChecked(false);
    action_10->setChecked(false);
  }
  else
  {
    action_2->setChecked(true);
  }
}


void TMap::on_action_3_triggered()
{
  if (action_3->isChecked() == true)
  {
    (static_cast<TBase*>(OWNER))->ShellGIS->SetProjection(TGISLib::SOUTHPOLE);
    action->setChecked(false);
    action_2->setChecked(false);
    action_9->setChecked(false);
    action_10->setChecked(false);
  }
  else
  {
    action_3->setChecked(true);
  }
}


void TMap::on_action_4_triggered()
{
  (static_cast<TBase*>(OWNER))->ShellGIS->ShowAllMap();
}


void TMap::on_action_6_triggered()
{
  if (action_6->isChecked() == true)
  {
    (static_cast<TBase*>(OWNER))->ShellGIS->SetTool(TView::MOVE);
    action_7->setChecked(false);
    action_8->setChecked(false);
  }
  else
  {
    action_6->setChecked(true);
  }
}


void TMap::on_action_7_triggered()
{
  if (action_7->isChecked() == true)
  {
    (static_cast<TBase*>(OWNER))->ShellGIS->SetTool(TView::RULER);
    action_6->setChecked(false);
    action_8->setChecked(false);
  }
  else
  {
    action_7->setChecked(true);
  }
}


void TMap::on_action_5_triggered()
{
  (static_cast<TBase*>(OWNER))->LayerCtrl->exec();
}


void TMap::on_action_8_triggered()
{
  if (action_8->isChecked() == true)
  {
    (static_cast<TBase*>(OWNER))->ShellGIS->SetTool(TView::ARROW);
    action_7->setChecked(false);
    action_6->setChecked(false);
  }
  else
  {
    action_8->setChecked(true);
  }
}


void TMap::on_action_9_triggered()
{
  if (action_9->isChecked() == true)
  {
    (static_cast<TBase*>(OWNER))->ShellGIS->SetProjection(TGISLib::MERCATOR);
    action->setChecked(false);
    action_2->setChecked(false);
    action_3->setChecked(false);
    action_10->setChecked(false);
  }
  else
  {
    action_9->setChecked(true);
  }
}


void TMap::on_action_10_triggered()
{
  if (action_10->isChecked() == true)
  {
    (static_cast<TBase*>(OWNER))->ShellGIS->SetProjection(TGISLib::KAVRAYSKIY);
    action->setChecked(false);
    action_2->setChecked(false);
    action_3->setChecked(false);
    action_9->setChecked(false);
  }
  else
  {
    action_10->setChecked(true);
  }
}


void TMap::on_action_11_triggered()
{  //Показать
  (static_cast<TBase*>(OWNER))->ShellGIS->ShowLayer("динам_точки");
}


void TMap::on_action_12_triggered()
{  //Скрыть
  (static_cast<TBase*>(OWNER))->ShellGIS->HideLayer("динам_точки");
}
