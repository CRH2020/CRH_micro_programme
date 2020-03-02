/*!
 * \file MovingManager.hpp
 * 
 * \brief fichier header de MovingManager
 */
#ifndef DEF_MOVINGMANAGER
#define DEF_MOVINGMANAGER

#include "mbed.h"
#include "Sensor.hpp"
#include "Motor.hpp"
#include "PrintDebug.hpp"

/*!
 * \class MovingManager
 * 
 * \brief gestion des séquances mécanique
 * 
 *  la classe lance les séquances pour les mécanismes du robot.
 * 
*/
class MovingManager {
    public:
        MovingManager(Motor& motors,Sensor& sensors);/*!< constructeur de MovingManager */
        int moveRobot(double distance,double angle);
        ~MovingManager();/*!< destructeur de MovingManager */
    private:
        void movingThread();
        Motor& _motors;
        Sensor& _sensors;
        Thread thread;
        EventFlags runMoveFlag;
        double _angle,_distance;
        bool isMoving;
};

#endif