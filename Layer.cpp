//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл Layer.cpp                                                             //
//                                                                            //
//                    *** TLAYER КАРТОГРАФИЧЕСКИЙ СЛОЙ ***                    //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include "Layer.h"
#include "MapData.h"
#include "GISLib.h"


TLayer::TLayer(void)
{
  OWNER = NULL;
  Name = "";
  Visible = true;
  Objects.clear();
}


TLayer::~TLayer(void)
{
unsigned int i;
  Hide();
  OWNER = NULL;

  for(i=0;i<Objects.size();i++)
  {
    Objects[i].HandlePointAsEllipse = NULL;
    Objects[i].HandlePointAsRect = NULL;
    Objects[i].HandleRegion = NULL;
    Objects[i].HandlePolyLine = NULL;

    Objects[i].Header.ID = 0;
    Objects[i].Header.Name = "";
    Objects[i].Hemisphere = NONE_HEM;
    Objects[i].Type = NONE_OBJ;
    Objects[i].Point.Type = NONE_SYMBOL;

    if (Objects[i].Point.Pen != NULL)
      delete Objects[i].Point.Pen;

    if (Objects[i].Point.Brush != NULL)
      delete Objects[i].Point.Brush;

    Objects[i].PolyLine.Spot.clear();

    if (Objects[i].PolyLine.Pen != NULL)
      delete Objects[i].PolyLine.Pen;

    Objects[i].Region.Spot.clear();

    if (Objects[i].Region.Pen != NULL)
      delete Objects[i].Region.Pen;

    if (Objects[i].Region.Brush != NULL)
      delete Objects[i].Region.Brush;
  }
  Objects.clear();
}


void TLayer::RGBToMI(int R, int G, int B, int *MI)
{
  *MI = (65536*R) + (256*G) + B;
}


void TLayer::MIToRGB(int MI, int *R, int *G, int *B)
{
  *R = MI/65536;
  *G = (MI - (*R)*65536)/256;
  *B = MI - (*R)*65536 - (*G)*256;
}


QPen TLayer::PenMIToQPen(int WidthMI, int PatternMI, int ColorMI)
{
QPen Pen;
QColor Color;
Qt::PenStyle Style;
int R, G, B;
  Pen = QPen();
  Pen.setWidth(WidthMI);

  switch (PatternMI)
  {
    case 1:
      Style = Qt::NoPen;
    break;

    case 2:
      Style = Qt::SolidLine;
    break;

    case 3:
      Style = Qt::DotLine;
    break;

    case 4:
      Style = Qt::DotLine;
    break;

    case 5:
      Style = Qt::DashLine;
    break;

    case 6:
      Style = Qt::DashLine;
    break;

    case 7:
      Style = Qt::DashLine;
    break;

    case 8:
      Style = Qt::DashLine;
    break;

    case 9:
      Style = Qt::DashLine;
    break;

    case 10:
      Style = Qt::DashLine;
    break;

    case 11:
      Style = Qt::DashLine;
    break;

    case 12:
      Style = Qt::DashLine;
    break;

    case 13:
      Style = Qt::DashLine;
    break;

    case 14:
      Style = Qt::DashDotLine;
    break;

    case 15:
      Style = Qt::DashDotLine;
    break;

    case 16:
      Style = Qt::DashDotLine;
    break;

    case 17:
      Style = Qt::DashDotLine;
    break;

    case 18:
      Style = Qt::DashDotDotLine;
    break;

    case 19:
      Style = Qt::DashDotDotLine;
    break;

    case 20:
      Style = Qt::DashDotDotLine;
    break;

    case 21:
      Style = Qt::DashDotDotLine;
    break;

    case 22:
      Style = Qt::DashDotDotLine;
    break;

    case 23:
      Style = Qt::DashDotDotLine;
    break;

    case 24:
      Style = Qt::DashDotDotLine;
    break;

    case 25:
      Style = Qt::DashDotDotLine;
    break;

    default:
      Style = Qt::SolidLine;
    break;
  }

  Pen.setStyle(Style);

  MIToRGB(ColorMI, &R, &G, &B);
  Color = QColor(R, G, B);

  Pen.setColor(Color);

  return Pen;
}


