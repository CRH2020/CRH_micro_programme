/*!
 * \file Motor.h
 * 
 * \brief fichier header de Motor
 */
#ifndef DEF_MOTOR
#define DEF_MOTOR

#include "mbed.h"
#include "StepperMotor.h"
#include <std_msgs/StringLib.h>

typedef enum{
    MOTOR_LEFT,MOTOR_RIGHT
} StepperId;

/*!
 * \class Motor
 * 
 * \brief gestion de l'ensemble des moteur
 * 
 *  la classe stock et contrôle tout les moteurs du robot
 * 
*/
class Motor {
    public:
        Motor();/*!< constructeur de Motor */
        StepperMotor& getStepper(StepperId stepperId);
        ~Motor();/*!< destructeur de Motor */
    private:
        CAN can;
        StepperMotor mL,mR;
};
#endif