/*!
 * \file Motor.h
 * 
 * \brief fichier header de Motor
 */
#ifndef DEF_MOTOR
#define DEF_MOTOR

#include "mbed.h"
#include "StepperMotor.h"
#include "ServoMotor.h"
#include "RobotConfig.h"
#include "PrintDebug.h"

typedef enum{
    MOTOR_LEFT,MOTOR_RIGHT
} StepperId;

typedef enum{
    TEST
} ServoId;

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
        ServoMotor& getServo(ServoId servoId);
        ~Motor();/*!< destructeur de Motor */
    private:
        CAN can;
        StepperMotor mL,mR;
        ServoMotor mTest;
};
#endif