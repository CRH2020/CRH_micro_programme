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
    /* 65535 indique que les capteurs ne sont pas initialisés */
    valCaptDist.resize(6, 65535);

    /* Initilise tous les capteurs de distances */
    for (size_t i = 0 ; i < valCaptDist.size(); i++) {

        /* Selectionne le canal */
        i2cMux.ch(CH2 << i);    
        printf("Capteur dist N %d -> init ", i);
        
        /* Test si le capteur est branché */
        if ( !capteurDistance.init() ) {
            printf("FAILED (wrong sensor)\n\r"); //Initialize device and check for errors
            continue ;
        } else {
            /* Met le mode de lecture continue (periode de 10ms) */
            capteurDistance.startContinuous(10);
            /* Test si le capteur est correctement init */
            uint16_t checkInit = capteurDistance.readRangeContinuousMillimeters();
            if (checkInit != 0 && checkInit != 65535){
                printf("success - "); 
                /* Met à jour le vecteur de donnée */
                valCaptDist[i] = checkInit;
                printf("Val = %d (mm)\n\r", valCaptDist[i] );
            } else {
                printf("FAILED (nothing plugged)\r\n"); //Initialize device and check for errors
                continue ;
            }
        }
       
    }

    // Pas possible de lancer le thread de lecture constantes des capteurs ici car le fonctionne se termine juste après
}

double Sensor::getSensorData(SensorDataId sensorDataId){
    switch(sensorDataId){
        case ODOMETER_X:
            return odometer.getX();
        case ODOMETER_Y:
            return odometer.getY();
        case ODOMETER_ALPHA:
            return odometer.getAlpha();
        case DISTANCE_1:
            return valCaptDist[0];
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

