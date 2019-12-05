/*!
 * \file Odometer.h
 * 
 * \brief fichier header de Odometer
 */
#ifndef DEF_ODOMETER
#define DEF_ODOMETER

#include "mbed.h"
#include "ros.h"
#include <std_msgs/StringLib.h>

/*!
 * \class Odometer
 * 
 * \brief calcul de la position
 * 
 * la classe lit les deux encodeur et calcul la position x y et l'angle du robot 
 * 
*/
class Odometer {
    public:
        Odometer();/*!< constructeur de Odometer */
        ~Odometer();/*!< destructeur de Odometer */
    private:
};
#endif