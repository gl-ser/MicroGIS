//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл MapData.cpp                                                           //
//                                                                            //
//                  *** TMAPDATA КАРТОГРАФИЧЕСКИЕ ДАННЫЕ ***                  //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QApplication>
#include <QFile>
#include "MapData.h"
#include "GISLib.h"


TMapData::TMapData(void)
{
  OWNER = NULL;

  ShowFrame = false;
  ShowGrid15 = false;

  //Рамка карты и 15-градусная сетка
  Frame = new TFrame();
  Frame->OWNER = this;

  Layers.clear();
}


TMapData::~TMapData(void)
{
unsigned int i;

  for(i=0;i<Layers.size();i++)
    delete (Layers[i]);

  Layers.clear();

  delete Frame;

  OWNER = NULL;
}


QString TMapData::GetStringHintUnderCursor(QList<QGraphicsItem *> Arr)
{
int i, j;
std::string str;
QString res;
  res = "";
  for(i=static_cast<int>(Layers.size()-1);i>=0;i--)
  for(j=0;j<Arr.size();j++)
  {
    str = Layers[static_cast<unsigned int>(i)]->GetStringObj(Arr[j]);
    if (str != "")
    {
      if (res != "")
        res = res + '\n' + QString::fromStdString(str);
      else
        res = QString::fromStdString(str);
    }
  }
  if (res == "")
    res = "[пусто]";
  return res;
}


TMapData::TObjList TMapData::GetObjListUnderCursor(QList<QGraphicsItem *> Arr)
{
int i, j;
TMapData::TObjList res;
TLayer::THeaderOfObj Header;
  res.clear();
  for(i=static_cast<int>(Layers.size()-1);i>=0;i--)
  for(j=0;j<Arr.size();j++)
  {
    Header = Layers[static_cast<unsigned int>(i)]->GetHeaderObj(Arr[j]);

    if ((Header.ID != 0) && (Header.Name != "[пусто]"))
    {
      res.resize(res.size()+1);
      res[res.size()-1].LayerName = Layers[static_cast<unsigned int>(i)]->Name;
      res[res.size()-1].ObjID = Header.ID;
      res[res.size()-1].ObjName = Header.Name;
    }
  }
  return res;
}


void TMapData::CoolRePaint()
{
unsigned int i;
  for(i=0;i<Layers.size();i++)
    Layers[i]->CoolRePaint();

  if (ShowFrame == true)
  {
    Frame->RePaint();
  }

  if (ShowGrid15 == true)
  {
    Frame->RePaintGrid();
  }
}


void TMapData::RePaint()
{
unsigned int i;
  for(i=0;i<Layers.size();i++)
    Layers[i]->RePaint();

  if (ShowFrame == true)
  {
    Frame->RePaint();
  }

  if (ShowGrid15 == true)
  {
    Frame->RePaintGrid();
  }
}


void TMapData::WhatIsShow(bool _Frame, bool _Grid15)
{
  ShowFrame = _Frame;
  ShowGrid15 = _Grid15;

  if (ShowFrame == false)
  {
    Frame->Del();
  }

  if (ShowGrid15 == false)
  {
    Frame->DelGrid();
  }

  RePaint();
}


TMapData::TLayerList TMapData::GetLayerList()
{
TMapData::TLayerList res;
unsigned int i;
  res.clear();
  res.resize(Layers.size());
  for(i=0;i<Layers.size();i++)
  {
    res[i].Name = Layers[i]->Name;
    res[i].Visible = Layers[i]->GetVisible();
  }
  return res;
}


int TMapData::FindLayer(std::string Name)
{
int res;
unsigned int i;
  res = -1;
  for(i=0;i<Layers.size();i++)
  if (Layers[i]->Name == Name)
  {
    res = static_cast<int>(i);
    break;
  }
  return res;
}


bool TMapData::ShowLayer(std::string Name)
{
int index;
bool res;
  index = FindLayer(Name);
  if (index != -1)
  {
    Layers[static_cast<unsigned int>(index)]->Show();
    res = true;
  }
  else
  {
    res = false;
  }
  return res;
}


