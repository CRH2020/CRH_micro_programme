/*!
 * \file SequenceManager.cpp
 * 
 * \brief fichier des definition des fonctions de SequenceManager
 */
#include "SequenceManager.hpp"

/*!
 * \fn SequenceManager::SequenceManager (void)
 * 
 * \brief constructeur de SequenceManager
 * 
 * 
 */
SequenceManager::SequenceManager(Motor& motors,Sensor& sensors):_motors(motors),_sensors(sensors),runingId(SEQ_END){
    thread.start(callback(this,&SequenceManager::sequenceThread));
}

int SequenceManager::runSequence(SequenceId id,uint8_t nbArg,double* valArg ){

    if(id >= SEQ_END){
        PRINTDEBUG("Sequence id faux");
        return 1;
    }

    if(runingId != SEQ_END){
        PRINTDEBUG("Sequence deja en cour");
        return 1;
    }

    runingId = id;

    if(nbArg>0){
        valeurArg = new double[nbArg];
        for(uint8_t i=0;i<nbArg;i++){
            valeurArg[i] = valArg[i];
        }
    }
    nombreArg = nbArg;
    runingFlag.set(1);
    return 0;
}

void SequenceManager::sequenceThread(){

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

void SequenceManager::moveTo(){

}

void SequenceManager::testServo(){
    if(nombreArg == 0)
        return;

    
    _motors.getServo(TEST).setAngle(valeurArg[0]);
    ThisThread::sleep_for(1);
    _motors.getServo(TEST).setAngle(60);
}

/*!
 * \fn SequenceManager::~SequenceManager (void)
 * 
 * \brief destructeur de SequenceManager
 * 
 * 
 */
SequenceManager::~SequenceManager(){
    
}  