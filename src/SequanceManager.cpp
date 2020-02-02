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
SequanceManager::SequanceManager(Motor& motors,Sensor& sensors):_motors(motors),_sensors(sensors){

}

void SequanceManager::runSequance(SequanceId id,uint8_t nbArg,double* valArg ){
    mbed::Callback<void()> task;

    if(id >= SEQ_END)
        return;
    if(threads[id].get_state() != Thread::Inactive)
        return;


    switch(id){
        case MOVETO:
            if(nbArg<3)
                return;
            task = callback(this,&SequanceManager::moveTo);
            moveToX = valArg[0];
            moveToY = valArg[1];
            moveToAlpha =valArg[2];
            break;
        default:
            return;

    }

    threads[id].start(task);
}

void SequanceManager::moveTo(){

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