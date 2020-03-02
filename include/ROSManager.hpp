/*!
 * \file ROSManager.hpp
 * 
 * \brief fichier header de ROSManager
 */
#ifndef DEF_ROSMANAGER
#define DEF_ROSMANAGER

#include "mbed.h"
#include "Motor.hpp"
#include "StepperMotor.hpp"
#include "SequenceManager.hpp"
#include "MovingManager.hpp"
#include "ros.h"
#include <std_msgs/StringLib.h>
#include "RobotConfig.hpp"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose2D.h"
#include "shared/ProcessDeplacement.h"

#include "PrintDebug.hpp"

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
        ROSManager(Motor& motors,SequenceManager& sequencer,MovingManager& mover);/*!< constructeur de ROSManager */
        ~ROSManager();/*!< destructeur de ROSManager */
        int rosDebug(const char * fmt);
        void publishPosition(double x,double y,double alpha);
    private:
        void startRosMainThread(void);
        void startRosDeplacementThread(void);
        void messageVelocity(const geometry_msgs::Twist& msg);
        void messageSequence(const geometry_msgs::Pose2D& msg);
        void messageDeplacement(const shared::ProcessDeplacement::Request &req, shared::ProcessDeplacement::Response &res);

        Motor& _motors;
        SequenceManager& _sequencer;
        MovingManager& _mover;
        ros::NodeHandle  nodeMain,nodeDeplacement;
        ros::Subscriber<geometry_msgs::Twist, ROSManager> velocity;
        ros::Subscriber<geometry_msgs::Pose2D, ROSManager> sequence;
        ros::ServiceServer<shared::ProcessDeplacement::Request,shared::ProcessDeplacement::Response, ROSManager> deplacement;
        ros::Publisher pos;
        geometry_msgs::Pose2D posMsg;
        Thread rosMainThread,rosDeplacementThread;
};

#endif