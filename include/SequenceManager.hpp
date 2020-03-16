/*!
 * \file SequenceManager.hpp
 * 
 * \brief fichier header de SequenceManager
 */
#ifndef DEF_SequenceMANAGER
#define DEF_SequenceMANAGER

#include "mbed.h"
#include "Sensor.hpp"
#include "Motor.hpp"
#include "PrintDebug.hpp"

typedef enum{
    MOVETO=0,TESTSERVO,SEQ_END
} SequenceId;

/*!
 * \class SequenceManager
 * 
 * \brief gestion des séquances mécanique
 * 
 *  la classe lance les séquances pour les mécanismes du robot.
 * 
*/
class SequenceManager {
    public:
        SequenceManager(Motor& motors,Sensor& sensors);/*!< constructeur de SequenceManager */
        int runSequence(SequenceId id,uint8_t nbArg = 0,double* valArg = nullptr);
        ~SequenceManager();/*!< destructeur de SequenceManager */
    private:
        void moveTo();
        void testServo();
        void sequenceThread();
        Motor& _motors;
        Sensor& _sensors;
        Thread thread;
        EventFlags runingFlag;
        SequenceId runingId;
        double* valeurArg;
        uint8_t nombreArg;
};

#endif