/*!
 * \file Motor.cpp
 * 
 * \brief fichier des definition des fonctions de Motor
 */
#include "Motor.h"

/*!
 * \fn Motor::Motor (void)
 * 
 * \brief constructeur de Motor
 * 
 * 
 */
Motor::Motor():can(PIN_MOTOR_CAN_RD,PIN_MOTOR_CAN_TD),mL(can,200,false,0),mR(can,200,true,1),mTest(PIN_TESTSERVO,60){
  can.monitor(false);
}

StepperMotor& Motor::getStepper(StepperId stepperId){
    switch(stepperId){
        case MOTOR_LEFT:
            return mL;
        case MOTOR_RIGHT:
            return mR;
    }
}

ServoMotor& Motor::getServo(ServoId ServoId){
    switch(ServoId){
        case TEST:
            return mTest;
    }
}

/*!
 * \fn Motor::~Motor (void)
 * 
 * \brief destructeur de Motor
 * 
 * 
 */
Motor::~Motor(){
    
}  