//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл MapData.h                                                             //
//                                                                            //
//                  *** TMAPDATA КАРТОГРАФИЧЕСКИЕ ДАННЫЕ ***                  //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef MapDataH
#define MapDataH

#include <QTextStream>
#include "Frame.h"
#include "Layer.h"


class TMapData
{
  private:
    bool ShowFrame;   //Рамку карты рисовать или нет
    bool ShowGrid15;  //15-градусную сетку рисовать или нет

    //Рамка карты и 15-градусная сетка
    TFrame* Frame;

    //Набор слоев
    std::vector<TLayer*> Layers;

    //Тип описывает пару объектов "перо" и "заливка"
    struct PenBrush
    {
      PenBrush() : Pen(NULL), Brush(NULL) {}
      QPen* Pen;
      QBrush* Brush;
    };
    typedef struct PenBrush TPenBrush;

    //Тип описывает параметры визуализации различных объектов из оперативного каталога
    struct OpCat
    {
      OpCat() : Name(""), ID(-1) {}
      std::string Name;       //Название слоя с оперативным каталогом
      int ID;                 //Идентификатор слоя (индекс в массиве слоев)
      TPenBrush PointSimple;  //Отображение простого точечного объекта
      TPenBrush PointCool;    //Отображение волевого точечного объекта
      TPenBrush AreaSimple;   //Отображение простого площадного объекта
      TPenBrush AreaCool;     //Отображение волевого площадного объекта
    };
    typedef struct OpCat TOpCat;

    //Тип описывает параметры визуализации различных маршрутов
    struct Route
    {
      Route() : Name(""), ID(-1) {}
      std::string Name;       //Название слоя с маршрутами
      int ID;                 //Идентификатор слоя (индекс в массиве слоев)
      TPenBrush RouteSimple;  //Отображение простого маршрута
    };
    typedef struct Route TRoute;

    //Тип описывает параметры визуализации различных трасс полета
    struct Trass
    {
      Trass() : Name(""), ID(-1), Index(-1), Pen(NULL) {}
      std::string Name;  //Название слоя с трассами
      int ID;            //Идентификатор слоя (индекс в массиве слоев)
      int Index;         //Номер слоя с трассами (номер уникален среди слоев с трассами)
      QPen* Pen;         //Отображение простой трассы
    };
    typedef struct Trass TTrass;

    //Тип описывает параметры визуализации различных полос обзора
    struct Strip
    {
      Strip() : Name(""), ID(-1), Index(-1), Pen(NULL) {}
      std::string Name;  //Название слоя с полосами обзора
      int ID;            //Идентификатор слоя (индекс в массиве слоев)
      int Index;         //Номер слоя с полосами обзора (номер уникален среди слоев с полосами обзора)
      QPen* Pen;         //Отображение простой полосы обзора
    };
    typedef struct Strip TStrip;

    //Тип описывает параметры визуализации различных ЗРВ
    struct ZRV
    {
      ZRV() : Name(""), ID(-1), Index(-1), Pen(NULL) {}
      std::string Name;  //Название слоя с ЗРВ
      int ID;            //Идентификатор слоя (индекс в массиве слоев)
      int Index;         //Номер слоя с ЗРВ (номер уникален среди слоев с ЗРВ)
      QPen* Pen;         //Отображение простой ЗРВ
    };
    typedef struct ZRV TZRV;

    TOpCat OpCat;  //Параметры визуализации различных объектов из оперативного каталога

    TRoute Route;  //Параметры визуализации различных маршрутов

    std::vector<TTrass> Trasses;  //Параметры визуализации различных трасс

    std::vector<TStrip> Strips;  //Параметры визуализации различных полос обзора

    std::vector<TZRV> ArrZRV;  //Параметры визуализации различных ЗРВ

    TTrass CurrentTrass;  //Параметры визуализации текущей трассы

    TStrip CurrentStrip;  //Параметры визуализации текущей полосы обзора

    TZRV CurrentZRV;  //Параметры визуализации текущей ЗРВ

    //Очищает структуру OpCat
    void ClearOpCat(void);

    //Очищает структуру Route
    void ClearRoute(void);

    //Очищает элемент массива в Trasses
    void ClearTrass(int Index);

    //Очищает элемент массива в Strips
    void ClearStrip(int Index);

    //Очищает элемент массива в ArrZRV
    void ClearZRV(int Index);

    //Считывает заголовок файла
    bool ReadHeader(QTextStream *mif);

    //Доходит курсором файла до заголовка геометрического объекта (полилиния, регион)
    void FindGeometryObj(QTextStream *mif, int *type, int *size);

    //Считывает целое число
    int ReadInt(QTextStream *mif);

    //Считывает точки одного контура или одной полининии
    TMultitude::TSpot ReadPoints(QTextStream *mif, int quantity);

    //Считывает параметры пера
    void ReadPen(QTextStream *mif, int *WidthMI, int *PatternMI, int *ColorMI);

