//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл ShellGIS.cpp                                                          //
//                                                                            //
//         *** TSHELLGIS ОБОЛОЧКА ДВИЖКА ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***        //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include "ShellGIS.h"


TShellGIS::TShellGIS(void)
{
  //Подключение сигнала к сигналу, а не к слоту
  connect(this, SIGNAL(GetDataLeftMouse(TGISLib::TDataLeftMouse)), this, SIGNAL(GetDataLeftMouseARROW(TGISLib::TDataLeftMouse)));
}



TShellGIS::~TShellGIS(void)
{
  disconnect();
}


void TShellGIS::SetProjection(TGISLib::TProj Value)
{
TProjection Proj;  //Проекция-пустышка (не установлена)

  switch (Value)
  {
    //Цилиндрическая равнопромежуточная проекция Плате-Карре
    case CYLINDRICAL:
      Projection.Number = Value;
      Projection.Fi0 = 0.0;
      Projection.L0 =  0.0;
      Projection.Map.Xmin = -180.0;
      Projection.Map.Xmax = 180.0;
      Projection.Map.Ymin = -90.0;
      Projection.Map.Ymax = 90.0;
    break;

    //Азимутальная ортографическая проекция Северного Полюса
    case NORTHPOLE:
      Projection.Number = Value;
      Projection.Fi0 = 90.0;
      Projection.L0 = 0.0;
      Projection.Map.Xmin = -Cartography->RZEkv;
      Projection.Map.Xmax = Cartography->RZEkv;
      Projection.Map.Ymin = -Cartography->RZEkv;
      Projection.Map.Ymax = Cartography->RZEkv;
    break;

    //Азимутальная ортографическая проекция Южного Полюса
    case SOUTHPOLE:
      Projection.Number = Value;
      Projection.Fi0 = -90.0;
      Projection.L0 = 0.0;
      Projection.Map.Xmin = -Cartography->RZEkv;
      Projection.Map.Xmax = Cartography->RZEkv;
      Projection.Map.Ymin = -Cartography->RZEkv;
      Projection.Map.Ymax = Cartography->RZEkv;
    break;

    //Равноугольная цилиндрическая проекция Меркатора
    case MERCATOR:
      Projection.Number = Value;
      Projection.Fi0 = 0.0;
      Projection.L0 =  0.0;
      Projection.Map.Xmin = -M_PI*Cartography->RZEkv;
      Projection.Map.Xmax = M_PI*Cartography->RZEkv;
      Projection.Map.Ymin = -M_PI*Cartography->RZEkv;
      Projection.Map.Ymax = M_PI*Cartography->RZEkv;
    break;

    //Псевдоцилиндрическая проекция Каврайского
    case KAVRAYSKIY:
      Projection.Number = Value;
      Projection.Fi0 = 0.0;
      Projection.L0 =  0.0;
      Projection.Map.Xmin = -sqrt(3.0)*M_PI/2.0;
      Projection.Map.Xmax = sqrt(3.0)*M_PI/2.0;
      Projection.Map.Ymin = -M_PI/2.0;
      Projection.Map.Ymax = M_PI/2.0;
    break;

    //Проекция-пустышка
    case NONEPROJECTION:
      Projection.Number = Value;
      Projection.Fi0 = 0.0;
      Projection.L0 =  0.0;
      Projection.Map.Xmin = 0.0;
      Projection.Map.Xmax = 0.0;
      Projection.Map.Ymin = 0.0;
      Projection.Map.Ymax = 0.0;
    break;
  }

  if (Layout == NULL)
  {
    Projection = Proj;  //Если нет подключения к окну, тогда и проекцию не устанавливать (установить пустышку)
  }

  NormalizeScale();  //Нормализовать масштаб при изменении проекции

  MapData->CoolRePaint();
}


