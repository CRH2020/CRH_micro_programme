/*!
 * \file Motor.hpp
 * 
 * \brief fichier header de Motor
 */
#ifndef DEF_MOTOR
#define DEF_MOTOR

#include "mbed.h"
#include "StepperMotor.hpp"
#include "ServoMotor.hpp"
#include "RobotConfig.hpp"
#include "PrintDebug.hpp"
#include "TrinamicTmclDriver.hpp"

enum StepperId{
    MOTOR_LEFT,MOTOR_RIGHT
};

enum  ServoId{
    TEST
};

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
        void startThread();
        ~Motor();/*!< destructeur de Motor */
    private:
        CAN can;
        TrinamicTmclDriver driver1;
        StepperMotor mL,mR;
        ServoMotor mTest;
        Thread thread;

};
#endif