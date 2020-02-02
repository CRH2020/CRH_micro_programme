/*!
 * \file Odometer.h
 * 
 * \brief fichier header de Odometer
 */
#ifndef DEF_ODOMETER
#define DEF_ODOMETER



#include "mbed.h"
#include "ros.h"
#include "RobotConfig.h"
#include <std_msgs/StringLib.h>

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
        Odometer(PinName Aright,PinName Bright,PinName Aleft,PinName Bleft,double perimeter,double distCenter2Wheel,uint16_t NbPulse);/*!< constructeur de Odometer*/
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
        double _perimeter,_distCenter2Wheel;
        uint16_t _NbPulse;
        double x,y,z,alpha,dalpha,dl;
        



};
#endif