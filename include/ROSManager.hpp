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
#include "std_msgs/UInt8.h"
#include "std_msgs/Int8.h"
#include "shared/Deplacement.h"
#include "shared/Parametre.h"
#include "shared/SensorData.h"
#include "shared/SequenceAck.h"

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
        void publishDeplacement(int8_t result);
        void publishSequence(uint8_t id,uint8_t result);
        void publishSensor(uint8_t id, double data);


    private:
        void startRosMainThread(void);
        void startRosDeplacementThread(void);

        void messageVelocity(const geometry_msgs::Twist& msg);
        void messageSequence(const std_msgs::UInt8& msg);
        void messageDeplacement(const shared::Deplacement& msg);
        void messageParametre(const shared::Parametre& msg);
        void messageSensor(const std_msgs::UInt8& msg);

        Motor& _motors;
        SequenceManager& _sequencer;
        MovingManager& _mover;
        ros::NodeHandle  nodeMain;
        ros::Subscriber<geometry_msgs::Twist, ROSManager> velocity;

        ros::Subscriber<shared::Deplacement, ROSManager> deplacementIn;
        ros::Subscriber<std_msgs::UInt8, ROSManager> sequenceIn;
        ros::Subscriber<shared::Parametre, ROSManager> parametreIn;
        ros::Subscriber<std_msgs::UInt8, ROSManager>   sensorIn;

        ros::Publisher positionOut;
        ros::Publisher deplacementOut;
        ros::Publisher sequenceOut;
        ros::Publisher sensorOut;



        geometry_msgs::Pose2D posMsg;
        std_msgs::Int8 deplacementMsg;
        shared::SequenceAck sequenceMsg;
        shared::SensorData sensorMsg;

        Thread rosMainThread;
};

#endif