QBrush TLayer::BrushMIToQBrush(int PatternMI, int ColorMI)
{
QBrush Brush;
QColor Color;
Qt::BrushStyle Style;
int R, G, B;
  Brush = QBrush();

  switch (PatternMI)
  {
    case 1:
      Style = Qt::NoBrush;
    break;

    case 2:
      Style = Qt::SolidPattern;
    break;

    case 3:
      Style = Qt::HorPattern;
    break;

    case 4:
      Style = Qt::VerPattern;
    break;

    case 5:
      Style = Qt::BDiagPattern;
    break;

    case 6:
      Style = Qt::FDiagPattern;
    break;

    case 7:
      Style = Qt::CrossPattern;
    break;

    case 8:
      Style = Qt::DiagCrossPattern;
    break;

    case 12:
      Style = Qt::Dense1Pattern;
    break;

    case 13:
      Style = Qt::Dense2Pattern;
    break;

    case 14:
      Style = Qt::Dense3Pattern;
    break;

    case 15:
      Style = Qt::Dense4Pattern;
    break;

    case 16:
      Style = Qt::Dense5Pattern;
    break;

    case 17:
      Style = Qt::Dense6Pattern;
    break;

    case 18:
      Style = Qt::Dense7Pattern;
    break;

    case 19:
      Style = Qt::HorPattern;
    break;

    case 20:
      Style = Qt::HorPattern;
    break;

    case 21:
      Style = Qt::HorPattern;
    break;

    case 22:
      Style = Qt::HorPattern;
    break;

    case 23:
      Style = Qt::HorPattern;
    break;

    case 24:
      Style = Qt::VerPattern;
    break;

    case 25:
      Style = Qt::VerPattern;
    break;

    case 26:
      Style = Qt::VerPattern;
    break;

    case 27:
      Style = Qt::VerPattern;
    break;

    case 28:
      Style = Qt::VerPattern;
    break;

    case 29:
      Style = Qt::BDiagPattern;
    break;

    case 30:
      Style = Qt::BDiagPattern;
    break;

    case 31:
      Style = Qt::BDiagPattern;
    break;

    case 32:
      Style = Qt::BDiagPattern;
    break;

    case 33:
      Style = Qt::BDiagPattern;
    break;

    case 34:
      Style = Qt::FDiagPattern;
    break;

    case 35:
      Style = Qt::FDiagPattern;
    break;

    case 36:
      Style = Qt::FDiagPattern;
    break;

    case 37:
      Style = Qt::FDiagPattern;
    break;

    case 38:
      Style = Qt::FDiagPattern;
    break;

    case 39:
      Style = Qt::CrossPattern;
    break;

    case 40:
      Style = Qt::CrossPattern;
    break;

    case 41:
      Style = Qt::CrossPattern;
    break;

    case 42:
      Style = Qt::CrossPattern;
    break;

    case 43:
      Style = Qt::CrossPattern;
    break;

    case 44:
      Style = Qt::DiagCrossPattern;
    break;

    case 45:
      Style = Qt::DiagCrossPattern;
    break;

    case 46:
      Style = Qt::DiagCrossPattern;
    break;

    case 47:
      Style = Qt::DiagCrossPattern;
    break;

    default:
      Style = Qt::SolidPattern;
    break;
  }

  Brush.setStyle(Style);

  MIToRGB(ColorMI, &R, &G, &B);
  Color = QColor(R, G, B);
  Brush.setColor(Color);

  return Brush;
}


void TLayer::CoolRePaint()
{
  if (Visible == true)
  {
    Hide();
    Show();
  }
}


