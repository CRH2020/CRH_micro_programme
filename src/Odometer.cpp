/*!
 * \file Odometer.cpp
 * 
 * \brief fichier des definition des fonctions de Odometer
 */
#include "Odometer.h"

/*!
 * \fn Odometer::Odometer (void)
 * 
 * \brief constructeur de Odometer
 * 
 * 
 */
Odometer::Odometer(PinName Aright,PinName Bright,PinName Aleft,PinName Bleft,double perimeterRight,double perimeterLeft,double distCenter2Wheel,uint16_t NbPulse): _Aright(Aright),_Aleft(Aleft),_Bright(Bright),_Bleft(Bleft),test(PD_7) {
    _Aright.rise(callback(this, &Odometer::pulseRight));
    _Aleft.rise(callback(this, &Odometer::pulseLeft));

    _Aright.fall(callback(this, &Odometer::pulseRight));
    _Aleft.fall(callback(this, &Odometer::pulseLeft));

    stateR = (_Aright << 1) | (_Bright);
    oldStateR = stateR;

    stateL = (_Aleft << 1) | (_Bleft);
    oldStateL = stateL;

    dalphaR = perimeterRight/(NbPulse*distCenter2Wheel*2);
    dlR = dalphaR * distCenter2Wheel;

    dalphaL = perimeterLeft/(NbPulse*distCenter2Wheel*2);
    dlL = dalphaL * distCenter2Wheel;


    test = 1;
}

void Odometer::pulseRight(){
    test = 1;
    stateR = (_Aright << 1) | (_Bright);

    if (oldStateR == 0x3 && stateR == 0x0) {
        alpha+=dalphaR;
        computePos(dlR);
    }
    //10->01->10->01 is clockwise rotation or "backward".
    else if (oldStateR == 0x2 && stateR == 0x1) {
        alpha-=dalphaR;
        computePos(-dlR);
    }

    test=0;
    oldStateR = stateR;
}


void Odometer::pulseLeft(){
    stateL = (_Aleft << 1) | (_Bleft);

    if (oldStateL == 0x3 && stateL == 0x0) {
        alpha-=dalphaL;
        computePos(dlL);
    }
    //10->01->10->01 is clockwise rotation or "backward".
    else if (oldStateL == 0x2 && stateL == 0x1) {
        alpha+=dalphaL;
        computePos(-dlL);
    }

    oldStateL = stateL;
}

void Odometer::computePos(double dl){
    double dx(0),dy(0);
    
    dx = cos(alpha)* dl;
    dy = sin(alpha)* dl;

    x+=dx;
    y+=dy;
}

double Odometer::getX(){
    return x;
}
double Odometer::getY(){
    return y;
}
double Odometer::getAlpha(){
    return alpha;
}

/*!
 * \fn Odometer::~Odometer (void)
 * 
 * \brief destructeur de Odometer
 * 
 * 
 */
Odometer::~Odometer(){

} 