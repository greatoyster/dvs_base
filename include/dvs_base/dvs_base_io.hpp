#ifndef DVS_BASE_IO
#define DVS_BASE_IO

template <typename EventPacket>
void loadEventsFromBag(EventPacket &events, char *rosbag, char *topic_name);

template <typename EventPacket>
void loadEventsFromText(EventPacket &events, char* fin);

#endif