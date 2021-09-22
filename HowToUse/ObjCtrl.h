//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл ObjCtrl.h                                                             //
//                                                                            //
//              *** TOBJCTRL ОКНО УПРАВЛЕНИЯ ОБЪЕКТАМИ СЛОЯ ***               //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef OBJCTRL_H
#define OBJCTRL_H

#include "Placement.h"
#include "ui_ObjCtrl.h"


class TObjCtrl : public QDialog, private Ui::TObjCtrl
{
  Q_OBJECT

  private slots:
    void on_pushButton_clicked();    //Удалить

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
    explicit TObjCtrl(QWidget *parent = 0);
    ~TObjCtrl(void);

    //Задает путь и имя INI-файла, в котором хранятся настройки окна
    void IniFileName(std::string Value);

    std::string Name;  //Имя текущего слоя

    void* OWNER;
};


#endif
