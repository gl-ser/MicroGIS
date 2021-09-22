//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл LayerCtrl.h                                                           //
//                                                                            //
//                  *** TLAYERCTRL ОКНО УПРАВЛЕНИЯ СЛОЯМИ ***                 //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef LAYERCTRL_H
#define LAYERCTRL_H

#include "Placement.h"
#include "ui_LayerCtrl.h"


class TLayerCtrl : public QDialog, private Ui::TLayerCtrl
{
  Q_OBJECT

  private slots:
    void on_pushButton_clicked();    //Показать
    void on_pushButton_2_clicked();  //Скрыть
    void on_pushButton_3_clicked();  //Добавить новый
    void on_pushButton_4_clicked();  //Удалить существующий
    void on_CheckGrid15_clicked();   //Отображать 15° сетку
    void on_pushButton_5_clicked();  //Список объектов...

  private:
    TPlacement* Placement;  //Положение и размеры окна сохраняет и восстанавливает
    std::string FIniFileName;  //Путь и имя INI-файла, в котором хранятся настройки окна

    //Размещение окна по центру экрана
    void MoveToCenter(void);

    //Получение данных из ShellGIS
    void GetData(int Index);

  protected:
    //Обработчик OnShow окна
    void showEvent(QShowEvent *event);

    //Обработчик OnClose окна
    void hideEvent(QHideEvent *event);

  public:
    explicit TLayerCtrl(QWidget *parent = 0);
    ~TLayerCtrl(void);

    //Задает путь и имя INI-файла, в котором хранятся настройки окна
    void IniFileName(std::string Value);

    void* OWNER;
};


#endif
