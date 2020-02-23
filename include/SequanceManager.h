/*!
 * \file SequanceManager.h
 * 
 * \brief fichier header de SequanceManager
 */
#ifndef DEF_SEQUANCEMANAGER
#define DEF_SEQUANCEMANAGER

#include "mbed.h"
#include "Sensor.h"
#include "Motor.h"
#include "PrintDebug.h"

typedef enum{
    MOVETO=0,TESTSERVO,SEQ_END
} SequanceId;

/*!
 * \class SequanceManager
 * 
 * \brief gestion des séquances mécanique
 * 
 *  la classe lance les séquances pour les mécanismes du robot.
 * 
*/
class SequanceManager {
    public:
        SequanceManager(Motor& motors,Sensor& sensors);/*!< constructeur de SequanceManager */
        int runSequance(SequanceId id,uint8_t nbArg,double* valArg );
        ~SequanceManager();/*!< destructeur de SequanceManager */
    private:
        void moveTo();
        void testServo();
        void sequanceThread();
        Motor& _motors;
        Sensor& _sensors;
        Thread thread;
        EventFlags runingFlag;
        SequanceId runingId;
        double* valeurArg;
        uint8_t nombreArg;
};

#endif