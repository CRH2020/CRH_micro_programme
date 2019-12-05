/*!
 * \file StepperMotor.h
 * 
 * \brief fichier header de StepperMotor
 */
#ifndef DEF_SERVOMOTOR
#define DEF_SERVOMOTOR

#include "mbed.h"
#include "ros.h"
#include <std_msgs/StringLib.h>

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
        StepperMotor();/*!< constructeur de StepperMotor */
        ~StepperMotor();/*!< destructeur de StepperMotor */
    private:
};
#endif