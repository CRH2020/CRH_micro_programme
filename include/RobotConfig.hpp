/*!
 * \file RobotConfig.hpp
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

//Trinamic
#define TRINAMIC_ADDRESS_BOARD_1 1

//Stepper
#define STEPPER_BAUDRATE 9600

//Mécanique
#define ENTRAX_ROUES 230
#define ENTRAX_ROUE_CENTRE 115
#define PERIMETRE_ROBOT 850

// ROS

#define TOPIC_NAME_VELOCITY "velocity"

#define TOPIC_NAME_DEPLACEMENT_IN "deplacement_call"
#define TOPIC_NAME_DEPLACEMENT_OUT "deplacement_rep"
#define TOPIC_NAME_SEQUENCE_IN "sequence_call"
#define TOPIC_NAME_SEQUENCE_OUT "sequence_rep"
#define TOPIC_NAME_SENSOR_IN "sensor_get"
#define TOPIC_NAME_SENSOR_OUT "sensor_rep"
#define TOPIC_NAME_POSITION "pos"
#define TOPIC_NAME_PARAMETRE "param_set"