void TShellGIS::ConnectWindow(QGridLayout *FLayout, QLabel *FCurCoord, QLabel* FScale, QLabel* FRuler)
{
  if (Layout == NULL)
  {
    Layout = FLayout;
    Layout->addWidget(View);
    CurCoord = FCurCoord;
    CurrentScale = FScale;
    Ruler = FRuler;
  }
}


void TShellGIS::DisconnectWindow()
{
  if (Layout != NULL)
  {
    Layout->removeWidget(View);
    View->setParent(Q_NULLPTR);
    Layout = NULL;
    CurCoord = NULL;
    CurrentScale = NULL;
  }
}


void TShellGIS::ShowAllMap()
{
  NormalizeScale();
}


void TShellGIS::SetTool(TView::TTool Value)
{
  SetCurrentTool(Value);
}


TView::TTool TShellGIS::GetTool()
{
  return GetCurrentTool();
}


void TShellGIS::WhatIsShow(bool Frame, bool Grid15)
{
  MapData->WhatIsShow(Frame, Grid15);
}


void TShellGIS::RePaint()
{
  MapData->CoolRePaint();
}


TMapData::TLayerList TShellGIS::GetLayerList()
{
  return MapData->GetLayerList();
}


bool TShellGIS::FindLayer(std::string Name)
{
int res1;
bool res2;
  res1 = MapData->FindLayer(Name);
  if (res1 == -1)
  {
    res2 = false;
  }
  else
  {
    res2 = true;
  }
  return res2;
}


bool TShellGIS::ShowLayer(std::string Name)
{
  return MapData->ShowLayer(Name);
}


bool TShellGIS::HideLayer(std::string Name)
{
  return MapData->HideLayer(Name);
}


bool TShellGIS::AddLayer(std::string Name)
{
  return MapData->AddLayer(Name);
}


bool TShellGIS::DelLayer(std::string Name)
{
  return MapData->DelLayer(Name);
}


void TShellGIS::DelAllUserLayers()
{
  MapData->DelAllUserLayers();
}


bool TShellGIS::AddLayerFromMIF(std::string LayerName, std::string FilePathName)
{
  return MapData->AddLayerFromMIF(LayerName, FilePathName);
}


bool TShellGIS::AddLayerDynamicPoint()
{
  return MapData->AddLayerDynamicPoint();
}


unsigned int TShellGIS::GetFreeID(std::string Name)
{
  return MapData->GetFreeID(Name);
}


TLayer::THeadersObjects TShellGIS::GetObjList(std::string Name)
{
  return MapData->GetObjList(Name);
}


bool TShellGIS::AddInDynamicPoint(unsigned int ID, std::string Comment, TMultitude::TOnePoint Point, int ColorMI)
{
  return MapData->AddInDynamicPoint(ID, Comment, Point, ColorMI);
}


void TShellGIS::MoveInDynamicPoint(unsigned int ID, std::string Comment, TMultitude::TOnePoint Point)
{
  MapData->MoveInDynamicPoint(ID, Comment, Point);
}


bool TShellGIS::AddPointInLayer(std::string Name, unsigned int ID, std::string ObjName, TLayer::TTypeSymbol Type,
                                TMultitude::TOnePoint Point, QPen Pen, QBrush Brush)
{
  return MapData->AddPointInLayer(Name, ID, ObjName, Type, Point, Pen, Brush);
}


bool TShellGIS::AddPolyLineInLayer(std::string Name, unsigned int ID, std::string ObjName, TMultitude::TSpot Spot, QPen Pen)
{
  return MapData->AddPolyLineInLayer(Name, ID, ObjName, Spot, Pen);
}


bool TShellGIS::AddRegionInLayer(std::string Name, unsigned int ID, std::string ObjName, TMultitude::TSpot Spot, QPen Pen, QBrush Brush)
{
  return MapData->AddRegionInLayer(Name, ID, ObjName, Spot, Pen, Brush);
}


bool TShellGIS::DelObjFromLayer(std::string Name, unsigned int ID)
{
  return MapData->DelObjFromLayer(Name, ID);
}
