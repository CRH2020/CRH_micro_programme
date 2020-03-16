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
MovingManager::MovingManager(Motor& motors,Sensor& sensors):
    _motors(motors),
    _sensors(sensors),
    _angle(0),
    _distance(0),
    isMoving(false),
    _finDeplacementCallback(nullptr)
{
    thread.start(callback(this,&MovingManager::movingThread));

}

void MovingManager::attachEndMoving(Callback<void (int8_t result)> finDeplacementCallback){
    _finDeplacementCallback=finDeplacementCallback;
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
    uint8_t result;
    while(1){
        runMoveFlag.wait_any(1);
        PRINTDEBUG("On bouge");
        xdif = _angle*ENTRAX_ROUE_CENTRE;
        xL = _distance - xdif;
        xR = _distance + xdif;

        result+=_motors.getStepper(MOTOR_LEFT).moveto(xL);
        result+=_motors.getStepper(MOTOR_RIGHT).moveto(xR);

        if(!result){
            _motors.getStepper(MOTOR_LEFT).clearFinish();
            _motors.getStepper(MOTOR_RIGHT).clearFinish();

            _motors.getStepper(MOTOR_LEFT).waitForFinish();
            _motors.getStepper(MOTOR_RIGHT).waitForFinish();
        }
        if(_finDeplacementCallback != nullptr){
            _finDeplacementCallback(result);
        }
        isMoving = false;

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