void TLayer::RePaint()
{
bool IsShow;  //Признак: объект надо отрисовывать (true), или не надо отрисовывать (false)
unsigned int i, j;
double deltaX, deltaY, X, Y, X1, Y1, X2, Y2;
QRectF Rect;
QPolygonF Polygon;
QPointF Point;
QPainterPath Path;
QBrush Brush;
  Rect = QRectF();
  Point = QPointF();
  Polygon = QPolygonF();
  Brush = QBrush();

  if (Visible == true)
  {
    //Цикл по всем объектам слоя
    for(i=0;i<Objects.size();i++)
    {
      IsShow = true;

      if (static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Projection.Number == TGISLib::NORTHPOLE)
      if ((Objects[i].Hemisphere != NORTH_HEM) && (Objects[i].Hemisphere != BOTH_HEM))
        IsShow = false;

      if (static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Projection.Number == TGISLib::SOUTHPOLE)
      if ((Objects[i].Hemisphere != SOUTH_HEM) && (Objects[i].Hemisphere != BOTH_HEM))
        IsShow = false;
      //Определил, стереть объект или перерисовать объект

      if (IsShow == false)
      {  //Стираю объект
        if (Objects[i].HandlePointAsEllipse != NULL)
        {
          static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandlePointAsEllipse);
          delete Objects[i].HandlePointAsEllipse;
        }
        Objects[i].HandlePointAsEllipse = NULL;

        if (Objects[i].HandlePointAsRect != NULL)
        {
          static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandlePointAsRect);
          delete Objects[i].HandlePointAsRect;
        }
        Objects[i].HandlePointAsRect = NULL;

        if (Objects[i].HandleRegion != NULL)
        {
          static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandleRegion);
          delete Objects[i].HandleRegion;
        }
        Objects[i].HandleRegion = NULL;

        if (Objects[i].HandlePolyLine != NULL)
        {
          static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandlePolyLine);
          delete Objects[i].HandlePolyLine;
        }
        Objects[i].HandlePolyLine = NULL;
      }

      if (IsShow == true)
      {  //Перерисовываю объект

        //Объект типа "точка"
        if (Objects[i].Type == POINT_OBJ)
        {
          //Круг - тип символа
          if (Objects[i].Point.Type == CIRCLE_SYMBOL)
          {
            if (Objects[i].HandlePointAsEllipse != NULL)
            {  //Перерисовать
              deltaX = 5.0;  //Половина размера объекта "точка" по оси X
              deltaY = 5.0;  //Половина размера объекта "точка" по оси Y

              static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
                Cartography->PZ90BLToScreenXY(Objects[i].Point.Point.B, Objects[i].Point.Point.L, &X, &Y);

              X1 = X - deltaX;
              Y1 = Y - deltaY;

              X2 = X + deltaX;
              Y2 = Y + deltaY;

              Rect.setCoords(X1, Y1, X2, Y2);

              Objects[i].HandlePointAsEllipse->setRect(Rect);
            }
            else
            {  //Создать заново
              deltaX = 5.0;  //Половина размера объекта "точка" по оси X
              deltaY = 5.0;  //Половина размера объекта "точка" по оси Y

              static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
                Cartography->PZ90BLToScreenXY(Objects[i].Point.Point.B, Objects[i].Point.Point.L, &X, &Y);

              X1 = X - deltaX;
              Y1 = Y - deltaY;

              X2 = X + deltaX;
              Y2 = Y + deltaY;

              Rect.setCoords(X1, Y1, X2, Y2);

              Objects[i].HandlePointAsEllipse = static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
                Scene->addEllipse(Rect, *Objects[i].Point.Pen, *Objects[i].Point.Brush);
            }
          }

          //Квадрат - тип символа
          if (Objects[i].Point.Type == RECT_SYMBOL)
          {
            if (Objects[i].HandlePointAsRect != NULL)
            {  //Перерисовать
              deltaX = 5.0;  //Половина размера объекта "точка" по оси X
              deltaY = 5.0;  //Половина размера объекта "точка" по оси Y

              static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
                Cartography->PZ90BLToScreenXY(Objects[i].Point.Point.B, Objects[i].Point.Point.L, &X, &Y);

              X1 = X - deltaX;
              Y1 = Y - deltaY;

              X2 = X + deltaX;
              Y2 = Y + deltaY;

              Rect.setCoords(X1, Y1, X2, Y2);

              Objects[i].HandlePointAsRect->setRect(Rect);
            }
            else
            {  //Создать заново
              deltaX = 5.0;  //Половина размера объекта "точка" по оси X
              deltaY = 5.0;  //Половина размера объекта "точка" по оси Y

              static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
                Cartography->PZ90BLToScreenXY(Objects[i].Point.Point.B, Objects[i].Point.Point.L, &X, &Y);

              X1 = X - deltaX;
              Y1 = Y - deltaY;

              X2 = X + deltaX;
              Y2 = Y + deltaY;

              Rect.setCoords(X1, Y1, X2, Y2);

              Objects[i].HandlePointAsRect = static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
                Scene->addRect(Rect, *Objects[i].Point.Pen, *Objects[i].Point.Brush);
            }
          }
        }

        //Объект типа "полилиния"
        if (Objects[i].Type == POLYLINE_OBJ)
        {
          if (Objects[i].HandlePolyLine != NULL)
          {  //Перерисовать
            Path = QPainterPath();  //Очистка объекта
            static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
              Cartography->PZ90BLToScreenXY(Objects[i].PolyLine.Spot[0].B, Objects[i].PolyLine.Spot[0].L, &X1, &Y1);
            Path.moveTo(X1, Y1);
            for(j=1;j<Objects[i].PolyLine.Spot.size();j++)
            {
              static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
                Cartography->PZ90BLToScreenXY(Objects[i].PolyLine.Spot[j].B, Objects[i].PolyLine.Spot[j].L, &X1, &Y1);
              Path.lineTo(X1, Y1);
            }
            Objects[i].HandlePolyLine->setPath(Path);
          }
          else
          {  //Создать заново
            Path = QPainterPath();  //Очистка объекта
            static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
              Cartography->PZ90BLToScreenXY(Objects[i].PolyLine.Spot[0].B, Objects[i].PolyLine.Spot[0].L, &X1, &Y1);
            Path.moveTo(X1, Y1);
            for(j=1;j<Objects[i].PolyLine.Spot.size();j++)
            {
              static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
                Cartography->PZ90BLToScreenXY(Objects[i].PolyLine.Spot[j].B, Objects[i].PolyLine.Spot[j].L, &X1, &Y1);
              Path.lineTo(X1, Y1);
            }
            Objects[i].HandlePolyLine = static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
              Scene->addPath(Path, *Objects[i].PolyLine.Pen, Brush);
          }
        }

        //Объект типа "регион"
        if (Objects[i].Type == REGION_OBJ)
        {
          if (Objects[i].HandleRegion != NULL)
          {  //Перерисовать
            Polygon.clear();
            for(j=0;j<Objects[i].Region.Spot.size();j++)
            {
              static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
                Cartography->PZ90BLToScreenXY(Objects[i].Region.Spot[j].B, Objects[i].Region.Spot[j].L, &X, &Y);

              Point.setX(X);
              Point.setY(Y);

              Polygon.push_back(Point);
            }
            Objects[i].HandleRegion->setPolygon(Polygon);
          }
          else
          {  //Создать заново
            Polygon.clear();
            for(j=0;j<Objects[i].Region.Spot.size();j++)
            {
              static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
                Cartography->PZ90BLToScreenXY(Objects[i].Region.Spot[j].B, Objects[i].Region.Spot[j].L, &X, &Y);

              Point.setX(X);
              Point.setY(Y);

              Polygon.push_back(Point);
            }
            Objects[i].HandleRegion = static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
                Scene->addPolygon(Polygon, *Objects[i].Region.Pen, *Objects[i].Region.Brush);
          }
        }

      }

    }  //Конец цикла по всем объектам слоя
  }
  Polygon.clear();
}


