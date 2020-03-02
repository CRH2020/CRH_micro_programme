/*!
 * \file Sensor.cpp
 * 
 * \brief fichier des definition des fonctions de Sensor
 */
#include "Sensor.hpp"

/*!
 * \fn Sensor::Sensor (void)
 * 
 * \brief constructeur de Sensor
 * 
 * 
 */
Sensor::Sensor():odometer(PIN_ODOMETER_ARIGHT,PIN_ODOMETER_BRIGHT,PIN_ODOMETER_ALEFT,PIN_ODOMETER_BLEFT,PERIMETREWHEEL_RIGHT,PERIMETREWHEEL_LEFT,DISTCENTER2WHEEL,NBPULSE){
    
}

double Sensor::getSensorData(SensorDataId sensorDataId){
    switch(sensorDataId){
        case ODOMETER_X:
            return odometer.getX();
        case ODOMETER_Y:
            return odometer.getY();
        case ODOMETER_ALPHA:
            return odometer.getAlpha();
        default:
            return 0;
    }
}
/*!
 * \fn Sensor::~Sensor (void)
 * 
 * \brief destructeur de Sensor
 * 
 * 
 */
Sensor::~Sensor(){
    
}  