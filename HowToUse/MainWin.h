//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл MainWin.h                                                             //
//                                                                            //
//                        *** TMAINWIN ГЛАВНОЕ ОКНО ***                       //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef MAINWIN_H
#define MAINWIN_H

#include <QBasicTimer>
#include <QLabel>
#include <QProcess>
#include "Base.h"
#include "Placement.h"
#include "ui_MainWin.h"


class TMainWin : public QMainWindow, public Ui::TMainWin
{
  Q_OBJECT

  private slots:
    void on_action_triggered();     //Параметры приложения
    void on_action_4_triggered();   //Выход из программы
    void on_action_2_triggered();   //Открыть журнал
    void on_action_5_triggered();   //Открыть карту

  private:
    QLabel* CurTimeText;           //Место на главном окне, в которое выводятся показания текущего времени
    QBasicTimer* CurTimeTimer;     //Таймер текущего времени
    QBasicTimer* TimerQuit;        //Таймер выхода из приложения
    QBasicTimer* TimerFirstStart;  //Таймер срабатывает при первом старте приложения
    TPlacement* Placement;         //Положение и размеры окна сохраняет и восстанавливает

    //Путь и имя INI-файла, в котором хранятся настройки окна
    std::string FIniFileName;

    //Размещение окна по центру экрана
    void MoveToCenter(void);

  protected:
    bool first;

    //Обработчик событий таймеров
    void timerEvent(QTimerEvent *event);

  public:
    explicit TMainWin(QWidget *parent = 0);
    ~TMainWin(void);

    //Объект главного модуля данных приложения
    TBase *Base;

    //Задает путь и имя INI-файла, в котором хранятся настройки окна
    void IniFileName(std::string Value);

    //Запуск таймера TimerFirstStart
    void FirstStart(void);
};


#endif
