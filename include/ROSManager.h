/*!
 * \file ROSManager.h
 * 
 * \brief fichier header de ROSManager
 */
#ifndef DEF_ROSMANAGER
#define DEF_ROSMANAGER

#include "mbed.h"
#include "StepperMotor.h"
#include "SequanceManager.h"
#include "ros.h"
#include <std_msgs/StringLib.h>
#include "RobotConfig.h"
#include "geometry_msgs/Quaternion.h"

/*!
 * \class ROSManager
 * 
 * \brief gestion de la comunication ave ROS
 * 
 * la classe crée un node ROS, reçoit les commandes et envoi la position.
 * 
*/
class ROSManager {
    public:
        ROSManager(StepperMotor& motorLeft,StepperMotor& motorRight,SequanceManager& sequancer);/*!< constructeur de ROSManager */
        ~ROSManager();/*!< destructeur de ROSManager */
    private:
        void startThread(void);
        void messageVelocity(const geometry_msgs::Quaternion& msg);

        StepperMotor& _motorLeft,_motorRight;
        SequanceManager& _sequancer;
        ros::NodeHandle  node;
        ros::Subscriber<geometry_msgs::Quaternion, ROSManager> velocity;
        Thread thread;
};

#endif