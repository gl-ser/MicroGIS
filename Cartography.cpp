//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл Cartography.cpp                                                       //
//                                                                            //
//            *** TCARTOGRAPHY КАРТОГРАФИЧЕСКИЕ ПРЕОБРАЗОВАНИЯ ***            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include "Cartography.h"
#include "GISLib.h"


TCartography::TCartography(void)
{
  OWNER = NULL;
  RZEkv = 0.6378136e+7;
  ALPHA = 0.003352803743019476734910221586237;
}


TCartography::~TCartography(void)
{
  OWNER = NULL;
}


double TCartography::ArcSin(double Value)
{
double F;
  try
  {
    if (Value <= -1.0) Value = -1.0;
    if (Value >= 1.0) Value = 1.0;
    F = asin(Value);
  }
  catch(...)
  {
    F = 0.0;
  }
return F;
}


double TCartography::Tan(double Value)
{
double c, s, r;
  c = cos(Value);
  s = sin(Value);

  if (fabs(c) < 0.0000001)
  {
    if (s > 0.0)
      Value = 89.9*M_PI/180.0;
    else
      Value = 90.1*M_PI/180.0;
  }

  r = tan(Value);
  return r;
}


double TCartography::ArcTan2(double Y, double X)
{
double F;
  try
  {
    if ((Y != 0.0) && (X != 0.0))
      F = atan2(Y,X);
    else
      F = 0.0;
  }
  catch(...)
  {
    F = 0.0;
  }
return F;
}


double TCartography::ArcTan(double sinF, double cosF)
{
double F;
  try
  {
    if (cosF != 0.0)
    {
      F = sinF/cosF;
      F = atan(F);
      if (cosF < 0.0) F = F + M_PI; else if (F < 0.0) F = F + M_PI + M_PI;
    }
    else
    {
      F = M_PI/2.0;
      if (sinF < 0.0) F = F + M_PI;
    }
  }
  catch(...)
  {
    F = 0.0;
  }
  return F;
}


int TCartography::Trunc(double Value)
{
int res;
  try
  {
    res = 0;
    if (Value < 0.0)
    {
      res = static_cast<int>(floor(fabs(Value)));
      res = res * (-1);
    }
    else
    {
      res = static_cast<int>(floor(Value));
    }
  }
  catch(...)
  {
    res = 0;
  }
return res;
}


void TCartography::FiLambdaToCylindricalEqualSpaceXY(double Fi, double Lambda, double *X, double *Y)
{
  if ((static_cast<TGISLib*>(OWNER))->Projection.Number == TGISLib::CYLINDRICAL)
  {
    *X = Lambda*180.0/M_PI - (static_cast<TGISLib*>(OWNER))->Projection.L0;
    *Y = Fi*180.0/M_PI - (static_cast<TGISLib*>(OWNER))->Projection.Fi0;
  }
  else
  {
    *X = 0.0;
    *Y = 0.0;
  }
}


void TCartography::CylindricalEqualSpaceXYToFiLambda(double X, double Y, double *Fi, double *Lambda)
{
  if ((static_cast<TGISLib*>(OWNER))->Projection.Number == TGISLib::CYLINDRICAL)
  {
    *Lambda = (X + (static_cast<TGISLib*>(OWNER))->Projection.L0)*M_PI/180.0;
    *Fi = (Y + (static_cast<TGISLib*>(OWNER))->Projection.Fi0)*M_PI/180.0;
  }
  else
  {
    *Fi = 0.0;
    *Lambda = 0.0;
  }
}