void TLayer::Hide()
{
unsigned int i;
  Visible = false;

  for(i=0;i<Objects.size();i++)
  {
    if (Objects[i].HandlePointAsEllipse != NULL)
    {
      static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandlePointAsEllipse);
      delete Objects[i].HandlePointAsEllipse;
    }
    Objects[i].HandlePointAsEllipse = NULL;

    if (Objects[i].HandlePointAsRect != NULL)
    {
      static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandlePointAsRect);
      delete Objects[i].HandlePointAsRect;
    }
    Objects[i].HandlePointAsRect = NULL;

    if (Objects[i].HandleRegion != NULL)
    {
      static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandleRegion);
      delete Objects[i].HandleRegion;
    }
    Objects[i].HandleRegion = NULL;

    if (Objects[i].HandlePolyLine != NULL)
    {
      static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandlePolyLine);
      delete Objects[i].HandlePolyLine;
    }
    Objects[i].HandlePolyLine = NULL;
  }
}


void TLayer::Show()
{
bool IsShow;  //Признак: объект надо отрисовывать (true), или не надо отрисовывать (false)
unsigned int i, j;
double deltaX, deltaY, X, Y, X1, Y1, X2, Y2;
QRectF Rect;
QPolygonF Polygon;
QPointF Point;
QPainterPath Path;
QBrush Brush;
  Rect = QRectF();
  Point = QPointF();
  Polygon = QPolygonF();
  Brush = QBrush();

  //Почистить указатели на объекты, расположенные на сцене
  // И одновременно убрать со сцены всё, что там было отображено ранее
  Hide();

  Visible = true;

  //Цикл по всем объектам слоя
  for(i=0;i<Objects.size();i++)
  {
    IsShow = true;

    if (static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Projection.Number == TGISLib::NORTHPOLE)
    if ((Objects[i].Hemisphere != NORTH_HEM) && (Objects[i].Hemisphere != BOTH_HEM))
      IsShow = false;

    if (static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Projection.Number == TGISLib::SOUTHPOLE)
    if ((Objects[i].Hemisphere != SOUTH_HEM) && (Objects[i].Hemisphere != BOTH_HEM))
      IsShow = false;

    if (IsShow == true)
    {
      //Объект типа "точка"
      if (Objects[i].Type == POINT_OBJ)
      {
        deltaX = 5.0;  //Половина размера объекта "точка" по оси X
        deltaY = 5.0;  //Половина размера объекта "точка" по оси Y

        static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
          Cartography->PZ90BLToScreenXY(Objects[i].Point.Point.B, Objects[i].Point.Point.L, &X, &Y);

        X1 = X - deltaX;
        Y1 = Y - deltaY;

        X2 = X + deltaX;
        Y2 = Y + deltaY;

        Rect.setCoords(X1, Y1, X2, Y2);

        //Круг - тип символа
        if (Objects[i].Point.Type == CIRCLE_SYMBOL)
        {
          Objects[i].HandlePointAsEllipse = static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
            Scene->addEllipse(Rect, *Objects[i].Point.Pen, *Objects[i].Point.Brush);
        }

        //Квадрат - тип символа
        if (Objects[i].Point.Type == RECT_SYMBOL)
        {
          Objects[i].HandlePointAsRect = static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
            Scene->addRect(Rect, *Objects[i].Point.Pen, *Objects[i].Point.Brush);
        }
      }

      //Объект типа "полилиния"
      if (Objects[i].Type == POLYLINE_OBJ)
      {
        Path = QPainterPath();  //Очистка объекта
        static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
          Cartography->PZ90BLToScreenXY(Objects[i].PolyLine.Spot[0].B, Objects[i].PolyLine.Spot[0].L, &X1, &Y1);
        Path.moveTo(X1, Y1);
        for(j=1;j<Objects[i].PolyLine.Spot.size();j++)
        {
          static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
            Cartography->PZ90BLToScreenXY(Objects[i].PolyLine.Spot[j].B, Objects[i].PolyLine.Spot[j].L, &X1, &Y1);
          Path.lineTo(X1, Y1);
        }
        Objects[i].HandlePolyLine = static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
          Scene->addPath(Path, *Objects[i].PolyLine.Pen, Brush);
      }

      //Объект типа "регион"
      if (Objects[i].Type == REGION_OBJ)
      {
        Polygon.clear();

        for(j=0;j<Objects[i].Region.Spot.size();j++)
        {
          static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
            Cartography->PZ90BLToScreenXY(Objects[i].Region.Spot[j].B, Objects[i].Region.Spot[j].L, &X, &Y);

          Point.setX(X);
          Point.setY(Y);

          Polygon.push_back(Point);
        }

        Objects[i].HandleRegion = static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->
            Scene->addPolygon(Polygon, *Objects[i].Region.Pen, *Objects[i].Region.Brush);
      }
    }  //if (IsShow == true)
  }  //Конец цикла по всем объектам слоя
  Polygon.clear();
}


