//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл Base.h                                                                //
//                                                                            //
//               *** TBASE ГЛАВНЫЙ МОДУЛЬ ДАННЫХ ПРИЛОЖЕНИЯ ***               //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef BASE_H
#define BASE_H

#include <random>
#include <time.h>
#include <string>
#include <QObject>
#include <QApplication>
#include <QUuid>
#include <QDir>
#include <QHostInfo>
#include <QSettings>
#include <QTimer>
#include <QFileDialog>
#include <QSqlRecord>
#include <QDateTime>

#include "Wait.h"
#include "Error.h"
#include "WinTuner.h"
#include "WinLogBook.h"
#include "Map.h"
#include "LayerCtrl.h"
#include "LayerAdd.h"
#include "ObjCtrl.h"
#include "Nutation.h"

#include "../../Calendar/Calendar.h"
#include "../../Num/Numerical.h"
#include "../ShellGIS.h"


class TBase : public QObject
{
  Q_OBJECT
  public slots:
    //Обработка события щелчка левой кнопки "мыши" при активированном инструменте TView::ARROW
    void GetDataLeftMouseARROW(TGISLib::TDataLeftMouse Value);

  private:
    std::string IniFileName;  //Путь и имя INI-файла, в котором хранятся настройки
    std::string TempCatalog;  //Уникальное имя подкаталога для размещения временных файлов

  public:
    TBase(void* Owner);
    ~TBase(void);

    //Вычисление координат Солнца в Абсолютной СК (расстояния в метрах) на заданное время TDateTime (эпоха J2000)
    void SunCoordinates2000(double Time, TVector* R);

    //Вычисление координат Луны в Абсолютной СК (расстояния в метрах) на заданное время TDateTime (эпоха J2000)
    void MoonCoordinates2000(double Time, TVector* R);

    //Возвращает высоту луны [рад] над плоскостью местного горизонта для заданной точки на поверхности Земли
    // для заданного момента времени с учетом прецессии и нутации Земли
    //На вход подаются:
    //  - текущее время [TDateTime];
    //  - координаты точки на поверхности Земли в Гринвичской СК.
    //На выходе можно получить:
    //  - высоту луны над плоскостью местного горизонта [рад].
    double LunarHeight(double Time, TVector Point);

    //Возвращает высоту солнца [рад] над плоскостью местного горизонта для заданной точки на поверхности Земли
    // для заданного момента времени с учетом прецессии и нутации Земли
    //На вход подаются:
    //  - текущее время [TDateTime];
    //  - координаты точки на поверхности Земли в Гринвичской СК.
    //На выходе можно получить:
    //  - высоту солнца над плоскостью местного горизонта [рад].
    double SolarHeight(double Time, TVector Point);

    //Матрица перевода (вращения) из Гринвичской СК текущей эпохи в Абсолютную СК эпохи J2000.
    // Матрица учитывает прецессию и нутацию Земли по модели МАС2000
    // На вход подается текущее время [TDateTime]
    TMatrix OtnToAbsMatrixPrecision(double Time);

    //Перевод из Абсолютной СК эпохи J2000 в Гринвичскую СК текущей эпохи с учетом прецессии и нутации Земли по модели МАС2000
    // На вход подается текущее время [TDateTime]
    void AbsToOtnPrecision(TVector RAbs, TVector VAbs, double Time, TVector* ROtn, TVector* VOtn);

    //Отрисовка ProgressBar
    void HowCalc(qint64 Index, qint64 Quantity);

    //Возвращает сгенерированную случайную строку длиной PLen. Строка состоит из символов алфавита, который "прошит"
    // в самой функции. Может использоваться как генератор паролей или генератор случайного имени подкаталога для
    // размещения временных файлов текущего экземпляра приложения
    std::string RandomString(int PLen);

    //Возвращает имя подкаталога для размещения временных файлов
    std::string GetTempCatalog(void);

    //Добавляет запись в журнал
    void AddToLogBook(QString Value);

    //Добавляет запись в журнал и автоматически вставляет текущее время
    void AddToLogBookCurrentTime(QString Value);

    void* OWNER;

    bool Result;  //Результат загрузки (true - успешно, false - закончить работу приложения)

    //Идентификатор приложения после его инсталяции. Он сохраняется в INI-файле и читается при запуске приложения
    // Если INI-файл утерян или если приложение только устанавливается (первый запуск), то этот GUID создается новый
    // То есть по сути это идентификатор установленной копии приложения
    std::string _GUID_;

    std::string _DEBUG_;

    bool CheckProto;  //Автоматически открывать окно протокола
    bool CheckMap;    //Автоматически открывать окно карты

    bool IsReboot;  //Признак перезагрузки (true - перезагрузка, false - выключение)

    TError* Error;
    TWait* Wait;
    TWinTuner* Tuner;
    TWinLogBook* Log;

    TMap* Map;
    TLayerCtrl* LayerCtrl;
    TLayerAdd* LayerAdd;
    TObjCtrl* ObjCtrl;

    //Движок геоинформационной системы
    TShellGIS* ShellGIS;

    TNutation* Nutation;
};


#endif
