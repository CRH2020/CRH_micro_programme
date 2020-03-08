#ifndef _ROS_shared_SequenceAck_h
#define _ROS_shared_SequenceAck_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace shared
{

  class SequenceAck : public ros::Msg
  {
    public:
      typedef uint8_t _sequence_id_type;
      _sequence_id_type sequence_id;
      typedef uint8_t _result_code_type;
      _result_code_type result_code;

    SequenceAck():
      sequence_id(0),
      result_code(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->sequence_id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->sequence_id);
      *(outbuffer + offset + 0) = (this->result_code >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result_code);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->sequence_id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->sequence_id);
      this->result_code =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->result_code);
     return offset;
    }

    const char * getType(){ return "shared/SequenceAck"; };
    const char * getMD5(){ return "2e23a7df7b39755db4ff1617d17b331e"; };

  };

}
#endif
