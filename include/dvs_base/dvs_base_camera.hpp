#ifndef DVS_BASE_CAMERA
#define DVS_BASE_CAMERA

#include <image_geometry/pinhole_camera_model.h>
#include <opencv2/opencv.hpp>
#include <Eigen/Eigen>
#include <glog/logging.h>

namespace dvs_base
{
    template <typename Scalar>
    Eigen::Matrix<Scalar, 2, -1> getUndistortionMap(image_geometry::PinholeCameraModel &cam)
    {

        auto height = cam.fullResolution().height;
        auto width = cam.fullResolution().width;
        Eigen::Matrix<Scalar, 2, -1> lookup_table(2, height * width);

        for (auto h = 0; h < height; ++h)
        {
            for (auto w = 0; w < width; ++w)
            {
                cv::Point2d rectified_point = cam.rectifyPoint(cv::Point2d(h, w));
                lookup_table(0, h * width + w) = Scalar(rectified_point.x);
                lookup_table(1, h * width + w) = Scalar(rectified_point.y);
            }
        }
        
        return lookup_table;
    }
}
#endif