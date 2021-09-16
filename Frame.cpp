//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл Frame.cpp                                                             //
//                                                                            //
//               *** TFRAME РАМКА КАРТЫ И 15-ГРАДУСНАЯ СЕТКА ***              //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#include <QRectF>
#include <QPen>
#include "Frame.h"
#include "MapData.h"
#include "GISLib.h"


TFrame::TFrame(void)
{
unsigned int i;

  OWNER = NULL;

  Up = NULL;
  Down = NULL;
  Left = NULL;
  Right = NULL;
  VertCentral = NULL;
  HorCentral = NULL;

  Grid15.resize(288);
  for(i=0;i<Grid15.size();i++)
    Grid15[i].spot.resize(4);

  for(i=0;i<288;i++)
    IDGrid15[i] = NULL;

  Grid15[0].spot[0].L =-180; Grid15[0].spot[0].B =-90;
  Grid15[0].spot[1].L =-165; Grid15[0].spot[1].B =-90;
  Grid15[0].spot[2].L =-165; Grid15[0].spot[2].B =-75;
  Grid15[0].spot[3].L =-180; Grid15[0].spot[3].B =-75;

  Grid15[1].spot[0].L =-180; Grid15[1].spot[0].B =-75;
  Grid15[1].spot[1].L =-165; Grid15[1].spot[1].B =-75;
  Grid15[1].spot[2].L =-165; Grid15[1].spot[2].B =-60;
  Grid15[1].spot[3].L =-180; Grid15[1].spot[3].B =-60;

  Grid15[2].spot[0].L =-180; Grid15[2].spot[0].B =-60;
  Grid15[2].spot[1].L =-165; Grid15[2].spot[1].B =-60;
  Grid15[2].spot[2].L =-165; Grid15[2].spot[2].B =-45;
  Grid15[2].spot[3].L =-180; Grid15[2].spot[3].B =-45;

  Grid15[3].spot[0].L =-180; Grid15[3].spot[0].B =-45;
  Grid15[3].spot[1].L =-165; Grid15[3].spot[1].B =-45;
  Grid15[3].spot[2].L =-165; Grid15[3].spot[2].B =-30;
  Grid15[3].spot[3].L =-180; Grid15[3].spot[3].B =-30;

  Grid15[4].spot[0].L =-180; Grid15[4].spot[0].B =-30;
  Grid15[4].spot[1].L =-165; Grid15[4].spot[1].B =-30;
  Grid15[4].spot[2].L =-165; Grid15[4].spot[2].B =-15;
  Grid15[4].spot[3].L =-180; Grid15[4].spot[3].B =-15;

  Grid15[5].spot[0].L =-180; Grid15[5].spot[0].B =-15;
  Grid15[5].spot[1].L =-165; Grid15[5].spot[1].B =-15;
  Grid15[5].spot[2].L =-165; Grid15[5].spot[2].B =0  ;
  Grid15[5].spot[3].L =-180; Grid15[5].spot[3].B =0  ;

  Grid15[6].spot[0].L =-180; Grid15[6].spot[0].B =0  ;
  Grid15[6].spot[1].L =-165; Grid15[6].spot[1].B =0  ;
  Grid15[6].spot[2].L =-165; Grid15[6].spot[2].B =15 ;
  Grid15[6].spot[3].L =-180; Grid15[6].spot[3].B =15 ;

  Grid15[7].spot[0].L =-180; Grid15[7].spot[0].B =15 ;
  Grid15[7].spot[1].L =-165; Grid15[7].spot[1].B =15 ;
  Grid15[7].spot[2].L =-165; Grid15[7].spot[2].B =30 ;
  Grid15[7].spot[3].L =-180; Grid15[7].spot[3].B =30 ;

  Grid15[8].spot[0].L =-180; Grid15[8].spot[0].B =30 ;
  Grid15[8].spot[1].L =-165; Grid15[8].spot[1].B =30 ;
  Grid15[8].spot[2].L =-165; Grid15[8].spot[2].B =45 ;
  Grid15[8].spot[3].L =-180; Grid15[8].spot[3].B =45 ;

  Grid15[9].spot[0].L =-180; Grid15[9].spot[0].B =45 ;
  Grid15[9].spot[1].L =-165; Grid15[9].spot[1].B =45 ;
  Grid15[9].spot[2].L =-165; Grid15[9].spot[2].B =60 ;
  Grid15[9].spot[3].L =-180; Grid15[9].spot[3].B =60 ;

  Grid15[10].spot[0].L =-180; Grid15[10].spot[0].B =60 ;
  Grid15[10].spot[1].L =-165; Grid15[10].spot[1].B =60 ;
  Grid15[10].spot[2].L =-165; Grid15[10].spot[2].B =75 ;
  Grid15[10].spot[3].L =-180; Grid15[10].spot[3].B =75 ;

  Grid15[11].spot[0].L =-180; Grid15[11].spot[0].B =75 ;
  Grid15[11].spot[1].L =-165; Grid15[11].spot[1].B =75 ;
  Grid15[11].spot[2].L =-165; Grid15[11].spot[2].B =90 ;
  Grid15[11].spot[3].L =-180; Grid15[11].spot[3].B =90 ;

  Grid15[12].spot[0].L =-165; Grid15[12].spot[0].B =-90;
  Grid15[12].spot[1].L =-150; Grid15[12].spot[1].B =-90;
  Grid15[12].spot[2].L =-150; Grid15[12].spot[2].B =-75;
  Grid15[12].spot[3].L =-165; Grid15[12].spot[3].B =-75;

  Grid15[13].spot[0].L =-165; Grid15[13].spot[0].B =-75;
  Grid15[13].spot[1].L =-150; Grid15[13].spot[1].B =-75;
  Grid15[13].spot[2].L =-150; Grid15[13].spot[2].B =-60;
  Grid15[13].spot[3].L =-165; Grid15[13].spot[3].B =-60;

  Grid15[14].spot[0].L =-165; Grid15[14].spot[0].B =-60;
  Grid15[14].spot[1].L =-150; Grid15[14].spot[1].B =-60;
  Grid15[14].spot[2].L =-150; Grid15[14].spot[2].B =-45;
  Grid15[14].spot[3].L =-165; Grid15[14].spot[3].B =-45;

  Grid15[15].spot[0].L =-165; Grid15[15].spot[0].B =-45;
  Grid15[15].spot[1].L =-150; Grid15[15].spot[1].B =-45;
  Grid15[15].spot[2].L =-150; Grid15[15].spot[2].B =-30;
  Grid15[15].spot[3].L =-165; Grid15[15].spot[3].B =-30;

  Grid15[16].spot[0].L =-165; Grid15[16].spot[0].B =-30;
  Grid15[16].spot[1].L =-150; Grid15[16].spot[1].B =-30;
  Grid15[16].spot[2].L =-150; Grid15[16].spot[2].B =-15;
  Grid15[16].spot[3].L =-165; Grid15[16].spot[3].B =-15;

  Grid15[17].spot[0].L =-165; Grid15[17].spot[0].B =-15;
  Grid15[17].spot[1].L =-150; Grid15[17].spot[1].B =-15;
  Grid15[17].spot[2].L =-150; Grid15[17].spot[2].B =0  ;
  Grid15[17].spot[3].L =-165; Grid15[17].spot[3].B =0  ;

  Grid15[18].spot[0].L =-165; Grid15[18].spot[0].B =0  ;
  Grid15[18].spot[1].L =-150; Grid15[18].spot[1].B =0  ;
  Grid15[18].spot[2].L =-150; Grid15[18].spot[2].B =15 ;
  Grid15[18].spot[3].L =-165; Grid15[18].spot[3].B =15 ;

  Grid15[19].spot[0].L =-165; Grid15[19].spot[0].B =15 ;
  Grid15[19].spot[1].L =-150; Grid15[19].spot[1].B =15 ;
  Grid15[19].spot[2].L =-150; Grid15[19].spot[2].B =30 ;
  Grid15[19].spot[3].L =-165; Grid15[19].spot[3].B =30 ;

  Grid15[20].spot[0].L =-165; Grid15[20].spot[0].B =30 ;
  Grid15[20].spot[1].L =-150; Grid15[20].spot[1].B =30 ;
  Grid15[20].spot[2].L =-150; Grid15[20].spot[2].B =45 ;
  Grid15[20].spot[3].L =-165; Grid15[20].spot[3].B =45 ;

  Grid15[21].spot[0].L =-165; Grid15[21].spot[0].B =45 ;
  Grid15[21].spot[1].L =-150; Grid15[21].spot[1].B =45 ;
  Grid15[21].spot[2].L =-150; Grid15[21].spot[2].B =60 ;
  Grid15[21].spot[3].L =-165; Grid15[21].spot[3].B =60 ;

  Grid15[22].spot[0].L =-165; Grid15[22].spot[0].B =60 ;
  Grid15[22].spot[1].L =-150; Grid15[22].spot[1].B =60 ;
  Grid15[22].spot[2].L =-150; Grid15[22].spot[2].B =75 ;
  Grid15[22].spot[3].L =-165; Grid15[22].spot[3].B =75 ;

  Grid15[23].spot[0].L =-165; Grid15[23].spot[0].B =75 ;
  Grid15[23].spot[1].L =-150; Grid15[23].spot[1].B =75 ;
  Grid15[23].spot[2].L =-150; Grid15[23].spot[2].B =90 ;
  Grid15[23].spot[3].L =-165; Grid15[23].spot[3].B =90 ;

  Grid15[24].spot[0].L =-150; Grid15[24].spot[0].B =-90;
  Grid15[24].spot[1].L =-135; Grid15[24].spot[1].B =-90;
  Grid15[24].spot[2].L =-135; Grid15[24].spot[2].B =-75;
  Grid15[24].spot[3].L =-150; Grid15[24].spot[3].B =-75;

  Grid15[25].spot[0].L =-150; Grid15[25].spot[0].B =-75;
  Grid15[25].spot[1].L =-135; Grid15[25].spot[1].B =-75;
  Grid15[25].spot[2].L =-135; Grid15[25].spot[2].B =-60;
  Grid15[25].spot[3].L =-150; Grid15[25].spot[3].B =-60;

  Grid15[26].spot[0].L =-150; Grid15[26].spot[0].B =-60;
  Grid15[26].spot[1].L =-135; Grid15[26].spot[1].B =-60;
  Grid15[26].spot[2].L =-135; Grid15[26].spot[2].B =-45;
  Grid15[26].spot[3].L =-150; Grid15[26].spot[3].B =-45;

  Grid15[27].spot[0].L =-150; Grid15[27].spot[0].B =-45;
  Grid15[27].spot[1].L =-135; Grid15[27].spot[1].B =-45;
  Grid15[27].spot[2].L =-135; Grid15[27].spot[2].B =-30;
  Grid15[27].spot[3].L =-150; Grid15[27].spot[3].B =-30;

  Grid15[28].spot[0].L =-150; Grid15[28].spot[0].B = -30;
  Grid15[28].spot[1].L =-135; Grid15[28].spot[1].B = -30;
  Grid15[28].spot[2].L =-135; Grid15[28].spot[2].B = -15;
  Grid15[28].spot[3].L =-150; Grid15[28].spot[3].B = -15;

  Grid15[29].spot[0].L =-150; Grid15[29].spot[0].B = -15;
  Grid15[29].spot[1].L =-135; Grid15[29].spot[1].B = -15;
  Grid15[29].spot[2].L =-135; Grid15[29].spot[2].B = 0  ;
  Grid15[29].spot[3].L =-150; Grid15[29].spot[3].B = 0  ;

  Grid15[30].spot[0].L =-150; Grid15[30].spot[0].B = 0  ;
  Grid15[30].spot[1].L =-135; Grid15[30].spot[1].B = 0  ;
  Grid15[30].spot[2].L =-135; Grid15[30].spot[2].B = 15 ;
  Grid15[30].spot[3].L =-150; Grid15[30].spot[3].B = 15 ;

  Grid15[31].spot[0].L =-150; Grid15[31].spot[0].B = 15 ;
  Grid15[31].spot[1].L =-135; Grid15[31].spot[1].B = 15 ;
  Grid15[31].spot[2].L =-135; Grid15[31].spot[2].B = 30 ;
  Grid15[31].spot[3].L =-150; Grid15[31].spot[3].B = 30 ;

  Grid15[32].spot[0].L =-150; Grid15[32].spot[0].B = 30 ;
  Grid15[32].spot[1].L =-135; Grid15[32].spot[1].B = 30 ;
  Grid15[32].spot[2].L =-135; Grid15[32].spot[2].B = 45 ;
  Grid15[32].spot[3].L =-150; Grid15[32].spot[3].B = 45 ;

  Grid15[33].spot[0].L =-150; Grid15[33].spot[0].B = 45 ;
  Grid15[33].spot[1].L =-135; Grid15[33].spot[1].B = 45 ;
  Grid15[33].spot[2].L =-135; Grid15[33].spot[2].B = 60 ;
  Grid15[33].spot[3].L =-150; Grid15[33].spot[3].B = 60 ;

  Grid15[34].spot[0].L =-150; Grid15[34].spot[0].B = 60 ;
  Grid15[34].spot[1].L =-135; Grid15[34].spot[1].B = 60 ;
  Grid15[34].spot[2].L =-135; Grid15[34].spot[2].B = 75 ;
  Grid15[34].spot[3].L =-150; Grid15[34].spot[3].B = 75 ;

  Grid15[35].spot[0].L =-150; Grid15[35].spot[0].B = 75 ;
  Grid15[35].spot[1].L =-135; Grid15[35].spot[1].B = 75 ;
  Grid15[35].spot[2].L =-135; Grid15[35].spot[2].B = 90 ;
  Grid15[35].spot[3].L =-150; Grid15[35].spot[3].B = 90 ;

  Grid15[36].spot[0].L =-135; Grid15[36].spot[0].B = -90;
  Grid15[36].spot[1].L =-120; Grid15[36].spot[1].B = -90;
  Grid15[36].spot[2].L =-120; Grid15[36].spot[2].B = -75;
  Grid15[36].spot[3].L =-135; Grid15[36].spot[3].B = -75;

  Grid15[37].spot[0].L =-135; Grid15[37].spot[0].B = -75;
  Grid15[37].spot[1].L =-120; Grid15[37].spot[1].B = -75;
  Grid15[37].spot[2].L =-120; Grid15[37].spot[2].B = -60;
  Grid15[37].spot[3].L =-135; Grid15[37].spot[3].B = -60;

  Grid15[38].spot[0].L =-135; Grid15[38].spot[0].B = -60;
  Grid15[38].spot[1].L =-120; Grid15[38].spot[1].B = -60;
  Grid15[38].spot[2].L =-120; Grid15[38].spot[2].B = -45;
  Grid15[38].spot[3].L =-135; Grid15[38].spot[3].B = -45;

  Grid15[39].spot[0].L =-135; Grid15[39].spot[0].B = -45;
  Grid15[39].spot[1].L =-120; Grid15[39].spot[1].B = -45;
  Grid15[39].spot[2].L =-120; Grid15[39].spot[2].B = -30;
  Grid15[39].spot[3].L =-135; Grid15[39].spot[3].B = -30;

  Grid15[40].spot[0].L =-135; Grid15[40].spot[0].B = -30;
  Grid15[40].spot[1].L =-120; Grid15[40].spot[1].B = -30;
  Grid15[40].spot[2].L =-120; Grid15[40].spot[2].B = -15;
  Grid15[40].spot[3].L =-135; Grid15[40].spot[3].B = -15;

  Grid15[41].spot[0].L =-135; Grid15[41].spot[0].B = -15;
  Grid15[41].spot[1].L =-120; Grid15[41].spot[1].B = -15;
  Grid15[41].spot[2].L =-120; Grid15[41].spot[2].B = 0  ;
  Grid15[41].spot[3].L =-135; Grid15[41].spot[3].B = 0  ;

  Grid15[42].spot[0].L =-135; Grid15[42].spot[0].B = 0  ;
  Grid15[42].spot[1].L =-120; Grid15[42].spot[1].B = 0  ;
  Grid15[42].spot[2].L =-120; Grid15[42].spot[2].B = 15 ;
  Grid15[42].spot[3].L =-135; Grid15[42].spot[3].B = 15 ;

  Grid15[43].spot[0].L =-135; Grid15[43].spot[0].B = 15 ;
  Grid15[43].spot[1].L =-120; Grid15[43].spot[1].B = 15 ;
  Grid15[43].spot[2].L =-120; Grid15[43].spot[2].B = 30 ;
  Grid15[43].spot[3].L =-135; Grid15[43].spot[3].B = 30 ;

  Grid15[44].spot[0].L =-135; Grid15[44].spot[0].B = 30 ;
  Grid15[44].spot[1].L =-120; Grid15[44].spot[1].B = 30 ;
  Grid15[44].spot[2].L =-120; Grid15[44].spot[2].B = 45 ;
  Grid15[44].spot[3].L =-135; Grid15[44].spot[3].B = 45 ;

  Grid15[45].spot[0].L =-135; Grid15[45].spot[0].B = 45 ;
  Grid15[45].spot[1].L =-120; Grid15[45].spot[1].B = 45 ;
  Grid15[45].spot[2].L =-120; Grid15[45].spot[2].B = 60 ;
  Grid15[45].spot[3].L =-135; Grid15[45].spot[3].B = 60 ;

  Grid15[46].spot[0].L =-135; Grid15[46].spot[0].B = 60 ;
  Grid15[46].spot[1].L =-120; Grid15[46].spot[1].B = 60 ;
  Grid15[46].spot[2].L =-120; Grid15[46].spot[2].B = 75 ;
  Grid15[46].spot[3].L =-135; Grid15[46].spot[3].B = 75 ;

  Grid15[47].spot[0].L =-135; Grid15[47].spot[0].B = 75 ;
  Grid15[47].spot[1].L =-120; Grid15[47].spot[1].B = 75 ;
  Grid15[47].spot[2].L =-120; Grid15[47].spot[2].B = 90 ;
  Grid15[47].spot[3].L =-135; Grid15[47].spot[3].B = 90 ;

  Grid15[48].spot[0].L =-120; Grid15[48].spot[0].B = -90;
  Grid15[48].spot[1].L =-105; Grid15[48].spot[1].B = -90;
  Grid15[48].spot[2].L =-105; Grid15[48].spot[2].B = -75;
  Grid15[48].spot[3].L =-120; Grid15[48].spot[3].B = -75;

  Grid15[49].spot[0].L =-120; Grid15[49].spot[0].B = -75;
  Grid15[49].spot[1].L =-105; Grid15[49].spot[1].B = -75;
  Grid15[49].spot[2].L =-105; Grid15[49].spot[2].B = -60;
  Grid15[49].spot[3].L =-120; Grid15[49].spot[3].B = -60;

  Grid15[50].spot[0].L =-120; Grid15[50].spot[0].B = -60;
  Grid15[50].spot[1].L =-105; Grid15[50].spot[1].B = -60;
  Grid15[50].spot[2].L =-105; Grid15[50].spot[2].B = -45;
  Grid15[50].spot[3].L =-120; Grid15[50].spot[3].B = -45;

  Grid15[51].spot[0].L =-120; Grid15[51].spot[0].B = -45;
  Grid15[51].spot[1].L =-105; Grid15[51].spot[1].B = -45;
  Grid15[51].spot[2].L =-105; Grid15[51].spot[2].B = -30;
  Grid15[51].spot[3].L =-120; Grid15[51].spot[3].B = -30;

  Grid15[52].spot[0].L =-120; Grid15[52].spot[0].B = -30;
  Grid15[52].spot[1].L =-105; Grid15[52].spot[1].B = -30;
  Grid15[52].spot[2].L =-105; Grid15[52].spot[2].B = -15;
  Grid15[52].spot[3].L =-120; Grid15[52].spot[3].B = -15;

  Grid15[53].spot[0].L =-120; Grid15[53].spot[0].B = -15;
  Grid15[53].spot[1].L =-105; Grid15[53].spot[1].B = -15;
  Grid15[53].spot[2].L =-105; Grid15[53].spot[2].B = 0  ;
  Grid15[53].spot[3].L =-120; Grid15[53].spot[3].B = 0  ;

  Grid15[54].spot[0].L =-120; Grid15[54].spot[0].B = 0  ;
  Grid15[54].spot[1].L =-105; Grid15[54].spot[1].B = 0  ;
  Grid15[54].spot[2].L =-105; Grid15[54].spot[2].B = 15 ;
  Grid15[54].spot[3].L =-120; Grid15[54].spot[3].B = 15 ;

  Grid15[55].spot[0].L =-120; Grid15[55].spot[0].B = 15 ;
  Grid15[55].spot[1].L =-105; Grid15[55].spot[1].B = 15 ;
  Grid15[55].spot[2].L =-105; Grid15[55].spot[2].B = 30 ;
  Grid15[55].spot[3].L =-120; Grid15[55].spot[3].B = 30 ;

  Grid15[56].spot[0].L =-120; Grid15[56].spot[0].B = 30 ;
  Grid15[56].spot[1].L =-105; Grid15[56].spot[1].B = 30 ;
  Grid15[56].spot[2].L =-105; Grid15[56].spot[2].B = 45 ;
  Grid15[56].spot[3].L =-120; Grid15[56].spot[3].B = 45 ;

  Grid15[57].spot[0].L =-120; Grid15[57].spot[0].B = 45 ;
  Grid15[57].spot[1].L =-105; Grid15[57].spot[1].B = 45 ;
  Grid15[57].spot[2].L =-105; Grid15[57].spot[2].B = 60 ;
  Grid15[57].spot[3].L =-120; Grid15[57].spot[3].B = 60 ;

  Grid15[58].spot[0].L =-120; Grid15[58].spot[0].B = 60 ;
  Grid15[58].spot[1].L =-105; Grid15[58].spot[1].B = 60 ;
  Grid15[58].spot[2].L =-105; Grid15[58].spot[2].B = 75 ;
  Grid15[58].spot[3].L =-120; Grid15[58].spot[3].B = 75 ;

  Grid15[59].spot[0].L =-120; Grid15[59].spot[0].B = 75 ;
  Grid15[59].spot[1].L =-105; Grid15[59].spot[1].B = 75 ;
  Grid15[59].spot[2].L =-105; Grid15[59].spot[2].B = 90 ;
  Grid15[59].spot[3].L =-120; Grid15[59].spot[3].B = 90 ;

  Grid15[60].spot[0].L =-105; Grid15[60].spot[0].B = -90;
  Grid15[60].spot[1].L =-90 ; Grid15[60].spot[1].B =-90 ;
  Grid15[60].spot[2].L =-90 ; Grid15[60].spot[2].B =-75 ;
  Grid15[60].spot[3].L =-105; Grid15[60].spot[3].B = -75;

  Grid15[61].spot[0].L =-105; Grid15[61].spot[0].B = -75;
  Grid15[61].spot[1].L =-90 ; Grid15[61].spot[1].B =-75 ;
  Grid15[61].spot[2].L =-90 ; Grid15[61].spot[2].B =-60 ;
  Grid15[61].spot[3].L =-105; Grid15[61].spot[3].B = -60;

  Grid15[62].spot[0].L =-105; Grid15[62].spot[0].B = -60;
  Grid15[62].spot[1].L =-90 ; Grid15[62].spot[1].B =-60 ;
  Grid15[62].spot[2].L =-90 ; Grid15[62].spot[2].B =-45 ;
  Grid15[62].spot[3].L =-105; Grid15[62].spot[3].B = -45;

  Grid15[63].spot[0].L =-105; Grid15[63].spot[0].B = -45;
  Grid15[63].spot[1].L =-90 ; Grid15[63].spot[1].B =-45 ;
  Grid15[63].spot[2].L =-90 ; Grid15[63].spot[2].B =-30 ;
  Grid15[63].spot[3].L =-105; Grid15[63].spot[3].B = -30;

  Grid15[64].spot[0].L =-105; Grid15[64].spot[0].B = -30;
  Grid15[64].spot[1].L =-90 ; Grid15[64].spot[1].B =-30 ;
  Grid15[64].spot[2].L =-90 ; Grid15[64].spot[2].B =-15 ;
  Grid15[64].spot[3].L =-105; Grid15[64].spot[3].B = -15;

  Grid15[65].spot[0].L =-105; Grid15[65].spot[0].B = -15;
  Grid15[65].spot[1].L =-90 ; Grid15[65].spot[1].B =-15 ;
  Grid15[65].spot[2].L =-90 ; Grid15[65].spot[2].B =0   ;
  Grid15[65].spot[3].L =-105; Grid15[65].spot[3].B = 0  ;

  Grid15[66].spot[0].L =-105; Grid15[66].spot[0].B = 0  ;
  Grid15[66].spot[1].L =-90 ; Grid15[66].spot[1].B =0   ;
  Grid15[66].spot[2].L =-90 ; Grid15[66].spot[2].B =15  ;
  Grid15[66].spot[3].L =-105; Grid15[66].spot[3].B = 15 ;

  Grid15[67].spot[0].L =-105; Grid15[67].spot[0].B = 15 ;
  Grid15[67].spot[1].L =-90 ; Grid15[67].spot[1].B =15  ;
  Grid15[67].spot[2].L =-90 ; Grid15[67].spot[2].B =30  ;
  Grid15[67].spot[3].L =-105; Grid15[67].spot[3].B = 30 ;

  Grid15[68].spot[0].L =-105; Grid15[68].spot[0].B = 30 ;
  Grid15[68].spot[1].L =-90 ; Grid15[68].spot[1].B =30  ;
  Grid15[68].spot[2].L =-90 ; Grid15[68].spot[2].B =45  ;
  Grid15[68].spot[3].L =-105; Grid15[68].spot[3].B = 45 ;

  Grid15[69].spot[0].L =-105; Grid15[69].spot[0].B = 45 ;
  Grid15[69].spot[1].L =-90 ; Grid15[69].spot[1].B =45  ;
  Grid15[69].spot[2].L =-90 ; Grid15[69].spot[2].B =60  ;
  Grid15[69].spot[3].L =-105; Grid15[69].spot[3].B = 60 ;

  Grid15[70].spot[0].L =-105; Grid15[70].spot[0].B = 60 ;
  Grid15[70].spot[1].L =-90 ; Grid15[70].spot[1].B =60  ;
  Grid15[70].spot[2].L =-90 ; Grid15[70].spot[2].B =75  ;
  Grid15[70].spot[3].L =-105; Grid15[70].spot[3].B = 75 ;

  Grid15[71].spot[0].L =-105; Grid15[71].spot[0].B = 75 ;
  Grid15[71].spot[1].L =-90 ; Grid15[71].spot[1].B =75  ;
  Grid15[71].spot[2].L =-90 ; Grid15[71].spot[2].B =90  ;
  Grid15[71].spot[3].L =-105; Grid15[71].spot[3].B = 90 ;

  Grid15[72].spot[0].L =-90 ; Grid15[72].spot[0].B =-90 ;
  Grid15[72].spot[1].L =-75 ; Grid15[72].spot[1].B =-90 ;
  Grid15[72].spot[2].L =-75 ; Grid15[72].spot[2].B =-75 ;
  Grid15[72].spot[3].L =-90 ; Grid15[72].spot[3].B =-75 ;

  Grid15[73].spot[0].L =-90 ; Grid15[73].spot[0].B =-75 ;
  Grid15[73].spot[1].L =-75 ; Grid15[73].spot[1].B =-75 ;
  Grid15[73].spot[2].L =-75 ; Grid15[73].spot[2].B =-60 ;
  Grid15[73].spot[3].L =-90 ; Grid15[73].spot[3].B =-60 ;

  Grid15[74].spot[0].L =-90 ; Grid15[74].spot[0].B =-60 ;
  Grid15[74].spot[1].L =-75 ; Grid15[74].spot[1].B =-60 ;
  Grid15[74].spot[2].L =-75 ; Grid15[74].spot[2].B =-45 ;
  Grid15[74].spot[3].L =-90 ; Grid15[74].spot[3].B =-45 ;

  Grid15[75].spot[0].L =-90 ; Grid15[75].spot[0].B =-45 ;
  Grid15[75].spot[1].L =-75 ; Grid15[75].spot[1].B =-45 ;
  Grid15[75].spot[2].L =-75 ; Grid15[75].spot[2].B =-30 ;
  Grid15[75].spot[3].L =-90 ; Grid15[75].spot[3].B =-30 ;

  Grid15[76].spot[0].L =-90 ; Grid15[76].spot[0].B =-30 ;
  Grid15[76].spot[1].L =-75 ; Grid15[76].spot[1].B =-30 ;
  Grid15[76].spot[2].L =-75 ; Grid15[76].spot[2].B =-15 ;
  Grid15[76].spot[3].L =-90 ; Grid15[76].spot[3].B =-15 ;

  Grid15[77].spot[0].L =-90 ; Grid15[77].spot[0].B =-15 ;
  Grid15[77].spot[1].L =-75 ; Grid15[77].spot[1].B =-15 ;
  Grid15[77].spot[2].L =-75 ; Grid15[77].spot[2].B =0   ;
  Grid15[77].spot[3].L =-90 ; Grid15[77].spot[3].B =0   ;

  Grid15[78].spot[0].L =-90 ; Grid15[78].spot[0].B =0   ;
  Grid15[78].spot[1].L =-75 ; Grid15[78].spot[1].B =0   ;
  Grid15[78].spot[2].L =-75 ; Grid15[78].spot[2].B =15  ;
  Grid15[78].spot[3].L =-90 ; Grid15[78].spot[3].B =15  ;

  Grid15[79].spot[0].L =-90 ; Grid15[79].spot[0].B =15  ;
  Grid15[79].spot[1].L =-75 ; Grid15[79].spot[1].B =15  ;
  Grid15[79].spot[2].L =-75 ; Grid15[79].spot[2].B =30  ;
  Grid15[79].spot[3].L =-90 ; Grid15[79].spot[3].B =30  ;

  Grid15[80].spot[0].L =-90 ; Grid15[80].spot[0].B =30  ;
  Grid15[80].spot[1].L =-75 ; Grid15[80].spot[1].B =30  ;
  Grid15[80].spot[2].L =-75 ; Grid15[80].spot[2].B =45  ;
  Grid15[80].spot[3].L =-90 ; Grid15[80].spot[3].B =45  ;

  Grid15[81].spot[0].L =-90 ; Grid15[81].spot[0].B =45  ;
  Grid15[81].spot[1].L =-75 ; Grid15[81].spot[1].B =45  ;
  Grid15[81].spot[2].L =-75 ; Grid15[81].spot[2].B =60  ;
  Grid15[81].spot[3].L =-90 ; Grid15[81].spot[3].B =60  ;

  Grid15[82].spot[0].L =-90 ; Grid15[82].spot[0].B =60  ;
  Grid15[82].spot[1].L =-75 ; Grid15[82].spot[1].B =60  ;
  Grid15[82].spot[2].L =-75 ; Grid15[82].spot[2].B =75  ;
  Grid15[82].spot[3].L =-90 ; Grid15[82].spot[3].B =75  ;

  Grid15[83].spot[0].L =-90 ; Grid15[83].spot[0].B =75  ;
  Grid15[83].spot[1].L =-75 ; Grid15[83].spot[1].B =75  ;
  Grid15[83].spot[2].L =-75 ; Grid15[83].spot[2].B =90  ;
  Grid15[83].spot[3].L =-90 ; Grid15[83].spot[3].B =90  ;

  Grid15[84].spot[0].L =-75 ; Grid15[84].spot[0].B =-90 ;
  Grid15[84].spot[1].L =-60 ; Grid15[84].spot[1].B =-90 ;
  Grid15[84].spot[2].L =-60 ; Grid15[84].spot[2].B =-75 ;
  Grid15[84].spot[3].L =-75 ; Grid15[84].spot[3].B =-75 ;

  Grid15[85].spot[0].L =-75 ; Grid15[85].spot[0].B =-75 ;
  Grid15[85].spot[1].L =-60 ; Grid15[85].spot[1].B =-75 ;
  Grid15[85].spot[2].L =-60 ; Grid15[85].spot[2].B =-60 ;
  Grid15[85].spot[3].L =-75 ; Grid15[85].spot[3].B =-60 ;

  Grid15[86].spot[0].L =-75 ; Grid15[86].spot[0].B =-60 ;
  Grid15[86].spot[1].L =-60 ; Grid15[86].spot[1].B =-60 ;
  Grid15[86].spot[2].L =-60 ; Grid15[86].spot[2].B =-45 ;
  Grid15[86].spot[3].L =-75 ; Grid15[86].spot[3].B =-45 ;

  Grid15[87].spot[0].L =-75 ; Grid15[87].spot[0].B =-45 ;
  Grid15[87].spot[1].L =-60 ; Grid15[87].spot[1].B =-45 ;
  Grid15[87].spot[2].L =-60 ; Grid15[87].spot[2].B =-30 ;
  Grid15[87].spot[3].L =-75 ; Grid15[87].spot[3].B =-30 ;

  Grid15[88].spot[0].L =-75 ; Grid15[88].spot[0].B =-30 ;
  Grid15[88].spot[1].L =-60 ; Grid15[88].spot[1].B =-30 ;
  Grid15[88].spot[2].L =-60 ; Grid15[88].spot[2].B =-15 ;
  Grid15[88].spot[3].L =-75 ; Grid15[88].spot[3].B =-15 ;

  Grid15[89].spot[0].L =-75 ; Grid15[89].spot[0].B =-15 ;
  Grid15[89].spot[1].L =-60 ; Grid15[89].spot[1].B =-15 ;
  Grid15[89].spot[2].L =-60 ; Grid15[89].spot[2].B =0   ;
  Grid15[89].spot[3].L =-75 ; Grid15[89].spot[3].B =0   ;

  Grid15[90].spot[0].L =-75 ; Grid15[90].spot[0].B =0   ;
  Grid15[90].spot[1].L =-60 ; Grid15[90].spot[1].B =0   ;
  Grid15[90].spot[2].L =-60 ; Grid15[90].spot[2].B =15  ;
  Grid15[90].spot[3].L =-75 ; Grid15[90].spot[3].B =15  ;

  Grid15[91].spot[0].L =-75 ; Grid15[91].spot[0].B =15  ;
  Grid15[91].spot[1].L =-60 ; Grid15[91].spot[1].B =15  ;
  Grid15[91].spot[2].L =-60 ; Grid15[91].spot[2].B =30  ;
  Grid15[91].spot[3].L =-75 ; Grid15[91].spot[3].B =30  ;

  Grid15[92].spot[0].L =-75 ; Grid15[92].spot[0].B =30  ;
  Grid15[92].spot[1].L =-60 ; Grid15[92].spot[1].B =30  ;
  Grid15[92].spot[2].L =-60 ; Grid15[92].spot[2].B =45  ;
  Grid15[92].spot[3].L =-75 ; Grid15[92].spot[3].B =45  ;

  Grid15[93].spot[0].L =-75 ; Grid15[93].spot[0].B =45  ;
  Grid15[93].spot[1].L =-60 ; Grid15[93].spot[1].B =45  ;
  Grid15[93].spot[2].L =-60 ; Grid15[93].spot[2].B =60  ;
  Grid15[93].spot[3].L =-75 ; Grid15[93].spot[3].B =60  ;

  Grid15[94].spot[0].L =-75 ; Grid15[94].spot[0].B =60  ;
  Grid15[94].spot[1].L =-60 ; Grid15[94].spot[1].B =60  ;
  Grid15[94].spot[2].L =-60 ; Grid15[94].spot[2].B =75  ;
  Grid15[94].spot[3].L =-75 ; Grid15[94].spot[3].B =75  ;

  Grid15[95].spot[0].L =-75 ; Grid15[95].spot[0].B =75  ;
  Grid15[95].spot[1].L =-60 ; Grid15[95].spot[1].B =75  ;
  Grid15[95].spot[2].L =-60 ; Grid15[95].spot[2].B =90  ;
  Grid15[95].spot[3].L =-75 ; Grid15[95].spot[3].B =90  ;

  Grid15[96].spot[0].L =-60 ; Grid15[96].spot[0].B =-90 ;
  Grid15[96].spot[1].L =-45 ; Grid15[96].spot[1].B =-90 ;
  Grid15[96].spot[2].L =-45 ; Grid15[96].spot[2].B =-75 ;
  Grid15[96].spot[3].L =-60 ; Grid15[96].spot[3].B =-75 ;

  Grid15[97].spot[0].L =-60 ; Grid15[97].spot[0].B =-75 ;
  Grid15[97].spot[1].L =-45 ; Grid15[97].spot[1].B =-75 ;
  Grid15[97].spot[2].L =-45 ; Grid15[97].spot[2].B =-60 ;
  Grid15[97].spot[3].L =-60 ; Grid15[97].spot[3].B =-60 ;

  Grid15[98].spot[0].L =-60 ; Grid15[98].spot[0].B =-60 ;
  Grid15[98].spot[1].L =-45 ; Grid15[98].spot[1].B =-60 ;
  Grid15[98].spot[2].L =-45 ; Grid15[98].spot[2].B =-45 ;
  Grid15[98].spot[3].L =-60 ; Grid15[98].spot[3].B =-45 ;

  Grid15[99].spot[0].L =-60 ; Grid15[99].spot[0].B =-45 ;
  Grid15[99].spot[1].L =-45 ; Grid15[99].spot[1].B =-45 ;
  Grid15[99].spot[2].L =-45 ; Grid15[99].spot[2].B =-30 ;
  Grid15[99].spot[3].L =-60 ; Grid15[99].spot[3].B =-30 ;

  Grid15[100].spot[0].L =-60 ; Grid15[100].spot[0].B =-30 ;
  Grid15[100].spot[1].L =-45 ; Grid15[100].spot[1].B =-30 ;
  Grid15[100].spot[2].L =-45 ; Grid15[100].spot[2].B =-15 ;
  Grid15[100].spot[3].L =-60 ; Grid15[100].spot[3].B =-15 ;

  Grid15[101].spot[0].L =-60 ; Grid15[101].spot[0].B =-15 ;
  Grid15[101].spot[1].L =-45 ; Grid15[101].spot[1].B =-15 ;
  Grid15[101].spot[2].L =-45 ; Grid15[101].spot[2].B =0   ;
  Grid15[101].spot[3].L =-60 ; Grid15[101].spot[3].B =0   ;

  Grid15[102].spot[0].L =-60 ; Grid15[102].spot[0].B =0   ;
  Grid15[102].spot[1].L =-45 ; Grid15[102].spot[1].B =0   ;
  Grid15[102].spot[2].L =-45 ; Grid15[102].spot[2].B =15  ;
  Grid15[102].spot[3].L =-60 ; Grid15[102].spot[3].B =15  ;

  Grid15[103].spot[0].L =-60 ; Grid15[103].spot[0].B =15  ;
  Grid15[103].spot[1].L =-45 ; Grid15[103].spot[1].B =15  ;
  Grid15[103].spot[2].L =-45 ; Grid15[103].spot[2].B =30  ;
  Grid15[103].spot[3].L =-60 ; Grid15[103].spot[3].B =30  ;

  Grid15[104].spot[0].L =-60 ; Grid15[104].spot[0].B =30  ;
  Grid15[104].spot[1].L =-45 ; Grid15[104].spot[1].B =30  ;
  Grid15[104].spot[2].L =-45 ; Grid15[104].spot[2].B =45  ;
  Grid15[104].spot[3].L =-60 ; Grid15[104].spot[3].B =45  ;

  Grid15[105].spot[0].L =-60 ; Grid15[105].spot[0].B =45  ;
  Grid15[105].spot[1].L =-45 ; Grid15[105].spot[1].B =45  ;
  Grid15[105].spot[2].L =-45 ; Grid15[105].spot[2].B =60  ;
  Grid15[105].spot[3].L =-60 ; Grid15[105].spot[3].B =60  ;

  Grid15[106].spot[0].L =-60 ; Grid15[106].spot[0].B =60  ;
  Grid15[106].spot[1].L =-45 ; Grid15[106].spot[1].B =60  ;
  Grid15[106].spot[2].L =-45 ; Grid15[106].spot[2].B =75  ;
  Grid15[106].spot[3].L =-60 ; Grid15[106].spot[3].B =75  ;

  Grid15[107].spot[0].L =-60 ; Grid15[107].spot[0].B =75  ;
  Grid15[107].spot[1].L =-45 ; Grid15[107].spot[1].B =75  ;
  Grid15[107].spot[2].L =-45 ; Grid15[107].spot[2].B =90  ;
  Grid15[107].spot[3].L =-60 ; Grid15[107].spot[3].B =90  ;

  Grid15[108].spot[0].L =-45 ; Grid15[108].spot[0].B =-90 ;
  Grid15[108].spot[1].L =-30 ; Grid15[108].spot[1].B =-90 ;
  Grid15[108].spot[2].L =-30 ; Grid15[108].spot[2].B =-75 ;
  Grid15[108].spot[3].L =-45 ; Grid15[108].spot[3].B =-75 ;

  Grid15[109].spot[0].L =-45 ; Grid15[109].spot[0].B =-75 ;
  Grid15[109].spot[1].L =-30 ; Grid15[109].spot[1].B =-75 ;
  Grid15[109].spot[2].L =-30 ; Grid15[109].spot[2].B =-60 ;
  Grid15[109].spot[3].L =-45 ; Grid15[109].spot[3].B =-60 ;

  Grid15[110].spot[0].L =-45 ; Grid15[110].spot[0].B =-60 ;
  Grid15[110].spot[1].L =-30 ; Grid15[110].spot[1].B =-60 ;
  Grid15[110].spot[2].L =-30 ; Grid15[110].spot[2].B =-45 ;
  Grid15[110].spot[3].L =-45 ; Grid15[110].spot[3].B =-45 ;

  Grid15[111].spot[0].L =-45 ; Grid15[111].spot[0].B =-45 ;
  Grid15[111].spot[1].L =-30 ; Grid15[111].spot[1].B =-45 ;
  Grid15[111].spot[2].L =-30 ; Grid15[111].spot[2].B =-30 ;
  Grid15[111].spot[3].L =-45 ; Grid15[111].spot[3].B =-30 ;

  Grid15[112].spot[0].L =-45 ; Grid15[112].spot[0].B =-30 ;
  Grid15[112].spot[1].L =-30 ; Grid15[112].spot[1].B =-30 ;
  Grid15[112].spot[2].L =-30 ; Grid15[112].spot[2].B =-15 ;
  Grid15[112].spot[3].L =-45 ; Grid15[112].spot[3].B =-15 ;

  Grid15[113].spot[0].L =-45 ; Grid15[113].spot[0].B =-15 ;
  Grid15[113].spot[1].L =-30 ; Grid15[113].spot[1].B =-15 ;
  Grid15[113].spot[2].L =-30 ; Grid15[113].spot[2].B =0   ;
  Grid15[113].spot[3].L =-45 ; Grid15[113].spot[3].B =0   ;

  Grid15[114].spot[0].L =-45 ; Grid15[114].spot[0].B =0   ;
  Grid15[114].spot[1].L =-30 ; Grid15[114].spot[1].B =0   ;
  Grid15[114].spot[2].L =-30 ; Grid15[114].spot[2].B =15  ;
  Grid15[114].spot[3].L =-45 ; Grid15[114].spot[3].B =15  ;

  Grid15[115].spot[0].L =-45 ; Grid15[115].spot[0].B =15  ;
  Grid15[115].spot[1].L =-30 ; Grid15[115].spot[1].B =15  ;
  Grid15[115].spot[2].L =-30 ; Grid15[115].spot[2].B =30  ;
  Grid15[115].spot[3].L =-45 ; Grid15[115].spot[3].B =30  ;

  Grid15[116].spot[0].L =-45 ; Grid15[116].spot[0].B =30  ;
  Grid15[116].spot[1].L =-30 ; Grid15[116].spot[1].B =30  ;
  Grid15[116].spot[2].L =-30 ; Grid15[116].spot[2].B =45  ;
  Grid15[116].spot[3].L =-45 ; Grid15[116].spot[3].B =45  ;

  Grid15[117].spot[0].L =-45 ; Grid15[117].spot[0].B =45  ;
  Grid15[117].spot[1].L =-30 ; Grid15[117].spot[1].B =45  ;
  Grid15[117].spot[2].L =-30 ; Grid15[117].spot[2].B =60  ;
  Grid15[117].spot[3].L =-45 ; Grid15[117].spot[3].B =60  ;

  Grid15[118].spot[0].L =-45 ; Grid15[118].spot[0].B =60  ;
  Grid15[118].spot[1].L =-30 ; Grid15[118].spot[1].B =60  ;
  Grid15[118].spot[2].L =-30 ; Grid15[118].spot[2].B =75  ;
  Grid15[118].spot[3].L =-45 ; Grid15[118].spot[3].B =75  ;

  Grid15[119].spot[0].L =-45 ; Grid15[119].spot[0].B =75  ;
  Grid15[119].spot[1].L =-30 ; Grid15[119].spot[1].B =75  ;
  Grid15[119].spot[2].L =-30 ; Grid15[119].spot[2].B =90  ;
  Grid15[119].spot[3].L =-45 ; Grid15[119].spot[3].B =90  ;

  Grid15[120].spot[0].L =-30 ; Grid15[120].spot[0].B =-90 ;
  Grid15[120].spot[1].L =-15 ; Grid15[120].spot[1].B =-90 ;
  Grid15[120].spot[2].L =-15 ; Grid15[120].spot[2].B =-75 ;
  Grid15[120].spot[3].L =-30 ; Grid15[120].spot[3].B =-75 ;

  Grid15[121].spot[0].L =-30 ; Grid15[121].spot[0].B =-75 ;
  Grid15[121].spot[1].L =-15 ; Grid15[121].spot[1].B =-75 ;
  Grid15[121].spot[2].L =-15 ; Grid15[121].spot[2].B =-60 ;
  Grid15[121].spot[3].L =-30 ; Grid15[121].spot[3].B =-60 ;

  Grid15[122].spot[0].L =-30 ; Grid15[122].spot[0].B =-60 ;
  Grid15[122].spot[1].L =-15 ; Grid15[122].spot[1].B =-60 ;
  Grid15[122].spot[2].L =-15 ; Grid15[122].spot[2].B =-45 ;
  Grid15[122].spot[3].L =-30 ; Grid15[122].spot[3].B =-45 ;

  Grid15[123].spot[0].L =-30 ; Grid15[123].spot[0].B =-45 ;
  Grid15[123].spot[1].L =-15 ; Grid15[123].spot[1].B =-45 ;
  Grid15[123].spot[2].L =-15 ; Grid15[123].spot[2].B =-30 ;
  Grid15[123].spot[3].L =-30 ; Grid15[123].spot[3].B =-30 ;

  Grid15[124].spot[0].L =-30 ; Grid15[124].spot[0].B =-30 ;
  Grid15[124].spot[1].L =-15 ; Grid15[124].spot[1].B =-30 ;
  Grid15[124].spot[2].L =-15 ; Grid15[124].spot[2].B =-15 ;
  Grid15[124].spot[3].L =-30 ; Grid15[124].spot[3].B =-15 ;

  Grid15[125].spot[0].L =-30 ; Grid15[125].spot[0].B =-15 ;
  Grid15[125].spot[1].L =-15 ; Grid15[125].spot[1].B =-15 ;
  Grid15[125].spot[2].L =-15 ; Grid15[125].spot[2].B =0   ;
  Grid15[125].spot[3].L =-30 ; Grid15[125].spot[3].B =0   ;

  Grid15[126].spot[0].L =-30 ; Grid15[126].spot[0].B =0   ;
  Grid15[126].spot[1].L =-15 ; Grid15[126].spot[1].B =0   ;
  Grid15[126].spot[2].L =-15 ; Grid15[126].spot[2].B =15  ;
  Grid15[126].spot[3].L =-30 ; Grid15[126].spot[3].B =15  ;

  Grid15[127].spot[0].L =-30 ; Grid15[127].spot[0].B =15  ;
  Grid15[127].spot[1].L =-15 ; Grid15[127].spot[1].B =15  ;
  Grid15[127].spot[2].L =-15 ; Grid15[127].spot[2].B =30  ;
  Grid15[127].spot[3].L =-30 ; Grid15[127].spot[3].B =30  ;

  Grid15[128].spot[0].L =-30 ; Grid15[128].spot[0].B =30  ;
  Grid15[128].spot[1].L =-15 ; Grid15[128].spot[1].B =30  ;
  Grid15[128].spot[2].L =-15 ; Grid15[128].spot[2].B =45  ;
  Grid15[128].spot[3].L =-30 ; Grid15[128].spot[3].B =45  ;

  Grid15[129].spot[0].L =-30 ; Grid15[129].spot[0].B =45  ;
  Grid15[129].spot[1].L =-15 ; Grid15[129].spot[1].B =45  ;
  Grid15[129].spot[2].L =-15 ; Grid15[129].spot[2].B =60  ;
  Grid15[129].spot[3].L =-30 ; Grid15[129].spot[3].B =60  ;

  Grid15[130].spot[0].L =-30 ; Grid15[130].spot[0].B =60  ;
  Grid15[130].spot[1].L =-15 ; Grid15[130].spot[1].B =60  ;
  Grid15[130].spot[2].L =-15 ; Grid15[130].spot[2].B =75  ;
  Grid15[130].spot[3].L =-30 ; Grid15[130].spot[3].B =75  ;

  Grid15[131].spot[0].L =-30 ; Grid15[131].spot[0].B =75  ;
  Grid15[131].spot[1].L =-15 ; Grid15[131].spot[1].B =75  ;
  Grid15[131].spot[2].L =-15 ; Grid15[131].spot[2].B =90  ;
  Grid15[131].spot[3].L =-30 ; Grid15[131].spot[3].B =90  ;

  Grid15[132].spot[0].L =-15 ; Grid15[132].spot[0].B =-90 ;
  Grid15[132].spot[1].L = 0  ; Grid15[132].spot[1].B =-90 ;
  Grid15[132].spot[2].L = 0  ; Grid15[132].spot[2].B =-75 ;
  Grid15[132].spot[3].L =-15 ; Grid15[132].spot[3].B =-75 ;

  Grid15[133].spot[0].L =-15 ; Grid15[133].spot[0].B =-75 ;
  Grid15[133].spot[1].L = 0  ; Grid15[133].spot[1].B =-75 ;
  Grid15[133].spot[2].L = 0  ; Grid15[133].spot[2].B =-60 ;
  Grid15[133].spot[3].L =-15 ; Grid15[133].spot[3].B =-60 ;

  Grid15[134].spot[0].L =-15 ; Grid15[134].spot[0].B =-60 ;
  Grid15[134].spot[1].L = 0  ; Grid15[134].spot[1].B =-60 ;
  Grid15[134].spot[2].L = 0  ; Grid15[134].spot[2].B =-45 ;
  Grid15[134].spot[3].L =-15 ; Grid15[134].spot[3].B =-45 ;

  Grid15[135].spot[0].L =-15 ; Grid15[135].spot[0].B =-45 ;
  Grid15[135].spot[1].L = 0  ; Grid15[135].spot[1].B =-45 ;
  Grid15[135].spot[2].L = 0  ; Grid15[135].spot[2].B =-30 ;
  Grid15[135].spot[3].L =-15 ; Grid15[135].spot[3].B =-30 ;

  Grid15[136].spot[0].L =-15 ; Grid15[136].spot[0].B =-30 ;
  Grid15[136].spot[1].L = 0  ; Grid15[136].spot[1].B =-30 ;
  Grid15[136].spot[2].L = 0  ; Grid15[136].spot[2].B =-15 ;
  Grid15[136].spot[3].L =-15 ; Grid15[136].spot[3].B =-15 ;

  Grid15[137].spot[0].L =-15 ; Grid15[137].spot[0].B =-15 ;
  Grid15[137].spot[1].L = 0  ; Grid15[137].spot[1].B =-15 ;
  Grid15[137].spot[2].L = 0  ; Grid15[137].spot[2].B =0   ;
  Grid15[137].spot[3].L =-15 ; Grid15[137].spot[3].B =0   ;

  Grid15[138].spot[0].L =-15 ; Grid15[138].spot[0].B =0   ;
  Grid15[138].spot[1].L = 0  ; Grid15[138].spot[1].B =0   ;
  Grid15[138].spot[2].L = 0  ; Grid15[138].spot[2].B =15  ;
  Grid15[138].spot[3].L =-15 ; Grid15[138].spot[3].B =15  ;

  Grid15[139].spot[0].L =-15 ; Grid15[139].spot[0].B =15  ;
  Grid15[139].spot[1].L = 0  ; Grid15[139].spot[1].B =15  ;
  Grid15[139].spot[2].L = 0  ; Grid15[139].spot[2].B =30  ;
  Grid15[139].spot[3].L =-15 ; Grid15[139].spot[3].B =30  ;

  Grid15[140].spot[0].L =-15 ;  Grid15[140].spot[0].B =30  ;
  Grid15[140].spot[1].L = 0  ; Grid15[140].spot[1].B =30  ;
  Grid15[140].spot[2].L = 0  ; Grid15[140].spot[2].B =45  ;
  Grid15[140].spot[3].L =-15 ; Grid15[140].spot[3].B =45  ;

  Grid15[141].spot[0].L =-15 ; Grid15[141].spot[0].B =45  ;
  Grid15[141].spot[1].L = 0  ; Grid15[141].spot[1].B =45  ;
  Grid15[141].spot[2].L = 0  ; Grid15[141].spot[2].B =60  ;
  Grid15[141].spot[3].L =-15 ; Grid15[141].spot[3].B =60  ;

  Grid15[142].spot[0].L =-15 ; Grid15[142].spot[0].B =60  ;
  Grid15[142].spot[1].L = 0  ; Grid15[142].spot[1].B =60  ;
  Grid15[142].spot[2].L = 0  ; Grid15[142].spot[2].B =75  ;
  Grid15[142].spot[3].L =-15 ; Grid15[142].spot[3].B =75  ;

  Grid15[143].spot[0].L =-15 ; Grid15[143].spot[0].B =75  ;
  Grid15[143].spot[1].L = 0  ; Grid15[143].spot[1].B =75  ;
  Grid15[143].spot[2].L = 0  ; Grid15[143].spot[2].B =90  ;
  Grid15[143].spot[3].L =-15 ; Grid15[143].spot[3].B =90  ;

  Grid15[144].spot[0].L =0  ; Grid15[144].spot[0].B =-90  ;
  Grid15[144].spot[1].L =15 ; Grid15[144].spot[1].B =-90  ;
  Grid15[144].spot[2].L =15 ; Grid15[144].spot[2].B =-75  ;
  Grid15[144].spot[3].L =0  ; Grid15[144].spot[3].B =-75  ;

  Grid15[145].spot[0].L =0  ; Grid15[145].spot[0].B =-75  ;
  Grid15[145].spot[1].L =15 ; Grid15[145].spot[1].B =-75  ;
  Grid15[145].spot[2].L =15 ; Grid15[145].spot[2].B =-60  ;
  Grid15[145].spot[3].L =0  ; Grid15[145].spot[3].B =-60  ;

  Grid15[146].spot[0].L =0  ; Grid15[146].spot[0].B =-60  ;
  Grid15[146].spot[1].L =15 ; Grid15[146].spot[1].B =-60  ;
  Grid15[146].spot[2].L =15 ; Grid15[146].spot[2].B =-45  ;
  Grid15[146].spot[3].L =0  ; Grid15[146].spot[3].B =-45  ;

  Grid15[147].spot[0].L =0  ; Grid15[147].spot[0].B =-45  ;
  Grid15[147].spot[1].L =15 ; Grid15[147].spot[1].B =-45  ;
  Grid15[147].spot[2].L =15 ; Grid15[147].spot[2].B =-30  ;
  Grid15[147].spot[3].L =0  ; Grid15[147].spot[3].B =-30  ;

  Grid15[148].spot[0].L =0  ; Grid15[148].spot[0].B =-30  ;
  Grid15[148].spot[1].L =15 ; Grid15[148].spot[1].B =-30  ;
  Grid15[148].spot[2].L =15 ; Grid15[148].spot[2].B =-15  ;
  Grid15[148].spot[3].L =0  ; Grid15[148].spot[3].B =-15  ;

  Grid15[149].spot[0].L =0  ; Grid15[149].spot[0].B =-15  ;
  Grid15[149].spot[1].L =15 ; Grid15[149].spot[1].B =-15  ;
  Grid15[149].spot[2].L =15 ; Grid15[149].spot[2].B =0    ;
  Grid15[149].spot[3].L =0  ; Grid15[149].spot[3].B =0    ;

  Grid15[150].spot[0].L =0  ; Grid15[150].spot[0].B =0    ;
  Grid15[150].spot[1].L =15 ; Grid15[150].spot[1].B =0    ;
  Grid15[150].spot[2].L =15 ; Grid15[150].spot[2].B =15   ;
  Grid15[150].spot[3].L =0  ; Grid15[150].spot[3].B =15   ;

  Grid15[151].spot[0].L =0  ; Grid15[151].spot[0].B =15   ;
  Grid15[151].spot[1].L =15 ; Grid15[151].spot[1].B =15   ;
  Grid15[151].spot[2].L =15 ; Grid15[151].spot[2].B =30   ;
  Grid15[151].spot[3].L =0  ; Grid15[151].spot[3].B =30   ;

  Grid15[152].spot[0].L =0  ; Grid15[152].spot[0].B =30   ;
  Grid15[152].spot[1].L =15 ; Grid15[152].spot[1].B =30   ;
  Grid15[152].spot[2].L =15 ; Grid15[152].spot[2].B =45   ;
  Grid15[152].spot[3].L =0  ; Grid15[152].spot[3].B =45   ;

  Grid15[153].spot[0].L =0  ; Grid15[153].spot[0].B =45   ;
  Grid15[153].spot[1].L =15 ; Grid15[153].spot[1].B =45   ;
  Grid15[153].spot[2].L =15 ; Grid15[153].spot[2].B =60   ;
  Grid15[153].spot[3].L =0  ; Grid15[153].spot[3].B =60   ;

  Grid15[154].spot[0].L =0  ; Grid15[154].spot[0].B =60   ;
  Grid15[154].spot[1].L =15 ; Grid15[154].spot[1].B =60   ;
  Grid15[154].spot[2].L =15 ; Grid15[154].spot[2].B =75   ;
  Grid15[154].spot[3].L =0  ; Grid15[154].spot[3].B =75   ;

  Grid15[155].spot[0].L =0  ; Grid15[155].spot[0].B =75   ;
  Grid15[155].spot[1].L =15 ; Grid15[155].spot[1].B =75   ;
  Grid15[155].spot[2].L =15 ; Grid15[155].spot[2].B =90   ;
  Grid15[155].spot[3].L =0  ; Grid15[155].spot[3].B =90   ;

  Grid15[156].spot[0].L =15 ; Grid15[156].spot[0].B =-90  ;
  Grid15[156].spot[1].L =30 ; Grid15[156].spot[1].B =-90  ;
  Grid15[156].spot[2].L =30 ; Grid15[156].spot[2].B =-75  ;
  Grid15[156].spot[3].L =15 ; Grid15[156].spot[3].B =-75  ;

  Grid15[157].spot[0].L =15 ; Grid15[157].spot[0].B =-75  ;
  Grid15[157].spot[1].L =30 ; Grid15[157].spot[1].B =-75  ;
  Grid15[157].spot[2].L =30 ; Grid15[157].spot[2].B =-60  ;
  Grid15[157].spot[3].L =15 ; Grid15[157].spot[3].B =-60  ;

  Grid15[158].spot[0].L =15 ; Grid15[158].spot[0].B =-60  ;
  Grid15[158].spot[1].L =30 ; Grid15[158].spot[1].B =-60  ;
  Grid15[158].spot[2].L =30 ; Grid15[158].spot[2].B =-45  ;
  Grid15[158].spot[3].L =15 ; Grid15[158].spot[3].B =-45  ;

  Grid15[159].spot[0].L =15 ; Grid15[159].spot[0].B =-45  ;
  Grid15[159].spot[1].L =30 ; Grid15[159].spot[1].B =-45  ;
  Grid15[159].spot[2].L =30 ; Grid15[159].spot[2].B =-30  ;
  Grid15[159].spot[3].L =15 ; Grid15[159].spot[3].B =-30  ;

  Grid15[160].spot[0].L =15 ; Grid15[160].spot[0].B =-30  ;
  Grid15[160].spot[1].L =30 ; Grid15[160].spot[1].B =-30  ;
  Grid15[160].spot[2].L =30 ; Grid15[160].spot[2].B =-15  ;
  Grid15[160].spot[3].L =15 ; Grid15[160].spot[3].B =-15  ;

  Grid15[161].spot[0].L =15 ; Grid15[161].spot[0].B =-15  ;
  Grid15[161].spot[1].L =30 ; Grid15[161].spot[1].B =-15  ;
  Grid15[161].spot[2].L =30 ; Grid15[161].spot[2].B =0    ;
  Grid15[161].spot[3].L =15 ; Grid15[161].spot[3].B =0    ;

  Grid15[162].spot[0].L =15 ; Grid15[162].spot[0].B =0    ;
  Grid15[162].spot[1].L =30 ; Grid15[162].spot[1].B =0    ;
  Grid15[162].spot[2].L =30 ; Grid15[162].spot[2].B =15   ;
  Grid15[162].spot[3].L =15 ; Grid15[162].spot[3].B =15   ;

  Grid15[163].spot[0].L =15 ; Grid15[163].spot[0].B =15   ;
  Grid15[163].spot[1].L =30 ; Grid15[163].spot[1].B =15   ;
  Grid15[163].spot[2].L =30 ; Grid15[163].spot[2].B =30   ;
  Grid15[163].spot[3].L =15 ; Grid15[163].spot[3].B =30   ;

  Grid15[164].spot[0].L =15 ; Grid15[164].spot[0].B =30   ;
  Grid15[164].spot[1].L =30 ; Grid15[164].spot[1].B =30   ;
  Grid15[164].spot[2].L =30 ; Grid15[164].spot[2].B =45   ;
  Grid15[164].spot[3].L =15 ; Grid15[164].spot[3].B =45   ;

  Grid15[165].spot[0].L =15 ; Grid15[165].spot[0].B =45   ;
  Grid15[165].spot[1].L =30 ; Grid15[165].spot[1].B =45   ;
  Grid15[165].spot[2].L =30 ; Grid15[165].spot[2].B =60   ;
  Grid15[165].spot[3].L =15 ; Grid15[165].spot[3].B =60   ;

  Grid15[166].spot[0].L =15 ; Grid15[166].spot[0].B =60   ;
  Grid15[166].spot[1].L =30 ; Grid15[166].spot[1].B =60   ;
  Grid15[166].spot[2].L =30 ; Grid15[166].spot[2].B =75   ;
  Grid15[166].spot[3].L =15 ; Grid15[166].spot[3].B =75   ;

  Grid15[167].spot[0].L =15 ; Grid15[167].spot[0].B =75   ;
  Grid15[167].spot[1].L =30 ; Grid15[167].spot[1].B =75   ;
  Grid15[167].spot[2].L =30 ; Grid15[167].spot[2].B =90   ;
  Grid15[167].spot[3].L =15 ; Grid15[167].spot[3].B =90   ;

  Grid15[168].spot[0].L =30 ; Grid15[168].spot[0].B =-90  ;
  Grid15[168].spot[1].L =45 ; Grid15[168].spot[1].B =-90  ;
  Grid15[168].spot[2].L =45 ; Grid15[168].spot[2].B =-75  ;
  Grid15[168].spot[3].L =30 ; Grid15[168].spot[3].B =-75  ;

  Grid15[169].spot[0].L =30 ; Grid15[169].spot[0].B =-75  ;
  Grid15[169].spot[1].L =45 ; Grid15[169].spot[1].B =-75  ;
  Grid15[169].spot[2].L =45 ; Grid15[169].spot[2].B =-60  ;
  Grid15[169].spot[3].L =30 ; Grid15[169].spot[3].B =-60  ;

  Grid15[170].spot[0].L =30 ;  Grid15[170].spot[0].B =-60  ;
  Grid15[170].spot[1].L =45 ; Grid15[170].spot[1].B =-60  ;
  Grid15[170].spot[2].L =45 ; Grid15[170].spot[2].B =-45  ;
  Grid15[170].spot[3].L =30 ; Grid15[170].spot[3].B =-45  ;

  Grid15[171].spot[0].L =30 ;  Grid15[171].spot[0].B =-45  ;
  Grid15[171].spot[1].L =45 ; Grid15[171].spot[1].B =-45  ;
  Grid15[171].spot[2].L =45 ; Grid15[171].spot[2].B =-30  ;
  Grid15[171].spot[3].L =30 ; Grid15[171].spot[3].B =-30  ;

  Grid15[172].spot[0].L =30 ; Grid15[172].spot[0].B =-30  ;
  Grid15[172].spot[1].L =45 ; Grid15[172].spot[1].B =-30  ;
  Grid15[172].spot[2].L =45 ; Grid15[172].spot[2].B =-15  ;
  Grid15[172].spot[3].L =30 ; Grid15[172].spot[3].B =-15  ;

  Grid15[173].spot[0].L =30 ; Grid15[173].spot[0].B =-15  ;
  Grid15[173].spot[1].L =45 ; Grid15[173].spot[1].B =-15  ;
  Grid15[173].spot[2].L =45 ; Grid15[173].spot[2].B =0    ;
  Grid15[173].spot[3].L =30 ; Grid15[173].spot[3].B =0    ;

  Grid15[174].spot[0].L =30 ; Grid15[174].spot[0].B =0    ;
  Grid15[174].spot[1].L =45 ; Grid15[174].spot[1].B =0    ;
  Grid15[174].spot[2].L =45 ; Grid15[174].spot[2].B =15   ;
  Grid15[174].spot[3].L =30 ; Grid15[174].spot[3].B =15   ;

  Grid15[175].spot[0].L =30 ; Grid15[175].spot[0].B =15   ;
  Grid15[175].spot[1].L =45 ; Grid15[175].spot[1].B =15   ;
  Grid15[175].spot[2].L =45 ; Grid15[175].spot[2].B =30   ;
  Grid15[175].spot[3].L =30 ; Grid15[175].spot[3].B =30   ;

  Grid15[176].spot[0].L =30 ; Grid15[176].spot[0].B =30   ;
  Grid15[176].spot[1].L =45 ; Grid15[176].spot[1].B =30   ;
  Grid15[176].spot[2].L =45 ; Grid15[176].spot[2].B =45   ;
  Grid15[176].spot[3].L =30 ; Grid15[176].spot[3].B =45   ;

  Grid15[177].spot[0].L =30 ; Grid15[177].spot[0].B =45   ;
  Grid15[177].spot[1].L =45 ; Grid15[177].spot[1].B =45   ;
  Grid15[177].spot[2].L =45 ; Grid15[177].spot[2].B =60   ;
  Grid15[177].spot[3].L =30 ; Grid15[177].spot[3].B =60   ;

  Grid15[178].spot[0].L =30 ; Grid15[178].spot[0].B =60   ;
  Grid15[178].spot[1].L =45 ; Grid15[178].spot[1].B =60   ;
  Grid15[178].spot[2].L =45 ; Grid15[178].spot[2].B =75   ;
  Grid15[178].spot[3].L =30 ; Grid15[178].spot[3].B =75   ;

  Grid15[179].spot[0].L =30 ; Grid15[179].spot[0].B =75   ;
  Grid15[179].spot[1].L =45 ; Grid15[179].spot[1].B =75   ;
  Grid15[179].spot[2].L =45 ; Grid15[179].spot[2].B =90   ;
  Grid15[179].spot[3].L =30 ; Grid15[179].spot[3].B =90   ;

  Grid15[180].spot[0].L =45 ; Grid15[180].spot[0].B =-90  ;
  Grid15[180].spot[1].L =60 ; Grid15[180].spot[1].B =-90  ;
  Grid15[180].spot[2].L =60 ; Grid15[180].spot[2].B =-75  ;
  Grid15[180].spot[3].L =45 ; Grid15[180].spot[3].B =-75  ;

  Grid15[181].spot[0].L =45 ; Grid15[181].spot[0].B =-75  ;
  Grid15[181].spot[1].L =60 ; Grid15[181].spot[1].B =-75  ;
  Grid15[181].spot[2].L =60 ; Grid15[181].spot[2].B =-60  ;
  Grid15[181].spot[3].L =45 ; Grid15[181].spot[3].B =-60  ;

  Grid15[182].spot[0].L =45 ; Grid15[182].spot[0].B =-60  ;
  Grid15[182].spot[1].L =60 ; Grid15[182].spot[1].B =-60  ;
  Grid15[182].spot[2].L =60 ; Grid15[182].spot[2].B =-45  ;
  Grid15[182].spot[3].L =45 ; Grid15[182].spot[3].B =-45  ;

  Grid15[183].spot[0].L =45 ; Grid15[183].spot[0].B =-45  ;
  Grid15[183].spot[1].L =60 ; Grid15[183].spot[1].B =-45  ;
  Grid15[183].spot[2].L =60 ; Grid15[183].spot[2].B =-30  ;
  Grid15[183].spot[3].L =45 ; Grid15[183].spot[3].B =-30  ;

  Grid15[184].spot[0].L =45 ; Grid15[184].spot[0].B =-30  ;
  Grid15[184].spot[1].L =60 ; Grid15[184].spot[1].B =-30  ;
  Grid15[184].spot[2].L =60 ; Grid15[184].spot[2].B =-15  ;
  Grid15[184].spot[3].L =45 ; Grid15[184].spot[3].B =-15  ;

  Grid15[185].spot[0].L =45 ; Grid15[185].spot[0].B =-15  ;
  Grid15[185].spot[1].L =60 ; Grid15[185].spot[1].B =-15  ;
  Grid15[185].spot[2].L =60 ; Grid15[185].spot[2].B =0    ;
  Grid15[185].spot[3].L =45 ; Grid15[185].spot[3].B =0    ;

  Grid15[186].spot[0].L =45 ; Grid15[186].spot[0].B =0    ;
  Grid15[186].spot[1].L =60 ; Grid15[186].spot[1].B =0    ;
  Grid15[186].spot[2].L =60 ; Grid15[186].spot[2].B =15   ;
  Grid15[186].spot[3].L =45 ; Grid15[186].spot[3].B =15   ;

  Grid15[187].spot[0].L =45 ; Grid15[187].spot[0].B =15   ;
  Grid15[187].spot[1].L =60 ; Grid15[187].spot[1].B =15   ;
  Grid15[187].spot[2].L =60 ; Grid15[187].spot[2].B =30   ;
  Grid15[187].spot[3].L =45 ; Grid15[187].spot[3].B =30   ;

  Grid15[188].spot[0].L =45 ; Grid15[188].spot[0].B =30   ;
  Grid15[188].spot[1].L =60 ; Grid15[188].spot[1].B =30   ;
  Grid15[188].spot[2].L =60 ; Grid15[188].spot[2].B =45   ;
  Grid15[188].spot[3].L =45 ; Grid15[188].spot[3].B =45   ;

  Grid15[189].spot[0].L =45 ; Grid15[189].spot[0].B =45   ;
  Grid15[189].spot[1].L =60 ; Grid15[189].spot[1].B =45   ;
  Grid15[189].spot[2].L =60 ; Grid15[189].spot[2].B =60   ;
  Grid15[189].spot[3].L =45 ; Grid15[189].spot[3].B =60   ;

  Grid15[190].spot[0].L =45 ; Grid15[190].spot[0].B =60   ;
  Grid15[190].spot[1].L =60 ; Grid15[190].spot[1].B =60   ;
  Grid15[190].spot[2].L =60 ; Grid15[190].spot[2].B =75   ;
  Grid15[190].spot[3].L =45 ; Grid15[190].spot[3].B =75   ;

  Grid15[191].spot[0].L =45 ; Grid15[191].spot[0].B =75   ;
  Grid15[191].spot[1].L =60 ; Grid15[191].spot[1].B =75   ;
  Grid15[191].spot[2].L =60 ; Grid15[191].spot[2].B =90   ;
  Grid15[191].spot[3].L =45 ; Grid15[191].spot[3].B =90   ;

  Grid15[192].spot[0].L =60 ; Grid15[192].spot[0].B =-90  ;
  Grid15[192].spot[1].L =75 ; Grid15[192].spot[1].B =-90  ;
  Grid15[192].spot[2].L =75 ; Grid15[192].spot[2].B =-75  ;
  Grid15[192].spot[3].L =60 ; Grid15[192].spot[3].B =-75  ;

  Grid15[193].spot[0].L =60 ; Grid15[193].spot[0].B =-75  ;
  Grid15[193].spot[1].L =75 ; Grid15[193].spot[1].B =-75  ;
  Grid15[193].spot[2].L =75 ; Grid15[193].spot[2].B =-60  ;
  Grid15[193].spot[3].L =60 ; Grid15[193].spot[3].B =-60  ;

  Grid15[194].spot[0].L =60 ; Grid15[194].spot[0].B =-60  ;
  Grid15[194].spot[1].L =75 ; Grid15[194].spot[1].B =-60  ;
  Grid15[194].spot[2].L =75 ; Grid15[194].spot[2].B =-45  ;
  Grid15[194].spot[3].L =60 ; Grid15[194].spot[3].B =-45  ;

  Grid15[195].spot[0].L =60 ; Grid15[195].spot[0].B =-45  ;
  Grid15[195].spot[1].L =75 ; Grid15[195].spot[1].B =-45  ;
  Grid15[195].spot[2].L =75 ; Grid15[195].spot[2].B =-30  ;
  Grid15[195].spot[3].L =60 ; Grid15[195].spot[3].B =-30  ;

  Grid15[196].spot[0].L =60 ; Grid15[196].spot[0].B =-30  ;
  Grid15[196].spot[1].L =75 ; Grid15[196].spot[1].B =-30  ;
  Grid15[196].spot[2].L =75 ; Grid15[196].spot[2].B =-15  ;
  Grid15[196].spot[3].L =60 ; Grid15[196].spot[3].B =-15  ;

  Grid15[197].spot[0].L =60 ; Grid15[197].spot[0].B =-15  ;
  Grid15[197].spot[1].L =75 ; Grid15[197].spot[1].B =-15  ;
  Grid15[197].spot[2].L =75 ; Grid15[197].spot[2].B =0    ;
  Grid15[197].spot[3].L =60 ; Grid15[197].spot[3].B =0    ;

  Grid15[198].spot[0].L =60 ; Grid15[198].spot[0].B =0    ;
  Grid15[198].spot[1].L =75 ; Grid15[198].spot[1].B =0    ;
  Grid15[198].spot[2].L =75 ; Grid15[198].spot[2].B =15   ;
  Grid15[198].spot[3].L =60 ; Grid15[198].spot[3].B =15   ;

  Grid15[199].spot[0].L =60 ; Grid15[199].spot[0].B =15   ;
  Grid15[199].spot[1].L =75 ; Grid15[199].spot[1].B =15   ;
  Grid15[199].spot[2].L =75 ; Grid15[199].spot[2].B =30   ;
  Grid15[199].spot[3].L =60 ; Grid15[199].spot[3].B =30   ;

  Grid15[200].spot[0].L =60 ; Grid15[200].spot[0].B =30   ;
  Grid15[200].spot[1].L =75 ; Grid15[200].spot[1].B =30   ;
  Grid15[200].spot[2].L =75 ; Grid15[200].spot[2].B =45   ;
  Grid15[200].spot[3].L =60 ; Grid15[200].spot[3].B =45   ;

  Grid15[201].spot[0].L =60 ; Grid15[201].spot[0].B =45   ;
  Grid15[201].spot[1].L =75 ; Grid15[201].spot[1].B =45   ;
  Grid15[201].spot[2].L =75 ; Grid15[201].spot[2].B =60   ;
  Grid15[201].spot[3].L =60 ; Grid15[201].spot[3].B =60   ;

  Grid15[202].spot[0].L =60 ; Grid15[202].spot[0].B =60   ;
  Grid15[202].spot[1].L =75 ; Grid15[202].spot[1].B =60   ;
  Grid15[202].spot[2].L =75 ; Grid15[202].spot[2].B =75   ;
  Grid15[202].spot[3].L =60 ; Grid15[202].spot[3].B =75   ;

  Grid15[203].spot[0].L =60 ; Grid15[203].spot[0].B =75   ;
  Grid15[203].spot[1].L =75 ; Grid15[203].spot[1].B =75   ;
  Grid15[203].spot[2].L =75 ; Grid15[203].spot[2].B =90   ;
  Grid15[203].spot[3].L =60 ; Grid15[203].spot[3].B =90   ;

  Grid15[204].spot[0].L =75 ; Grid15[204].spot[0].B =-90  ;
  Grid15[204].spot[1].L =90 ; Grid15[204].spot[1].B =-90  ;
  Grid15[204].spot[2].L =90 ; Grid15[204].spot[2].B =-75  ;
  Grid15[204].spot[3].L =75 ; Grid15[204].spot[3].B =-75  ;

  Grid15[205].spot[0].L =75 ; Grid15[205].spot[0].B =-75  ;
  Grid15[205].spot[1].L =90 ; Grid15[205].spot[1].B =-75  ;
  Grid15[205].spot[2].L =90 ; Grid15[205].spot[2].B =-60  ;
  Grid15[205].spot[3].L =75 ; Grid15[205].spot[3].B =-60  ;

  Grid15[206].spot[0].L =75 ; Grid15[206].spot[0].B =-60  ;
  Grid15[206].spot[1].L =90 ; Grid15[206].spot[1].B =-60  ;
  Grid15[206].spot[2].L =90 ; Grid15[206].spot[2].B =-45  ;
  Grid15[206].spot[3].L =75 ; Grid15[206].spot[3].B =-45  ;

  Grid15[207].spot[0].L =75 ; Grid15[207].spot[0].B =-45  ;
  Grid15[207].spot[1].L =90 ; Grid15[207].spot[1].B =-45  ;
  Grid15[207].spot[2].L =90 ; Grid15[207].spot[2].B =-30  ;
  Grid15[207].spot[3].L =75 ; Grid15[207].spot[3].B =-30  ;

  Grid15[208].spot[0].L =75 ; Grid15[208].spot[0].B =-30  ;
  Grid15[208].spot[1].L =90 ; Grid15[208].spot[1].B =-30  ;
  Grid15[208].spot[2].L =90 ; Grid15[208].spot[2].B =-15  ;
  Grid15[208].spot[3].L =75 ; Grid15[208].spot[3].B =-15  ;

  Grid15[209].spot[0].L =75 ; Grid15[209].spot[0].B =-15  ;
  Grid15[209].spot[1].L =90 ; Grid15[209].spot[1].B =-15  ;
  Grid15[209].spot[2].L =90 ; Grid15[209].spot[2].B =0    ;
  Grid15[209].spot[3].L =75 ; Grid15[209].spot[3].B =0    ;

  Grid15[210].spot[0].L =75 ; Grid15[210].spot[0].B =0    ;
  Grid15[210].spot[1].L =90 ; Grid15[210].spot[1].B =0    ;
  Grid15[210].spot[2].L =90 ; Grid15[210].spot[2].B =15   ;
  Grid15[210].spot[3].L =75 ; Grid15[210].spot[3].B =15   ;

  Grid15[211].spot[0].L =75 ; Grid15[211].spot[0].B =15   ;
  Grid15[211].spot[1].L =90 ; Grid15[211].spot[1].B =15   ;
  Grid15[211].spot[2].L =90 ; Grid15[211].spot[2].B =30   ;
  Grid15[211].spot[3].L =75 ; Grid15[211].spot[3].B =30   ;

  Grid15[212].spot[0].L =75 ; Grid15[212].spot[0].B =30   ;
  Grid15[212].spot[1].L =90 ; Grid15[212].spot[1].B =30   ;
  Grid15[212].spot[2].L =90 ; Grid15[212].spot[2].B =45   ;
  Grid15[212].spot[3].L =75 ; Grid15[212].spot[3].B =45   ;

  Grid15[213].spot[0].L =75 ; Grid15[213].spot[0].B =45   ;
  Grid15[213].spot[1].L =90 ; Grid15[213].spot[1].B =45   ;
  Grid15[213].spot[2].L =90 ; Grid15[213].spot[2].B =60   ;
  Grid15[213].spot[3].L =75 ; Grid15[213].spot[3].B =60   ;

  Grid15[214].spot[0].L =75 ; Grid15[214].spot[0].B =60   ;
  Grid15[214].spot[1].L =90 ; Grid15[214].spot[1].B =60   ;
  Grid15[214].spot[2].L =90 ; Grid15[214].spot[2].B =75   ;
  Grid15[214].spot[3].L =75 ; Grid15[214].spot[3].B =75   ;

  Grid15[215].spot[0].L =75 ; Grid15[215].spot[0].B =75   ;
  Grid15[215].spot[1].L =90 ; Grid15[215].spot[1].B =75   ;
  Grid15[215].spot[2].L =90 ; Grid15[215].spot[2].B =90   ;
  Grid15[215].spot[3].L =75 ; Grid15[215].spot[3].B =90   ;

  Grid15[216].spot[0].L =90 ; Grid15[216].spot[0].B =-90  ;
  Grid15[216].spot[1].L =105; Grid15[216].spot[1].B = -90 ;
  Grid15[216].spot[2].L =105; Grid15[216].spot[2].B = -75 ;
  Grid15[216].spot[3].L =90 ; Grid15[216].spot[3].B =-75  ;

  Grid15[217].spot[0].L =90 ; Grid15[217].spot[0].B =-75  ;
  Grid15[217].spot[1].L =105; Grid15[217].spot[1].B = -75 ;
  Grid15[217].spot[2].L =105; Grid15[217].spot[2].B = -60 ;
  Grid15[217].spot[3].L =90 ; Grid15[217].spot[3].B =-60  ;

  Grid15[218].spot[0].L =90 ; Grid15[218].spot[0].B =-60  ;
  Grid15[218].spot[1].L =105; Grid15[218].spot[1].B = -60 ;
  Grid15[218].spot[2].L =105; Grid15[218].spot[2].B = -45 ;
  Grid15[218].spot[3].L =90 ; Grid15[218].spot[3].B =-45  ;

  Grid15[219].spot[0].L =90 ; Grid15[219].spot[0].B =-45  ;
  Grid15[219].spot[1].L =105; Grid15[219].spot[1].B = -45 ;
  Grid15[219].spot[2].L =105; Grid15[219].spot[2].B = -30 ;
  Grid15[219].spot[3].L =90 ; Grid15[219].spot[3].B =-30  ;

  Grid15[220].spot[0].L =90 ; Grid15[220].spot[0].B =-30  ;
  Grid15[220].spot[1].L =105; Grid15[220].spot[1].B = -30 ;
  Grid15[220].spot[2].L =105; Grid15[220].spot[2].B = -15 ;
  Grid15[220].spot[3].L =90 ; Grid15[220].spot[3].B =-15  ;

  Grid15[221].spot[0].L =90 ; Grid15[221].spot[0].B =-15  ;
  Grid15[221].spot[1].L =105; Grid15[221].spot[1].B = -15 ;
  Grid15[221].spot[2].L =105; Grid15[221].spot[2].B = 0   ;
  Grid15[221].spot[3].L =90 ; Grid15[221].spot[3].B =0    ;

  Grid15[222].spot[0].L =90 ; Grid15[222].spot[0].B =0    ;
  Grid15[222].spot[1].L =105; Grid15[222].spot[1].B = 0   ;
  Grid15[222].spot[2].L =105; Grid15[222].spot[2].B = 15  ;
  Grid15[222].spot[3].L =90 ; Grid15[222].spot[3].B =15   ;

  Grid15[223].spot[0].L =90 ; Grid15[223].spot[0].B =15   ;
  Grid15[223].spot[1].L =105; Grid15[223].spot[1].B = 15  ;
  Grid15[223].spot[2].L =105; Grid15[223].spot[2].B = 30  ;
  Grid15[223].spot[3].L =90 ; Grid15[223].spot[3].B =30   ;

  Grid15[224].spot[0].L =90 ; Grid15[224].spot[0].B =30   ;
  Grid15[224].spot[1].L =105; Grid15[224].spot[1].B = 30  ;
  Grid15[224].spot[2].L =105; Grid15[224].spot[2].B = 45  ;
  Grid15[224].spot[3].L =90 ; Grid15[224].spot[3].B =45   ;

  Grid15[225].spot[0].L =90 ; Grid15[225].spot[0].B =45   ;
  Grid15[225].spot[1].L =105; Grid15[225].spot[1].B = 45  ;
  Grid15[225].spot[2].L =105; Grid15[225].spot[2].B = 60  ;
  Grid15[225].spot[3].L =90 ; Grid15[225].spot[3].B =60   ;

  Grid15[226].spot[0].L =90 ; Grid15[226].spot[0].B =60   ;
  Grid15[226].spot[1].L =105; Grid15[226].spot[1].B = 60  ;
  Grid15[226].spot[2].L =105; Grid15[226].spot[2].B = 75  ;
  Grid15[226].spot[3].L =90 ; Grid15[226].spot[3].B =75   ;

  Grid15[227].spot[0].L =90 ; Grid15[227].spot[0].B =75   ;
  Grid15[227].spot[1].L =105; Grid15[227].spot[1].B = 75  ;
  Grid15[227].spot[2].L =105; Grid15[227].spot[2].B = 90  ;
  Grid15[227].spot[3].L =90 ; Grid15[227].spot[3].B =90   ;

  Grid15[228].spot[0].L =105; Grid15[228].spot[0].B = -90 ;
  Grid15[228].spot[1].L =120; Grid15[228].spot[1].B = -90 ;
  Grid15[228].spot[2].L =120; Grid15[228].spot[2].B = -75 ;
  Grid15[228].spot[3].L =105; Grid15[228].spot[3].B = -75 ;

  Grid15[229].spot[0].L =105; Grid15[229].spot[0].B = -75 ;
  Grid15[229].spot[1].L =120; Grid15[229].spot[1].B = -75 ;
  Grid15[229].spot[2].L =120; Grid15[229].spot[2].B = -60 ;
  Grid15[229].spot[3].L =105; Grid15[229].spot[3].B = -60 ;

  Grid15[230].spot[0].L =105; Grid15[230].spot[0].B = -60 ;
  Grid15[230].spot[1].L =120; Grid15[230].spot[1].B = -60 ;
  Grid15[230].spot[2].L =120; Grid15[230].spot[2].B = -45 ;
  Grid15[230].spot[3].L =105; Grid15[230].spot[3].B = -45 ;

  Grid15[231].spot[0].L =105; Grid15[231].spot[0].B = -45 ;
  Grid15[231].spot[1].L =120; Grid15[231].spot[1].B = -45 ;
  Grid15[231].spot[2].L =120; Grid15[231].spot[2].B = -30 ;
  Grid15[231].spot[3].L =105; Grid15[231].spot[3].B = -30 ;

  Grid15[232].spot[0].L =105; Grid15[232].spot[0].B = -30 ;
  Grid15[232].spot[1].L =120; Grid15[232].spot[1].B = -30 ;
  Grid15[232].spot[2].L =120; Grid15[232].spot[2].B = -15 ;
  Grid15[232].spot[3].L =105; Grid15[232].spot[3].B = -15 ;

  Grid15[233].spot[0].L =105; Grid15[233].spot[0].B = -15 ;
  Grid15[233].spot[1].L =120; Grid15[233].spot[1].B = -15 ;
  Grid15[233].spot[2].L =120; Grid15[233].spot[2].B = 0   ;
  Grid15[233].spot[3].L =105; Grid15[233].spot[3].B = 0   ;

  Grid15[234].spot[0].L =105; Grid15[234].spot[0].B = 0   ;
  Grid15[234].spot[1].L =120; Grid15[234].spot[1].B = 0   ;
  Grid15[234].spot[2].L =120; Grid15[234].spot[2].B = 15  ;
  Grid15[234].spot[3].L =105; Grid15[234].spot[3].B = 15  ;

  Grid15[235].spot[0].L =105; Grid15[235].spot[0].B = 15  ;
  Grid15[235].spot[1].L =120; Grid15[235].spot[1].B = 15  ;
  Grid15[235].spot[2].L =120; Grid15[235].spot[2].B = 30  ;
  Grid15[235].spot[3].L =105; Grid15[235].spot[3].B = 30  ;

  Grid15[236].spot[0].L =105; Grid15[236].spot[0].B = 30  ;
  Grid15[236].spot[1].L =120; Grid15[236].spot[1].B = 30  ;
  Grid15[236].spot[2].L =120; Grid15[236].spot[2].B = 45  ;
  Grid15[236].spot[3].L =105; Grid15[236].spot[3].B = 45  ;

  Grid15[237].spot[0].L =105; Grid15[237].spot[0].B = 45  ;
  Grid15[237].spot[1].L =120; Grid15[237].spot[1].B = 45  ;
  Grid15[237].spot[2].L =120; Grid15[237].spot[2].B = 60  ;
  Grid15[237].spot[3].L =105; Grid15[237].spot[3].B = 60  ;

  Grid15[238].spot[0].L =105; Grid15[238].spot[0].B = 60  ;
  Grid15[238].spot[1].L =120; Grid15[238].spot[1].B = 60  ;
  Grid15[238].spot[2].L =120; Grid15[238].spot[2].B = 75  ;
  Grid15[238].spot[3].L =105; Grid15[238].spot[3].B = 75  ;

  Grid15[239].spot[0].L =105; Grid15[239].spot[0].B = 75  ;
  Grid15[239].spot[1].L =120; Grid15[239].spot[1].B = 75  ;
  Grid15[239].spot[2].L =120; Grid15[239].spot[2].B = 90  ;
  Grid15[239].spot[3].L =105; Grid15[239].spot[3].B = 90  ;

  Grid15[240].spot[0].L =120; Grid15[240].spot[0].B = -90 ;
  Grid15[240].spot[1].L =135; Grid15[240].spot[1].B = -90 ;
  Grid15[240].spot[2].L =135; Grid15[240].spot[2].B = -75 ;
  Grid15[240].spot[3].L =120; Grid15[240].spot[3].B = -75 ;

  Grid15[241].spot[0].L =120; Grid15[241].spot[0].B = -75 ;
  Grid15[241].spot[1].L =135; Grid15[241].spot[1].B = -75 ;
  Grid15[241].spot[2].L =135; Grid15[241].spot[2].B = -60 ;
  Grid15[241].spot[3].L =120; Grid15[241].spot[3].B = -60 ;

  Grid15[242].spot[0].L =120; Grid15[242].spot[0].B = -60 ;
  Grid15[242].spot[1].L =135; Grid15[242].spot[1].B = -60 ;
  Grid15[242].spot[2].L =135; Grid15[242].spot[2].B = -45 ;
  Grid15[242].spot[3].L =120; Grid15[242].spot[3].B = -45 ;

  Grid15[243].spot[0].L =120; Grid15[243].spot[0].B = -45 ;
  Grid15[243].spot[1].L =135; Grid15[243].spot[1].B = -45 ;
  Grid15[243].spot[2].L =135; Grid15[243].spot[2].B = -30 ;
  Grid15[243].spot[3].L =120; Grid15[243].spot[3].B = -30 ;

  Grid15[244].spot[0].L =120; Grid15[244].spot[0].B = -30 ;
  Grid15[244].spot[1].L =135; Grid15[244].spot[1].B = -30 ;
  Grid15[244].spot[2].L =135; Grid15[244].spot[2].B = -15 ;
  Grid15[244].spot[3].L =120; Grid15[244].spot[3].B = -15 ;

  Grid15[245].spot[0].L =120; Grid15[245].spot[0].B = -15 ;
  Grid15[245].spot[1].L =135; Grid15[245].spot[1].B = -15 ;
  Grid15[245].spot[2].L =135; Grid15[245].spot[2].B = 0   ;
  Grid15[245].spot[3].L =120; Grid15[245].spot[3].B = 0   ;

  Grid15[246].spot[0].L =120; Grid15[246].spot[0].B = 0   ;
  Grid15[246].spot[1].L =135; Grid15[246].spot[1].B = 0   ;
  Grid15[246].spot[2].L =135; Grid15[246].spot[2].B = 15  ;
  Grid15[246].spot[3].L =120; Grid15[246].spot[3].B = 15  ;

  Grid15[247].spot[0].L =120; Grid15[247].spot[0].B = 15  ;
  Grid15[247].spot[1].L =135; Grid15[247].spot[1].B = 15  ;
  Grid15[247].spot[2].L =135; Grid15[247].spot[2].B = 30  ;
  Grid15[247].spot[3].L =120; Grid15[247].spot[3].B = 30  ;

  Grid15[248].spot[0].L =120; Grid15[248].spot[0].B = 30  ;
  Grid15[248].spot[1].L =135; Grid15[248].spot[1].B = 30  ;
  Grid15[248].spot[2].L =135; Grid15[248].spot[2].B = 45  ;
  Grid15[248].spot[3].L =120; Grid15[248].spot[3].B = 45  ;

  Grid15[249].spot[0].L =120; Grid15[249].spot[0].B = 45  ;
  Grid15[249].spot[1].L =135; Grid15[249].spot[1].B = 45  ;
  Grid15[249].spot[2].L =135; Grid15[249].spot[2].B = 60  ;
  Grid15[249].spot[3].L =120; Grid15[249].spot[3].B = 60  ;

  Grid15[250].spot[0].L =120; Grid15[250].spot[0].B = 60  ;
  Grid15[250].spot[1].L =135; Grid15[250].spot[1].B = 60  ;
  Grid15[250].spot[2].L =135; Grid15[250].spot[2].B = 75  ;
  Grid15[250].spot[3].L =120; Grid15[250].spot[3].B = 75  ;

  Grid15[251].spot[0].L =120; Grid15[251].spot[0].B = 75  ;
  Grid15[251].spot[1].L =135; Grid15[251].spot[1].B = 75  ;
  Grid15[251].spot[2].L =135; Grid15[251].spot[2].B = 90  ;
  Grid15[251].spot[3].L =120; Grid15[251].spot[3].B = 90  ;

  Grid15[252].spot[0].L =135; Grid15[252].spot[0].B = -90 ;
  Grid15[252].spot[1].L =150; Grid15[252].spot[1].B = -90 ;
  Grid15[252].spot[2].L =150; Grid15[252].spot[2].B = -75 ;
  Grid15[252].spot[3].L =135; Grid15[252].spot[3].B = -75 ;

  Grid15[253].spot[0].L =135; Grid15[253].spot[0].B = -75 ;
  Grid15[253].spot[1].L =150; Grid15[253].spot[1].B = -75 ;
  Grid15[253].spot[2].L =150; Grid15[253].spot[2].B = -60 ;
  Grid15[253].spot[3].L =135; Grid15[253].spot[3].B = -60 ;

  Grid15[254].spot[0].L =135; Grid15[254].spot[0].B = -60 ;
  Grid15[254].spot[1].L =150; Grid15[254].spot[1].B = -60 ;
  Grid15[254].spot[2].L =150; Grid15[254].spot[2].B = -45 ;
  Grid15[254].spot[3].L =135; Grid15[254].spot[3].B = -45 ;

  Grid15[255].spot[0].L =135; Grid15[255].spot[0].B = -45 ;
  Grid15[255].spot[1].L =150; Grid15[255].spot[1].B = -45 ;
  Grid15[255].spot[2].L =150; Grid15[255].spot[2].B = -30 ;
  Grid15[255].spot[3].L =135; Grid15[255].spot[3].B = -30 ;

  Grid15[256].spot[0].L =135; Grid15[256].spot[0].B = -30 ;
  Grid15[256].spot[1].L =150; Grid15[256].spot[1].B = -30 ;
  Grid15[256].spot[2].L =150; Grid15[256].spot[2].B = -15 ;
  Grid15[256].spot[3].L =135; Grid15[256].spot[3].B = -15 ;

  Grid15[257].spot[0].L =135; Grid15[257].spot[0].B = -15 ;
  Grid15[257].spot[1].L =150; Grid15[257].spot[1].B = -15 ;
  Grid15[257].spot[2].L =150; Grid15[257].spot[2].B = 0   ;
  Grid15[257].spot[3].L =135; Grid15[257].spot[3].B = 0   ;

  Grid15[258].spot[0].L =135; Grid15[258].spot[0].B = 0   ;
  Grid15[258].spot[1].L =150; Grid15[258].spot[1].B = 0   ;
  Grid15[258].spot[2].L =150; Grid15[258].spot[2].B = 15  ;
  Grid15[258].spot[3].L =135; Grid15[258].spot[3].B = 15  ;

  Grid15[259].spot[0].L =135; Grid15[259].spot[0].B = 15  ;
  Grid15[259].spot[1].L =150; Grid15[259].spot[1].B = 15  ;
  Grid15[259].spot[2].L =150; Grid15[259].spot[2].B = 30  ;
  Grid15[259].spot[3].L =135; Grid15[259].spot[3].B = 30  ;

  Grid15[260].spot[0].L =135; Grid15[260].spot[0].B = 30  ;
  Grid15[260].spot[1].L =150; Grid15[260].spot[1].B = 30  ;
  Grid15[260].spot[2].L =150; Grid15[260].spot[2].B = 45  ;
  Grid15[260].spot[3].L =135; Grid15[260].spot[3].B = 45  ;

  Grid15[261].spot[0].L =135; Grid15[261].spot[0].B = 45  ;
  Grid15[261].spot[1].L =150; Grid15[261].spot[1].B = 45  ;
  Grid15[261].spot[2].L =150; Grid15[261].spot[2].B = 60  ;
  Grid15[261].spot[3].L =135; Grid15[261].spot[3].B = 60  ;

  Grid15[262].spot[0].L =135; Grid15[262].spot[0].B = 60  ;
  Grid15[262].spot[1].L =150; Grid15[262].spot[1].B = 60  ;
  Grid15[262].spot[2].L =150; Grid15[262].spot[2].B = 75  ;
  Grid15[262].spot[3].L =135; Grid15[262].spot[3].B = 75  ;

  Grid15[263].spot[0].L =135; Grid15[263].spot[0].B = 75  ;
  Grid15[263].spot[1].L =150; Grid15[263].spot[1].B = 75  ;
  Grid15[263].spot[2].L =150; Grid15[263].spot[2].B = 90  ;
  Grid15[263].spot[3].L =135; Grid15[263].spot[3].B = 90  ;

  Grid15[264].spot[0].L =150; Grid15[264].spot[0].B = -90 ;
  Grid15[264].spot[1].L =165; Grid15[264].spot[1].B = -90 ;
  Grid15[264].spot[2].L =165; Grid15[264].spot[2].B = -75 ;
  Grid15[264].spot[3].L =150; Grid15[264].spot[3].B = -75 ;

  Grid15[265].spot[0].L =150; Grid15[265].spot[0].B = -75 ;
  Grid15[265].spot[1].L =165; Grid15[265].spot[1].B = -75 ;
  Grid15[265].spot[2].L =165; Grid15[265].spot[2].B = -60 ;
  Grid15[265].spot[3].L =150; Grid15[265].spot[3].B = -60 ;

  Grid15[266].spot[0].L =150; Grid15[266].spot[0].B = -60 ;
  Grid15[266].spot[1].L =165; Grid15[266].spot[1].B = -60 ;
  Grid15[266].spot[2].L =165; Grid15[266].spot[2].B = -45 ;
  Grid15[266].spot[3].L =150; Grid15[266].spot[3].B = -45 ;

  Grid15[267].spot[0].L =150; Grid15[267].spot[0].B = -45 ;
  Grid15[267].spot[1].L =165; Grid15[267].spot[1].B = -45 ;
  Grid15[267].spot[2].L =165; Grid15[267].spot[2].B = -30 ;
  Grid15[267].spot[3].L =150; Grid15[267].spot[3].B = -30 ;

  Grid15[268].spot[0].L =150; Grid15[268].spot[0].B = -30 ;
  Grid15[268].spot[1].L =165; Grid15[268].spot[1].B = -30 ;
  Grid15[268].spot[2].L =165; Grid15[268].spot[2].B = -15 ;
  Grid15[268].spot[3].L =150; Grid15[268].spot[3].B = -15 ;

  Grid15[269].spot[0].L =150; Grid15[269].spot[0].B = -15 ;
  Grid15[269].spot[1].L =165; Grid15[269].spot[1].B = -15 ;
  Grid15[269].spot[2].L =165; Grid15[269].spot[2].B = 0   ;
  Grid15[269].spot[3].L =150; Grid15[269].spot[3].B = 0   ;

  Grid15[270].spot[0].L =150; Grid15[270].spot[0].B = 0   ;
  Grid15[270].spot[1].L =165; Grid15[270].spot[1].B = 0   ;
  Grid15[270].spot[2].L =165; Grid15[270].spot[2].B = 15  ;
  Grid15[270].spot[3].L =150; Grid15[270].spot[3].B = 15  ;

  Grid15[271].spot[0].L =150; Grid15[271].spot[0].B = 15  ;
  Grid15[271].spot[1].L =165; Grid15[271].spot[1].B = 15  ;
  Grid15[271].spot[2].L =165; Grid15[271].spot[2].B = 30  ;
  Grid15[271].spot[3].L =150; Grid15[271].spot[3].B = 30  ;

  Grid15[272].spot[0].L =150; Grid15[272].spot[0].B = 30  ;
  Grid15[272].spot[1].L =165; Grid15[272].spot[1].B = 30  ;
  Grid15[272].spot[2].L =165; Grid15[272].spot[2].B = 45  ;
  Grid15[272].spot[3].L =150; Grid15[272].spot[3].B = 45  ;

  Grid15[273].spot[0].L =150; Grid15[273].spot[0].B = 45  ;
  Grid15[273].spot[1].L =165; Grid15[273].spot[1].B = 45  ;
  Grid15[273].spot[2].L =165; Grid15[273].spot[2].B = 60  ;
  Grid15[273].spot[3].L =150; Grid15[273].spot[3].B = 60  ;

  Grid15[274].spot[0].L =150; Grid15[274].spot[0].B = 60  ;
  Grid15[274].spot[1].L =165; Grid15[274].spot[1].B = 60  ;
  Grid15[274].spot[2].L =165; Grid15[274].spot[2].B = 75  ;
  Grid15[274].spot[3].L =150; Grid15[274].spot[3].B = 75  ;

  Grid15[275].spot[0].L =150; Grid15[275].spot[0].B = 75  ;
  Grid15[275].spot[1].L =165; Grid15[275].spot[1].B = 75  ;
  Grid15[275].spot[2].L =165; Grid15[275].spot[2].B = 90  ;
  Grid15[275].spot[3].L =150; Grid15[275].spot[3].B = 90  ;

  Grid15[276].spot[0].L =165; Grid15[276].spot[0].B = -90 ;
  Grid15[276].spot[1].L =180; Grid15[276].spot[1].B = -90 ;
  Grid15[276].spot[2].L =180; Grid15[276].spot[2].B = -75 ;
  Grid15[276].spot[3].L =165; Grid15[276].spot[3].B = -75 ;

  Grid15[277].spot[0].L =165; Grid15[277].spot[0].B = -75 ;
  Grid15[277].spot[1].L =180; Grid15[277].spot[1].B = -75 ;
  Grid15[277].spot[2].L =180; Grid15[277].spot[2].B = -60 ;
  Grid15[277].spot[3].L =165; Grid15[277].spot[3].B = -60 ;

  Grid15[278].spot[0].L =165; Grid15[278].spot[0].B = -60 ;
  Grid15[278].spot[1].L =180; Grid15[278].spot[1].B = -60 ;
  Grid15[278].spot[2].L =180; Grid15[278].spot[2].B = -45 ;
  Grid15[278].spot[3].L =165; Grid15[278].spot[3].B = -45 ;

  Grid15[279].spot[0].L =165; Grid15[279].spot[0].B = -45 ;
  Grid15[279].spot[1].L =180; Grid15[279].spot[1].B = -45 ;
  Grid15[279].spot[2].L =180; Grid15[279].spot[2].B = -30 ;
  Grid15[279].spot[3].L =165; Grid15[279].spot[3].B = -30 ;

  Grid15[280].spot[0].L =165; Grid15[280].spot[0].B = -30 ;
  Grid15[280].spot[1].L =180; Grid15[280].spot[1].B = -30 ;
  Grid15[280].spot[2].L =180; Grid15[280].spot[2].B = -15 ;
  Grid15[280].spot[3].L =165; Grid15[280].spot[3].B = -15 ;

  Grid15[281].spot[0].L =165; Grid15[281].spot[0].B = -15 ;
  Grid15[281].spot[1].L =180; Grid15[281].spot[1].B = -15 ;
  Grid15[281].spot[2].L =180; Grid15[281].spot[2].B = 0   ;
  Grid15[281].spot[3].L =165; Grid15[281].spot[3].B = 0   ;

  Grid15[282].spot[0].L =165; Grid15[282].spot[0].B = 0   ;
  Grid15[282].spot[1].L =180; Grid15[282].spot[1].B = 0   ;
  Grid15[282].spot[2].L =180; Grid15[282].spot[2].B = 15  ;
  Grid15[282].spot[3].L =165; Grid15[282].spot[3].B = 15  ;

  Grid15[283].spot[0].L =165; Grid15[283].spot[0].B = 15  ;
  Grid15[283].spot[1].L =180; Grid15[283].spot[1].B = 15  ;
  Grid15[283].spot[2].L =180; Grid15[283].spot[2].B = 30  ;
  Grid15[283].spot[3].L =165; Grid15[283].spot[3].B = 30  ;

  Grid15[284].spot[0].L =165; Grid15[284].spot[0].B = 30  ;
  Grid15[284].spot[1].L =180; Grid15[284].spot[1].B = 30  ;
  Grid15[284].spot[2].L =180; Grid15[284].spot[2].B = 45  ;
  Grid15[284].spot[3].L =165; Grid15[284].spot[3].B = 45  ;

  Grid15[285].spot[0].L =165; Grid15[285].spot[0].B = 45  ;
  Grid15[285].spot[1].L =180; Grid15[285].spot[1].B = 45  ;
  Grid15[285].spot[2].L =180; Grid15[285].spot[2].B = 60  ;
  Grid15[285].spot[3].L =165; Grid15[285].spot[3].B = 60  ;

  Grid15[286].spot[0].L =165; Grid15[286].spot[0].B = 60  ;
  Grid15[286].spot[1].L =180; Grid15[286].spot[1].B = 60  ;
  Grid15[286].spot[2].L =180; Grid15[286].spot[2].B = 75  ;
  Grid15[286].spot[3].L =165; Grid15[286].spot[3].B = 75  ;

  Grid15[287].spot[0].L =165; Grid15[287].spot[0].B = 75  ;
  Grid15[287].spot[1].L =180; Grid15[287].spot[1].B = 75  ;
  Grid15[287].spot[2].L =180; Grid15[287].spot[2].B = 90  ;
  Grid15[287].spot[3].L =165; Grid15[287].spot[3].B = 90  ;
}


