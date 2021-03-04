#ifndef DVS_BASE_IO
#define DVS_BASE_IO
#include <boost/foreach.hpp>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <vector>
namespace dvs_base
{

    template <typename EventPacket>
    void loadEventsFromBag(EventPacket &event_packet, const char *rosbag, const char *topic_name)
    {
        event_packet.load(rosbag, topic_name);
    }

    template <typename EventPacket>
    void loadEventsFromText(EventPacket &event_packet, const char *fin)
    {
        event_packet.load(fin);
    }

    template <typename MsgType>
    void loadMsgFromBag(std::vector<MsgType> &vec, const char *rosbag, const char *topic_name)
    {
        auto bag = rosbag::Bag(rosbag, rosbag::bagmode::Read);
        if (!bag.isOpen())
        {
            std::cerr << "Can not open bag file!" << std::endl;
        }
        std::vector<std::string> topics;
        std::string topic = topic_name;
        topics.push_back(topic);
        rosbag::View view(bag, rosbag::TopicQuery(topics));

        BOOST_FOREACH (rosbag::MessageInstance const m, view)
        {
            const std::string &current_topic_name = m.getTopic();
            if (topic_name == current_topic_name)
            {
                typename MsgType::ConstPtr msg = m.instantiate<MsgType>();
                if (msg != NULL)
                {
                    vec.push_back(*msg);
                }
            }
        }
        bag.close();
    }
    template <typename MsgType>
    std::vector<MsgType> loadMsgFromBag(const char *rosbag, const char *topic_name)
    {
        std::vector<MsgType> vec;
        auto bag = rosbag::Bag(rosbag, rosbag::bagmode::Read);
        if (!bag.isOpen())
        {
            std::cerr << "Can not open bag file!" << std::endl;
        }
        std::vector<std::string> topics;
        std::string topic = topic_name;
        topics.push_back(topic);
        rosbag::View view(bag, rosbag::TopicQuery(topics));

        BOOST_FOREACH (rosbag::MessageInstance const m, view)
        {
            const std::string &current_topic_name = m.getTopic();
            if (topic_name == current_topic_name)
            {
                typename MsgType::ConstPtr msg = m.instantiate<MsgType>();
                if (msg != NULL)
                {
                    vec.push_back(*msg);
                }
            }
        }
        bag.close();
        return vec;
    }
}
#endif