TLayer::THemisphere TLayer::GetHemisphere(TMultitude::TSpot Spot)
{
TLayer::THemisphere res;
bool north, south;
unsigned int i;
  res = NONE_HEM;
  north = false;
  south = false;
  for(i=0;i<Spot.size();i++)
  {
    if (Spot[i].B >= 0.0)
      north = true;

    if (Spot[i].B <= 0.0)
      south = true;
  }

  if ((north == true) && (south == true))
  {
    res = BOTH_HEM;
    goto endd;
  }

  if (north == true)
  {
    res = NORTH_HEM;
    goto endd;
  }

  if (south == true)
  {
    res = SOUTH_HEM;
    goto endd;
  }

endd:

  return res;
}


bool TLayer::GetVisible()
{
  return Visible;
}


std::string TLayer::GetStringObj(QGraphicsItem *ID)
{
unsigned int i;
std::string res;
QString str;
  res = "";
  str = QString::fromStdString(Name);
  str = str.toUpper();

  for(i=0;i<Objects.size();i++)
  {
    if (static_cast<QGraphicsItem*>(Objects[i].HandlePointAsEllipse) == ID)
    {
      res = " " + str.toStdString() + ": " + Objects[i].Header.Name + " ";
      break;
    }

    if (static_cast<QGraphicsItem*>(Objects[i].HandlePointAsRect) == ID)
    {
      res = " " + str.toStdString() + ": " + Objects[i].Header.Name + " ";
      break;
    }

    if (static_cast<QGraphicsItem*>(Objects[i].HandleRegion) == ID)
    {
      res = " " + str.toStdString() + ": " + Objects[i].Header.Name + " ";
      break;
    }

    if (static_cast<QGraphicsItem*>(Objects[i].HandlePolyLine) == ID)
    {
      res = " " + str.toStdString() + ": " + Objects[i].Header.Name + " ";
      break;
    }
  }
  return res;
}

