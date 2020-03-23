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
    
    printf("INIT Sensor ! \n\r");

    /* Init le vecteur qui contiendra les valeurs des capteurs de distance mis à jour régulièrement */
    valCaptDist.resize(6,0);

    int checkInit = 0;

    /* Initilise les 6 capteurs de distances */
    for (size_t i = 0 ; i < valCaptDist.size(); i++) {

        /* Selectionne le canal */
        i2cMux.ch(CH2 << i);
        
        /* Test si le capteur est branché */
        if ( !capteurDistance.init() ) {
            printf("FAILED TO INIT sensor dist (n = %d)\n\r", i); //Initialize device and check for errors

            continue ;
        } else {
            
            /* Test si le capteur est correctement init */
            checkInit = capteurDistance.readRangeSingleMillimeters();
            if (checkInit != 0){
                printf("INIT OK sensor (n = %d) : ", i ); 
                printf("Dist. sensor (n = %d) (mm) = %d - ", i, checkInit );
            } else {
                printf("FAILED TO INIT sensor dist (n = %d) - ", i); //Initialize device and check for errors
            }
        }
        /* Met à jour le vecteur de donnée */
        valCaptDist[i] = checkInit;
        printf("Val = %d \n\r", valCaptDist[i] );
    }
    

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