TFrame::~TFrame(void)
{
unsigned int i;

  for(i=0;i<Grid15.size();i++)
    Grid15[i].spot.clear();
  Grid15.clear();

  OWNER = NULL;

  Up = NULL;
  Down = NULL;
  Left = NULL;
  Right = NULL;
  VertCentral = NULL;
  HorCentral = NULL;

  for(i=0;i<288;i++)
    IDGrid15[i] = NULL;
}


void TFrame::Add()
{
QRectF rect;
QPen Pen;
  Pen = QPen(Qt::green);

  rect = static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->sceneRect();

  Up = static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->addLine(rect.left(), rect.top(),
         rect.left()+rect.width(), rect.top(), Pen);

  Left = static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->addLine(rect.left(), rect.top(),
         rect.left(), rect.top()+rect.height(), Pen);

  Right = static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->addLine(rect.left()+rect.width(), rect.top(),
         rect.left()+rect.width(), rect.top()+rect.height(), Pen);

  Down = static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->addLine(rect.left(), rect.top()+rect.height(),
         rect.left()+rect.width(), rect.top()+rect.height(), Pen);

  HorCentral = static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->addLine(rect.left(), rect.top()+rect.height()/2.0,
         rect.left()+rect.width(), rect.top()+rect.height()/2.0, Pen);

  VertCentral = static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->addLine(rect.left()+rect.width()/2.0, rect.top(),
         rect.left()+rect.width()/2.0, rect.top()+rect.height(), Pen);
}


