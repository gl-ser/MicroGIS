//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл Base.cpp                                                              //
//                                                                            //
//               *** TBASE ГЛАВНЫЙ МОДУЛЬ ДАННЫХ ПРИЛОЖЕНИЯ ***               //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include "Base.h"
#include "MainWin.h"


TBase::TBase(void* Owner)
{
int i;
bool pr1;
std::string FilePath, HomeCatalog, str;
QStringList ParamStr;  //Командная строка приложения
QDir *Dir;  //Класс управления каталогами
std::string ComputerNetName;  //Имя компьютера
QSettings *ConfigFile;  //INI-файл настроек приложения
QFile FileDB;

  OWNER = Owner;
  IsReboot = false;
  Result = true;
  pr1 = false;

  CheckProto = false;
  CheckMap = false;

  _DEBUG_ = "0";

  //Запоминаю имя компьютера
  ComputerNetName = QHostInfo::localHostName().toStdString();

  //Запоминаю путь к имени файла приложения
  FilePath = qApp->applicationDirPath().toStdString()+'/';

  //Главный INI-файл приложения. Запоминаю его имя и путь к нему
  IniFileName = FilePath + "Astronomer.ini";

  //>>> Создание временного каталога >>>
  Dir = new QDir();
  i = 0;

beginn:

  i = i + 1;
  TempCatalog = RandomString(10);
  TempCatalog = FilePath + TempCatalog;
  //Сгенерировал уникальное имя подкаталога для размещения временных файлов

  //Создаю случайно сгенерированный подкаталог
  if (Dir->mkdir(QString::fromStdString(TempCatalog)) == false)
  {
    //Если произошла ошибка создания случайно сгенерированного подкаталога, значит такой каталог каким-то случайным образом уже
    // есть на диске и надо перегенерировать имя подкаталога
    if (i < 100000)
      goto beginn;
    else
      Result = false;
  }

  #ifdef __unix__
  QFile f;
  f.setFileName(QString::fromStdString(TempCatalog));
  f.setPermissions(QFileDevice::ReadOwner | QFileDevice::ReadGroup | QFileDevice::ReadOther |
                   QFileDevice::WriteOwner | QFileDevice::WriteGroup | QFileDevice::WriteOther |
                   QFileDevice::ExeOwner | QFileDevice::ExeGroup | QFileDevice::ExeOther);
  #endif

  delete Dir;
  //<<< Создание временного каталога <<<

  //>>> Инициализация INI-файла >>>
  ConfigFile = new QSettings(QString::fromStdString(IniFileName), QSettings::IniFormat);

  //Каталог, в котором находится приложение (имя компьютера + путь)
  HomeCatalog = ComputerNetName+"::"+FilePath;

  if (ConfigFile->value("START/Dir", "").toString().toStdString() != HomeCatalog)
  {  //Если приложение было скопировано в другой каталог или на другой компьютер
    ConfigFile->remove("");  //Очистка всего INI-файла
    ConfigFile->setValue("START/Dir", QString::fromStdString(HomeCatalog));
    _GUID_ = QUuid::createUuid().toString().toStdString();  //Генерация нового GUID'а
    ConfigFile->setValue("START/GUID", QString::fromStdString(_GUID_));

    ConfigFile->setValue("USER/CheckProto", "0");
    ConfigFile->setValue("USER/CheckMap", "0");

    ConfigFile->setValue("USER/DEBUG","0");

    //!!! ЗДЕСЬ ПИШЕМ !!!

    pr1 = true;  //Признак первого запуска приложения
  }
  else
  {  //Если это не первый запуск приложения
    _GUID_ = ConfigFile->value("START/GUID", "").toString().toStdString();
    if (_GUID_ == "")
    {
      //Генерация GUID'а заново, т.к. соответствующая секция INI-файла почему-то испорчена
      _GUID_ = QUuid::createUuid().toString().toStdString();
      ConfigFile->setValue("START/GUID", QString::fromStdString(_GUID_));
    }

    _DEBUG_ = ConfigFile->value("USER/DEBUG", "").toString().toStdString();
    if ((_DEBUG_ != "0") && (_DEBUG_ != "1"))
    {
      ConfigFile->setValue("USER/DEBUG", "0");
    }

    if (ConfigFile->value("USER/CheckProto", "").toString().toInt() > 0)
    {
      if (ConfigFile->value("USER/CheckProto", "").toString().toInt() == 0)
        CheckProto = false;
      else
        CheckProto = true;
    }
    else
    {
      ConfigFile->setValue("USER/CheckProto", "0");
    }

    if (ConfigFile->value("USER/CheckMap", "").toString().toInt() > 0)
    {
      if (ConfigFile->value("USER/CheckMap", "").toString().toInt() == 0)
        CheckMap = false;
      else
        CheckMap = true;
    }
    else
    {
      ConfigFile->setValue("USER/CheckMap", "0");
    }

    //!!! ЗДЕСЬ ПИШЕМ !!!

  }
  delete ConfigFile;

  #ifdef __unix__
  f.setFileName(QString::fromStdString(IniFileName));
  f.setPermissions(QFileDevice::ReadOwner | QFileDevice::ReadGroup | QFileDevice::ReadOther |
                   QFileDevice::WriteOwner | QFileDevice::WriteGroup | QFileDevice::WriteOther |
                   QFileDevice::ExeOwner | QFileDevice::ExeGroup | QFileDevice::ExeOther);
  #endif

  //<<< Инициализация INI-файла <<<

  Error = new TError(static_cast<QWidget*>(OWNER));
  Wait = new TWait(static_cast<QWidget*>(OWNER));
  Tuner = new TWinTuner(static_cast<QWidget*>(OWNER));
  Tuner->OWNER = this;
  Log = new TWinLogBook(static_cast<QWidget*>(OWNER));
  Log->OWNER = this;

  Map = new TMap(static_cast<QWidget*>(OWNER));
  Map->OWNER = this;
  LayerCtrl = new TLayerCtrl(static_cast<QWidget*>(OWNER));
  LayerCtrl->OWNER = this;
  LayerAdd = new TLayerAdd(static_cast<QWidget*>(OWNER));
  ObjCtrl = new TObjCtrl(static_cast<QWidget*>(OWNER));
  ObjCtrl->OWNER = this;

  Nutation = new TNutation();

  ShellGIS = new TShellGIS();
  ShellGIS->ConnectWindow(Map->gridLayout, Map->CurCoord, Map->CurrentScale, Map->Ruler);
  ShellGIS->SetProjection(TGISLib::CYLINDRICAL);
  ShellGIS->WhatIsShow(false, true);

  (static_cast<TMainWin*>(OWNER))->IniFileName(IniFileName);
  Error->IniFileName(IniFileName);
  Wait->IniFileName(IniFileName);
  Tuner->IniFileName(IniFileName);
  Log->IniFileName(IniFileName);
  Map->IniFileName(IniFileName);
  LayerCtrl->IniFileName(IniFileName);
  LayerAdd->IniFileName(IniFileName);
  ObjCtrl->IniFileName(IniFileName);

  if (Result == false)
    Error->MessageRed("Нет прав для создания временного каталога");

  #ifndef __unix__
  //Этот вызов необходим для корректной инициализации "шрифтового менеджера" под ОС Windows
  Wait->show();
  QTimer::singleShot(1000, Wait, SLOT(close()));
  #endif


  //В случае первого запуска приложения отложенно (по таймеру) открывается окно настроек приложения
  if ((Result == true) && (pr1 == true))
  {
    (static_cast<TMainWin*>(OWNER))->FirstStart();
  }

  if (CheckProto == true)
    Log->show();

  ShellGIS->AddLayerFromMIF("моря", ":/1/Map/WorldSeas.MIF");
  ShellGIS->AddLayerFromMIF("континенты", ":/1/Map/WorldContinents.MIF");
  ShellGIS->AddLayerFromMIF("границы", ":/1/Map/WorldBorders.MIF");
  ShellGIS->AddLayerFromMIF("озера", ":/1/Map/WorldLakes.MIF");
  ShellGIS->AddLayerFromMIF("реки", ":/1/Map/WorldRivers.MIF");

  connect(ShellGIS, SIGNAL(GetDataLeftMouseARROW(TGISLib::TDataLeftMouse)),
          this, SLOT(GetDataLeftMouseARROW(TGISLib::TDataLeftMouse)));

  if (CheckMap == true)
    Map->show();
}


