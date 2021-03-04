#include <dvs_base/dvs_base.hpp>
#include <rpg_dvs/rpg_dvs_event.hpp>
#include <iostream>
#include <chrono>
#include <cassert>
#include <glog/logging.h>
#include <string>

using EventPacketA = dvs_base::EventPacketBase<Eigen::MatrixXd, Eigen::Vector4d>;
using EventPacketB = dvs_base::EventPacketBase<Eigen::MatrixXf, Eigen::Vector4f>;
using EventA = dvs_base::EventBase<int, int, int>;
using EventPacketC = dvs_base::EventPacketBase<std::vector<EventA>, EventA>;


using EventPacketD = rpg_dvs::DvsPacket;
int main(int argc, char **argv)
{
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    FLAGS_colorlogtostderr = true;

    dvs_base::exp_sys::setRootDir("/home/yangjq/etam_ws/src/dvs_base");

    EventPacketD e;

    int count = 0;

    auto rosbag = dvs_base::exp_sys::appendByRoot("datasets/simulation_3planes.bag").string();

    auto t0 = std::chrono::high_resolution_clock::now();

    auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<dvs_msgs::EventArray> vec1;

    dvs_base::loadMsgFromBag(vec1, rosbag.c_str(), "/dvs/events");

    auto t2 = std::chrono::high_resolution_clock::now();

    auto vec2 = dvs_base::loadMsgFromBag<dvs_msgs::EventArray>(rosbag.c_str(), "/dvs/events");
    std::vector<rpg_dvs::DvsPacket> event_packets; 
    for (auto v:vec2){
        rpg_dvs::DvsPacket d;
    }

    auto t3 = std::chrono::high_resolution_clock::now();

    LOG(INFO) << vec1.size();
    CHECK(vec1.size() == vec2.size());

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() << std::endl;
    
    return 0;
}