TLayer::THeaderOfObj TLayer::GetHeaderObj(QGraphicsItem *ID)
{
TLayer::THeaderOfObj res;
unsigned int i;
  res.ID = 0;
  res.Name = "[пусто]";
  for(i=0;i<Objects.size();i++)
  {
    if (static_cast<QGraphicsItem*>(Objects[i].HandlePointAsEllipse) == ID)
    {
      res = Objects[i].Header;
      break;
    }

    if (static_cast<QGraphicsItem*>(Objects[i].HandlePointAsRect) == ID)
    {
      res = Objects[i].Header;
      break;
    }

    if (static_cast<QGraphicsItem*>(Objects[i].HandleRegion) == ID)
    {
      res = Objects[i].Header;
      break;
    }

    if (static_cast<QGraphicsItem*>(Objects[i].HandlePolyLine) == ID)
    {
      res = Objects[i].Header;
      break;
    }
  }
  return res;
}


unsigned int TLayer::GetFreeID()
{
bool pr;
unsigned int i, j, res;
  res = 0;
  for(j=1;j<Objects.size()+2;j++)
  {
    res = j;
    pr = false;
    for(i=0;i<Objects.size();i++)
    if (res == Objects[i].Header.ID)
      pr = true;

    if (pr == false)
      goto endd;
  }
endd:
  return res;
}


TLayer::THeadersObjects TLayer::GetObjList()
{
TLayer::THeadersObjects res;
unsigned int i;
  res.clear();
  res.resize(Objects.size());
  for(i=0;i<Objects.size();i++)
  {
    res[i].ID = Objects[i].Header.ID;
    res[i].Name = Objects[i].Header.Name;
  }
  return res;
}


void TLayer::AddPointQuick(unsigned int ID, std::string Name, TLayer::TTypeSymbol Type, TMultitude::TOnePoint Point, QPen Pen, QBrush Brush)
{
TObj Obj;
QPen *_Pen;
QBrush *_Brush;
  if (Type != NONE_SYMBOL)
  {
    _Pen = new QPen(Pen);        //Динамическое создание объекта, являющегося копией заданного
    _Brush = new QBrush(Brush);  //Динамическое создание объекта, являющегося копией заданного

    Obj.Header.ID = ID;          //Идентификатор объекта
    Obj.Header.Name = Name;      //Наименование объекта

    if (Point.B <= 0.0)
      Obj.Hemisphere = SOUTH_HEM;

    if (Point.B >= 0.0)
      Obj.Hemisphere = NORTH_HEM;

    if (fabs(Point.B - 0.0) <= 0.000000001)
      Obj.Hemisphere = BOTH_HEM;

    Obj.Type = POINT_OBJ;        //Тип объекта
    Obj.Point.Type = Type;       //Тип символа, изображающего объект "точка"
    Obj.Point.Point = Point;     //Геодезические координаты объекта "точка"
    Obj.Point.Pen = _Pen;        //Перо для рисования объекта "точка"
    Obj.Point.Brush = _Brush;    //Заливка для рисования объекта "точка"

    Objects.push_back(Obj);
    _Pen = NULL;
    _Brush = NULL;
  }
}


