/*!
 * \file Odometer.hpp
 * 
 * \brief fichier header de Odometer
 */
#ifndef DEF_ODOMETER
#define DEF_ODOMETER



#include "mbed.h"
#include "RobotConfig.hpp"

/*!
 * \class Odometer
 * 
 * \brief calcul de la position
 * 
 * la classe lit les deux encodeur et calcul la position x y et l'angle du robot 
 * 
*/
class Odometer {
    public:
        Odometer(PinName Aright,PinName Bright,PinName Aleft,PinName Bleft,double perimeterRight,double perimeterLeft,double distCenter2Wheel,uint16_t NbPulse);/*!< constructeur de Odometer*/
        double getX();
        double getY();
        double getAlpha();
        ~Odometer();/*!< destructeur de Odometer*/
    private:
        void pulseRight();
        void pulseLeft();
        void computePos(double dl);
        InterruptIn _Aright,_Aleft;
        DigitalIn _Bright,_Bleft;
        DigitalOut test;
        uint16_t _NbPulse;
        double x,y,z,alpha,dalphaR,dlR,dalphaL,dlL;
        uint8_t stateR,stateL,oldStateR,oldStateL;
        



};
#endif