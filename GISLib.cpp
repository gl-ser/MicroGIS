//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл GISLib.cpp                                                            //
//                                                                            //
//                 *** TGISLIB БАЗОВЫЙ КЛАСС ДЛЯ ENGINEGIS ***                //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QString>
#include <QList>
#include "GISLib.h"


TGISLib::TGISLib(void)
{
  //--- ИНИЦИАЛИЗАЦИЯ КОНСТАНТ ---
  CONST_MaxScale = 1000.0;
  CONST_MinScale = 100.0;
  CONST_StepScale = 10.0;
  CONST_NormScale = 100.0;

  Scale = CONST_NormScale;

  Layout = NULL;
  CurCoord = NULL;
  CurrentScale = NULL;
  Ruler = NULL;

  Cartography = new TCartography();
  Cartography->OWNER = this;

  //Инициализация графической сцены
  Scene = new TScene();
  Scene->OWNER = this;

  //Вид для отрисовки карты
  View = new TView(Scene);
  View->OWNER = this;

  //Картографические данные
  MapData = new TMapData();
  MapData->OWNER = this;

  ProportionX = 1.0;
  ProportionY = 1.0;

  //Инструмент по умолчанию
  SetCurrentTool(TView::MOVE);
}



TGISLib::~TGISLib(void)
{
  delete MapData;
  delete Scene;
  delete View;
  delete Cartography;

  Layout = NULL;
  CurCoord = NULL;
  CurrentScale = NULL;
  Ruler = NULL;
}


void TGISLib::Proportion()
{
double DlX, DlY;
  DlX = (PlaneCoord.Xmax - PlaneCoord.Xmin)*1000.0;
  DlY = (PlaneCoord.Ymax - PlaneCoord.Ymin)*1000.0;

  if (((Screen.Xmax - Screen.Xmin) > 0.0) && ((Screen.Ymax - Screen.Ymin) > 0.0))
  {
    ProportionX = DlX/(Screen.Xmax - Screen.Xmin);
    ProportionY = DlY/(Screen.Ymax - Screen.Ymin);

    if ((ProportionX < 0.0) || (ProportionY < 0.0))
    {
      ProportionX = ProportionX * 1000000.0;
      ProportionY = ProportionY * 1000000.0;
    }
  }
  else
  {
    ProportionX = 1.0;
    ProportionY = 1.0;
  }
}


void TGISLib::SetCurrentTool(TView::TTool Value)
{
  if (Ruler != NULL)
    Ruler->setText(" длина = [пусто] ");

  Tool = Value;
  View->SetCursor(Value);
}


TView::TTool TGISLib::GetCurrentTool()
{
  return Tool;
}


void TGISLib::PlusScale()
{
double Xsr, Ysr, DlX, DlY, Xmin, Xmax, Ymin, Ymax, NewDlX, NewDlY;
  Xsr = PlaneCoord.Xmin + (PlaneCoord.Xmax - PlaneCoord.Xmin)/2.0;  //X средняя
  Ysr = PlaneCoord.Ymin + (PlaneCoord.Ymax - PlaneCoord.Ymin)/2.0;  //Y средняя

  DlX = PlaneCoord.Xmax - PlaneCoord.Xmin;  //Старая длина по X
  DlY = PlaneCoord.Ymax - PlaneCoord.Ymin;  //Старая длина по Y

  NewDlX = DlX*(1.0-CONST_StepScale/100.0);  //Новая длина по X
  NewDlY = DlY*(1.0-CONST_StepScale/100.0);  //Новая длина по Y

  Xmin = Xsr - NewDlX/2.0;
  Xmax = Xsr + NewDlX/2.0;

  Ymin = Ysr - NewDlY/2.0;
  Ymax = Ysr + NewDlY/2.0;

  Scale = Scale + CONST_StepScale;

  if (Scale > CONST_MaxScale)
  {
    Scale = CONST_MaxScale;
  }
  else
  {
    PlaneCoord.Xmin = Xmin;
    PlaneCoord.Xmax = Xmax;
    PlaneCoord.Ymin = Ymin;
    PlaneCoord.Ymax = Ymax;

    MapData->RePaint();
  }
}


