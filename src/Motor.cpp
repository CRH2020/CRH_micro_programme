/*!
 * \file Motor.cpp
 * 
 * \brief fichier des definition des fonctions de Motor
 */
#include "Motor.hpp"

/*!
 * \fn Motor::Motor (void)
 * 
 * \brief constructeur de Motor
 * 
 * 
 */
Motor::Motor():can(PIN_MOTOR_CAN_RD,PIN_MOTOR_CAN_TD),driver1(can,TRINAMIC_ADDRESS_BOARD_1),mL(driver1,200,false,0),mR(driver1,200,true,1),mTest(PIN_TESTSERVO,60){
  can.monitor(false);
  can.attach(callback(this,&Motor::canRx));

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

void Motor::canRx(){
    CANMessage msg;
    if(can.read(msg)){
        switch(msg.data[0]){
            case TRINAMIC_ADDRESS_BOARD_1:
                driver1.msgRx(msg.data,msg.len);
                break;
            default:
                break;
        }
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