void TCartography::FiLambdaToAzimuthOrthographicNorthXY(double Fi, double Lambda, double *X, double *Y)
{
double SinFi0, CosFi0, SinFi, CosFi, CosLambdaMinusLambda0, CosC;

  if ((static_cast<TGISLib*>(OWNER))->Projection.Number == TGISLib::NORTHPOLE)
  {
    if (Fi < 0.0)
      Fi = 0.0;

    SinFi0 = sin((static_cast<TGISLib*>(OWNER))->Projection.Fi0*M_PI/180.0);
    CosFi0 = cos((static_cast<TGISLib*>(OWNER))->Projection.Fi0*M_PI/180.0);
    SinFi = sin(Fi);
    CosFi = cos(Fi);
    CosLambdaMinusLambda0 = cos(Lambda - (static_cast<TGISLib*>(OWNER))->Projection.L0*M_PI/180.0);

    //CosC = SinFi0*SinFi + CosFi0*CosFi*CosLambdaMinusLambda0;
    CosC = 0.0;
    if (CosC >= 0.0)
    {
      *X = RZEkv*CosFi*sin(Lambda - (static_cast<TGISLib*>(OWNER))->Projection.L0*M_PI/180.0);
      *Y = RZEkv*(CosFi0*SinFi - SinFi0*CosFi*CosLambdaMinusLambda0);
    }
    else
    {
      *X = 0.0;
      *Y = 0.0;
    }
  }
  else
  {
    *X = 0.0;
    *Y = 0.0;
  }
}


void TCartography::AzimuthOrthographicNorthXYToFiLambda(double X, double Y, double *Fi, double *Lambda)
{
double c, ro, SinC, CosC, SinFi0, CosFi0;

  if ((static_cast<TGISLib*>(OWNER))->Projection.Number == TGISLib::NORTHPOLE)
  {
    ro = sqrt(X*X + Y*Y);
    c = ArcSin(ro/RZEkv);

    SinC = sin(c);
    CosC = cos(c);
    SinFi0 = sin((static_cast<TGISLib*>(OWNER))->Projection.Fi0*M_PI/180.0);
    CosFi0 = cos((static_cast<TGISLib*>(OWNER))->Projection.Fi0*M_PI/180.0);

    *Fi = ArcSin(CosC*SinFi0 + Y*SinC*CosFi0/ro);
    *Lambda = (static_cast<TGISLib*>(OWNER))->Projection.L0*M_PI/180.0 + ArcTan2(X*SinC, ro*CosC*CosFi0 - Y*SinC*SinFi0);
  }
  else
  {
    *Fi = 0.0;
    *Lambda = 0.0;
  }
}


void TCartography::FiLambdaToAzimuthOrthographicSouthXY(double Fi, double Lambda, double *X, double *Y)
{
double SinFi0, CosFi0, SinFi, CosFi, CosLambdaMinusLambda0, CosC;

  if ((static_cast<TGISLib*>(OWNER))->Projection.Number == TGISLib::SOUTHPOLE)
  {
    if (Fi > 0.0)
      Fi = 0.0;

    SinFi0 = sin((static_cast<TGISLib*>(OWNER))->Projection.Fi0*M_PI/180.0);
    CosFi0 = cos((static_cast<TGISLib*>(OWNER))->Projection.Fi0*M_PI/180.0);
    SinFi = sin(Fi);
    CosFi = cos(Fi);
    CosLambdaMinusLambda0 = cos(Lambda - (static_cast<TGISLib*>(OWNER))->Projection.L0*M_PI/180.0);

    //CosC = SinFi0*SinFi + CosFi0*CosFi*CosLambdaMinusLambda0;
    CosC = 0.0;
    if (CosC >= 0.0)
    {
      *X = RZEkv*CosFi*sin(Lambda - (static_cast<TGISLib*>(OWNER))->Projection.L0*M_PI/180.0);
      *Y = RZEkv*(CosFi0*SinFi - SinFi0*CosFi*CosLambdaMinusLambda0);
    }
    else
    {
      *X = 0.0;
      *Y = 0.0;
    }
  }
  else
  {
    *X = 0.0;
    *Y = 0.0;
  }
}


