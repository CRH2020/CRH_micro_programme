/*!
 * \file StepperMotor.cpp
 * 
 * \brief fichier des definition des fonctions de StepperMotor
 */
#include "StepperMotor.hpp"

/*!
 * \fn ServoMotor::ServoMotor (void)
 * 
 * \brief constructeur de ServoMotor
 * 
 * 
 */
StepperMotor::StepperMotor(TrinamicTmclDriver& driver, double pasParUnite,bool inverse,uint8_t motorNum):_pasParUnite(pasParUnite),_driver(driver),_inverse(inverse),_motorNum(motorNum){
    _driver.sendTMCL(SAP,154,motorNum,0);
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
            _driver.sendTMCL(ROL,0,_motorNum,(uint32_t)v_pas);
        else
            _driver.sendTMCL(ROR,0,_motorNum,(uint32_t)v_pas);
    }
    else{
        if (_inverse)
            _driver.sendTMCL(ROR,0,_motorNum,(uint32_t)(-v_pas));
        else
            _driver.sendTMCL(ROL,0,_motorNum,(uint32_t)(-v_pas));
    }

}

void StepperMotor::moveto(double distance){
    double nb_pas;
    nb_pas = distance * _pasParUnite;
    if(_inverse){
        nb_pas = -nb_pas;
    }
    _driver.sendTMCL(MVP,1,_motorNum,(int32_t)nb_pas);
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