bool TLayer::AddPoint(unsigned int ID, std::string Name, TLayer::TTypeSymbol Type, TMultitude::TOnePoint Point, QPen Pen, QBrush Brush)
{
bool res;
TObj Obj;
QPen *_Pen;
QBrush *_Brush;
unsigned int i;
  res = false;
  if (Type != NONE_SYMBOL)
  {
    res = true;
    for(i=0;i<Objects.size();i++)
    if (ID == Objects[i].Header.ID)
      res = false;

    if (res == true)
    {
      _Pen = new QPen(Pen);        //Динамическое создание объекта, являющегося копией заданного
      _Brush = new QBrush(Brush);  //Динамическое создание объекта, являющегося копией заданного

      Obj.Header.ID = ID;          //Идентификатор объекта
      Obj.Header.Name = Name;      //Наименование объекта

      if (Point.B <= 0.0)
        Obj.Hemisphere = SOUTH_HEM;

      if (Point.B >= 0.0)
        Obj.Hemisphere = NORTH_HEM;

      if (fabs(Point.B - 0.0) <= 0.000000001)
        Obj.Hemisphere = BOTH_HEM;

      Obj.Type = POINT_OBJ;        //Тип объекта
      Obj.Point.Type = Type;       //Тип символа, изображающего объект "точка"
      Obj.Point.Point = Point;     //Геодезические координаты объекта "точка"
      Obj.Point.Pen = _Pen;        //Перо для рисования объекта "точка"
      Obj.Point.Brush = _Brush;    //Заливка для рисования объекта "точка"

      Objects.push_back(Obj);
    }
    _Pen = NULL;
    _Brush = NULL;
  }
  return res;
}


void TLayer::AddPolyLineQuick(unsigned int ID, std::string Name, TMultitude::TSpot Spot, QPen Pen)
{
TObj Obj;
QPen *_Pen;
  if (Spot.size() > 1)
  {
    _Pen = new QPen(Pen);      //Динамическое создание объекта, являющегося копией заданного

    Obj.Header.ID = ID;        //Идентификатор объекта
    Obj.Header.Name = Name;    //Наименование объекта
    Obj.Hemisphere = GetHemisphere(Spot);
    Obj.Type = POLYLINE_OBJ;   //Тип объекта
    Obj.PolyLine.Spot = Spot;  //Массив узловых точек
    Obj.PolyLine.Pen = _Pen;   //Перо для рисования объекта "полилиния"

    Objects.push_back(Obj);
  }
  _Pen = NULL;
}


bool TLayer::AddPolyLine(unsigned int ID, std::string Name, TMultitude::TSpot Spot, QPen Pen)
{
bool res;
TObj Obj;
QPen *_Pen;
unsigned int i;
  res = true;
  for(i=0;i<Objects.size();i++)
  if (ID == Objects[i].Header.ID)
    res = false;

  if (Spot.size() <= 1)
    res = false;

  if (res == true)
  {
    _Pen = new QPen(Pen);      //Динамическое создание объекта, являющегося копией заданного

    Obj.Header.ID = ID;        //Идентификатор объекта
    Obj.Header.Name = Name;    //Наименование объекта
    Obj.Hemisphere = GetHemisphere(Spot);
    Obj.Type = POLYLINE_OBJ;   //Тип объекта
    Obj.PolyLine.Spot = Spot;  //Массив узловых точек
    Obj.PolyLine.Pen = _Pen;   //Перо для рисования объекта "полилиния"

    Objects.push_back(Obj);
  }
  _Pen = NULL;
  return res;
}


void TLayer::AddRegionQuick(unsigned int ID, std::string Name, TMultitude::TSpot Spot, QPen Pen, QBrush Brush)
{
TObj Obj;
QPen *_Pen;
QBrush *_Brush;
  if (Spot.size() > 2)
  {
    _Pen = new QPen(Pen);        //Динамическое создание объекта, являющегося копией заданного
    _Brush = new QBrush(Brush);  //Динамическое создание объекта, являющегося копией заданного

    Obj.Header.ID = ID;          //Идентификатор объекта
    Obj.Header.Name = Name;      //Наименование объекта
    Obj.Hemisphere = GetHemisphere(Spot);
    Obj.Type = REGION_OBJ;       //Тип объекта
    Obj.Region.Spot = Spot;      //Массив узловых точек
    Obj.Region.Pen = _Pen;       //Перо для рисования объекта "регион"
    Obj.Region.Brush = _Brush;   //Заливка для рисования объекта "регион"

    Objects.push_back(Obj);
  }
  _Pen = NULL;
  _Brush = NULL;
}