bool TMapData::HideLayer(std::string Name)
{
int index;
bool res;
  index = FindLayer(Name);
  if (index != -1)
  {
    Layers[static_cast<unsigned int>(index)]->Hide();
    res = true;
  }
  else
  {
    res = false;
  }
  return res;
}


bool TMapData::AddLayer(std::string Name)
{
int index;
bool res;
TLayer* Layer;
  index = FindLayer(Name);
  if (index == -1)
  {
    Layer = new TLayer();
    Layer->Name = Name;
    Layer->OWNER = this;

    Layers.push_back(Layer);

    Layer = NULL;

    res = true;
  }
  else
  {
    res = false;
  }
  return res;
}


bool TMapData::DelLayer(std::string Name)
{
int index;
bool res;
unsigned int i;
std::vector<TLayer*> Temp;
  index = FindLayer(Name);
  if (index != -1)
  {
    delete (Layers[static_cast<unsigned int>(index)]);

    Temp.clear();
    for(i=0;i<Layers.size();i++)
    if (i != static_cast<unsigned int>(index))
      Temp.push_back(Layers[i]);

    Layers.clear();
    for(i=0;i<Temp.size();i++)
      Layers.push_back(Temp[i]);

    res = true;
  }
  else
  {
    res = false;
  }

  Temp.clear();
  return res;
}


void TMapData::DelAllUserLayers()
{
unsigned int i;

beginn:

  for(i=0; i<Layers.size(); i++)
  if ((Layers[i]->Name != "моря") && (Layers[i]->Name != "континенты") && (Layers[i]->Name != "границы") &&
      (Layers[i]->Name != "озера") && (Layers[i]->Name != "реки"))
  {
    DelLayer(Layers[i]->Name);
    goto beginn;
  }
  RePaint();
}


bool TMapData::AddLayerFromMIF(std::string LayerName, std::string FilePathName)
{
bool res;
int i, type, size, sub_size;
int PenWidthMI, PenPatternMI, PenColorMI, BrushPatternMI, BrushColorMI;
unsigned int ii, LayerID, ObjID;
QFile mif_file;
QTextStream *mif;
QString str;
TMultitude::TArraySpot Arr;
TMultitude::TSpot Spot;
QPen Pen;
QBrush Brush;
  Arr.clear();
  Spot.clear();
  mif_file.setFileName(QString::fromStdString(FilePathName));
  res = mif_file.open(QIODevice::ReadOnly);
  if (res == true)
  {  //Успешное открытие MIF-файла на чтение
    mif = new QTextStream(&mif_file);
    res = AddLayer(LayerName);
    if (res == true)
    {  //Успешное добавление пустого слоя
      LayerID = static_cast<unsigned int>(FindLayer(LayerName));
      res = ReadHeader(mif);
      if (res == true)
      {  //Заголовок файла успешно считан
        ObjID = 1;
        //Цикл по всем строкам файла
        while (!mif->atEnd())
        {
          FindGeometryObj(mif, &type, &size);

          if (type == 1)
          {  //Объект - регион
            for(ii=0;ii<Arr.size();ii++)
              Arr[ii].spot.clear();
            Arr.clear();
            Arr.resize(static_cast<unsigned int>(size));

            //Цикл по всем контурам региона. size - кол-во контуров у региона
            for(i=1;i<=size;i++)
            {
              sub_size = ReadInt(mif);  //Кол-во точек в i-м контуре региона
              Spot = ReadPoints(mif, sub_size);

              Arr[static_cast<unsigned int>(i-1)].spot = Spot;
            }

            ReadPen(mif, &PenWidthMI, &PenPatternMI, &PenColorMI);
            ReadBrush(mif, &BrushPatternMI, &BrushColorMI);

            Pen = Layers[LayerID]->PenMIToQPen(PenWidthMI, PenPatternMI, PenColorMI);
            Brush = Layers[LayerID]->BrushMIToQBrush(BrushPatternMI, BrushColorMI);

            for(ii=0;ii<Arr.size();ii++)
            {
              Layers[LayerID]->AddRegionQuick(ObjID, "Регион из MIF-файла", Arr[ii].spot, Pen, Brush);
              ObjID++;
              qApp->processEvents();
            }
          }

          if (type == 2)
          {  //Объект - полилиния
            Spot = ReadPoints(mif, size);

            ReadPen(mif, &PenWidthMI, &PenPatternMI, &PenColorMI);

            Pen = Layers[LayerID]->PenMIToQPen(PenWidthMI, PenPatternMI, PenColorMI);

            Layers[LayerID]->AddPolyLineQuick(ObjID, "Полилиния из MIF-файла", Spot, Pen);
            ObjID++;
            qApp->processEvents();
          }

        }  //Конец цикла по всем строкам файла
      }  //Заголовок файла успешно считан
    }  //Успешное добавление пустого слоя
    delete mif;
    mif_file.close();
  }

  Spot.clear();
  for(ii=0;ii<Arr.size();ii++)
    Arr[ii].spot.clear();
  Arr.clear();

  return res;
}


