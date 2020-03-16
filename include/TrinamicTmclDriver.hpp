/*!
 * \file TrinamicTmclDriver.hpp
 * 
 * \brief fichier header de TrinamicTmclDriver
 */
#ifndef DEF_TRINAMICTMCLDRIVER
#define DEF_TRINAMICTMCLDRIVER

#include "mbed.h"
#include "PrintDebug.hpp"

#define FLAG_REPLY 0x7F

enum eTMCLInstruction {
    ROR = 1,
    ROL = 2,
    MST = 3,
    MVP = 4,
    SAP = 5,
    RTP = 138
};

class TrinamicTmclDriver
{
    public:
        TrinamicTmclDriver(CAN& can,uint8_t _target);
        int sendTMCL(eTMCLInstruction instruction,uint8_t type,uint8_t motor,uint32_t value);
        void configureMotor(uint8_t motorNum);
        void msgRx(uint8_t* data,uint8_t len);
        EventFlags& getRTPflag();
        ~TrinamicTmclDriver();
    private:
        CAN& _can;
        uint8_t _target;
        EventFlags replyMsg;
        EventFlags RTPflag;
        uint8_t motorMask;
};



#endif