#ifndef DVS_BASE_EVENT_PACKET
#define DVS_BASE_EVENT_PACKET

#include <vector>
#include <Eigen/Eigen>
#include <cassert>

/* Three main types of event packet: Eigen matrix, vector<vector<Scalar>>, dvs_msgs::EventArray */

template <typename Container, typename Event>
class EventPacketBase
{
public:
    /* Event packet traits */
    typedef Container ContainerType;
    typedef Event EventType;
    /* Common interfaces */
    EventPacketBase() = default;
    EventPacketBase(ContainerType packet) : packet_(packet){};
    EventType operator[](size_t index) = 0;
    size_t size() = 0;
    /* Event acess by traits */
    typename EventType::TimestampType ts(size_t index) = 0;
    typename EventType::CoordType xs(size_t index) = 0;
    typename EventType::CoordType ys(size_t index) = 0;
    typename EventType::PolarityType polarities(size_t index) = 0;
    /* Stored data */
    ContainerType packet_;
};

template <typename Event>
class EventPacketBase<std::vector<Event>, Event>
{
public:
    /* Event packet traits */
    typedef std::vector<Event> ContainerType;
    typedef Event EventType;
    /* Common interfaces */
    EventPacketBase() = default;
    EventPacketBase(ContainerType packet) : packet_(packet){};
    EventType operator[](size_t index) { return packet_.at(index); };
    size_t size() { return packet_.size(); };
    /* Event acess by traits */
    typename EventType::TimestampType ts(size_t index) { return packet_[index].ts(); };
    typename EventType::CoordType xs(size_t index) { return packet_[index].x(); };
    typename EventType::CoordType ys(size_t index) { return packet_[index].y(); };
    typename EventType::PolarityType polarities(size_t index) { return packet_[index].polarity(); };
    /* Stored data */
    ContainerType packet_;
};

template <typename Scalar>
class EventPacketBase<Eigen::Matrix<Scalar, -1, -1>, Eigen::Matrix<Scalar, 4, 1>>
{
public:
    /* Event packet traits */
    typedef Eigen::MatrixXd ContainerType;
    typedef Eigen::Vector4d EventType;
    /* Common interfaces */
    EventPacketBase() = default;
    EventPacketBase(ContainerType packet) : packet_(packet){};
    size_t size() { return packet_.cols(); };
    EventType operator[](size_t index) { return packet_.block<4, 1>(0, index); };
    /* Event acess by traits */
    Scalar ts(size_t index) { return packet_(0, index); };
    Scalar xs(size_t index) { return packet_(1, index); };
    Scalar ys(size_t index) { return packet_(2, index); };
    Scalar polarities(size_t index) { return packet_(3, index); };
    /* Stored data */
    ContainerType packet_;
};

#endif