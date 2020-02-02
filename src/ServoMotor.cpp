/*!
 * \file ServoMotor.cpp
 * 
 * \brief fichier des definition des fonctions de ServoMotor
 */
#include "ServoMotor.h"

/*!
 * \fn ServoMotor::ServoMotor (void)
 * 
 * \brief constructeur de ServoMotor
 * 
 * 
 */
ServoMotor::ServoMotor(PinName gpioNum,double angleMax,double frequance):servo(gpioNum),_angleMax(angleMax){
    servo.period(1/frequance);
    rapportFrequ = frequance*0.001;
}

void ServoMotor::setAngle(double angle){
    double dutyF;

    if(angle > _angleMax) angle = _angleMax;
    if(angle < 0) angle = 0;

    dutyF = (angle / _angleMax)*rapportFrequ + rapportFrequ;

    servo.write(dutyF);

}

/*!
 * \fn ServoMotor::~ServoMotor (void)
 * 
 * \brief destructeur de ServoMotor
 * 
 * 
 */
ServoMotor::~ServoMotor(){
    
}  