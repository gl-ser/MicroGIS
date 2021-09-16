//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл View.cpp                                                              //
//                                                                            //
//              *** TVIEW ВИД ДЛЯ ОТРИСОВКИ ГРАФИЧЕСКОЙ СЦЕНЫ ***             //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QApplication>
#include <QPainter>
#include <QEvent>
#include "View.h"
#include "GISLib.h"


TView::TView(void)
{
  Contructor();
}


TView::TView(QGraphicsScene *Value) : QGraphicsView(Value)
{
  Contructor();
}


TView::~TView(void)
{
  OWNER = NULL;

  delete CursorArrow;
  delete CursorMove;
  delete CursorRuler;

  delete Hint;
  delete HintTimer;
}


void TView::Contructor()
{
  OWNER = NULL;
  this->setRenderHint(QPainter::Antialiasing);                   //Установить сглаживание
  //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    //Отключить ScrollBar по вертикали
  //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //Отключить ScrollBar по горизонтали
  this->setMouseTracking(true);  //Разрешить отслеживание положения курсора мыши без необходимости нажатия на кнопки мыши

  CursorArrow = new QCursor(Qt::ArrowCursor);
  CursorMove = new QCursor(Qt::OpenHandCursor);
  CursorRuler = new QCursor(Qt::CrossCursor);

  this->setCursor(*CursorArrow);  //Курсор по умолчанию

  Hint = new QLabel("", NULL);  //Контекстная подсказка

  //Устанавливаю значки заголовка окна
  Hint->setWindowFlags(Qt::ToolTip);

  HintTimer = new QBasicTimer();
}


void TView::timerEvent(QTimerEvent *event)
{
  if (event->timerId() == HintTimer->timerId())
  {
    CloseHint();
  }
  else
  {
    QWidget::timerEvent(event);
  }
}


void TView::SetCursor(TView::TTool Value)
{
  CloseHint();
  switch (Value)
  {
    //Движение карты
    case MOVE:
      this->setCursor(*CursorMove);
    break;

    //Линейка
    case RULER:
      this->setCursor(*CursorRuler);
    break;

    //Стрелка
    case ARROW:
      this->setCursor(*CursorArrow);
    break;
  }
}


void TView::CloseHint()
{
  HintTimer->stop();
  Hint->close();
  qApp->processEvents();
}


void TView::resizeEvent(QResizeEvent *event)
{
  if(event->type() == QEvent::Resize)
  {
    (static_cast<TGISLib*>(OWNER))->OnViewResize(event);
  }
  else
  {
    QGraphicsView::resizeEvent(event);
  }
}


bool TView::event(QEvent *event)
{
int ViewX, ViewY, GlobalX, GlobalY;
  if (event->type() == QEvent::ToolTip)
  {
    if ((static_cast<TGISLib*>(OWNER))->GetCurrentTool() == ARROW)
    {  //Показать всплывающую подсказку
      CloseHint();

      //Координаты курсора "мыши" на "виде"
      ViewX = static_cast<QHelpEvent*>(event)->x();
      ViewY = static_cast<QHelpEvent*>(event)->y();

      //Экранные координаты курсора "мыши"
      GlobalX = static_cast<QHelpEvent*>(event)->globalX();
      GlobalY = static_cast<QHelpEvent*>(event)->globalY();

      Hint->move(TCartography::Trunc(GlobalX+10), TCartography::Trunc(GlobalY));

      Hint->setText((static_cast<TGISLib*>(OWNER))->MapData->GetStringHintUnderCursor(items(ViewX, ViewY)));
      Hint->show();
      HintTimer->start(10000, this);
      qApp->processEvents();
    }
  }
  else
  {
    QGraphicsView::event(event);
  }
  return true;
}
