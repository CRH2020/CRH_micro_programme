/*!
 * \file StepperMotor.hpp
 * 
 * \brief fichier header de StepperMotor
 */
#ifndef DEF_STEPPERMOTOR
#define DEF_STEPPERMOTOR

#include "mbed.h"
#include "RobotConfig.hpp"
#include "PrintDebug.hpp"
#include "TrinamicTmclDriver.hpp"

/*!
 * \class StepperMotor
 * 
 * \brief controle des moteur pas à pas
 * 
 *  la classe actionne un moteur pas à pas à la position ou la vitesse voulue
 * 
*/
class StepperMotor {
    public:
        StepperMotor(TrinamicTmclDriver& driver, double pasParUnite, bool inverse,uint8_t motorNum);/*!< constructeur de StepperMotor */
        ~StepperMotor();/*!< destructeur de StepperMotor */

        void move(double vitesse);
        void moveto(double distance);
    private:
        double _pasParUnite;
        TrinamicTmclDriver& _driver;
        bool _inverse;
        uint8_t _motorNum;
};
#endif