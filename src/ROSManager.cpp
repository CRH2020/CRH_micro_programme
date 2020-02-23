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
ROSManager::ROSManager(Motor& motors,SequanceManager& sequancer): _motors(motors),_sequancer(sequancer),velocity(TOPIC_NAME_VELOCITY,&ROSManager::messageVelocity,this),sequance("sequance",&ROSManager::messageSequance,this),pos("pos",&posMsg){
    node.initNode();
    node.subscribe(velocity);
    node.subscribe(sequance);
    node.advertise(pos);

    thread.start(callback(this,&ROSManager::startThread));
    PRINTDEBUG  = callback(this,&ROSManager::rosDebug);

}

void ROSManager::startThread(void){
    while(1){
        node.spinOnce();
        ThisThread::sleep_for(1);
    }

}

void ROSManager::messageVelocity(const geometry_msgs::Twist& msg){
    double vdif,vL,vR;

    vdif = msg.angular.z*ENTRAX_ROUE_CENTRE;
    vL = msg.linear.x - vdif;
    vR = msg.linear.x + vdif;

    //sprintf(textBuff,"Motor Gauche v=%lf",vL);
    //rosDebug(textBuff);
    _motors.getStepper(MOTOR_LEFT).move(vL);
    //sprintf(textBuff,"Motor Droit v=%lf",vR);
    //rosDebug(textBuff);
    ThisThread::sleep_for(1);
    _motors.getStepper(MOTOR_RIGHT).move(vR);
}

void ROSManager::publishPosition(double x,double y,double alpha){
    posMsg.x = x;
    posMsg.y = y;
    posMsg.theta = alpha;

    pos.publish(&posMsg);
}

void ROSManager::messageSequance(const geometry_msgs::Pose2D& msg){
    double angle;
    angle = msg.x;
    _sequancer.runSequance(TESTSERVO,1,&angle);
}

int ROSManager::rosDebug(const char * fmt){
    node.loginfo(fmt);
    return 0;
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