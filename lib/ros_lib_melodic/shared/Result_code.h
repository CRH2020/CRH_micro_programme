#ifndef _ROS_shared_Result_code_h
#define _ROS_shared_Result_code_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace shared
{

  class Result_code : public ros::Msg
  {
    public:
      typedef int8_t _result_code_type;
      _result_code_type result_code;

    Result_code():
      result_code(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_result_code;
      u_result_code.real = this->result_code;
      *(outbuffer + offset + 0) = (u_result_code.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result_code);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_result_code;
      u_result_code.base = 0;
      u_result_code.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result_code = u_result_code.real;
      offset += sizeof(this->result_code);
     return offset;
    }

    const char * getType(){ return "shared/Result_code"; };
    const char * getMD5(){ return "873ed3f54847f7a2d6c6991693b8ccbc"; };

  };

}
#endif
