#ifndef DVS_BASE_QUAT_TRANSFORM
#define DVS_BASE_QUAT_TRANSFORM

#include <Eigen/Eigen>
#include <kindr/minimal/quat-transformation.h>

namespace dvs_base
{
    using Transformation = kindr::minimal::QuatTransformation;
    using Quaternion = kindr::minimal::RotationQuaternion;

    Transformation identityTransform()
    {
        return Transformation(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Identity());
    }
}
#endif