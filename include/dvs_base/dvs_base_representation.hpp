#ifndef DVS_BASE_REPRESENTATION
#define DVS_BASE_REPRESENTATION

#include <Eigen/Eigen>

namespace dvs_base
{
    template <typename EventPacket, typename Scalar, int Height, int Width>
    Eigen::Matrix<Scalar, Height, Width> spatioTemporal(EventPacket &packet);

    template <typename EventPacket, typename Scalar, int Height, int Width>
    Eigen::Matrix<Scalar, Height, Width> accumulatedEvents(EventPacket &packet);

}

#endif