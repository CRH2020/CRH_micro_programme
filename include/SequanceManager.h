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
#include "ros.h"
#include <std_msgs/StringLib.h>

typedef enum{
    MOVETO=0,SEQ_END
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
        void runSequance(SequanceId id,uint8_t nbArg,double* valArg );
        ~SequanceManager();/*!< destructeur de SequanceManager */
    private:
        void moveTo();
        Motor& _motors;
        Sensor& _sensors;
        Thread threads[SEQ_END];
        double moveToX,moveToY,moveToAlpha;
};
#endif