/*!
 * \file ServoMotor.hpp
 * 
 * \brief fichier header de ServoMotor
 */
#ifndef DEF_SERVOMOTOR
#define DEF_SERVOMOTOR

#include "mbed.h"
#include "PrintDebug.hpp"

/*!
 * \class ServoMotor
 * 
 * \brief controle des servos motor
 * 
 *  la classe deplace un servo moteur à un angle voulu
 * 
*/
class ServoMotor {
    public:
        ServoMotor(PinName gpioNum,double angleMax,double frequance=50.0);/*!< constructeur de ServoMotor */
        void setAngle(double angle);
        ~ServoMotor();/*!< destructeur de ServoMotor */
    private:
        PwmOut servo;
        double rapportFrequ;
        double _angleMax;
        
};
#endif