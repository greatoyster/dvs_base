#ifndef DVS_BASE_IO
#define DVS_BASE_IO
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

}
#endif