    //Считывает параметры заливки
    void ReadBrush(QTextStream *mif, int *PatternMI, int *ColorMI);

  public:
    //Тип описывает список слоев (не сами слои)
    struct OneLayer
    {
      OneLayer() : Name(""), Visible(false) {}
      std::string Name;
      bool Visible;
    };
    typedef std::vector<struct OneLayer> TLayerList;

    //Тип описывает возвращаемый из карты список объектов
    struct Obj
    {
      Obj() : LayerName(""), ObjID(0), ObjName("") {}
      std::string LayerName;  //Имя слоя
      unsigned int ObjID;     //Идентификатор объекта в указанном слое
      std::string ObjName;    //Имя объекта
    };
    typedef std::vector<struct Obj> TObjList;

    TMapData(void);
    virtual ~TMapData(void);

    //Возвращает строку всплывающей подсказки, используя данные под курсором
    QString GetStringHintUnderCursor(QList<QGraphicsItem *> Arr);

    //Возвращает список объектов, используя данные под курсором
    TObjList GetObjListUnderCursor(QList<QGraphicsItem *> Arr);

    //Быстро перерисовать картографические данные
    void RePaint(void);

    //Перерисовать картографические данные путем удаления и создания объектов слоев
    void CoolRePaint(void);

    //Устанавливает признаки отображения тех или иных типов картографических данных
    void WhatIsShow(bool _Frame, bool _Grid15);

    //Возвращает список слоев
    TLayerList GetLayerList(void);

    //Найти слой, обратившись к нему по имени
    int FindLayer(std::string Name);

    //Показать слой, обратившись к нему по имени
    bool ShowLayer(std::string Name);

    //Скрыть слой, обратившись к нему по имени
    bool HideLayer(std::string Name);

    //Добавить новый слой, задав ему имя
    bool AddLayer(std::string Name);

    //Удалить существующий слой, обратившись к нему по имени
    bool DelLayer(std::string Name);

    //Удаляет все пользовательские слои и перерисовывает карту
    void DelAllUserLayers(void);

    //Добавить новый слой, создав его из MIF-файла формата MapInfo
    // На вход подаются:
    // - имя слоя;
    // - путь и имя MIF-файла.
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddLayerFromMIF(std::string LayerName, std::string FilePathName);

    //Добавить новый слой, содержащий данные оперативного каталога
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddLayerOpCat(void);

    //Добавить новый слой, содержащий данные по маршрутам
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddLayerRoute(void);

    //Добавить новый слой, содержащий данные по трассе полета. Может быть создано несколько слоев с трассами
    // На вход подаются:
    // - номер слоя с трассами;
    // - ширина линии в формате MapInfo;
    // - тип линии в формате MapInfo;
    // - цвет линии в формате MapInfo.
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddLayerTrass(int Index, int WidthMI, int PatternMI, int ColorMI);

    //Устанавлявает текущий слой с трассой
    // На вход подаются:
    // - номер слоя с трассами
    void SetCurrentTrass(int Index);

    //Удалить текущий слой с трассой
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool DelCurrentTrass(void);

    //Добавить новый слой, содержащий данные по полосе обзора. Может быть создано несколько слоев с полосами обзора
    // На вход подаются:
    // - номер слоя с полосами обзора;
    // - ширина линии в формате MapInfo;
    // - тип линии в формате MapInfo;
    // - цвет линии в формате MapInfo.
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddLayerStrip(int Index, int WidthMI, int PatternMI, int ColorMI);

    //Устанавлявает текущий слой с полосой обзора
    // На вход подаются:
    // - номер слоя с полосами обзора
    void SetCurrentStrip(int Index);

    //Удалить текущий слой с полосой обзора
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool DelCurrentStrip(void);

    //Добавить новый слой, содержащий данные по часто перерисовываемым точечным объектам
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddLayerDynamicPoint(void);

    //Добавить новый слой, содержащий данные по ЗРВ. Может быть создано несколько слоев с ЗРВ
    // На вход подаются:
    // - номер слоя с ЗРВ;
    // - ширина линии в формате MapInfo;
    // - тип линии в формате MapInfo;
    // - цвет линии в формате MapInfo.
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddLayerZRV(int Index, int WidthMI, int PatternMI, int ColorMI);

    //Устанавлявает текущий слой с ЗРВ
    // На вход подаются:
    // - номер слоя с трассами
    void SetCurrentZRV(int Index);

    //Удалить текущий слой с ЗРВ
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool DelCurrentZRV(void);

    //Возвращает минимальное свободное значение идентификатора для размещения нового объекта в слое
    // Обращается к слою по имени
    // На выходе можно получить:
    // - свободное значение идентификатора объекта
    unsigned int GetFreeID(std::string Name);

    //Возвращает список заголовков объектов в существующем слое. Обращается к слою по имени
    // На вход подаются:
    // - имя слоя.
    // На выходе можно получить:
    // - список заголовков объектов в указанном слое
    TLayer::THeadersObjects GetObjList(std::string Name);