void TGISLib::MinusScale()
{
double Xsr, Ysr, DlX, DlY, Xmin, Xmax, Ymin, Ymax, NewDlX, NewDlY;
  Xsr = PlaneCoord.Xmin + (PlaneCoord.Xmax - PlaneCoord.Xmin)/2.0;  //X средняя
  Ysr = PlaneCoord.Ymin + (PlaneCoord.Ymax - PlaneCoord.Ymin)/2.0;  //Y средняя

  DlX = PlaneCoord.Xmax - PlaneCoord.Xmin;  //Старая длина по X
  DlY = PlaneCoord.Ymax - PlaneCoord.Ymin;  //Старая длина по Y

  NewDlX = DlX*(1.0+CONST_StepScale/100.0);  //Новая длина по X
  NewDlY = DlY*(1.0+CONST_StepScale/100.0);  //Новая длина по Y

  Xmin = Xsr - NewDlX/2.0;
  Xmax = Xsr + NewDlX/2.0;

  Ymin = Ysr - NewDlY/2.0;
  Ymax = Ysr + NewDlY/2.0;

  Scale = Scale - CONST_StepScale;

  if (Scale <= CONST_MinScale)
  {
    Scale = CONST_MinScale;

    PlaneCoord.Xmin = Projection.Map.Xmin;
    PlaneCoord.Xmax = Projection.Map.Xmax;
    PlaneCoord.Ymin = Projection.Map.Ymin;
    PlaneCoord.Ymax = Projection.Map.Ymax;
  }
  else
  {
    PlaneCoord.Xmin = Xmin;
    PlaneCoord.Xmax = Xmax;
    PlaneCoord.Ymin = Ymin;
    PlaneCoord.Ymax = Ymax;
  }

  MapData->RePaint();
}


void TGISLib::NormalizeScale()
{
  CurrentScale->setText(" условный масштаб = 100% ");
  Ruler->setText(" длина = [пусто] ");
  CurCoord->setText(" широта = [пусто]   долгота = [пусто] ");

  Scale = CONST_NormScale;

  PlaneCoord.Xmin = Projection.Map.Xmin;
  PlaneCoord.Xmax = Projection.Map.Xmax;
  PlaneCoord.Ymin = Projection.Map.Ymin;
  PlaneCoord.Ymax = Projection.Map.Ymax;

  Proportion();

  View->CloseHint();  //Закрыть всплывающую подсказку

  MapData->RePaint();
}


double TGISLib::GetScale()
{
  return Scale;
}


void TGISLib::OnSceneMouseMove(QGraphicsSceneMouseEvent *event)
{
double SceneX, SceneY, B, L;
  //Координаты курсора "мыши" на сцене
  SceneX = event->scenePos().x();
  SceneY = event->scenePos().y();

  Cartography->ScreenXYToPZ90BL(SceneX, SceneY, &B, &L);
  B = B*180.0/M_PI;
  L = L*180.0/M_PI;

  CurCoord->setText(" широта = " + QString::number(B) + "°   долгота = " + QString::number(L) + "° ");

  CurrentScale->setText(" условный масштаб = " + QString::number(GetScale()) + "% ");
}


void TGISLib::OnViewResize(QResizeEvent *event)
{
QRectF rect;
  //Установить новый размер графической сцены
  // Начало системы координат графической сцены расположено в центре вида
  Scene->setSceneRect(-event->size().width()/2.0, -event->size().height()/2.0,
                      event->size().width(), event->size().height());

  rect = Scene->sceneRect();

  //Запомнить границы области отображения карты в координатах сцены
  Screen.Xmin = rect.left();
  Screen.Xmax = rect.left()+rect.width();
  Screen.Ymin = rect.top();
  Screen.Ymax = rect.top()+rect.height();

  Proportion();

  //Перерисовать картографические данные
  MapData->RePaint();
}


void TGISLib::OnSceneMouseWheel(QGraphicsSceneWheelEvent *event)
{
  if (event->delta() > 0)
    PlusScale();
  else
    MinusScale();

  CurrentScale->setText(" условный масштаб = " + QString::number(GetScale()) + "% ");
}


