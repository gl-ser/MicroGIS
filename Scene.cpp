//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл Scene.cpp                                                             //
//                                                                            //
//                      *** TSCENE ГРАФИЧЕСКАЯ СЦЕНА ***                      //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QEvent>
#include <QPen>
#include "Scene.h"
#include "GISLib.h"


TScene::TScene(void)
{
  OWNER = NULL;

  DownSceneX = 0.0;
  DownSceneY = 0.0;

  UpSceneX = 0.0;
  UpSceneY = 0.0;

  DownViewX = 0.0;
  DownViewY = 0.0;

  UpViewX = 0.0;
  UpViewY = 0.0;

  PrLeftButtonDown = false;

  RulerLine = NULL;
}


TScene::~TScene(void)
{
  OWNER = NULL;

  if (RulerLine != NULL)
    delete RulerLine;

  RulerLine = NULL;
}


void TScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if(event->type() == QEvent::GraphicsSceneMouseMove)
  {
    if (event->buttons() == Qt::NoButton)
    {
      (static_cast<TGISLib*>(OWNER))->OnSceneMouseMove(event);
    }

    if (event->buttons() == Qt::LeftButton)
    {
      if ((static_cast<TGISLib*>(OWNER))->GetCurrentTool() == TView::RULER)
      if (RulerLine != NULL)
      {
        RulerLine->setLine(DownSceneX, DownSceneY, event->scenePos().x(), event->scenePos().y());
        (static_cast<TGISLib*>(OWNER))->OnSceneDragAndDrop(DownSceneX, DownSceneY, event->scenePos().x(), event->scenePos().y(),
                                                           DownViewX, DownViewY, UpViewX, UpViewY);
        (static_cast<TGISLib*>(OWNER))->OnSceneMouseMove(event);
      }
      //Перерисовка объекта "линия", отвечающего за отображение измеряемого линейкой пути
    }
  }
  else
  {
    QGraphicsScene::mouseMoveEvent(event);
  }
}


void TScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
  if(event->type() == QEvent::GraphicsSceneWheel)
  {
    (static_cast<TGISLib*>(OWNER))->OnSceneMouseWheel(event);
  }
  else
  {
    QGraphicsScene::wheelEvent(event);
  }
}


void TScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
QPen Pen;
QPoint in, out;
  in = QPoint();
  out = QPoint();
  Pen = QPen(Qt::black);

  if(event->type() == QEvent::GraphicsSceneMousePress)
  {
    if (event->buttons() == Qt::LeftButton)
    {
      PrLeftButtonDown = true;

      //Получаю координаты на сцене
      DownSceneX = event->scenePos().x();
      DownSceneY = event->scenePos().y();

      //Получаю экранные координаты
      in.setX(static_cast<int>(event->screenPos().x()));
      in.setY(static_cast<int>(event->screenPos().y()));

      //Перевожу экранные координаты в координаты "вида"
      out = (static_cast<TGISLib*>(OWNER))->View->mapFromGlobal(in);
      DownViewX = out.x();
      DownViewY = out.y();

      if ((static_cast<TGISLib*>(OWNER))->GetCurrentTool() == TView::RULER)
      {  //Текущий инструмент - линейка
        if (RulerLine != NULL)
        {
          (static_cast<TGISLib*>(OWNER))->Scene->removeItem(RulerLine);
          delete RulerLine;
          RulerLine = NULL;
        }
        RulerLine = (static_cast<TGISLib*>(OWNER))->Scene->addLine(DownSceneX, DownSceneY, DownSceneX+1, DownSceneY+1, Pen);
        //Создал объект "линия", отвечающий за прорисовку измеряемого линейкой расстояния
      }
    }
  }
  else
  {
    QGraphicsScene::mousePressEvent(event);
  }
}


void TScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
QPoint in, out;
  in = QPoint();
  out = QPoint();
  if(event->type() == QEvent::GraphicsSceneMouseRelease)
  {
    if (PrLeftButtonDown == true)
    {
      PrLeftButtonDown = false;

      //Получаю координаты на сцене
      UpSceneX = event->scenePos().x();
      UpSceneY = event->scenePos().y();

      //Получаю экранные координаты
      in.setX(static_cast<int>(event->screenPos().x()));
      in.setY(static_cast<int>(event->screenPos().y()));

      //Перевожу экранные координаты в координаты "вида"
      out = (static_cast<TGISLib*>(OWNER))->View->mapFromGlobal(in);
      UpViewX = out.x();
      UpViewY = out.y();

      if (RulerLine != NULL)
      {
        (static_cast<TGISLib*>(OWNER))->Scene->removeItem(RulerLine);
        delete RulerLine;
        RulerLine = NULL;
      }
      //Удалил объект "линия", отвечающий за прорисовку измеряемого линейкой расстояния

      (static_cast<TGISLib*>(OWNER))->OnSceneDragAndDrop(DownSceneX, DownSceneY, UpSceneX, UpSceneY,
                                                         DownViewX, DownViewY, UpViewX, UpViewY);
    }
  }
  else
  {
    QGraphicsScene::mouseReleaseEvent(event);
  }
}
