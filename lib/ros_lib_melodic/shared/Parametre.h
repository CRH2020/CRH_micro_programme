#ifndef _ROS_shared_Parametre_h
#define _ROS_shared_Parametre_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace shared
{

  class Parametre : public ros::Msg
  {
    public:
      typedef uint8_t _param_id_type;
      _param_id_type param_id;
      typedef double _param_data_type;
      _param_data_type param_data;

    Parametre():
      param_id(0),
      param_data(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->param_id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->param_id);
      union {
        double real;
        uint64_t base;
      } u_param_data;
      u_param_data.real = this->param_data;
      *(outbuffer + offset + 0) = (u_param_data.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_param_data.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_param_data.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_param_data.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_param_data.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_param_data.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_param_data.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_param_data.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->param_data);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->param_id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->param_id);
      union {
        double real;
        uint64_t base;
      } u_param_data;
      u_param_data.base = 0;
      u_param_data.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_param_data.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_param_data.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_param_data.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_param_data.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_param_data.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_param_data.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_param_data.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->param_data = u_param_data.real;
      offset += sizeof(this->param_data);
     return offset;
    }

    const char * getType(){ return "shared/Parametre"; };
    const char * getMD5(){ return "f0c70acd586808cf71f86c1bbc48a62f"; };

  };

}
#endif