bool TLayer::AddRegion(unsigned int ID, std::string Name, TMultitude::TSpot Spot, QPen Pen, QBrush Brush)
{
bool res;
TObj Obj;
QPen *_Pen;
QBrush *_Brush;
unsigned int i;
  res = true;
  for(i=0;i<Objects.size();i++)
  if (ID == Objects[i].Header.ID)
    res = false;

  if (Spot.size() <= 2)
    res = false;

  if (res == true)
  {
    _Pen = new QPen(Pen);        //Динамическое создание объекта, являющегося копией заданного
    _Brush = new QBrush(Brush);  //Динамическое создание объекта, являющегося копией заданного

    Obj.Header.ID = ID;          //Идентификатор объекта
    Obj.Header.Name = Name;      //Наименование объекта
    Obj.Hemisphere = GetHemisphere(Spot);
    Obj.Type = REGION_OBJ;       //Тип объекта
    Obj.Region.Spot = Spot;      //Массив узловых точек
    Obj.Region.Pen = _Pen;       //Перо для рисования объекта "регион"
    Obj.Region.Brush = _Brush;   //Заливка для рисования объекта "регион"

    Objects.push_back(Obj);
  }
  _Pen = NULL;
  _Brush = NULL;
  return res;
}


bool TLayer::DelObj(unsigned int ID)
{
bool res;
unsigned int i, j;
TObjects Temp;
  res = false;
  for(i=0;i<Objects.size();i++)
  if (ID == Objects[i].Header.ID)
  {
    res = true;
    //Точка
    if (Objects[i].Type == POINT_OBJ)
    {
      //Круг
      if (Objects[i].Point.Type == CIRCLE_SYMBOL)
      {
        if (Objects[i].HandlePointAsEllipse != NULL)
          static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandlePointAsEllipse);
        Objects[i].HandlePointAsEllipse = NULL;
      }

      //Квадрат
      if (Objects[i].Point.Type == RECT_SYMBOL)
      {
        if (Objects[i].HandlePointAsRect != NULL)
          static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandlePointAsRect);
        Objects[i].HandlePointAsRect = NULL;
      }
    }

    //Полилиния
    if (Objects[i].Type == POLYLINE_OBJ)
    {
      if (Objects[i].HandlePolyLine != NULL)
        static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandlePolyLine);
      Objects[i].HandlePolyLine = NULL;
    }

    //Регион
    if (Objects[i].Type == REGION_OBJ)
    {
      if (Objects[i].HandleRegion != NULL)
        static_cast<TGISLib*>((static_cast<TMapData*>(OWNER))->OWNER)->Scene->removeItem(Objects[i].HandleRegion);
      Objects[i].HandleRegion = NULL;
    }
    //Убрал с карты объект

    Objects[i].HandlePointAsEllipse = NULL;
    Objects[i].HandlePointAsRect = NULL;
    Objects[i].HandleRegion = NULL;
    Objects[i].HandlePolyLine = NULL;

    Objects[i].Header.ID = 0;
    Objects[i].Header.Name = "";
    Objects[i].Hemisphere = NONE_HEM;
    Objects[i].Type = NONE_OBJ;
    Objects[i].Point.Type = NONE_SYMBOL;

    if (Objects[i].Point.Pen != NULL)
      delete Objects[i].Point.Pen;

    if (Objects[i].Point.Brush != NULL)
      delete Objects[i].Point.Brush;

    Objects[i].PolyLine.Spot.clear();

    if (Objects[i].PolyLine.Pen != NULL)
      delete Objects[i].PolyLine.Pen;

    Objects[i].Region.Spot.clear();

    if (Objects[i].Region.Pen != NULL)
      delete Objects[i].Region.Pen;

    if (Objects[i].Region.Brush != NULL)
      delete Objects[i].Region.Brush;
    //Освободил занимаемую память

    Temp.clear();
    for(j=0;j<Objects.size();j++)
    if (j != i)
      Temp.push_back(Objects[j]);

    for(j=0;j<Objects.size();j++)
    {
      Objects[j].PolyLine.Spot.clear();
      Objects[j].Region.Spot.clear();
    }
    Objects.clear();

    for(j=0;j<Temp.size();j++)
      Objects.push_back(Temp[j]);

    break;
  }

  for(j=0;j<Temp.size();j++)
  {
    Temp[j].PolyLine.Spot.clear();
    Temp[j].Region.Spot.clear();
  }
  Temp.clear();

  return res;
}
