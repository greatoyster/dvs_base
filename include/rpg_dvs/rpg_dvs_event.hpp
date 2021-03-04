#ifndef RPG_DVS_EVENT
#define RPG_DVS_EVENT

#include <boost/foreach.hpp>
#include <dvs_base/dvs_base_event_packet.hpp>
#include <dvs_base/dvs_base_event.hpp>
#include <dvs_msgs/EventArray.h>
#include <dvs_msgs/Event.h>
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <glog/logging.h>

namespace rpg_dvs
{

    struct DvsEvent : dvs_base::EventBase<ros::Time, uint8_t, uint8_t>
    {
        DvsEvent(dvs_msgs::Event &e)
        {
            ts_ = e.ts;
            x_ = e.x;
            y_ = e.y;
            polarity_ = e.polarity;
        };
    };

    class DvsPacket : public dvs_base::EventPacketBase<std::vector<DvsEvent>, DvsEvent>
    {
    public:
        void load(dvs_msgs::EventArray &earray)
        {
            for (auto ev:earray.events){
                packet_.push_back(DvsEvent(ev));
            }
        };
    };
}
#endif