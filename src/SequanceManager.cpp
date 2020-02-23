/*!
 * \file SequanceManager.cpp
 * 
 * \brief fichier des definition des fonctions de SequanceManager
 */
#include "SequanceManager.h"

/*!
 * \fn SequanceManager::SequanceManager (void)
 * 
 * \brief constructeur de SequanceManager
 * 
 * 
 */
SequanceManager::SequanceManager(Motor& motors,Sensor& sensors):_motors(motors),_sensors(sensors),runingId(SEQ_END){
    thread.start(callback(this,&SequanceManager::sequanceThread));
}

int SequanceManager::runSequance(SequanceId id,uint8_t nbArg,double* valArg ){

    if(id >= SEQ_END){
        PRINTDEBUG("Sequance id faux");
        return 1;
    }

    if(runingId != SEQ_END){
        PRINTDEBUG("Sequance deja en cour");
        return 1;
    }

    runingId = id;

    if(nbArg>0){
        valeurArg = new double[nbArg];
        for(uint8_t i=0;i<nbArg;i++){
            valeurArg[i] = valArg[i];
        }
        nombreArg = nbArg;
    }
    runingFlag.set(1);
    return 0;
}

void SequanceManager::sequanceThread(){

    while(1){
        runingFlag.wait_any(1);

        switch(runingId){
            case TESTSERVO:
                testServo();
                break;
            default:
                PRINTDEBUG("INVALID ID");
        }

        runingId = SEQ_END;
        if(nombreArg > 0)
            delete valeurArg;
    }
}

void SequanceManager::moveTo(){

}

void SequanceManager::testServo(){
    if(nombreArg == 0)
        return;
    _motors.getServo(TEST).setAngle(valeurArg[0]);
}

/*!
 * \fn SequanceManager::~SequanceManager (void)
 * 
 * \brief destructeur de SequanceManager
 * 
 * 
 */
SequanceManager::~SequanceManager(){
    
}  