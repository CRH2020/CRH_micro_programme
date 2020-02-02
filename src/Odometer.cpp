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
Odometer::Odometer(PinName Aright,PinName Bright,PinName Aleft,PinName Bleft,double perimeter,double distCenter2Wheel,uint16_t NbPulse): _Aright(Aright),_Aleft(Aleft),_Bright(Bright),_Bleft(Bleft),_perimeter(perimeter),_distCenter2Wheel(distCenter2Wheel),_NbPulse(NbPulse) {
    _Aright.rise(callback(this, &Odometer::pulseRight));
    _Aleft.rise(callback(this, &Odometer::pulseLeft));
    dalpha = perimeter/(NbPulse*distCenter2Wheel*2);
    dl = dalpha * _distCenter2Wheel;
}

void Odometer::pulseRight(){
    if(_Bright){
        alpha+=dalpha;
        computePos(dl);
    }else{
        alpha-=dalpha;
        computePos(-dl);
    }
}


void Odometer::pulseLeft(){
    if(_Bleft){
        alpha-=dalpha;
        computePos(-dl);
    }else{
        alpha+=dalpha;
        computePos(dl);
    }
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