//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл WinLogBook.h                                                          //
//                                                                            //
//                      *** TWINLOGBOOK ОКНО ЖУРНАЛА ***                      //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef WINLOGBOOK_H
#define WINLOGBOOK_H

#include <QLabel>
#include "Placement.h"
#include "ui_WinLogBook.h"


class TWinLogBook : public QMainWindow, public Ui::TWinLogBook
{
  Q_OBJECT

  private slots:
    void on_action_4_triggered();   //Сохранить в файле
    void on_action_5_triggered();   //Очистить журнал

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
    explicit TWinLogBook(QWidget *parent = 0);
    ~TWinLogBook(void);

    //Задает путь и имя INI-файла, в котором хранятся настройки окна
    void IniFileName(std::string Value);

    //Сохраняет содержимое журнала в новом файле
    // Если ReWrite==true, тогда файл создается заново
    // Если ReWrite==false, тогда файл дописывается
    void SaveToFile(QString FilePathName, bool ReWrite);

    void* OWNER;
};


#endif