void TCartography::AzimuthOrthographicSouthXYToFiLambda(double X, double Y, double *Fi, double *Lambda)
{
double c, ro, SinC, CosC, SinFi0, CosFi0;

  if ((static_cast<TGISLib*>(OWNER))->Projection.Number == TGISLib::SOUTHPOLE)
  {
    ro = sqrt(X*X + Y*Y);
    c = ArcSin(ro/RZEkv);

    SinC = sin(c);
    CosC = cos(c);
    SinFi0 = sin((static_cast<TGISLib*>(OWNER))->Projection.Fi0*M_PI/180.0);
    CosFi0 = cos((static_cast<TGISLib*>(OWNER))->Projection.Fi0*M_PI/180.0);

    *Fi = ArcSin(CosC*SinFi0 + Y*SinC*CosFi0/ro);
    *Lambda = (static_cast<TGISLib*>(OWNER))->Projection.L0*M_PI/180.0 + ArcTan2(X*SinC, ro*CosC*CosFi0 - Y*SinC*SinFi0);
  }
  else
  {
    *Fi = 0.0;
    *Lambda = 0.0;
  }
}


void TCartography::FiLambdaToMercatorXY(double Fi, double Lambda, double *X, double *Y)
{
  if ((static_cast<TGISLib*>(OWNER))->Projection.Number == TGISLib::MERCATOR)
  {
    if (Fi > 85.0*M_PI/180.0)
      Fi = 85.0*M_PI/180.0;

    if (Fi < -85.0*M_PI/180.0)
      Fi = -85.0*M_PI/180.0;

    *X = (Lambda - (static_cast<TGISLib*>(OWNER))->Projection.L0)*RZEkv;
    *Y = RZEkv*log(Tan(Fi/2.0 + M_PI/4.0));
  }
  else
  {
    *X = 0.0;
    *Y = 0.0;
  }
}


void TCartography::MercatorXYToFiLambda(double X, double Y, double *Fi, double *Lambda)
{
  if ((static_cast<TGISLib*>(OWNER))->Projection.Number == TGISLib::MERCATOR)
  {
    *Lambda = X/RZEkv + (static_cast<TGISLib*>(OWNER))->Projection.L0;
    *Fi = M_PI/2.0 - 2.0*atan(pow(M_E,-Y/RZEkv));
  }
  else
  {
    *Fi = 0.0;
    *Lambda = 0.0;
  }
}


void TCartography::FiLambdaToKavrayskiyXY(double Fi, double Lambda, double *X, double *Y)
{
double A;
  if ((static_cast<TGISLib*>(OWNER))->Projection.Number == TGISLib::KAVRAYSKIY)
  {
    A = M_PI*M_PI/3.0 - Fi*Fi;

    if (A < 0.0)
      *X = 0.0;
    else
      *X = 3.0*Lambda/(2.0*M_PI)*sqrt(M_PI*M_PI/3.0 - Fi*Fi);

    *Y = Fi;
  }
  else
  {
    *X = 0.0;
    *Y = 0.0;
  }
}


void TCartography::KavrayskiyXYToFiLambda(double X, double Y, double *Fi, double *Lambda)
{
double A;
  if ((static_cast<TGISLib*>(OWNER))->Projection.Number == TGISLib::KAVRAYSKIY)
  {
    A = M_PI*M_PI/3.0 - Y*Y;

    if (A <= 0.0)
      *Lambda = 0.0;
    else
      *Lambda = 2.0*M_PI*X/(3.0*sqrt(A));

    *Fi = Y;
  }
  else
  {
    *Fi = 0.0;
    *Lambda = 0.0;
  }
}


double TCartography::FiToB(double Fi, double H)
{
  return ArcTan2(sin(Fi), (0.993306+0.000001*0.0011*H)*cos(Fi));
}


double TCartography::BToFi(double B, double H)
{
  return ArcTan2((0.993306+0.000001*0.0011*H)*sin(B), cos(B));
}


