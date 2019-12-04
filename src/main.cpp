/*! \file main.cpp 
 * 
 *  \brief fichier principale
 * 
 *  On retrouve le code de la tache principale qui s'executera en premier.
 */
#include <mbed.h>
#include <ros.h>
#include <std_msgs/StringLib.h>



ros::NodeHandle  nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";
/*!
 * \fn int main (void)
 * 
 * \brief fonction de la tache principale
 * 
 * la fonction pricinpale tout sera initialisé ici.
 * 
 */
int main() {
  printf("Start: Salut");
  DigitalOut myled(LED1);
  int i = 0;

  nh.initNode();
  nh.advertise(chatter);
  

  while(1) {
        myled.write(1);        // set LED1 pin to high
        ThisThread::sleep_for(500);
        myled.write(0);     // set LED1 pin to low
        ThisThread::sleep_for(500);
        sprintf(hello,"%d",i);
        str_msg.data = hello;
        chatter.publish( &str_msg );
        nh.spinOnce();
        i++;
  }
}