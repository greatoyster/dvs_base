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
        void load(const char *rosbag, const char *topic_name) override
        {
            auto bag = rosbag::Bag(rosbag, rosbag::bagmode::Read);
            CHECK(bag.isOpen()) << "Can not open bag file";
            std::vector<std::string> topics;
            std::string topic = topic_name;
            topics.push_back(topic);
            rosbag::View view(bag, rosbag::TopicQuery(topics));
            bool continue_looping_through_bag = true;
            bool got_initial_stamp = false;
            ros::Time initial_timestamp;
            BOOST_FOREACH (rosbag::MessageInstance const m, view)
            {
                if (!continue_looping_through_bag)
                {
                    break;
                }

                const std::string &current_topic_name = m.getTopic();

                if (topic_name == current_topic_name)
                {
                    dvs_msgs::EventArray::ConstPtr msg = m.instantiate<dvs_msgs::EventArray>();
                    if (msg != NULL)
                    {
                        if (msg->events.empty())
                        {
                            continue;
                        }
                        const ros::Time &stamp = msg->events[0].ts;
                        if (!got_initial_stamp)
                        {
                            initial_timestamp = stamp;
                            LOG(INFO) << "initial stamp: " << stamp;
                            got_initial_stamp = true;
                        }
                        for (size_t i = 0; i < msg->events.size(); ++i)
                        {
                            auto rel_stamp = msg->events[i].ts - initial_timestamp;
                            dvs_msgs::Event ev_modified(msg->events[i]);
                            ev_modified.ts = ros::Time(ev_modified.ts.toSec() - initial_timestamp.toSec());
                            DvsEvent ev_to_fill(ev_modified);
                            packet_.push_back(ev_to_fill);
                        }
                    }
                }
            }
        };
    };
}
#endif