void TCartography::BLHToOtn(double B, double L, double H, TVector *R)
{
double N, M, sb, cb, sl, cl;
double RZEkv = 0.6378136e+7;
double ALPHA = 0.003352803743019476734910221586237;
  try
  {
    sb = sin(B);
    cb = cos(B);
    sl = sin(L);
    cl = cos(L);
    N = RZEkv / sqrt( 1.0 - ALPHA * (2.0 - ALPHA) * sb * sb);
    M = (1 - ALPHA) * (1 - ALPHA) * N;
    R->x = (N + H) * cb * cl;
    R->y = (N + H) * cb * sl;
    R->z = (M + H) * sb;
  }
  catch(...)
  {
    R->Empty();
  }
}


void TCartography::OtnToBLH(TVector R, double *B, double *L, double *H)
{
double rr, r1, fic, eMal, Re, delta, ekvadrat, SinFiC, CosFiC;
double RZEkv = 0.6378136e+7;
double ALPHA = 0.003352803743019476734910221586237;
  try
  {
    if (R.getModul() == 0.0)
    {
      *B = 0.0;
      *L = 0.0;
      *H = 0.0;
    }
    else
    {
      *L = ArcTan2(R.y, R.x);
      if (*L < 0.0) *L = M_PI*2.0 + *L;
      r1 = static_cast<double>(sqrt(R.x*R.x + R.y*R.y));
      rr = static_cast<double>(sqrt(r1*r1 + R.z*R.z));
      SinFiC = R.z / rr;
      CosFiC = r1 / rr;
      fic = ArcTan2(R.z, r1);
      ekvadrat = (2.0 - ALPHA) * ALPHA;
      r1 = 1.0 - ekvadrat * CosFiC * CosFiC;
      delta = ekvadrat * SinFiC * CosFiC / r1;
      Re = RZEkv * sqrt(1.0 - ekvadrat) / sqrt(r1);
      eMal = Re * delta / rr;
      *B = fic + eMal;
      *H = (rr - Re) * (1.0 - eMal * delta / 2.0);
    }
  }
  catch(...)
  {
    *B = 0.0;
    *L = 0.0;
    *H = 0.0;
  }
}


double TCartography::AzimuthOfEnd(double B1, double L1, double H1, double B2, double L2, double H2)
{
double sb1, cb1, sl1, cl1, xn, yn, zn, x, y, z, rez4, rez6, r1, r2, r3, r4, Result;
TVector RR;
  try
  {
    //ПЕРЕВОД В ГСК ТОЧКИ НОМЕР 1
    sb1 = sin(B1);
    cb1 = cos(B1);
    sl1 = sin(L1);
    cl1 = cos(L1);
    TCartography::BLHToOtn(B1, L1, H1, &RR);
    xn = RR.x;
    yn = RR.y;
    zn = RR.z;

    //ПЕРЕВОД В ГСК ТОЧКИ НОМЕР 2
    TCartography::BLHToOtn(B2, L2, H2, &RR);
    x = RR.x;
    y = RR.y;
    z = RR.z;

    //ПЕРЕВОД В ТОПОЦЕНТРИЧЕСКУЮ СК ТОЧКИ НОМЕР 2 ОТНОСИТЕЛЬНО ТОЧКИ 1
    r1 = z-zn;
    r2 = x-xn;
    r3 = y-yn;
    r4 = r2*cl1+r3*sl1;
    rez4 = cb1*r1-sb1*r4;
    rez6 = r3*cl1-r2*sl1;

    //РАСЧЕТ АЗИМУТА НА ТОЧКУ НОМЕР 2 ОТ ТОЧКИ 1
    Result = TCartography::ArcTan(rez6, rez4);
  }
  catch(...)
  {
    Result = 0.0;
  }
return Result;
}


double TCartography::Strain(double X, double A, double B, double Alpha, double Betta)
{
  return ((X-A)/(B-A))*(Betta - Alpha) + Alpha;
}


