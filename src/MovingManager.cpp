/*!
 * \file MovingManager.cpp
 * 
 * \brief fichier des definition des fonctions de MovingManager
 */
#include "MovingManager.hpp"

/*!
 * \fn MovingManager::MovingManager (void)
 * 
 * \brief constructeur de MovingManager
 * 
 * 
 */
MovingManager::MovingManager(Motor& motors,Sensor& sensors):_motors(motors),_sensors(sensors),_angle(0),_distance(0),isMoving(false){
    thread.start(callback(this,&MovingManager::movingThread));
}

int MovingManager::moveRobot(double distance,double angle){
    _distance = distance;
    _angle = angle;

    if(!isMoving){
        runMoveFlag.set(1);
        isMoving = true;
        return 0;
    }
    
    return 1;
}

void MovingManager::movingThread(){
    double xdif,xL,xR;
    while(1){
        runMoveFlag.wait_any(1);
        
        xdif = _angle*ENTRAX_ROUE_CENTRE;
        xL = _distance - xdif;
        xR = _distance + xdif;

        _motors.getStepper(MOTOR_LEFT).moveto(xL);
        _motors.getStepper(MOTOR_LEFT).moveto(xR);

    }
}


/*!
 * \fn MovingManager::~MovingManager (void)
 * 
 * \brief destructeur de MovingManager
 * 
 * 
 */
MovingManager::~MovingManager(){
    
}  