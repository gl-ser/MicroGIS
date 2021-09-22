//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл Placement.cpp                                                         //
//                                                                            //
//      *** TPLACEMENT КЛАСС ДЛЯ СОХРАНЕНИЯ ПОЛОЖЕНИЯ И РАЗМЕРОВ ОКОН ***     //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QSettings>
#include <QWidget>
#include <QDialog>
#include <QMainWindow>
#include <QSplitter>
#include "Placement.h"


TPlacement::TPlacement(void *Owner)
{
  OWNER = Owner;
  FIniFileName = "";
  FIniSection = "";
  Visible = false;
}


TPlacement::~TPlacement()
{
  OWNER = NULL;
  FIniFileName = "";
  FIniSection = "";
  Visible = false;
}


void TPlacement::Save(void)
{
int i, j;
QSettings *ConfigFile;  //INI-файл настроек приложения
QString s, ClassName;
QStringList ls;

  if ((OWNER != NULL) && (FIniFileName != "") && (FIniSection != ""))
  {
    ConfigFile = new QSettings(QString::fromStdString(FIniFileName), QSettings::IniFormat);

    ConfigFile->setValue(QString::fromStdString(FIniSection+"/Place"), static_cast<QWidget*>(OWNER)->saveGeometry());


    ClassName = "QSplitter";
    s = Children(static_cast<QObject*>(OWNER), ClassName);
    if ((s != "") && (Visible == true))
    {
      ls = s.split(QLatin1Char(','));
      for(j=0; j<ls.size(); j++)
      {
        s = "";
        for(i=0; i<((static_cast<QObject*>(OWNER)->findChild<QSplitter*>(ls[j]))->sizes()).size(); i++)
        {
          if (s == "")
            s = QString::number(((static_cast<QObject*>(OWNER)->findChild<QSplitter*>(ls[j]))->sizes())[i]);
          else
            s = s + "," + QString::number(((static_cast<QObject*>(OWNER)->findChild<QSplitter*>(ls[j]))->sizes())[i]);
        }
        ConfigFile->setValue(QString::fromStdString(FIniSection+"/"+ls[j].toStdString()), s);
      }
    }


    delete ConfigFile;
  }
}


QString TPlacement::Children(QObject* ValueObj, QString ValueName)
{
int i;
QString res, str;
QObjectList list;
  res = "";

  list = ValueObj->children();

  for(i=0; i<list.size(); i++)
  {
    if (QString::fromUtf8(list[i]->metaObject()->className()) == ValueName)
    {
      if (res == "")
        res = list[i]->objectName();
      else
        res = res + "," + list[i]->objectName();
    }
    if (!(qobject_cast<QMainWindow*>(list[i])) && !(qobject_cast<QDialog*>(list[i])))
    {
      str = Children(list[i], ValueName);

      if (str != "")
      {
        if (res == "")
          res = str;
        else
          res = res + "," + str;
      }
    }
  }
  list.clear();

  return res;
}


void TPlacement::Restore(std::string IniFileName, std::string IniSection)
{
QSettings *ConfigFile;  //INI-файл настроек приложения
int i, j;
QString s, ClassName;
QStringList ls, ls2;
QList<int> attr;

  FIniFileName = IniFileName;
  FIniSection = IniSection;
  ConfigFile = new QSettings(QString::fromStdString(FIniFileName), QSettings::IniFormat);

  if (ConfigFile->value(QString::fromStdString(FIniSection+"/Place"), "").toString().toStdString() != "")
  {
    static_cast<QWidget*>(OWNER)->restoreGeometry(ConfigFile->value(QString::fromStdString(FIniSection+"/Place"), "").toByteArray());

    ClassName = "QSplitter";
    s = Children(static_cast<QObject*>(OWNER), ClassName);
    if (s != "")
    {
      ls = s.split(QLatin1Char(','));
      for(j=0; j<ls.size(); j++)
      {
        s = ConfigFile->value(QString::fromStdString(FIniSection+"/"+ls[j].toStdString()), "").toString();
        ls2.clear();
        attr.clear();
        if (s != "")
        {
          ls2 = s.split(QLatin1Char(','));
          for(i=0; i<ls2.size(); i++)
            attr.push_back(ls2[i].toInt());

          static_cast<QObject*>(OWNER)->findChild<QSplitter*>(ls[j])->setSizes(attr);
        }
      }
    }
  }

  delete ConfigFile;
}


void TPlacement::IsVisible()
{
  Visible = true;
}