bool TCartography::MiddlePointOnRoute(double Corner, TVector StartPoint, TVector StopPoint,
                                      double AEarthOskul, double BEarthOskul, TVector *MiddlePoint)
{
TQuaternion Q;
TVector Norm;
double r;
  try
  {
    //Вычисляю вектор нормали к плоскости маршрута (Плоскость маршрута проходит через точки начала, конца
    // маршрута и центр Земли)
    Norm = StartPoint^StopPoint;

    //Вычисляю кватернион, с помощью которого я поверну радиус-вектор точки начала маршрута на заданный угол Corner
    // При этом угол Corner будет лежать в плоскости маршрута
    Q.MakeQuat(Corner,Norm);

    //Поворачиваю радиус-вектор точки начала маршрута на заданный плоский угол с помощью кватерниона
    *MiddlePoint = Q*StartPoint;
    //Но пока точка MiddlePoint в общем случае не лежит на поверхности Оскулирующей Земли. Она либо под поверхностью
    // Оскулирующей Земли, либо над ней. Потому что поворот выполнен вокруг центра Земли (как поворот внутри сферы),
    // а Земля имеет форму эллипсоида

    //Вычисляю координаты точки пересечения луча, на котором лежит радиус-вектор, и Оскулирующей Земли
    r = 1.0/sqrt(MiddlePoint->x*MiddlePoint->x/(AEarthOskul*AEarthOskul)
              + MiddlePoint->y*MiddlePoint->y/(AEarthOskul*AEarthOskul)
              + MiddlePoint->z*MiddlePoint->z/(BEarthOskul*BEarthOskul));

    MiddlePoint->x = MiddlePoint->x * r;
    MiddlePoint->y = MiddlePoint->y * r;
    MiddlePoint->z = MiddlePoint->z * r;

    return true;
  }
  catch(...)
  {
    MiddlePoint->Empty();
    return false;
  }
}


void TCartography::PZ90BLToFiLambda(double B, double L, double H, double* Fi, double* Lambda)
{
  *Fi = BToFi(B, H);
  *Lambda = L;
}


void TCartography::FiLambdaToPZ90BL(double Fi, double Lambda, double H, double *B, double *L)
{
  *B = FiToB(Fi, H);
  *L = Lambda;
}


