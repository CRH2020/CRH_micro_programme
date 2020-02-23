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

#define PIN_ODOMETER_ARIGHT PG_0
#define PIN_ODOMETER_BRIGHT PG_1

#define PIN_ODOMETER_ALEFT PG_2
#define PIN_ODOMETER_BLEFT PG_3

#define PIN_TESTSERVO      PE_9

//Odometer
#define DISTCENTER2WHEEL 83.5
#define PERIMETREWHEEL_LEFT  125.66
#define PERIMETREWHEEL_RIGHT  116.32
#define NBPULSE         1024

//Stepper
#define STEPPER_BAUDRATE 9600

//Mécanique
#define ENTRAX_ROUES 400
#define ENTRAX_ROUE_CENTRE 200
#define PERIMETRE_ROBOT 1256

// ROS

#define TOPIC_NAME_VELOCITY "velocity"