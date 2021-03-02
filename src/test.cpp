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

    auto rosbag = dvs_base::exp_sys::appendByRoot("datasets/simulation_3walls.bag").string();
    
    auto t0 = std::chrono::high_resolution_clock::now();
    
    dvs_base::loadEventsFromBag<EventPacketD>(e, rosbag.c_str(), "/dvs/events");

    auto t1 = std::chrono::high_resolution_clock::now();

    

    auto t2 = std::chrono::high_resolution_clock::now();

    auto t3 = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() << std::endl;

    return 0;
}