void TCartography::ScreenXYToProjectionXY(double ScreenX, double ScreenY, double *X, double *Y)
{
double ProX, ProY;
  //Так как начало сценической системы координат расположено в центре "вида", а начало плановой системы координат
  // из-за сдвига её пользователем может находиться за пределами "вида", именно поэтому изменение пропорциональности
  // картинки (ProX/ProY или ProY/ProX) производится для сценической системы координат.
  // Нельзя применять изменение пропорциональности картинки для плановой системы координат

  //Оси OY сценической и плановой систем координат направлены в противоположные стороны. Из-за вышеуказанной симметричности
  // сценической системы относительно "вида", умножение Y на (-1) производится именно для сценических координат.
  // Умножать Y на (-1) для плановых координат нельзя

  //Взаимные отношения величин ProX и ProY задают соотношение сторон экрана (пропорциональность картинки)
  ProX = (static_cast<TGISLib*>(OWNER))->ProportionX;
  ProY = (static_cast<TGISLib*>(OWNER))->ProportionY;

  if (fabs((static_cast<TGISLib*>(OWNER))->GetScale() - 100.0) <= 0.0001)
  {  //Для масштаба 100%
    if (ProX > ProY)
    {  //Картинку надо сжать по вертикали, потому что она по вертикали сильно растянута
      *X = Strain(ScreenX, (static_cast<TGISLib*>(OWNER))->Screen.Xmin,
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmax,
                           (static_cast<TGISLib*>(OWNER))->Projection.Map.Xmin,
                           (static_cast<TGISLib*>(OWNER))->Projection.Map.Xmax);

      *Y = Strain((-1)*ScreenY, (static_cast<TGISLib*>(OWNER))->Screen.Ymin*(ProY/ProX),
                                (static_cast<TGISLib*>(OWNER))->Screen.Ymax*(ProY/ProX),
                                (static_cast<TGISLib*>(OWNER))->Projection.Map.Ymin,
                                (static_cast<TGISLib*>(OWNER))->Projection.Map.Ymax);
    }
    else
    {  //Картинку надо сжать по горизонтали, потому что она по горизонтали сильно растянута
      *X = Strain(ScreenX, (static_cast<TGISLib*>(OWNER))->Screen.Xmin*(ProX/ProY),
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmax*(ProX/ProY),
                           (static_cast<TGISLib*>(OWNER))->Projection.Map.Xmin,
                           (static_cast<TGISLib*>(OWNER))->Projection.Map.Xmax);

      *Y = Strain((-1)*ScreenY, (static_cast<TGISLib*>(OWNER))->Screen.Ymin,
                                (static_cast<TGISLib*>(OWNER))->Screen.Ymax,
                                (static_cast<TGISLib*>(OWNER))->Projection.Map.Ymin,
                                (static_cast<TGISLib*>(OWNER))->Projection.Map.Ymax);
    }
  }
  else
  {  //Для любого другого масштаба (не 100%)
    if (ProX > ProY)
    {  //Картинку надо сжать по вертикали, потому что она по вертикали сильно растянута
      *X = Strain(ScreenX, (static_cast<TGISLib*>(OWNER))->Screen.Xmin,
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmax,
                           (static_cast<TGISLib*>(OWNER))->PlaneCoord.Xmin,
                           (static_cast<TGISLib*>(OWNER))->PlaneCoord.Xmax);

      *Y = Strain((-1)*ScreenY, (static_cast<TGISLib*>(OWNER))->Screen.Ymin*(ProY/ProX),
                                (static_cast<TGISLib*>(OWNER))->Screen.Ymax*(ProY/ProX),
                                (static_cast<TGISLib*>(OWNER))->PlaneCoord.Ymin,
                                (static_cast<TGISLib*>(OWNER))->PlaneCoord.Ymax);
    }
    else
    {  //Картинку надо сжать по горизонтали, потому что она по горизонтали сильно растянута
      *X = Strain(ScreenX, (static_cast<TGISLib*>(OWNER))->Screen.Xmin*(ProX/ProY),
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmax*(ProX/ProY),
                           (static_cast<TGISLib*>(OWNER))->PlaneCoord.Xmin,
                           (static_cast<TGISLib*>(OWNER))->PlaneCoord.Xmax);

      *Y = Strain((-1)*ScreenY, (static_cast<TGISLib*>(OWNER))->Screen.Ymin,
                                (static_cast<TGISLib*>(OWNER))->Screen.Ymax,
                                (static_cast<TGISLib*>(OWNER))->PlaneCoord.Ymin,
                                (static_cast<TGISLib*>(OWNER))->PlaneCoord.Ymax);
    }
  }
}


