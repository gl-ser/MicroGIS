//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл Layer.h                                                               //
//                                                                            //
//                    *** TLAYER КАРТОГРАФИЧЕСКИЙ СЛОЙ ***                    //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef LayerH
#define LayerH

#include <string>
#include <QPen>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsPathItem>
#include "../Multitude/Multitude.h"


class TLayer
{
  public:
    //Тип символа, изображающего объект "точка" в слое
    enum TTypeSymbol
    {
      NONE_SYMBOL = 0,    //Не задан
      CIRCLE_SYMBOL = 1,  //Круг
      RECT_SYMBOL = 2     //Квадрат
    };

    //Тип объекта в слое
    enum TTypeObj
    {
      NONE_OBJ = 0,      //Не задан
      POINT_OBJ = 1,     //Точка
      POLYLINE_OBJ = 2,  //Полилиния
      REGION_OBJ = 3     //Регион
    };

    //Полушарие Земли, в котором располагается объект
    enum THemisphere
    {
      NONE_HEM = 0,   //Не задано
      NORTH_HEM = 1,  //Северное полушарие
      SOUTH_HEM = 2,  //Южное полушарие
      BOTH_HEM = 3    //Оба полушария (северное и южное)
    };

    //Тип описывает параметры объекта "точка" в слое
    struct ObjPoint
    {
      ObjPoint() : Type(NONE_SYMBOL), Pen(NULL), Brush(NULL) {}
      TTypeSymbol Type;             //Тип символа, изображающего объект "точка"
      TMultitude::TOnePoint Point;  //Геодезические координаты объекта "точка"
      QPen *Pen;                    //Перо для рисования объекта "точка"
      QBrush *Brush;                //Заливка для рисования объекта "точка"
    };
    typedef struct ObjPoint TObjPoint;

    //Тип описывает параметры объекта "полилиния" в слое
    struct ObjPolyLine
    {
      ObjPolyLine() : Pen(NULL) {}
      TMultitude::TSpot Spot;  //Геодезические координаты узловых точек полилинии
      QPen *Pen;               //Перо для рисования объекта "полилиния"
    };
    typedef struct ObjPolyLine TObjPolyLine;

    //Тип описывает параметры объекта "регион" в слое
    struct ObjRegion
    {
      ObjRegion() : Pen(NULL), Brush(NULL) {}
      TMultitude::TSpot Spot;  //Геодезические координаты узловых точек региона
      QPen *Pen;               //Перо для рисования объекта "регион"
      QBrush *Brush;           //Заливка для рисования объекта "регион"
    };
    typedef struct ObjRegion TObjRegion;

    //Тип описывает заголовок одного объекта в слое
    struct HeaderOfObj
    {
      HeaderOfObj() : ID(0), Name("") {}
      unsigned int ID;   //Идентификатор объекта
      std::string Name;  //Наименование объекта
    };
    typedef struct HeaderOfObj THeaderOfObj;

    //Тип описывает все заголовки объектов в слое
    typedef std::vector<THeaderOfObj> THeadersObjects;

    //Тип описывает параметры одного объекта в слое
    struct Obj
    {
      Obj() : HandlePointAsEllipse(NULL), HandlePointAsRect(NULL), HandleRegion(NULL), HandlePolyLine(NULL),
              Hemisphere(NONE_HEM), Type(NONE_OBJ) {}
      QGraphicsEllipseItem *HandlePointAsEllipse;       //Указатель на item кружочка, помещенного на сцену. Пользователь не заполняет
      QGraphicsRectItem *HandlePointAsRect;             //Указатель на item квадрата, помещенного на сцену. Пользователь не заполняет
      QGraphicsPolygonItem *HandleRegion;               //Указатель на item полигона, помещенного на сцену. Пользователь не заполняет
      QGraphicsPathItem *HandlePolyLine;                //Указатель на item полилинии, помещенной на сцену. Пользователь не заполняет
      THeaderOfObj Header;     //Заголовок объекта
      THemisphere Hemisphere;  //Полушарие Земли, в котором располагается объект
      TTypeObj Type;           //Тип объекта
      TObjPoint Point;         //Тип объекта POINT_OBJ - "точка"
      TObjPolyLine PolyLine;   //Тип объекта POLYLINE_OBJ - "полилиния"
      TObjRegion Region;       //Тип объекта REGION_OBJ - "регион"
    };
    typedef struct Obj TObj;

    //Тип описывает параметры всех объектов в слое
    typedef std::vector<TObj> TObjects;

  private:
    //Возвращает название полушария Земли, в котором располагается объект
    THemisphere GetHemisphere(TMultitude::TSpot Spot);

    bool Visible;  //Признак визуализации слоя

  public:
    TLayer(void);
    virtual ~TLayer(void);

    //Переводит цвета R, G, B в код цвета MapInfo
    // На вход подаются:
    // - красный;
    // - зеленый;
    // - синий.
    // На выходе можно получить:
    // - цвет в формате MapInfo
    void RGBToMI(int R, int G, int B, int* MI);

