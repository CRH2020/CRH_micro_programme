/*!
 * \file StepperMotor.cpp
 * 
 * \brief fichier des definition des fonctions de StepperMotor
 */
#include "StepperMotor.h"

/*!
 * \fn ServoMotor::ServoMotor (void)
 * 
 * \brief constructeur de ServoMotor
 * 
 * 
 */
StepperMotor::StepperMotor(CAN& can, double pasParUnite,bool inverse,uint8_t motorNum):_pasParUnite(pasParUnite),_can(can),_inverse(inverse),_motorNum(motorNum){
    sendTMCL(1,SAP,154,motorNum,0);
}

void StepperMotor::move(double vitesse){
    double v_pas;
    v_pas = vitesse *_pasParUnite;

    if(v_pas > 2047)
        v_pas=2047;
    else if(v_pas < -2047)
        v_pas = -2047;

    if((v_pas>0)){
        if (_inverse)
            sendTMCL(1,ROL,0,_motorNum,(uint32_t)v_pas);
        else
            sendTMCL(1,ROR,0,_motorNum,(uint32_t)v_pas);
    }
    else{
        if (_inverse)
            sendTMCL(1,ROR,0,_motorNum,(uint32_t)(-v_pas));
        else
            sendTMCL(1,ROL,0,_motorNum,(uint32_t)(-v_pas));
    }

}

void StepperMotor::sendTMCL(uint8_t target,eTMCLInstruction instruction,uint8_t type,uint8_t motor,uint32_t value){
    uint8_t packet[7];
    uint8_t increment=0;
    //packet[0] = target;
    packet[0] = (uint8_t)instruction;
    packet[1] = type;

    packet[2] = motor;

    packet[3] = (value>>24) & 0xFF;
    packet[4] = (value>>16) & 0xFF;
    packet[5] = (value>>8) & 0xFF;
    packet[6] = value & 0xFF;

    //packet[8] = cheksumCalulation(packet,8);

    CANMessage msg(target,packet,7);

    while(!_can.write(msg) &&  increment<5){
        _can.reset();
        increment++;
        ThisThread::sleep_for(1);
    }
}

uint8_t StepperMotor::cheksumCalulation(uint8_t* data,uint8_t N){
    uint8_t cheksum=0,i;

    for(i=0;i<N;i++){
        cheksum+=data[i];
    }

    return cheksum;
}

/*!
 * \fn StepperMotor::~StepperMotor (void)
 * 
 * \brief destructeur de StepperMotor
 * 
 * 
 */
StepperMotor::~StepperMotor(){
    
}  