void TCartography::ProjectionXYToScreenXY(double X, double Y, double *ScreenX, double *ScreenY)
{
double ProX, ProY;
  //Так как начало сценической системы координат расположено в центре "вида", а начало плановой системы координат
  // из-за сдвига её пользователем может находиться за пределами "вида", именно поэтому изменение пропорциональности
  // картинки (ProX/ProY или ProY/ProX) производится для сценической системы координат.
  // Нельзя применять изменение пропорциональности картинки для плановой системы координат

  //Оси OY сценической и плановой систем координат направлены в противоположные стороны. Из-за вышеуказанной симметричности
  // сценической системы относительно "вида", умножение Y на (-1) производится именно для сценических координат.
  // Умножать Y на (-1) для плановых координат нельзя

  //Взаимные отношения величин ProX и ProY задают соотношение сторон экрана (пропорциональность картинки)
  ProX = (static_cast<TGISLib*>(OWNER))->ProportionX;
  ProY = (static_cast<TGISLib*>(OWNER))->ProportionY;

  if (fabs((static_cast<TGISLib*>(OWNER))->GetScale() - 100.0) <= 0.0001)
  {  //Для масштаба 100%
    if (ProX > ProY)
    {  //Картинку надо сжать по вертикали, потому что она по вертикали сильно растянута
      *ScreenX = Strain(X, (static_cast<TGISLib*>(OWNER))->Projection.Map.Xmin,
                           (static_cast<TGISLib*>(OWNER))->Projection.Map.Xmax,
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmin,
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmax);

      *ScreenY = Strain(Y, (static_cast<TGISLib*>(OWNER))->Projection.Map.Ymin,
                           (static_cast<TGISLib*>(OWNER))->Projection.Map.Ymax,
                           (static_cast<TGISLib*>(OWNER))->Screen.Ymin*(ProY/ProX),
                           (static_cast<TGISLib*>(OWNER))->Screen.Ymax*(ProY/ProX));
    }
    else
    {  //Картинку надо сжать по горизонтали, потому что она по горизонтали сильно растянута
      *ScreenX = Strain(X, (static_cast<TGISLib*>(OWNER))->Projection.Map.Xmin,
                           (static_cast<TGISLib*>(OWNER))->Projection.Map.Xmax,
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmin*(ProX/ProY),
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmax*(ProX/ProY));

      *ScreenY = Strain(Y, (static_cast<TGISLib*>(OWNER))->Projection.Map.Ymin,
                           (static_cast<TGISLib*>(OWNER))->Projection.Map.Ymax,
                           (static_cast<TGISLib*>(OWNER))->Screen.Ymin,
                           (static_cast<TGISLib*>(OWNER))->Screen.Ymax);
    }
    *ScreenY = (-1)*(*ScreenY);
  }
  else
  {  //Для любого другого масштаба (не 100%)
    if (ProX > ProY)
    {  //Картинку надо сжать по вертикали, потому что она по вертикали сильно растянута
      *ScreenX = Strain(X, (static_cast<TGISLib*>(OWNER))->PlaneCoord.Xmin,
                           (static_cast<TGISLib*>(OWNER))->PlaneCoord.Xmax,
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmin,
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmax);

      *ScreenY = Strain(Y, (static_cast<TGISLib*>(OWNER))->PlaneCoord.Ymin,
                           (static_cast<TGISLib*>(OWNER))->PlaneCoord.Ymax,
                           (static_cast<TGISLib*>(OWNER))->Screen.Ymin*(ProY/ProX),
                           (static_cast<TGISLib*>(OWNER))->Screen.Ymax*(ProY/ProX));
    }
    else
    {  //Картинку надо сжать по горизонтали, потому что она по горизонтали сильно растянута
      *ScreenX = Strain(X, (static_cast<TGISLib*>(OWNER))->PlaneCoord.Xmin,
                           (static_cast<TGISLib*>(OWNER))->PlaneCoord.Xmax,
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmin*(ProX/ProY),
                           (static_cast<TGISLib*>(OWNER))->Screen.Xmax*(ProX/ProY));

      *ScreenY = Strain(Y, (static_cast<TGISLib*>(OWNER))->PlaneCoord.Ymin,
                           (static_cast<TGISLib*>(OWNER))->PlaneCoord.Ymax,
                           (static_cast<TGISLib*>(OWNER))->Screen.Ymin,
                           (static_cast<TGISLib*>(OWNER))->Screen.Ymax);
    }
    *ScreenY = (-1)*(*ScreenY);
  }
}


void TCartography::ScreenXYToPZ90BL(double ScreenX, double ScreenY, double *B, double *L)
{
double X, Y, Fi, Lambda;

  ScreenXYToProjectionXY(ScreenX, ScreenY, &X, &Y);
  //Получил плановые координаты

  Fi = 0.0;
  Lambda = 0.0;
  switch ((static_cast<TGISLib*>(OWNER))->Projection.Number)
  {
    //Цилиндрическая равнопромежуточная проекция
    case TGISLib::CYLINDRICAL:
      CylindricalEqualSpaceXYToFiLambda(X, Y, &Fi, &Lambda);
    break;

    //Азимутальная ортографическая проекция Северного Полюса
    case TGISLib::NORTHPOLE:
      AzimuthOrthographicNorthXYToFiLambda(X, Y, &Fi, &Lambda);
    break;

    //Азимутальная ортографическая проекция Южного Полюса
    case TGISLib::SOUTHPOLE:
      AzimuthOrthographicSouthXYToFiLambda(X, Y, &Fi, &Lambda);
    break;

    //Равноугольная цилиндрическая проекция Меркатора
    case TGISLib::MERCATOR:
      MercatorXYToFiLambda(X, Y, &Fi, &Lambda);
    break;

    //Псевдоцилиндрическая проекция Каврайского
    case TGISLib::KAVRAYSKIY:
      KavrayskiyXYToFiLambda(X, Y, &Fi, &Lambda);
    break;

    //Проекция-пустышка
    case TGISLib::NONEPROJECTION:

    break;
  }
  //Получил сферические геоцентрические координаты

  FiLambdaToPZ90BL(Fi, Lambda, 0.0, B, L);
  //Получил геодезические координаты эллипсоида ПЗ-90
}


