/*!
 * \file Sensor.h
 * 
 * \brief fichier header de Sensor
 */
#ifndef DEF_SENSOR
#define DEF_SENSOR

#include "mbed.h"
#include "Odometer.h"
#include <std_msgs/StringLib.h>

typedef enum{
    ODOMETER_X,ODOMETER_Y,ODOMETER_ALPHA   
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
    private:
        Odometer odometer;

};
#endif