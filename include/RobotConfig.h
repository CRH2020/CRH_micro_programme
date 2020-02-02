/*!
 * \file RobotConfig.h
 * 
 * \brief fichier de configuration principale
 * 
 * \details Définition de toute les configurations pour le robot
 */
//MATH DEFINITION

#define PI  3.1415926535897
#define PI2 6.2831853071794
//PIN DEFINITION
#define PIN_MOTOR_CAN_RD PD_0
#define PIN_MOTOR_CAN_TD PD_1

#define PIN_ODOMETER_ARIGHT PD_2
#define PIN_ODOMETER_ALEFT PD_3
#define PIN_ODOMETER_BRIGHT PD_4
#define PIN_ODOMETER_BLEFT PD_5

//Odometer
#define DISTCENTER2WHEEL 150
#define PERIMETREWHEEL  200
#define NBPULSE         1024

//Stepper
#define STEPPER_BAUDRATE 9600

//Mécanique
#define ENTRAX_ROUES 400
#define ENTRAX_ROUE_CENTRE 200
#define PERIMETRE_ROBOT 1256

// ROS

#define TOPIC_NAME_VELOCITY "velocity"