void TCartography::PZ90BLToScreenXY(double B, double L, double *ScreenX, double *ScreenY)
{
double X, Y, Fi, Lambda;

  PZ90BLToFiLambda(B, L, 0.0, &Fi, &Lambda);
  //Получил сферические геоцентрические координаты

  X = 0.0;
  Y = 0.0;
  switch ((static_cast<TGISLib*>(OWNER))->Projection.Number)
  {
    //Цилиндрическая равнопромежуточная проекция
    case TGISLib::CYLINDRICAL:
      FiLambdaToCylindricalEqualSpaceXY(Fi, Lambda, &X, &Y);
    break;

    //Азимутальная ортографическая проекция Северного Полюса
    case TGISLib::NORTHPOLE:
      FiLambdaToAzimuthOrthographicNorthXY(Fi, Lambda, &X, &Y);
    break;

    //Азимутальная ортографическая проекция Южного Полюса
    case TGISLib::SOUTHPOLE:
      FiLambdaToAzimuthOrthographicSouthXY(Fi, Lambda, &X, &Y);
    break;

    //Равноугольная цилиндрическая проекция Меркатора
    case TGISLib::MERCATOR:
      FiLambdaToMercatorXY(Fi, Lambda, &X, &Y);
    break;

    //Псевдоцилиндрическая проекция Каврайского
    case TGISLib::KAVRAYSKIY:
      FiLambdaToKavrayskiyXY(Fi, Lambda, &X, &Y);
    break;

    //Проекция-пустышка
    case TGISLib::NONEPROJECTION:

    break;
  }
  //Получил плановые координаты

  ProjectionXYToScreenXY(X, Y, ScreenX, ScreenY);
  //Получил сценические координаты
}


double TCartography::RulerLength(double StartB, double StartL, double StopB, double StopL)
{
int i, quantity;
unsigned int ii;
double beta, delta, res;
TVector R1, R2, R3;
std::vector<TVector> ArrPoint;
  ArrPoint.clear();
  BLHToOtn(StartB, StartL, 0.0, &R1);
  BLHToOtn(StopB, StopL, 0.0, &R2);

  R3 = R2 - R1;

  quantity = Trunc(R3.getModul()/1000.0);
  if (quantity < 1.0)
    quantity = 1;
  //quantity содержит кол-во точек на геодезической линии. Расстояния между точками - около 1 км

  if (quantity > 1)
  {
    beta = TMultitude::ArcCos((R1*R2)/(R1.getModul()*R2.getModul()));
    delta = beta/(static_cast<double>(quantity));

    ArrPoint.push_back(R1);
    for(i=1;i<=quantity;i++)
    {
      MiddlePointOnRoute(delta*(static_cast<double>(i)), R1, R2, RZEkv, RZEkv-ALPHA*RZEkv, &R3);
      ArrPoint.push_back(R3);
    }

    res = 0.0;
    for(ii=0;ii<ArrPoint.size()-1;ii++)
    {
      R3 = ArrPoint[ii+1]-ArrPoint[ii];
      res = res + R3.getModul();
    }
  }
  else
  {
    res = R3.getModul();
  }

  ArrPoint.clear();
  return res;
}
