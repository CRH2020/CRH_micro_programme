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

    deplacementIn(TOPIC_NAME_DEPLACEMENT_IN,&ROSManager::messageDeplacement,this),
    sequenceIn(TOPIC_NAME_SEQUENCE_IN,&ROSManager::messageSequence,this),
    parametreIn(TOPIC_NAME_PARAMETRE,&ROSManager::messageParametre,this),
    sensorIn(TOPIC_NAME_SENSOR_IN,&ROSManager::messageSensor,this),

    positionOut(TOPIC_NAME_POSITION,&posMsg),
    deplacementOut(TOPIC_NAME_DEPLACEMENT_OUT,&deplacementMsg),
    sequenceOut(TOPIC_NAME_SEQUENCE_OUT,&sequenceMsg),
    sensorOut(TOPIC_NAME_SENSOR_OUT,&sensorMsg)
{

    // node pour message non bloquant
    nodeMain.initNode();
    nodeMain.subscribe(velocity);

    nodeMain.subscribe(deplacementIn);
    nodeMain.subscribe(sequenceIn);
    nodeMain.subscribe(parametreIn);
    nodeMain.subscribe(sensorIn);

    nodeMain.advertise(positionOut);
    nodeMain.advertise(deplacementOut);
    nodeMain.advertise(sequenceOut);
    nodeMain.advertise(sensorOut);

    rosMainThread.start(callback(this,&ROSManager::startRosMainThread));
    PRINTDEBUG  = callback(this,&ROSManager::rosDebug);

    _mover.attachEndMoving(callback(this,&ROSManager::publishDeplacement));

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

void ROSManager::messageSequence(const std_msgs::UInt8& msg){
    _sequencer.runSequence((SequenceId)msg.data);
}

void ROSManager::messageDeplacement(const shared::Deplacement& msg){
    _mover.moveRobot(msg.distance,msg.angle);
}

void ROSManager::messageParametre(const shared::Parametre& msg){

}
void ROSManager::messageSensor(const std_msgs::UInt8& msg){

}

void ROSManager::publishPosition(double x,double y,double alpha){
    posMsg.x = x;
    posMsg.y = y;
    posMsg.theta = alpha;

    positionOut.publish(&posMsg);
}

void ROSManager::publishDeplacement(int8_t result){
    deplacementMsg.data = result;
    deplacementOut.publish(&deplacementMsg);
}
void ROSManager::publishSequence(uint8_t id,uint8_t result){
    sequenceMsg.sequence_id = id;
    sequenceMsg.result_code = result;
    sequenceOut.publish(&sequenceMsg);

}
void ROSManager::publishSensor(uint8_t id, double data){
    sensorMsg.sensor_data = data;
    sensorMsg.sensor_id = id;
    sensorOut.publish(&sensorMsg);
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