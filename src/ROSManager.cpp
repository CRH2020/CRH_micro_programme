/*!
 * \file ROSManager.cpp
 * 
 * \brief fichier des definition des fonctions de ROSManager
 */
#include "ROSManager.hpp"

/*!
 * \fn ROSManager::ROSManager (void)
 * 
 * \brief constructeur de ROSManager
 * 
 * 
 */
ROSManager::ROSManager(Motor& motors,SequenceManager& sequencer,MovingManager& mover) :
    _motors(motors),
    _sequencer(sequencer),
    _mover(mover),
    velocity(TOPIC_NAME_VELOCITY,&ROSManager::messageVelocity,this),
    sequence("sequence",&ROSManager::messageSequence,this),
    deplacement("deplacement",&ROSManager::messageDeplacement,this),
    pos("pos",&posMsg)
{

    // node pour message non bloquant
    nodeMain.initNode();
    nodeMain.subscribe(velocity);
    nodeMain.subscribe(sequence);
    nodeMain.advertise(pos);
    nodeMain.subscribe(deplacement);

    rosMainThread.start(callback(this,&ROSManager::startRosMainThread));
    PRINTDEBUG  = callback(this,&ROSManager::rosDebug);

}

void ROSManager::startRosMainThread(void){
    while(1){
        nodeMain.spinOnce();
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

void ROSManager::messageSequence(const geometry_msgs::Pose2D& msg){
    double angle;
    angle = msg.x;
    _sequencer.runSequence(TESTSERVO,1,&angle);
}

void ROSManager::messageDeplacement(const geometry_msgs::Pose2D& msg){

    _mover.moveRobot(msg.x,msg.theta);
}

int ROSManager::rosDebug(const char * fmt){
    nodeMain.loginfo(fmt);
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