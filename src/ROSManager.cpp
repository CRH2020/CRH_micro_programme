/*!
 * \file ROSManager.cpp
 * 
 * \brief fichier des definition des fonctions de ROSManager
 */
#include "ROSManager.h"

/*!
 * \fn ROSManager::ROSManager (void)
 * 
 * \brief constructeur de ROSManager
 * 
 * 
 */
ROSManager::ROSManager(StepperMotor& motorLeft,StepperMotor& motorRight,SequanceManager& sequancer): _motorLeft(motorLeft),_motorRight(motorRight),_sequancer(sequancer),velocity(TOPIC_NAME_VELOCITY,&ROSManager::messageVelocity,this){
    node.initNode();
    node.subscribe(velocity);
    thread.start(callback(this,&ROSManager::startThread));

}

void ROSManager::startThread(void){
    while(1){
        node.spinOnce();
        ThisThread::sleep_for(1);
    }

}

void ROSManager::messageVelocity(const geometry_msgs::Quaternion& msg){
    double vdif,vL,vR;
    char textBuff[50];

    vdif = msg.w*ENTRAX_ROUE_CENTRE;
    vL = msg.x - vdif;
    vR = msg.x + vdif;

    sprintf(textBuff,"Motor Gauche v=%lf",vL);
    rosDebug(textBuff);
    _motorLeft.move(vL);
    sprintf(textBuff,"Motor Droit v=%lf",vR);
    rosDebug(textBuff);
    _motorRight.move(vR);
}

void ROSManager::rosDebug(const char * fmt){
    node.loginfo(fmt);
}

/*!
 * \fn ROSManager::~ROSManager (void)
 * 
 * \brief destructeur de ROSManager
 * 
 * 
 */
ROSManager::~ROSManager(){
    
}  