TBase::~TBase(void)
{
QDir *Dir;  //Класс управления каталогами
QString FilePath, LogFileName;

  //Запоминаю путь к имени файла приложения
  FilePath = qApp->applicationDirPath() + "/";

  //Главный LOG-файл приложения
  LogFileName = FilePath + "Astronomer.txt";

  Log->TextProtocol->append(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") + " Приложение остановлено");

  //Сохранить журнал в главном LOG-файле приложения
  Log->SaveToFile(LogFileName, false);

  delete Error;
  delete Wait;
  delete Tuner;
  delete Log;

  ShellGIS->DisconnectWindow();
  delete Map;
  delete LayerCtrl;
  delete LayerAdd;
  delete ObjCtrl;
  delete ShellGIS;
  delete Nutation;

  IniFileName = "";
  Result = false;

  Dir = new QDir(QString::fromStdString(TempCatalog));

  //Получаем список файлов во временном каталоге
  QStringList lstFiles = Dir->entryList(QDir::Files);

  //Удаляем временные файлы из каталога
  foreach (QString entry, lstFiles)
  {
    QString entryAbsPath = Dir->absolutePath() + "/" + entry;
    QFile::setPermissions(entryAbsPath, QFile::ReadOwner | QFile::WriteOwner);
    QFile::remove(entryAbsPath);
  }

  //Удаляем сам временный каталог
  Dir->rmdir(QString::fromStdString(TempCatalog));

  delete Dir;


  TempCatalog = "";
  OWNER = NULL;
  IsReboot = false;
}


void TBase::SunCoordinates2000(double Time, TVector *R)
{
double D, L, P, G, E, La, v, sinv, cosv, y, e1, ek, t, t2, t3, omt, psi, RSolnModul;
double ase;  //Среднее расстояние от Земли до Солнца [км]
double dn2000;  //Число суток от начала отсчета до 01.01.2000 г. + 0.5 суток
int i;
  try
  {
    dn2000 = 36526.5;  //Число суток от начала отсчета до 01.01.2000 г. + 0.5 суток
    ase = 149600000.0;
    D = Time - 0.125;
    t = (D - dn2000)/36525.0;  //Юлианский период от 12:00 01.01.2000 г.
    t2 = t*t;
    t3 = t2*t;

    //Средняя долгота
    L = 4.8481368110953599e-6*(1009677.850 + (100*1296000.0 + 2771.270)*t + 1.089*t2);

    //Долгота перигелия
    P = 4.8481368110953599e-6*(1018578.046 + 6190.046*t + 1.666*t2 + 0.012*t3);

    //Эксцентриситет земной орбиты
    ek = 0.0167086342 - 0.00004203654*t - 0.00000012673*t2;

    //Средний наклон эклиптики
    e1 = 4.8481368110953599e-6*(84381.448 - 46.84024*t - 0.00059*t2 + 0.001813*t3);

    //Истинный наклон эклиптики
    omt = 2.182438624e0 - 33.757045936e0*t + 3.61429e-5*t2 + 3.88e-8*t3;
    psi = 4.8481368110953599e-6*9.2025e0*cos(omt);
    e1 = e1 + psi;

    //Средняя аномалия Земли
    G = L - P;
    E = G + ek;

    for(i=0; i<=4; i++)
      E = G + ek * sin(E);

    //Расстояние до Земли
    RSolnModul = ase*(1.0 - ek*cos(E));
    RSolnModul = RSolnModul*1.0e3;

    //Истинная аномалия
    sinv = ase/RSolnModul*sqrt(1.0 - ek*ek)*sin(E);
    cosv = ase/RSolnModul*(cos(E) - ek);
    v = TCartography::ArcTan2(sinv, cosv);

    //Эклиптическая истинная долгота
    La = v + P;

    //Собственно вычисления координат
    R->x = RSolnModul*cos(La);
    y = RSolnModul*sin(La);
    R->y = y*cos(e1);
    R->z = y*sin(e1);
  }
  catch(...)
  {
    R->Empty();
  }
}


void TBase::MoonCoordinates2000(double Time, TVector *R)
{
double Ll, Ls, F, D, Vl, pl1, Vsin, D2, arg, betta, ep, sb, se, sl, cb, ce, cl, t, t2, t3, RLModul;
double dn2000;  //Число суток от начала отсчета до 01.01.2000 г. + 0.5 суток
  try
  {
    dn2000 = 36526.5;  //Число суток от начала отсчета до 01.01.2000 г. + 0.5 суток
    D = Time - 0.125;
    t = (D - dn2000) / 36525.0;  //Юлианский период от 12:00 01.01.2000 г.
    t2 = t * t;
    t3 = t2 * t;

    //Средняя аномалия Луны
    Ll = 2.3555483935439407 + 8328.691422883895400*t + 0.0001517951635554*t2 + 0.0000003102807559*t3;

    //Средняя аномалия Солнца
    Ls = 6.2400359393260230 + 628.3019560241841650*t - 0.0000027973749400*t2 - 0.0000000581776417*t3;

    //Средний аргумент широты Луны
    F = 1.6279019339719609 + 8433.4661583184533800*t - 0.0000642717497047*t2 + 0.0000000533295049*t3;

    //Разность средних долгот Луны и Солнца
    D = 5.1984695135799228 + 7771.3771461706410300*t - 0.0000334085107653*t2 + 0.0000000921145994*t3;

    D2 = D + D;

    //Вычисление горизонтального паралакса
    pl1 = 4.8481368110953599e-6*(3422.7+28.233*cos(D2)+
          3.086*cos(Ll+D2)+186.539*cos(Ll)+34.311*cos(Ll-D2)+
          0.6*cos(Ll-4*D)-0.399*cos(Ls)+
          1.917*cos(Ls-D2)-0.978*cos(D)+10.165*cos(2*Ll)-
          0.949*cos(Ll+Ls)+1.443*cos(Ll+Ls-D2)+1.152*cos(Ll-Ls)+
          0.621*cos(3*Ll)-0.713*cos(Ll-2*F));

    RLModul = 6378.14/pl1;
    RLModul = RLModul*1.0e3;

    //Средняя долгота Луны
    Vl = 3.8103405583329555 + 8399.7091123847003500*t - 0.0000281288897780*t2 + 0.0000000921145994*t3;

    //Вычисление эклиптической долготы Луны
    Vsin = 4.8481368110953599e-6*(2369.9*sin(D2)+191.95*sin(Ll+D2)+
           22639.5*sin(Ll)-4586.42*sin(Ll-D2)-668.11*sin(Ls)-
           165.14*sin(Ls-D2)-125.15*sin(D)+769.01*sin(2*Ll)-
           211.65*sin(2*Ll-D2)-109.66*sin(Ll+Ls)-
           205.96*sin(Ll+Ls-D2)+147.69*sin(Ll-Ls)-411.6*sin(2*F));
    arg = Vl + Vsin;
    cl = cos(arg);
    sl = sin(arg);

    //Вычисление эклиптической широты Луны
    betta = 4.8481368110953599e-6*(117.26*sin(F+D2)+18461.48*sin(F)-
            623.65*sin(F-D2)+1010.18*sin(Ll+F)-
            166.57*sin(Ll+F-D2)+199.48*sin(-Ll+F+D2)-
            999.69*sin(-Ll+F));
    cb = cos(betta);
    sb = sin(betta);

    //Средний наклон эклиптики
    ep = 0.4090928042223290 - 0.0002269655248114*t - 0.0000000028604007*t2 + 0.0000000087896720*t3;
    ce = cos(ep);
    se = sin(ep);

    R->x = RLModul*cl*cb;
    R->y = RLModul*(sl*cb*ce - sb*se);
    R->z = RLModul*(sb*ce + sl*cb*se);
  }
  catch (...)
  {
    R->Empty();
  }
}


double TBase::LunarHeight(double Time, TVector Point)
{
TVector Moon;
double RMoon, RPoint, result;
  try
  {
    MoonCoordinates2000(Time, &Moon);  //Координаты Луны в Абсолютной СК

    Moon = OtnToAbsMatrixPrecision(Time).getTrans() * Moon;  //Координаты Луны в Гринвичской СК

    RMoon = Moon.getModul();
    RPoint = Point.getModul();
    result = TCartography::ArcSin((Moon.x*Point.x + Moon.y*Point.y + Moon.z*Point.z)/(RPoint*RMoon));
  }
  catch(...)
  {
    result = 0.0;
  }
return result;
}


double TBase::SolarHeight(double Time, TVector Point)
{
TVector Sun;
double RSun, RPoint, result;
  try
  {
    SunCoordinates2000(Time, &Sun);  //Координаты Солнца в Абсолютной СК

    Sun = OtnToAbsMatrixPrecision(Time).getTrans() * Sun;  //Координаты Солнца в Гринвичской СК

    RSun = Sun.getModul();
    RPoint = Point.getModul();
    result = TCartography::ArcSin((Sun.x*Point.x + Sun.y*Point.y + Sun.z*Point.z)/(RPoint*RSun));
  }
  catch(...)
  {
    result = 0.0;
  }
return result;
}


TMatrix TBase::OtnToAbsMatrixPrecision(double Time)
{
TMatrix M, S, N, Pr;
double T, T2, T3, Npsi, Neps, Eps0, StarTime;
  try
  {
    //Истинное звездное время
    StarTime = Nutation->StarTimeTrue(Time);

    //Матрица звездного времени (из АСК в ГСК)
    S = Nutation->OtnToAbsStarTimeMatrix(StarTime).getTrans();

    //Расчет юлианских столетий
    Nutation->Julian2000(Time, &T, &T2, &T3);

    //Расчет нутации Земли в долготе и наклоне, а также среднего наклона эклиптики к экватору
    Nutation->NutationDolgotaNaklon(T, T2, T3, &Npsi, &Neps, &Eps0);

    //Матрица нутации (из АСК в ГСК)
    N = Nutation->NutationMatrix(Npsi, Neps, Eps0);

    //Матрица прецессии (из АСК в ГСК)
    Pr = Nutation->PrecessionMatrix(T, T2, T3);

    //Матрица вращения (перехода) из Гринвичской СК в Абсолютную СК с учетом прецессии, нутации, звездного времени
    M = (Pr.getTrans()*N.getTrans())*S.getTrans();
  }
  catch(...)
  {
    M.Empty();
  }
return M;
}


void TBase::AbsToOtnPrecision(TVector RAbs, TVector VAbs, double Time, TVector *ROtn, TVector *VOtn)
{
TMatrix M;
double WZ;  //Угловая скорость вращения Земли из ПЗ-90.02
  try
  {
    WZ = 0.7292115e-4;
    M = OtnToAbsMatrixPrecision(Time).getTrans();
    *ROtn = M*RAbs;
    *VOtn = M*VAbs;

    VOtn->x = VOtn->x + WZ * ROtn->y;
    VOtn->y = VOtn->y - WZ * ROtn->x;
  }
  catch(...)
  {
    ROtn->Empty();
    VOtn->Empty();
  }
}


void TBase::GetDataLeftMouseARROW(TGISLib::TDataLeftMouse Value)
{
  Error->MessageGreen("Bn=" + std::to_string(Value.CoordDown.B*180.0/M_PI) + " " + "Ln="
                      + std::to_string(Value.CoordDown.L*180.0/M_PI) + " " +
                      "Bk=" + std::to_string(Value.CoordUp.B*180.0/M_PI) + " " + "Lk="
                      + std::to_string(Value.CoordUp.L*180.0/M_PI));
}


void TBase::HowCalc(qint64 Index, qint64 Quantity)
{
int _Index;
bool pr;
  _Index = static_cast<int>((static_cast<double>(Index) / static_cast<double>(Quantity)) * 100.0);
  pr = false;

  switch (_Index)
  {
    case 0:
      pr = true;
    break;

    case 10:
      pr = true;
    break;

    case 20:
      pr = true;
    break;

    case 30:
      pr = true;
    break;

    case 40:
      pr = true;
    break;

    case 50:
      pr = true;
    break;

    case 60:
      pr = true;
    break;

    case 70:
      pr = true;
    break;

    case 80:
      pr = true;
    break;

    case 90:
      pr = true;
    break;

    case 100:
      pr = true;
    break;
  }

  if (pr == true)
  {
    qApp->processEvents();
    (static_cast<TMainWin*>(OWNER))->progressBar->setMinimum(0);
    (static_cast<TMainWin*>(OWNER))->progressBar->setMaximum(100);
    (static_cast<TMainWin*>(OWNER))->progressBar->setValue(_Index);
    qApp->processEvents();
  }
}


std::string TBase::RandomString(int PLen)
{
std::string str1, Result;
std::mt19937 gen(static_cast<unsigned>(time(NULL)));  //Создаю генератор с произвольным начальным состоянием
std::uniform_int_distribution<> Distr(0, 25);  //Создаю равномерное целочисленное распределение

  str1 = "abcdefghijklmnopqrstuvwxyz";  //Строка "алфавита", из символов которого будет сгенерирована результирующая строка
  Result = "";
  do
    Result = Result + str1[static_cast<unsigned>(Distr(gen))];
  while (Result.size() < static_cast<unsigned>(PLen));

  return Result;
}


std::string TBase::GetTempCatalog()
{
  return TempCatalog;
}


void TBase::AddToLogBook(QString Value)
{
QString FilePath, LogFileName;
  if (Log->TextProtocol->document()->lineCount() > 500)
  {
    //Запоминаю путь к имени файла приложения
    FilePath = qApp->applicationDirPath() + "/";

    //Главный LOG-файл приложения
    LogFileName = FilePath + "Astronomer.txt";

    Log->TextProtocol->append(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") + " Протокол переполнен");

    //Сохранить переполненный журнал в главном LOG-файле приложения
    Log->SaveToFile(LogFileName, false);

    Log->TextProtocol->document()->clear();

    Log->TextProtocol->append(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") +
                              " Содержимое протокола автоматически сохранено в главном LOG-файле приложения");

    Log->TextProtocol->append(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") + " Протокол очищен");
  }
  Log->TextProtocol->append(Value);

  //Прокрутка текста вниз
  QTextCursor cursor = Log->TextProtocol->textCursor();
  cursor.movePosition(QTextCursor::End);
  Log->TextProtocol->setTextCursor(cursor);
}


void TBase::AddToLogBookCurrentTime(QString Value)
{
  AddToLogBook(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") + " " + Value);
}
