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
    
    printf("\n\rINIT Sensor ! \n\r");

    /* Init le vecteur qui contiendra les valeurs des capteurs de distance mis à jour régulièrement */
    /* 65535 indique que les capteurs ne sont pas initialisés */
    valCaptDist.resize(6, 65535);

    /* Start le thread principal */
    updateSensorThread.start(callback(this,&Sensor::runThread));
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

/* Thread principal des capteurs */
void Sensor::runThread() {

    uint32_t timer = 0;

    /* Permet d'init les capteurs de distance */
    initDistanceSensor();

    /* Boucle mettant à jour les divers capteurs */
    /* (Définir les périodes de màj dans Sensor.hpp) */
    while(1){
       
        /* Màj les capteurs de distance */
        if ((timer % COUNT_PERIODE(PERIODE_DISTANCE_SENSOR_MS) ) == 0) {
            majDistanceSensor();
        }

        /* Attend la période souhaité */
        ThisThread::sleep_for(PERIODE_MIN_MS);
        timer++;
    }
}

/* Permet d'init les capteurs de distance */
void Sensor::majDistanceSensor() {
     /* Pour chaque capteur */
    for (size_t i = 0 ; i <  valCaptDist.size(); i++) {

        /* Check si le capteur est correctement init */
        if (valCaptDist[i] == 65535) {
            continue ;
        }

        /* Selectionne le canal */
        i2cMux.ch(CH2 << i);
        /* Lis la valeur du capteur */
        valCaptDist[i] = capteurDistance.readRangeContinuousMillimeters();

        printf("N %d = %d (mm) / ", i, valCaptDist[i] );
    }

    printf("\n\r");
}

/* Permet d'init les capteurs de distance */
void Sensor::initDistanceSensor() {

    int nbSensorError = 0;

    i2cMux.init(CH2);
    /* Initilise tous les capteurs de distances */
    for (size_t i = 0 ; i < valCaptDist.size(); i++) {

        /* Selectionne le canal */
        i2cMux.ch(CH2 << i);    
        printf("Capteur dist N %d - init -> ", i);
        
        /* Test si le bon capteur est bien branché */
        if ( !capteurDistance.init() ) {
            printf("FAILED \n\r");
            nbSensorError++;
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
                printf("FAILED \r\n"); //Initialize device and check for errors
                nbSensorError++;
                continue ;
            }
        }
       
    }

    /* Indique les eventuelles erreurs */
    if (nbSensorError == 6){
        printf("\r\n\r\nI2C no plugged !\r\n"); 
    } else if (nbSensorError > 0) {
        printf("\r\n\r\n%d distance sensor failed !\r\n", nbSensorError); 
    }
}