bool TMapData::AddLayerDynamicPoint()
{
bool res;
int id;
std::string Name;
  Name = "динам_точки";
  id = FindLayer(Name);
  if (id != -1)
  {  //Слой ранее уже был создан
    DelLayer(Name);
  }
  res = AddLayer(Name);
  return res;
}


bool TMapData::ReadHeader(QTextStream *mif)
{
QString str;
bool res;
  res = false;  //Файл ломаный, заголовка нет
  while (!mif->atEnd())
  {
    str = mif->readLine();  //Текущая строка из файла
    str = str.trimmed();
    str = str.toLower();
    if (str == "data")
    {
      res = true;  //Заголовок успешно считан
      break;
    }
  }
  return res;
}


void TMapData::FindGeometryObj(QTextStream *mif, int *type, int *size)
{
QString str, str1, str2, str3;
  *type = 0;
  *size = 0;
  while (!mif->atEnd())
  {
    str = mif->readLine();  //Текущая строка из файла
    str = str.trimmed();
    str = str.toLower();
    str1 = str.mid(0, 6);
    str2 = str.mid(0, 5);

    if (str1 == "region")
    if (str.length() >= 8)
    {
      str3 = str.mid(6);
      str3 = str3.trimmed();
      if (str3.length() > 0)
      {
        *type = 1;
        *size = str3.toInt();
        if (*size < 1)
        {
          *type = 0;
          *size = 0;
        }
        else
        {
          break;
        }
      }
    }

    if (str2 == "pline")
    if (str.length() >= 7)
    {
      str3 = str.mid(5);
      str3 = str3.trimmed();
      if (str3.length() > 0)
      {
        *type = 2;
        *size = str3.toInt();
        if (*size < 1)
        {
          *type = 0;
          *size = 0;
        }
        else
        {
          break;
        }
      }
    }
  }
}


int TMapData::ReadInt(QTextStream *mif)
{
QString str;
int res;
  res = 0;
  while (!mif->atEnd())
  {
    str = mif->readLine();  //Текущая строка из файла
    str = str.trimmed();
    str = str.toLower();

    res = str.toInt();
    if (res >= 1)
    {
      break;
    }
  }
  return res;
}


TMultitude::TSpot TMapData::ReadPoints(QTextStream *mif, int quantity)
{
int i;
QString str;
TMultitude::TSpot res;
QStringList list;
TMultitude::TOnePoint point;
  res.clear();
  i = 0;
  while (!mif->atEnd())
  {
    i++;
    str = mif->readLine();  //Текущая строка из файла
    str = str.trimmed();

    if (str != "")
    {
      list.clear();
      list = str.split(' ');

      if (list.size() == 2)
      {
        point.L = list[0].toDouble();
        point.B = list[1].toDouble();

        point.B = point.B * M_PI/180.0;
        point.L = point.L * M_PI/180.0;

        res.push_back(point);
      }

      if (i == quantity)
      {
        break;
      }
    }
  }
  list.clear();
  return res;
}


