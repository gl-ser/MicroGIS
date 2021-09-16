//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл View.h                                                                //
//                                                                            //
//              *** TVIEW ВИД ДЛЯ ОТРИСОВКИ ГРАФИЧЕСКОЙ СЦЕНЫ ***             //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef ViewH
#define ViewH

#include <QGraphicsView>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QBasicTimer>
#include <QLabel>
#include <QCursor>


class TView : public QGraphicsView
{
  Q_OBJECT
  signals:

  private:
    //Общие действия для конструкторов
    void Contructor(void);

    QCursor* CursorArrow;  //Курсор "стрелка"
    QCursor* CursorMove;   //Курсор "движение карты"
    QCursor* CursorRuler;  //Курсор "линейка"

    QLabel* Hint;            //Всплывающая подсказка
    QBasicTimer* HintTimer;  //Таймер для сокрытия всплывающей подсказки

  protected:
    //Обработчик OnResize вида
    void resizeEvent(QResizeEvent *event);

    //Здесь ловлю момент, когда надо показывать всплывающую подсказку
    bool event(QEvent *event);

    //Обработчик событий таймеров
    void timerEvent(QTimerEvent *event);

  public:
    //Инструменты по работе с картой
    enum TTool
    {
      MOVE = 1,   //Движение карты
      RULER = 2,  //Линейка
      ARROW = 3   //Стрелка
    };

    TView(void);
    TView(QGraphicsScene* Value);
    virtual ~TView(void);

    //Устанавливает вид курсора в соответствии с инструментом по работе с картой
    void SetCursor(TTool Value);

    //Закрывает всплывающую подсказку
    void CloseHint(void);

    void* OWNER;  //Обязателен к заполнению
};


#endif
