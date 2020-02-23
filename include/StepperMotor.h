/*!
 * \file StepperMotor.h
 * 
 * \brief fichier header de StepperMotor
 */
#ifndef DEF_STEPPERMOTOR
#define DEF_STEPPERMOTOR

#include "mbed.h"
#include "RobotConfig.h"
#include "PrintDebug.h"

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
        StepperMotor(CAN& can, double pasParUnite, bool inverse,uint8_t motorNum);/*!< constructeur de StepperMotor */
        ~StepperMotor();/*!< destructeur de StepperMotor */

        void move(double vitesse);
    private:
        enum eTMCLInstruction {
            ROR = 1,
            ROL = 2,
            MST = 3,
            MVP = 4,
            SAP = 5
        };
        
        double _pasParUnite;
        CAN& _can;
        bool _inverse;
        uint8_t _motorNum;

        void sendTMCL(uint8_t target,eTMCLInstruction instruction,uint8_t type,uint8_t motor,uint32_t value);
        uint8_t cheksumCalulation(uint8_t* data,uint8_t N);
};
#endif