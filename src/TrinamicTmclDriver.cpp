
/*!
 * \file TrinamicTmclDriver.cpp
 * 
 * \brief fichier source de TrinamicTmclDriver
 */

#include "TrinamicTmclDriver.hpp"

TrinamicTmclDriver::TrinamicTmclDriver(CAN& can,uint8_t target): _can(can),_target(target){

}

int TrinamicTmclDriver::sendTMCL(eTMCLInstruction instruction,uint8_t type,uint8_t motor,uint32_t value){
    uint8_t packet[7];
    uint8_t increment=0;
    uint8_t status;
    //packet[0] = target;
    packet[0] = (uint8_t)instruction;
    packet[1] = type;

    packet[2] = motor;

    packet[3] = (value>>24) & 0xFF;
    packet[4] = (value>>16) & 0xFF;
    packet[5] = (value>>8) & 0xFF;
    packet[6] = value & 0xFF;

    //packet[8] = cheksumCalulation(packet,8);

    CANMessage msg(_target,packet,7);

    while(!_can.write(msg) &&  increment<5){
        _can.reset();
        increment++;
        ThisThread::sleep_for(1);
    }

    if(increment>=5){
        PRINTDEBUG("TrinamicTmclDriver: sendTMCL : CAN transmission error");
        return 1;
    }

    status = replyMsg.wait_any(FLAG_REPLY,100);

    if(status==100)
        return 0;
    else if(!status || status==254){
        PRINTDEBUG("TrinamicTmclDriver: sendTMCL : rep timout");
        replyMsg.clear(0xFF);
        return 2;
    }
    else{
        PRINTDEBUG("TrinamicTmclDriver: sendTMCL : error inconnue");
        return -1;
    }
    
}

void TrinamicTmclDriver::configureMotor(uint8_t motorNum){
    motorMask |= 0x01<<motorNum;
    sendTMCL(SAP,154,motorNum,0);
    sendTMCL(RTP,1,0,3);
}


void TrinamicTmclDriver::msgRx(uint8_t* data,uint8_t len){
    uint8_t status = data[1];

    switch(status){
        case 100:
            PRINTDEBUG("TrinamicTmclDriver: msgRx : Commande ok");
            break;
        case 101:
            break;
        case 1:
            PRINTDEBUG("TrinamicTmclDriver: msgRx : Wrong checksum");
            break;
        case 2:
            PRINTDEBUG("TrinamicTmclDriver: msgRx : Invalid command");
            break;
        case 3:
            PRINTDEBUG("TrinamicTmclDriver: msgRx : Wrong type");
            break;
        case 4:
            PRINTDEBUG("TrinamicTmclDriver: msgRx : Invalid value");
            break;
        case 5:
            PRINTDEBUG("TrinamicTmclDriver: msgRx : Configuration EEPROM locked");
            break;
        case 6:
            PRINTDEBUG("TrinamicTmclDriver: msgRx : Command not available");
            break;
        case 128:
            PRINTDEBUG("TrinamicTmclDriver: msgRx : Position atteinte");
            break;
        default:
            PRINTDEBUG("TrinamicTmclDriver: msgRx : unkown status");
    }

    if(status != 128){
        replyMsg.set(FLAG_REPLY & status);
    }
    else
    {
        RTPflag.set(data[6]);
    }
    
}


EventFlags& TrinamicTmclDriver::getRTPflag(){
    return RTPflag;
}

TrinamicTmclDriver::~TrinamicTmclDriver(){
    
}