void TGISLib::OnSceneDragAndDrop(double DownSceneX, double DownSceneY, double UpSceneX, double UpSceneY,
                                 double DownViewX, double DownViewY, double UpViewX, double UpViewY)
{
double DeltaX, DeltaY, DlX, DlY, DX, DY, Xsr, Ysr, StartB, StartL, StopB, StopL, dl;
TDataLeftMouse LM;
  if (Tool == TView::MOVE)
  {  //Движение карты
    if (fabs(GetScale() - 100.0) <= 0.0001)
    {  //Для масштаба 100%

    }
    else
    {  //Для любого другого масштаба (не 100%)
      DeltaX = UpSceneX - DownSceneX;  //Смещение по X (в координатах сцены)
      DeltaY = UpSceneY - DownSceneY;  //Смещение по Y (в координатах сцены)

      DlX = Screen.Xmax - Screen.Xmin;  //Длина по X (в координатах сцены)
      DlY = Screen.Ymax - Screen.Ymin;  //Длина по Y (в координатах сцены)

      DX = DeltaX/DlX;  //Относительное смещение по X
      DY = DeltaY/DlY;  //Относительное смещение по Y

      if (ProportionX > ProportionY)
      {
        DY = DY*(ProportionX/ProportionY);
      }
      else
      {
        DX = DX*(ProportionY/ProportionX);
      }

      Xsr = PlaneCoord.Xmin + (PlaneCoord.Xmax - PlaneCoord.Xmin)/2.0;  //X средняя (в координатах проекции)
      Ysr = PlaneCoord.Ymin + (PlaneCoord.Ymax - PlaneCoord.Ymin)/2.0;  //Y средняя (в координатах проекции)

      DlX = PlaneCoord.Xmax - PlaneCoord.Xmin;  //Длина по X (в координатах проекции)
      DlY = PlaneCoord.Ymax - PlaneCoord.Ymin;  //Длина по Y (в координатах проекции)

      Xsr = Xsr - DX*DlX;
      Ysr = Ysr + DY*DlY;

      PlaneCoord.Xmin = Xsr - DlX/2.0;
      PlaneCoord.Xmax = Xsr + DlX/2.0;

      PlaneCoord.Ymin = Ysr - DlY/2.0;
      PlaneCoord.Ymax = Ysr + DlY/2.0;

      Proportion();

      MapData->RePaint();
    }
  }

  if (Tool == TView::RULER)
  {  //Линейка
    Cartography->ScreenXYToPZ90BL(DownSceneX, DownSceneY, &StartB, &StartL);
    Cartography->ScreenXYToPZ90BL(UpSceneX, UpSceneY, &StopB, &StopL);

    dl = Cartography->RulerLength(StartB, StartL, StopB, StopL);
    if (dl >= 10000.0)
    {
      Ruler->setText(" длина = " + QString::number(dl/1000.0) + " км ");
    }
    else
    {
      Ruler->setText(" длина = " + QString::number(dl) + " м ");
    }
  }

  if (Tool == TView::ARROW)
  {  //Информация по объектам карты
    Cartography->ScreenXYToPZ90BL(DownSceneX, DownSceneY, &StartB, &StartL);
    Cartography->ScreenXYToPZ90BL(UpSceneX, UpSceneY, &StopB, &StopL);

    LM.CoordDown.B = StartB;
    LM.CoordDown.L = StartL;
    LM.ObjectsDown = MapData->GetObjListUnderCursor(View->items(static_cast<int>(DownViewX), static_cast<int>(DownViewY)));

    LM.CoordUp.B = StopB;
    LM.CoordUp.L = StopL;
    LM.ObjectsUp = MapData->GetObjListUnderCursor(View->items(static_cast<int>(UpViewX), static_cast<int>(UpViewY)));

    //Передать в пользовательскую программу данные по нажатию и отпусканию левой клавиши "мыши"
    emit GetDataLeftMouse(LM);
  }

  LM.ObjectsDown.clear();
  LM.ObjectsUp.clear();
}