void TMapData::ReadPen(QTextStream *mif, int *WidthMI, int *PatternMI, int *ColorMI)
{
QString str, str1, str3;
QStringList list;
  while (!mif->atEnd())
  {
    str = mif->readLine();  //Текущая строка из файла
    str = str.trimmed();
    str = str.toLower();

    str1 = str.mid(0, 3);

    if (str1 == "pen")
    if (str.length() >= 10)
    {
      str3 = str.mid(3);
      str3 = str3.trimmed();
      if (str3.length() > 0)
      {
        str1 = str3.mid(1, str3.length()-2);
        str1 = str1.trimmed();

        list.clear();
        list = str1.split(',');

        if (list.size() == 3)
        {
          *WidthMI = list[0].toInt();
          *PatternMI = list[1].toInt();
          *ColorMI = list[2].toInt();
          break;
        }
      }
    }
  }
  list.clear();
}


void TMapData::ReadBrush(QTextStream *mif, int *PatternMI, int *ColorMI)
{
QString str, str1, str3;
QStringList list;
  while (!mif->atEnd())
  {
    str = mif->readLine();  //Текущая строка из файла
    str = str.trimmed();
    str = str.toLower();

    str1 = str.mid(0, 5);

    if (str1 == "brush")
    if (str.length() >= 10)
    {
      str3 = str.mid(5);
      str3 = str3.trimmed();
      if (str3.length() > 0)
      {
        str1 = str3.mid(1, str3.length()-2);
        str1 = str1.trimmed();

        list.clear();
        list = str1.split(',');

        if ((list.size() == 2) || (list.size() == 3))
        {
          *PatternMI = list[0].toInt();
          *ColorMI = list[1].toInt();
          break;
        }
      }
    }
  }
  list.clear();
}


unsigned int TMapData::GetFreeID(std::string Name)
{
int index;
unsigned int res;
  index = FindLayer(Name);
  if (index != -1)
  {
    res = Layers[static_cast<unsigned int>(index)]->GetFreeID();
  }
  else
  {
    res = 1;
  }
  return res;
}


TLayer::THeadersObjects TMapData::GetObjList(std::string Name)
{
int index;
TLayer::THeadersObjects res;
  res.clear();
  index = FindLayer(Name);
  if (index != -1)
  {
    res = Layers[static_cast<unsigned int>(index)]->GetObjList();
  }
  return res;
}


bool TMapData::AddInDynamicPoint(unsigned int ID, std::string Comment, TMultitude::TOnePoint Point, int ColorMI)
{
int id;
bool res;
std::string Name;
QPen Pen;
QBrush Brush;
  res = false;
  if (Point.L > M_PI)
    Point.L = Point.L - 2.0*M_PI;

  Name = "динам_точки";
  id = FindLayer(Name);
  if (id != -1)
  {
    Pen = Layers[static_cast<unsigned int>(id)]->PenMIToQPen(1, 2, 0);
    Brush = Layers[static_cast<unsigned int>(id)]->BrushMIToQBrush(2, ColorMI);

    Layers[static_cast<unsigned int>(id)]->AddPointQuick(ID, Comment, TLayer::TTypeSymbol::CIRCLE_SYMBOL, Point, Pen, Brush);
    res = true;
  }

  return res;
}


