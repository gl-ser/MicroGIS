//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл Frame.h                                                               //
//                                                                            //
//               *** TFRAME РАМКА КАРТЫ И 15-ГРАДУСНАЯ СЕТКА ***              //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef FrameH
#define FrameH

#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include "../Multitude/Multitude.h"


class TFrame
{
  private:
    QGraphicsLineItem *Up, *Down, *Left, *Right, *VertCentral, *HorCentral;

    QGraphicsPolygonItem *IDGrid15[288];

    TMultitude::TArraySpot Grid15;  //Пятнадцатиградусная сетка. 12 штук по широте и 24 штуки по долготе

  public:
    TFrame(void);
    virtual ~TFrame(void);

    //Добавить рамку на карту
    void Add(void);

    //Удалить рамку карты
    void Del(void);

    //Перерисовать рамку
    void RePaint(void);

    //Добавить 15-градусную сетку на карту
    void AddGrid(void);

    //Удалить 15-градусную сетку
    void DelGrid(void);

    //Перерисовать 15-градусную сетку
    void RePaintGrid(void);

    void* OWNER;  //Обязателен к заполнению
};


#endif
