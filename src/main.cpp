/*! \file main.cpp 
 * 
 *  \brief fichier principale
 * 
 *  On retrouve le code de la tache principale qui s'executera en premier.
 */
#include <mbed.h>
#include <ros.h>
#include <std_msgs/StringLib.h>
#include "PrintDebug.hpp"
#include "ROSManager.hpp"
#include "SequenceManager.hpp"
#include "StepperMotor.hpp"
#include "MovingManager.hpp"

void updateSensorDistance(Sensor* sensor);

/*!
 * \fn int main (void)
 * 
 * \brief fonction de la tache principale
 * 
 * la fonction pricinpale tout sera initialisé ici.
 * 
 */
void run_app() {
  sleep_manager_lock_deep_sleep_internal();
  Motor motors;
  Sensor sensors;
  MovingManager mover(motors,sensors);
  SequenceManager sequenceur(motors,sensors);
  //ROSManager rosmanager(motors,sequenceur,mover);
  //rosmanager.rosDebug("Salut");
  while(1) {
    //ThisThread::sleep_for(5000);
    //mover.moveRobot(1000,0);
    //rosmanager.publishPosition(sensors.getSensorData(ODOMETER_X),sensors.getSensorData(ODOMETER_Y),sensors.getSensorData(ODOMETER_ALPHA));
    //sprintf(textBuff,"x: %lf,y: %lf,alpha: %lf\n\r",sensors.getSensorData(ODOMETER_X),sensors.getSensorData(ODOMETER_Y),sensors.getSensorData(ODOMETER_ALPHA));
    //rosmanager.rosDebug(textBuff);

    /* Mise à jour des capteurs de distance (à définir la période) */
    ThisThread::sleep_for(100);
    updateSensorDistance(&sensors);
  }
}

int main(){
  DigitalOut myled(LED1);
  Thread app_thread(osPriorityNormal, 8 * 1024); // 8K stack
  app_thread.start(&run_app);
  while(1) {
        myled=!myled; // set LED1 pin to high
        ThisThread::sleep_for(500);
  }
}



void updateSensorDistance(Sensor* sensor) {

    /* Pour chaque capteur */
    for (size_t i = 0 ; i <  sensor->valCaptDist.size(); i++) {

        /* Check si le capteur est correctement init */
        if (sensor->valCaptDist[i] == 65535) {
          continue ;
        }

        /* Selectionne le canal */
        sensor->i2cMux.ch(CH2 << i);
        /* Lis la valeur du capteur */
        sensor->valCaptDist[i] = sensor->capteurDistance.readRangeContinuousMillimeters();

        printf("N %d = %d (mm) / ", i, sensor->valCaptDist[i] );
    }

    printf("\n\r");

    return;

}