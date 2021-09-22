//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл Map.h                                                                 //
//                                                                            //
//                           *** TMAP ОКНО КАРТЫ ***                          //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef MAP_H
#define MAP_H

#include <QLabel>
#include "Placement.h"
#include "ui_Map.h"


class TMap : public QMainWindow, public Ui::TMap
{
  Q_OBJECT

  private slots:
    void on_action_triggered();     //Цилиндрическая равнопромежуточная проекция Плате-Карре
    void on_action_2_triggered();   //Азимутальная ортографическая проекция Северного Полюса
    void on_action_3_triggered();   //Азимутальная ортографическая проекция Южного Полюса
    void on_action_4_triggered();   //Показать всю карту
    void on_action_6_triggered();   //Движение карты
    void on_action_7_triggered();   //Линейка
    void on_action_5_triggered();   //Управление слоями
    void on_action_8_triggered();   //Стрелка
    void on_action_9_triggered();   //Равноугольная цилиндрическая проекция Меркатора
    void on_action_10_triggered();  //Псевдоцилиндрическая проекция Каврайского
    void on_action_11_triggered();  //Показать
    void on_action_12_triggered();  //Скрыть

  private:
    TPlacement* Placement;  //Положение и размеры окна сохраняет и восстанавливает
    std::string FIniFileName;  //Путь и имя INI-файла, в котором хранятся настройки окна

    //Размещение окна по центру экрана
    void MoveToCenter(void);

  protected:
    //Обработчик OnShow окна
    void showEvent(QShowEvent *event);

    //Обработчик OnClose окна
    void hideEvent(QHideEvent *event);

  public:
    explicit TMap(QWidget *parent = 0);
    ~TMap(void);

    //Задает путь и имя INI-файла, в котором хранятся настройки окна
    void IniFileName(std::string Value);

    void* OWNER;

    QLabel* CurCoord;      //Место на StatusBar'е, в которое выводятся координаты курсора
    QLabel* CurrentScale;  //Место на StatusBar'е, в которое выводится текущий условный масштаб
    QLabel* Ruler;         //Место на StatusBar'е, в которое выводится величина измеренного расстояния
};


#endif
