#ifndef DVS_BASE_CAMERA
#define DVS_BASE_CAMERA

#include <image_geometry/pinhole_camera_model.h>
#include <opencv2/opencv.hpp>
#include <Eigen/Eigen>

namespace dvs_base
{
    template <typename Scalar>
    Eigen::Matrix<Scalar, 2, -1> getUndistortionMap(image_geometry::PinholeCameraModel &cam)
    {

        auto height = cam.fullResolution().height;
        auto width = cam.fullResolution().width;
        Eigen::Matrix<Scalar, 2, -1> map(2, height * width);
        for (auto h = 0; h < height; ++h)
        {
            for (auto w = 0; w < width; ++w)
            {
                cv::Point2d p = cam.rectifyPoint(cv::Point2d(h, w));
                map(h * width + w, 0) = Scalar(p.x);
                map(h * width + w, 1) = Scalar(p.y);
            }
        }
        return map;
    }
}
#endif