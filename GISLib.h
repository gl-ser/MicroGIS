//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл GISLib.h                                                              //
//                                                                            //
//                 *** TGISLIB БАЗОВЫЙ КЛАСС ДЛЯ ENGINEGIS ***                //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef GISLibH
#define GISLibH

#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>
#include <QResizeEvent>
#include <QGraphicsSceneWheelEvent>
#include "Scene.h"
#include "View.h"
#include "MapData.h"
#include "Cartography.h"


class TGISLib : public QObject
{
  Q_OBJECT

  public:
    //Тип описывает данные, возвращаемые в пользовательскую программу по событию
    // щелчка левой кнопки "мыши" при активированном инструменте TView::ARROW
    struct DataLeftMouse
    {
      TMultitude::TOnePoint CoordDown;  //Геодезические координаты (на эллипсоиде ПЗ-90) нажатия кнопки
      TMapData::TObjList ObjectsDown;   //Список объектов карты по координатам нажтия кнопки
      TMultitude::TOnePoint CoordUp;    //Геодезические координаты (на эллипсоиде ПЗ-90) отпускания кнопки
      TMapData::TObjList ObjectsUp;     //Список объектов карты по координатам отпускания кнопки
    };
    typedef struct DataLeftMouse TDataLeftMouse;

  signals:
    //Обработка события щелчка левой кнопки "мыши" при активированном инструменте TView::ARROW
    void GetDataLeftMouse(TGISLib::TDataLeftMouse Value);

  public:
    //Картографические проекции
    enum TProj
    {
      NONEPROJECTION = 0,  //Проекция НЕ установлена
      CYLINDRICAL = 1,     //Цилиндрическая равнопромежуточная проекция Плате-Карре
      NORTHPOLE = 2,       //Азимутальная ортографическая проекция Северного Полюса
      SOUTHPOLE = 3,       //Азимутальная ортографическая проекция Южного Полюса
      MERCATOR = 4,        //Равноугольная цилиндрическая проекция Меркатора
      KAVRAYSKIY = 5       //Псевдоцилиндрическая проекция Каврайского
    };

  private:
    //--- Константы ---
    double CONST_MaxScale;   //Максимальный условный масштаб отображения карты
    double CONST_MinScale;   //Минимальный условный масштаб отображения карты
    double CONST_StepScale;  //Шаг изменения условного масштаба отображения карты
    double CONST_NormScale;  //Значение масштаба по умолчанию

    //Условный масштаб отображения карты
    double Scale;

    //Текущий инструмент по работе с картой
    TView::TTool Tool;

  protected:
    //Тип описывает границы прямоугольной области
    struct Screen
    {
      Screen() : Xmin(0.0), Xmax(0.0), Ymin(0.0), Ymax(0.0) {}
      double Xmin;  //Минимальное значение абсциссы плановых координат
      double Xmax;  //Максимальное значение абсциссы плановых координат
      double Ymin;  //Минимальное значение ординаты плановых координат
      double Ymax;  //Максимальное значение ординаты плановых координат
    };
    typedef struct Screen TScreen;

    //Тип описывает параметры текущей картографической проекции
    struct Projection
    {
      Projection() : Number(NONEPROJECTION), Fi0(0.0), L0(0.0) {}
      TProj Number;  //Номер проекции
      double Fi0;    //Геоцентрическая широта базисной точки
      double L0;     //Геоцентрическая долгота базисной точки
      TScreen Map;   //Границы картографической проекции
    };
    typedef struct Projection TProjection;

    //Вычисляет пропорции окна отображения карты
    void Proportion(void);

    //Устанавливает (активирует) инструмент по работе с картой
    void SetCurrentTool(TView::TTool Value);

    //Указатель на Layout окна, на котором производится отрисовка карты
    QGridLayout* Layout;

    //Указатель на поле status bar окна, на котором производится отрисовка карты (для вывода координат указателя "мыши")
    QLabel* CurCoord;

    //Указатель на поле status bar окна, на котором производится отрисовка карты (для вывода текущего условного масштаба)
    QLabel* CurrentScale;

    //Указатель на поле status bar окна, на котором производится отрисовка карты (для вывода величины измеренного расстояния)
    QLabel* Ruler;

  public:
    TGISLib(void);
    virtual ~TGISLib(void);

    //Увеличивает масштаб на шаг
    void PlusScale(void);

    //Уменьшает масштаб на шаг
    void MinusScale(void);

    //Нормализует масштаб (приводит к начальному)
    void NormalizeScale(void);

    //Возвращает текущий масштаб
    double GetScale(void);

    //Обработчик OnMouseMove графической сцены
    void OnSceneMouseMove(QGraphicsSceneMouseEvent *event);

    //Обработчик OnResize вида
    void OnViewResize(QResizeEvent *event);

    //Обработчик OnMouseWheel графической сцены
    void OnSceneMouseWheel(QGraphicsSceneWheelEvent *event);

    //Обработчик OnDragAndDrop графической сцены
    void OnSceneDragAndDrop(double DownSceneX, double DownSceneY, double UpSceneX, double UpSceneY,
                            double DownViewX, double DownViewY, double UpViewX, double UpViewY);

    //Возвращает текущий инструмент по работе с картой
    TView::TTool GetCurrentTool(void);

    //Графическая сцена
    TScene* Scene;

    //Вид, на котором производится отрисовка сцены
    TView* View;

    //Картографические данные
    TMapData* MapData;

    //Параметры текущей картографической проекции
    TProjection Projection;

    //Текущие границы области отображения карты (координаты сцены)
    TScreen Screen;

    //Текущие размеры области отображения карты (плановые координаты)
    TScreen PlaneCoord;

    //Пропорции окна отображения карты по осям X и Y
    //Взаимные отношения величин ProportionX и ProportionY задают соотношение сторон экрана (пропорциональность картинки)
    double ProportionX, ProportionY;

    //Объект Cartography осуществляет картографические преобразования
    TCartography* Cartography;
};


#endif