    //Переводит цвета R, G, B в код цвета MapInfo
    // На вход подаются:
    // - цвет в формате MapInfo.
    // На выходе можно получить:
    // - красный;
    // - зеленый;
    // - синий
    void MIToRGB(int MI, int* R, int* G, int* B);

    //Переводит перо формата MapInfo в формат QPen
    // На вход подаются:
    // - ширина линии в формате MapInfo;
    // - тип линии в формате MapInfo;
    // - цвет линии в формате MapInfo.
    // На выходе можно получить:
    // - перо QPen
    QPen PenMIToQPen(int WidthMI, int PatternMI, int ColorMI);

    //Переводит заливку формата MapInfo в формат QBrush
    // На вход подаются:
    // - тип штриховки в формате MapInfo;
    // - цвет штриховки в формате MapInfo.
    // На выходе можно получить:
    // - заливку QBrush
    QBrush BrushMIToQBrush(int PatternMI, int ColorMI);

    //Быстро перерисовать слой
    void RePaint(void);

    //Перерисовать слой путем удаления и создания всех его объектов
    void CoolRePaint(void);

    //Скрыть (девизуализировать) слой
    void Hide(void);

    //Показать (визуализировать) слой
    void Show(void);

    //Возвращает признак визуализации слоя
    bool GetVisible(void);

    //Возвращает строку (содержащую имя слоя и имя объекта) по указателю, если такой объект найдется в слое
    std::string GetStringObj(QGraphicsItem* ID);

    //Возвращает заголовок объекта по указателю, если такой объект найдется в слое
    THeaderOfObj GetHeaderObj(QGraphicsItem* ID);

    //Возвращает минимальное свободное значение идентификатора для размещения нового объекта в слое
    // На выходе можно получить:
    // - свободное значение идентификатора объекта
    unsigned int GetFreeID(void);

    //Возвращает список заголовков объектов в слое
    THeadersObjects GetObjList(void);

    //Добавляет в слой объект типа "полилиния"
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор объекта;
    // - наименование объекта;
    // - геодезические координаты узловых точек полилинии на эллипсоиде ПЗ-90 [рад];
    // - перо для рисования объекта "полилиния"
    void AddPolyLineQuick(unsigned int ID, std::string Name, TMultitude::TSpot Spot, QPen Pen);

    //Добавляет в слой объект типа "регион"
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор объекта;
    // - наименование объекта;
    // - геодезические координаты узловых точек региона на эллипсоиде ПЗ-90 [рад];
    // - перо для рисования объекта "регион";
    // - заливка для рисования объекта "регион"
    void AddRegionQuick(unsigned int ID, std::string Name, TMultitude::TSpot Spot, QPen Pen, QBrush Brush);

    //Добавляет в слой объект типа "точка"
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор объекта;
    // - наименование объекта;
    // - тип символа, изображающего объект "точка";
    // - геодезические координаты объекта "точка" на эллипсоиде ПЗ-90 [рад];
    // - перо для рисования объекта "точка";
    // - заливка для рисования объекта "точка"
    void AddPointQuick(unsigned int ID, std::string Name, TTypeSymbol Type, TMultitude::TOnePoint Point, QPen Pen, QBrush Brush);

    //Добавляет в слой объект типа "точка"
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор объекта;
    // - наименование объекта;
    // - тип символа, изображающего объект "точка";
    // - геодезические координаты объекта "точка" на эллипсоиде ПЗ-90 [рад];
    // - перо для рисования объекта "точка";
    // - заливка для рисования объекта "точка".
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddPoint(unsigned int ID, std::string Name, TTypeSymbol Type, TMultitude::TOnePoint Point, QPen Pen, QBrush Brush);

    //Добавляет в слой объект типа "полилиния"
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор объекта;
    // - наименование объекта;
    // - геодезические координаты узловых точек полилинии на эллипсоиде ПЗ-90 [рад];
    // - перо для рисования объекта "полилиния".
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddPolyLine(unsigned int ID, std::string Name, TMultitude::TSpot Spot, QPen Pen);

    //Добавляет в слой объект типа "регион"
    // !!! Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint !!!
    // На вход подаются:
    // - идентификатор объекта;
    // - наименование объекта;
    // - геодезические координаты узловых точек региона на эллипсоиде ПЗ-90 [рад];
    // - перо для рисования объекта "регион";
    // - заливка для рисования объекта "регион".
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool AddRegion(unsigned int ID, std::string Name, TMultitude::TSpot Spot, QPen Pen, QBrush Brush);

    //Удаляет объект любого типа из слоя
    // На вход подаются:
    // - идентификатор объекта.
    // На выходе можно получить:
    // - true в случае успешного выполнения процедуры;
    // - false в случае какой-либо ошибки
    bool DelObj(unsigned int ID);

    TObjects Objects;  //Объекты, содержащиеся в слое

    std::string Name;  //Имя слоя обязательно к заполнению

    void* OWNER;  //Обязателен к заполнению
};


#endif
