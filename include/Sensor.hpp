/*!
 * \file Sensor.hpp
 * 
 * \brief fichier header de Sensor
 */
#ifndef DEF_SENSOR
#define DEF_SENSOR

#include "mbed.h"
#include "Odometer.hpp"

#include "TCA9548.h"
#include "TCS34725.h"
#include <VL53L0X.h>
#include <vector>

typedef enum{
    ODOMETER_X,ODOMETER_Y,ODOMETER_ALPHA,DISTANCE_1,DISTANCE_2,DISTANCE_3,DISTANCE_4,DISTANCE_5,DISTANCE_6   
} SensorDataId;

/*!
 * \class Sensor
 * 
 * \brief gestion de l'ensemble des capteurs
 * 
 *  la classe stock et contrôle tout les capteurs du robot
 * 
*/
class Sensor {
    public:
        Sensor();/*!< constructeur de Sensor */
        double getSensorData(SensorDataId SensorDataId);
        ~Sensor();/*!< destructeur de Sensor */

        /* Donnée régulièrement mis à jour si la couleur lue est rouge ou pas */
        int isRed = -1;

        /* Vecteur de donnée des distances régulièrement mis à jour */
        std::vector<uint16_t> valCaptDist;

    //private:

        Odometer odometer;
        /* Crée le switch avec l'adresse de base 0x70 */
        TCA9548 i2cMux;
        
        /* Crée la capteur de couleur avec l'adresse de base 0x29 */
        TCS34725 capteurCouleur;

        /* Crée la capteur de distance avec l'adresse de base 0x29 */
        VL53L0X capteurDistance;

};
#endif