void TFrame::Del()
{
  if (Up != NULL)
  {
    static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->removeItem(Up);
    delete Up;
    Up = NULL;
  }

  if (Left != NULL)
  {
    static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->removeItem(Left);
    delete Left;
    Left = NULL;
  }

  if (Right != NULL)
  {
    static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->removeItem(Right);
    delete Right;
    Right = NULL;
  }

  if (Down != NULL)
  {
    static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->removeItem(Down);
    delete Down;
    Down = NULL;
  }

  if (HorCentral != NULL)
  {
    static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->removeItem(HorCentral);
    delete HorCentral;
    HorCentral = NULL;
  }

  if (VertCentral != NULL)
  {
    static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->removeItem(VertCentral);
    delete VertCentral;
    VertCentral = NULL;
  }
}


void TFrame::RePaint()
{
  Del();
  Add();
}


void TFrame::AddGrid()
{
unsigned int i;
double Y1, X1, Y2, X2, Y3, X3, Y4, X4;
QPen Pen;
QBrush Brush;
QPolygonF Polygon;
QPointF point;
QVector<QPointF> vect;

  Pen = QPen(Qt::black);
  Brush = QBrush();

  for(i=0;i<288;i++)
  {
    static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Cartography->PZ90BLToScreenXY(Grid15[i].spot[0].B*M_PI/180.0,
        Grid15[i].spot[0].L*M_PI/180.0, &X1, &Y1);

    static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Cartography->PZ90BLToScreenXY(Grid15[i].spot[1].B*M_PI/180.0,
        Grid15[i].spot[1].L*M_PI/180.0, &X2, &Y2);

    static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Cartography->PZ90BLToScreenXY(Grid15[i].spot[2].B*M_PI/180.0,
        Grid15[i].spot[2].L*M_PI/180.0, &X3, &Y3);

    static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Cartography->PZ90BLToScreenXY(Grid15[i].spot[3].B*M_PI/180.0,
        Grid15[i].spot[3].L*M_PI/180.0, &X4, &Y4);

    vect.clear();

    point = QPoint(static_cast<int>(X1), static_cast<int>(Y1));
    vect.push_back(point);

    point = QPoint(static_cast<int>(X2), static_cast<int>(Y2));
    vect.push_back(point);

    point = QPoint(static_cast<int>(X3), static_cast<int>(Y3));
    vect.push_back(point);

    point = QPoint(static_cast<int>(X4), static_cast<int>(Y4));
    vect.push_back(point);

    Polygon = QPolygonF(vect);

    IDGrid15[i] = static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->addPolygon(Polygon, Pen, Brush);
  }
}


void TFrame::DelGrid()
{
unsigned int i;

  for(i=0;i<288;i++)
  if (IDGrid15[i] != NULL)
  {
    static_cast<TGISLib*>(static_cast<TMapData*>(OWNER)->OWNER)->Scene->removeItem(IDGrid15[i]);
    delete IDGrid15[i];
    IDGrid15[i] = NULL;
  }
}


void TFrame::RePaintGrid()
{
  DelGrid();
  AddGrid();
}
