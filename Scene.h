//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл Scene.h                                                               //
//                                                                            //
//                      *** TSCENE ГРАФИЧЕСКАЯ СЦЕНА ***                      //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef SceneH
#define SceneH

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>


class TScene : public QGraphicsScene
{
  Q_OBJECT
  signals:

  private:
    //Координаты курсора на сцене в тот момент, когда произошло событие OnMouseDown
    double DownSceneX, DownSceneY;

    //Координаты курсора на сцене в тот момент, когда произошло событие OnMouseUp
    double UpSceneX, UpSceneY;

    //Координаты курсора на "виде" в тот момент, когда произошло событие OnMouseDown
    double DownViewX, DownViewY;

    //Координаты курсора на "виде" в тот момент, когда произошло событие OnMouseUp
    double UpViewX, UpViewY;

    //Признак того, что была нажата левая клавиша "мыши".
    // Нужен, чтобы лишний раз не обрабатывать OnMouseUp при нажатии правой клавиши мыши
    bool PrLeftButtonDown;

    //Линия, рисуемая в процессе измерения карты линейкой
    QGraphicsLineItem *RulerLine;

    //Обработчик OnMouseMove сцены
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //Обработчик OnMouseWheel сцены
    void wheelEvent(QGraphicsSceneWheelEvent *event);

    //Обработчик OnMouseDown сцены
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //Обработчик OnMouseUp сцены
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

  public:
    TScene(void);
    virtual ~TScene(void);

    void* OWNER;  //Обязателен к заполнению
};


#endif
