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
#include "RobotConfig.h"

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
        StepperMotor(CAN& can, double pasParUnite, bool inverse);/*!< constructeur de StepperMotor */
        ~StepperMotor();/*!< destructeur de StepperMotor */

        void move(double vitesse);
    private:
        enum eTMCLInstruction {
            ROR = 1,
            ROL = 2,
            MST = 3,
            MVP = 4 
        };
        
        double _pasParUnite;
        CAN& _can;
        bool _inverse;

        void sendTMCL(uint8_t target,eTMCLInstruction instruction,uint8_t type,uint8_t motor,uint32_t value);
        uint8_t cheksumCalulation(uint8_t* data,uint8_t N);
};
#endif