void TMapData::MoveInDynamicPoint(unsigned int ID, std::string Comment, TMultitude::TOnePoint Point)
{
int id;
bool IsShow;  //Признак: объект надо отрисовывать (true), или не надо отрисовывать (false)
unsigned int i;
double deltaX, deltaY, X, Y, X1, Y1, X2, Y2;
std::string Name;
QRectF Rect;
  Name = "динам_точки";
  id = FindLayer(Name);
  if (id != -1)
  if (Layers[static_cast<unsigned int>(id)]->GetVisible() == true)
  {
    for(i=0; i<Layers[static_cast<unsigned int>(id)]->Objects.size(); i++)
    if (ID == Layers[static_cast<unsigned int>(id)]->Objects[i].Header.ID)
    if (Layers[static_cast<unsigned int>(id)]->Objects[i].Type == TLayer::TTypeObj::POINT_OBJ)
    {
      if (Point.L > M_PI)
        Point.L = Point.L - 2.0*M_PI;

      Layers[static_cast<unsigned int>(id)]->Objects[i].Point.Point = Point;

      if (Point.B <= 0.0)
        Layers[static_cast<unsigned int>(id)]->Objects[i].Hemisphere = TLayer::THemisphere::SOUTH_HEM;

      if (Point.B >= 0.0)
        Layers[static_cast<unsigned int>(id)]->Objects[i].Hemisphere = TLayer::THemisphere::NORTH_HEM;

      if (fabs(Point.B - 0.0) <= 0.000000001)
        Layers[static_cast<unsigned int>(id)]->Objects[i].Hemisphere = TLayer::THemisphere::BOTH_HEM;

      IsShow = true;

      if (static_cast<TGISLib*>(OWNER)->Projection.Number == TGISLib::NORTHPOLE)
      if ((Layers[static_cast<unsigned int>(id)]->Objects[i].Hemisphere != TLayer::THemisphere::NORTH_HEM) &&
          (Layers[static_cast<unsigned int>(id)]->Objects[i].Hemisphere != TLayer::THemisphere::BOTH_HEM))
        IsShow = false;

      if (static_cast<TGISLib*>(OWNER)->Projection.Number == TGISLib::SOUTHPOLE)
      if ((Layers[static_cast<unsigned int>(id)]->Objects[i].Hemisphere != TLayer::THemisphere::SOUTH_HEM) &&
          (Layers[static_cast<unsigned int>(id)]->Objects[i].Hemisphere != TLayer::THemisphere::BOTH_HEM))
        IsShow = false;

      if (IsShow == true)
      {
        Layers[static_cast<unsigned int>(id)]->Objects[i].Header.Name = Comment;

        deltaX = 5.0;  //Половина размера объекта "точка" по оси X
        deltaY = 5.0;  //Половина размера объекта "точка" по оси Y

        static_cast<TGISLib*>(OWNER)->Cartography->PZ90BLToScreenXY(Point.B, Point.L, &X, &Y);

        X1 = X - deltaX;
        Y1 = Y - deltaY;

        X2 = X + deltaX;
        Y2 = Y + deltaY;

        Rect.setCoords(X1, Y1, X2, Y2);

        Layers[static_cast<unsigned int>(id)]->Objects[i].HandlePointAsEllipse->setRect(Rect);
      }
      break;
    }
  }
}


bool TMapData::AddPointInLayer(std::string Name, unsigned int ID, std::string ObjName, TLayer::TTypeSymbol Type,
                               TMultitude::TOnePoint Point, QPen Pen, QBrush Brush)
{
int index;
bool res;
  if (Point.L > M_PI)
    Point.L = Point.L - 2.0*M_PI;

  index = FindLayer(Name);
  if (index != -1)
  {
    res = Layers[static_cast<unsigned int>(index)]->AddPoint(ID, ObjName, Type, Point, Pen, Brush);
  }
  else
  {
    res = false;
  }
  return res;
}


bool TMapData::AddPolyLineInLayer(std::string Name, unsigned int ID, std::string ObjName, TMultitude::TSpot Spot, QPen Pen)
{
unsigned int i;
int index;
bool res;
  for(i=0;i<Spot.size();i++)
  if (Spot[i].L > M_PI)
    Spot[i].L = Spot[i].L - 2.0*M_PI;

  index = FindLayer(Name);
  if (index != -1)
  {
    res = Layers[static_cast<unsigned int>(index)]->AddPolyLine(ID, ObjName, Spot, Pen);
  }
  else
  {
    res = false;
  }
  return res;
}


bool TMapData::AddRegionInLayer(std::string Name, unsigned int ID, std::string ObjName, TMultitude::TSpot Spot, QPen Pen, QBrush Brush)
{
unsigned int i;
int index;
bool res;
  for(i=0;i<Spot.size();i++)
  if (Spot[i].L > M_PI)
    Spot[i].L = Spot[i].L - 2.0*M_PI;

  index = FindLayer(Name);
  if (index != -1)
  {
    res = Layers[static_cast<unsigned int>(index)]->AddRegion(ID, ObjName, Spot, Pen, Brush);
  }
  else
  {
    res = false;
  }
  return res;
}


bool TMapData::DelObjFromLayer(std::string Name, unsigned int ID)
{
int index;
bool res;
  index = FindLayer(Name);
  if (index != -1)
  {
    res = Layers[static_cast<unsigned int>(index)]->DelObj(ID);
  }
  else
  {
    res = false;
  }
  return res;
}
