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
  char textBuff[50];
  DigitalOut myled(LED1);
  CANMessage msg;
  SequanceManager sequanceur;
  CAN can(PIN_MOTOR_CAN_RD,PIN_MOTOR_CAN_TD);
  can.monitor(false);
  //can.mode(CAN::GlobalTest);
  StepperMotor mL(can,200,false,0);
  StepperMotor mR(can,200,true,1);
  ROSManager rosmanger(mL,mR,sequanceur);
  rosmanger.rosDebug("Salut");

  while(1) {
        myled=!myled;        // set LED1 pin to high
        if(can.read(msg)) {
            sprintf(textBuff,"Message received: %d %d %d\n\n", msg.data[0],msg.data[1],msg.data[2]);
            rosmanger.rosDebug(textBuff);
        }
        ThisThread::sleep_for(500);

  }
}