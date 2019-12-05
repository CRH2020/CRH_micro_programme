/*!
 * \file SequanceManager.h
 * 
 * \brief fichier header de SequanceManager
 */
#ifndef DEF_SEQUANCEMANAGER
#define DEF_SEQUANCEMANAGER

#include "mbed.h"
#include "ros.h"
#include <std_msgs/StringLib.h>

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
        SequanceManager();/*!< constructeur de SequanceManager */
        ~SequanceManager();/*!< destructeur de SequanceManager */
    private:
};
#endif