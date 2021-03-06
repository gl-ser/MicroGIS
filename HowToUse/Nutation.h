//----------------------------------------------------------------------------//
//                              *** АСТРОНОМ ***                              //
//                                                                            //
// Файл Nutation.h                                                            //
//                                                                            //
//     *** TNUTATION КЛАСС РЕАЛИЗУЕТ МОДЕЛЬ ПРЕЦЕССИИ И НУТАЦИИ ЗЕМЛИ ***     //
//                                                                            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef NutationH
#define NutationH

#include <vector>
#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include "../../QuatVectMatr/GeneralLib.h"
#include "../../GIS/Cartography.h"


class TNutation
{
  private:
    //--- Константы для нутации ---

    //Каждая строка описывает константы при членах, стоящих под знаком суммы
    // Первые 5 чисел в каждой строке описывают коэффициенты при фундаментальных
    // аргументах L,Lm,F,D,Om, где
    // L - средняя аномалия Луны;
    // Lm - средняя аномалия Солнца;
    // F - средний аргумент широты Луны;
    // D - разность средних долгот Луны и Солнца;
    // Om - средняя долгота восходящего узла орбиты Луны на эклиптике.
    // Числа под индексами 6, 7 и 10 в каждой строке являются коэффициентами
    // A, B и C в разложении нутации в долготе.
    // Числа под индексами 8, 9 и 11 в каждой строке являются коэффициентами
    // A, B и C в разложении нутации в наклоне.
    // Размерность чисел под индексами 6-11 - это десятые доли угловых милисекунд
    double CONST_NUTATION[678][11];

    //Вычисляет в радианах фундаментальные аргументы:
    // Eps0 - средний наклон эклиптики к экватору;
    // L - средняя аномалия Луны;
    // Lm - средняя аномалия Солнца;
    // F - средний аргумент широты Луны;
    // D - разность средних долгот Луны и Солнца;
    // Om - средняя долгота восходящего узла орбиты Луны на эклиптике.
    // На вход подается время в юлианских столетиях от начала эпохи J2000
    void Fundamental(double T, double T2, double T3, double* Eps0, double* L, double* Lm, double* F, double* D, double* Om);

  public:
    TNutation(void);
    virtual ~TNutation(void);

    //Расчет истинного Звездого времени от начала эпохи J2000
    double StarTimeTrue(double Time);

    //Вычисляет матрицу звездного времени для перехода из Гринвичской СК в Абсолютную СК одной и той же эпохи
    // На вход подается звездное время [рад]
    TMatrix OtnToAbsStarTimeMatrix(double StarTime);

    //Возвращает время (а также время в квадрате и время в кубе) в юлианских столетиях, прошедших от 12:00 01.01.2000 г.
    // до заданного момента времени
    // На вход подается текущее декретное московское время
    void Julian2000(double Time, double* T, double* T2, double* T3);

    //Вычисляет нутацию в долготе (Npsi) и нутацию в наклоне (Neps) в радианах, а также средний наклон эклиптики к экватору Eps0
    // На вход подается время в юлианских столетиях от начала эпохи J2000
    void NutationDolgotaNaklon(double T, double T2, double T3, double* Npsi, double* Neps, double* Eps0);

    //Вычисляет нутацию в долготе (Npsi) и нутацию в наклоне (Neps) в радианах по упрощенной формуле без
    // использования массива констант
    // На вход подается время в юлианских столетиях от начала эпохи J2000
    void NutationDolgotaNaklonSimple(double T, double T2, double T3, double* Npsi, double* Neps, double* Eps0);

    //Вычисляет матрицу нутации
    // На вход подается нутация в долготе, нутация в наклоне, средний наклон эклиптики к экватору
    TMatrix NutationMatrix(double Npsi, double Neps, double Eps0);

    //Вычисляет матрицу прецессии
    // На вход подается время в юлианских столетиях от начала эпохи J2000
    TMatrix PrecessionMatrix(double T, double T2, double T3);
};


#endif
