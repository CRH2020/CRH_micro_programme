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


/*!
 * \fn int main (void)
 * 
 * \brief fonction de la tache principale
 * 
 * la fonction pricinpale tout sera initialisé ici.
 * 
 */
int main() {
  sleep_manager_lock_deep_sleep_internal();

  DigitalOut myled(LED1);
  Motor motors;
  Sensor sensors;
  MovingManager mover(motors,sensors);
  SequenceManager sequenceur(motors,sensors);
  ROSManager rosmanager(motors,sequenceur,mover);
  rosmanager.rosDebug("Salut");

  while(1) {
        myled=!myled; // set LED1 pin to high
        ThisThread::sleep_for(500);
        rosmanager.publishPosition(sensors.getSensorData(ODOMETER_X),sensors.getSensorData(ODOMETER_Y),sensors.getSensorData(ODOMETER_ALPHA));
        //sprintf(textBuff,"x: %lf,y: %lf,alpha: %lf\n\r",sensors.getSensorData(ODOMETER_X),sensors.getSensorData(ODOMETER_Y),sensors.getSensorData(ODOMETER_ALPHA));
        //rosmanager.rosDebug(textBuff);
  }
}