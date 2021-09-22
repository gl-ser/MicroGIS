//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл LayerAdd.h                                                            //
//                                                                            //
//                *** TLAYERADD ОКНО ДОБАВЛЕНИЯ НОВОГО СЛОЯ ***               //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef LAYERADD_H
#define LAYERADD_H

#include "Placement.h"
#include "ui_LayerAdd.h"


class TLayerAdd : public QDialog, public Ui::TLayerAdd
{
  Q_OBJECT

  private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

  private:
    TPlacement* Placement;  //Положение и размеры окна сохраняет и восстанавливает
    std::string FIniFileName;  //Путь и имя INI-файла, в котором хранятся настройки окна
    std::string FName;

    //Размещение окна по центру экрана
    void MoveToCenter(void);

  protected:
    //Обработчик OnShow окна
    void showEvent(QShowEvent *event);

    //Обработчик OnClose окна
    void hideEvent(QHideEvent *event);

  public:
    explicit TLayerAdd(QWidget *parent = 0);
    ~TLayerAdd(void);

    //Задает путь и имя INI-файла, в котором хранятся настройки окна
    void IniFileName(std::string Value);

    //Возвращает имя слоя
    std::string GetLayerName(void);
};


#endif
