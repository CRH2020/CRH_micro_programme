#ifndef _ROS_shared_SensorData_h
#define _ROS_shared_SensorData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace shared
{

  class SensorData : public ros::Msg
  {
    public:
      typedef uint8_t _sensor_id_type;
      _sensor_id_type sensor_id;
      typedef double _sensor_data_type;
      _sensor_data_type sensor_data;

    SensorData():
      sensor_id(0),
      sensor_data(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->sensor_id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->sensor_id);
      union {
        double real;
        uint64_t base;
      } u_sensor_data;
      u_sensor_data.real = this->sensor_data;
      *(outbuffer + offset + 0) = (u_sensor_data.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sensor_data.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sensor_data.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sensor_data.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_sensor_data.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_sensor_data.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_sensor_data.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_sensor_data.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->sensor_data);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->sensor_id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->sensor_id);
      union {
        double real;
        uint64_t base;
      } u_sensor_data;
      u_sensor_data.base = 0;
      u_sensor_data.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sensor_data.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sensor_data.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sensor_data.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_sensor_data.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_sensor_data.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_sensor_data.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_sensor_data.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->sensor_data = u_sensor_data.real;
      offset += sizeof(this->sensor_data);
     return offset;
    }

    const char * getType(){ return "shared/SensorData"; };
    const char * getMD5(){ return "9d8028e1d27b3b4a2b4bce26e38d46e8"; };

  };

}
#endif
