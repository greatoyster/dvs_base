#include <dvs_base/dvs_base_event_packet.hpp>
#include <dvs_base/dvs_base_event.hpp>
#include <iostream>
using EventPacketA = EventPacketBase<Eigen::MatrixXd, Eigen::Vector4d>;
using EventPacketB = EventPacketBase<Eigen::MatrixXf, Eigen::Vector4f>;
using EventA = EventBase<int, int, int>;
using EventPacketC = EventPacketBase<std::vector<EventA>, EventA>;

int main()
{
    auto data = Eigen::Matrix4d::Identity();
    EventPacketA p(data);
    std::cout << p.packet_ << "\n"
              << "size: " << p.size() << "\n"
              << "row1: " << p[2] << std::endl;
    EventPacketB q(data);
    std::cout << q[0] << std::endl;

    EventA e1;

    printf("sizeof e1: %ld\n", sizeof e1);

    EventPacketC k;
    k.packet_.push_back(e1);
    printf("sizeof PacketC:%ld, its size is %ld", sizeof(k),k.size());

    return 0;
}