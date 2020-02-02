/*! \file main.cpp 
 * 
 *  \brief fichier principale
 * 
 *  On retrouve le code de la tache principale qui s'executera en premier.
 */
#include <mbed.h>
#include <ros.h>
#include <std_msgs/StringLib.h>
#include "ROSManager.h"
#include "SequanceManager.h"
#include "StepperMotor.h"

/*!
 * \fn int main (void)
 * 
 * \brief fonction de la tache principale
 * 
 * la fonction pricinpale tout sera initialisé ici.
 * 
 */
int main() {
  DigitalOut myled(LED1);
  Motor motors;
  Sensor sensors;
  SequanceManager sequanceur(motors,sensors);
  ROSManager rosmanger(motors,sequanceur);
  rosmanger.rosDebug("Salut");

  while(1) {
        myled=!myled; // set LED1 pin to high
        ThisThread::sleep_for(500);
  }
}