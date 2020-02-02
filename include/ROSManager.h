/*!
 * \file ROSManager.h
 * 
 * \brief fichier header de ROSManager
 */
#ifndef DEF_ROSMANAGER
#define DEF_ROSMANAGER

#include "mbed.h"
#include "Motor.h"
#include "StepperMotor.h"
#include "SequanceManager.h"
#include "ros.h"
#include <std_msgs/StringLib.h>
#include "RobotConfig.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose2D.h"

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
        ROSManager(Motor& motors,SequanceManager& sequancer);/*!< constructeur de ROSManager */
        ~ROSManager();/*!< destructeur de ROSManager */
        void rosDebug(const char * fmt);
    private:
        void startThread(void);
        void messageVelocity(const geometry_msgs::Twist& msg);

        Motor& _motors;
        SequanceManager& _sequancer;
        ros::NodeHandle  node;
        ros::Subscriber<geometry_msgs::Twist, ROSManager> velocity;
        Thread thread;
};

#endif