    //Добавляет в слой оперативного каталога точечный объект наблюдения
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор объекта;
    // - описание объекта;
    // - признак волевого объекта;
    // - геодезические координаты объекта "точка" на эллипсоиде ПЗ-90 [рад].
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddPointInOpCat(unsigned int ID, std::string Comment, bool Volition, TMultitude::TOnePoint Point);

    //Добавляет в слой оперативного каталога площадной объект наблюдения
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор объекта;
    // - описание объекта;
    // - признак волевого объекта;
    // - геодезические координаты узловых точек площадного объекта на эллипсоиде ПЗ-90 [рад].
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddAreaInOpCat(unsigned int ID, std::string Comment, bool Volition, TMultitude::TSpot Spot);

    //Добавляет в слой, содержащий данные по маршрутам, новый маршрут
    // !!! Добавление маршрута в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор маршрута;
    // - описание маршрута;
    // - геодезические координаты узловых абриса маршрута на эллипсоиде ПЗ-90 [рад].
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddInRoute(unsigned int ID, std::string Comment, TMultitude::TSpot Spot);

    //Добавляет в текущий слой с трассами новый участок
    // !!! Добавление участка трассы в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор участка трассы;
    // - описание участка трассы;
    // - геодезические координаты участка трассы (узлы линии или полилинии) на эллипсоиде ПЗ-90 [рад].
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddInCurrentTrass(unsigned int ID, std::string Comment, TMultitude::TSpot Spot);

    //Добавляет в текущий слой с полосами обзора новый участок
    // !!! Добавление участка полосы обзора в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор участка полосы обзора;
    // - описание участка полосы обзора;
    // - геодезические координаты участка полосы обзора (узлы линии или полилинии) на эллипсоиде ПЗ-90 [рад].
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddInCurrentStrip(unsigned int ID, std::string Comment, TMultitude::TSpot Spot);

    //Добавляет в слой с динамическими точками новый объект
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор объекта;
    // - описание объекта;
    // - геодезические координаты объекта "точка" на эллипсоиде ПЗ-90 [рад];
    // - код цвета MapInfo.
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddInDynamicPoint(unsigned int ID, std::string Comment, TMultitude::TOnePoint Point, int ColorMI);

    //Быстро сдвигает объект в слое с динамическими точками
    // На вход подаются:
    // - идентификатор объекта;
    // - описание объекта;
    // - геодезические координаты объекта "точка" на эллипсоиде ПЗ-90 [рад]
    void MoveInDynamicPoint(unsigned int ID, std::string Comment, TMultitude::TOnePoint Point);

    //Добавляет в текущий слой с ЗРВ новый участок
    // !!! Добавление участка ЗРВ в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор участка ЗРВ;
    // - описание участка ЗРВ;
    // - геодезические координаты участка ЗРВ (узлы линии или полилинии) на эллипсоиде ПЗ-90 [рад].
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddInCurrentZRV(unsigned int ID, std::string Comment, TMultitude::TSpot Spot);

    //Добавляет в существующий слой объект типа "точка". Обращается к слою по имени
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - имя слоя;
    // - идентификатор объекта;
    // - наименование объекта;
    // - тип символа, изображающего объект "точка";
    // - геодезические координаты объекта "точка" на эллипсоиде ПЗ-90 [рад];
    // - перо для рисования объекта "точка";
    // - заливка для рисования объекта "точка".
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddPointInLayer(std::string Name, unsigned int ID, std::string ObjName, TLayer::TTypeSymbol Type,
                         TMultitude::TOnePoint Point, QPen Pen, QBrush Brush);

    //Добавляет в существующий слой объект типа "полилиния". Обращается к слою по имени
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - имя слоя;
    // - идентификатор объекта;
    // - наименование объекта;
    // - геодезические координаты узловых точек полилинии на эллипсоиде ПЗ-90 [рад];
    // - перо для рисования объекта "полилиния".
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddPolyLineInLayer(std::string Name, unsigned int ID, std::string ObjName, TMultitude::TSpot Spot, QPen Pen);

    //Добавляет в существующий слой объект типа "регион". Обращается к слою по имени
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - имя слоя;
    // - идентификатор объекта;
    // - наименование объекта;
    // - геодезические координаты узловых точек региона на эллипсоиде ПЗ-90 [рад];
    // - перо для рисования объекта "регион";
    // - заливка для рисования объекта "регион".
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddRegionInLayer(std::string Name, unsigned int ID, std::string ObjName, TMultitude::TSpot Spot, QPen Pen, QBrush Brush);

    //Удаляет объект любого типа из существующего слоя. Обращается к слою по имени
    // На вход подаются:
    // - имя слоя;
    // - идентификатор объекта.
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool DelObjFromLayer(std::string Name, unsigned int ID);

    void* OWNER;  //Обязателен к заполнению
};


#endif