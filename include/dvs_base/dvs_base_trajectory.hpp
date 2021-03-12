#ifndef DVS_BASE_TRAJECTORY
#define DVS_BASE_TRAJECTORY

#include "dvs_base_quat_transform.hpp"
#include <map>
#include <ros/time.h>
#include <glog/logging.h>

namespace dvs_base {

    template<class DerivedTrajectory>
    class Trajectory {
    public:
        typedef std::map<ros::Time, dvs_base::Transformation> PoseMap;

        DerivedTrajectory &derived() {
            return static_cast<DerivedTrajectory &>(*this);
        }

        Trajectory() {}

        Trajectory(const PoseMap &poses)
                : poses_(poses) {
        }

        // Returns T_W_C (mapping points from C to the world frame W)
        bool getPoseAt(const ros::Time &t, dvs_base::Transformation &T) const {
            return derived().getPoseAt(t, T);
        }

        void getFirstControlPose(dvs_base::Transformation *T, ros::Time *t) const {
            *t = poses_.begin()->first;
            *T = poses_.begin()->second;
        }

        void getLastControlPose(dvs_base::Transformation *T, ros::Time *t) const {
            *t = poses_.rbegin()->first;
            *T = poses_.rbegin()->second;
        }

        size_t getNumControlPoses() const {
            return poses_.size();
        }

        bool print() const {
            size_t control_pose_idx = 0u;
            for (auto it : poses_) {
                VLOG(1) << "--Control pose #" << control_pose_idx++ << ". time = " << it.first;
                VLOG(1) << "--T = ";
                VLOG(1) << it.second;
            }
            return true;
        }

    protected:
        PoseMap poses_;
    };

    class LinearTrajectory : public Trajectory<LinearTrajectory> {
    public:
        LinearTrajectory() : Trajectory() {}

        LinearTrajectory(const PoseMap &poses)
                : Trajectory(poses) {
            CHECK_GE(poses_.size(), 2u) << "At least two poses need to be provided";
        }

        bool getPoseAt(const ros::Time &t, dvs_base::Transformation &T) const {
            ros::Time t0_, t1_;
            dvs_base::Transformation T0_, T1_;

            // Check if it is between two known poses
            auto it1 = poses_.upper_bound(t);
            if (it1 == poses_.begin()) {
                LOG_FIRST_N(WARNING, 5) << "Cannot extrapolate in the past. Requested pose: "
                                        << t << " but the earliest pose available is at time: "
                                        << poses_.begin()->first;
                return false;
            } else if (it1 == poses_.end()) {
                LOG_FIRST_N(WARNING, 5) << "Cannot extrapolate in the future. Requested pose: "
                                        << t << " but the latest pose available is at time: "
                                        << (poses_.rbegin())->first;
                return false;
            } else {
                auto it0 = std::prev(it1);
                t0_ = (it0)->first;
                T0_ = (it0)->second;
                t1_ = (it1)->first;
                T1_ = (it1)->second;
            }

            // Linear interpolation in SE(3)
            auto T_relative = T0_.inverse() * T1_;
            auto delta_t = (t - t0_).toSec() / (t1_ - t0_).toSec();
            T = T0_ * dvs_base::Transformation::exp(delta_t * T_relative.log());
            return true;
        }
    };


    class WindowedSpline : public Trajectory<WindowedSpline> {
    public:
        WindowedSpline() {}

        WindowedSpline(const PoseMap &poses) {
            CHECK_GE(poses_.size(), 4) << "At least 4 poses need to be provided";
            LinearTrajectory traj(poses);

            /*  TODO: Add curve fitting here. */
        }

        WindowedSpline(const LinearTrajectory &traj) {
            CHECK_GE(traj.getNumControlPoses(), 4) << "At least " << 4 << " poses need to be provided";
            /*  TODO: Add curve fitting here. */
        }

        bool getPoseAt(const ros::Time &t, dvs_base::Transformation &T) const {
            ros::Time t0_, t1_, t2_, t3_;
            dvs_base::Transformation T0_, T1_, T2_, T3_;
            // Check if it is between two known control points
            auto it = poses_.begin();
            t0_ = it->first;
            T0_ = (it++)->second;
            t1_ = it->first;
            T1_ = (it++)->second;
            t2_ = it->first;
            T2_ = (it++)->second;
            t3_ = it->first;
            T3_ = (it++)->second;
            auto p0_ = T0_.getPosition();
            auto p1_ = T1_.getPosition();
            auto p2_ = T2_.getPosition();
            auto p3_ = T3_.getPosition();

            it = poses_.upper_bound(t);
            it = poses_.lower_bound(t);

            if (t < t0_) {
                LOG_FIRST_N(WARNING, 5) << "Cannot extrapolate in the past. Requested pose: "
                                        << t << " but the earliest pose available is at time: "
                                        << poses_.begin()->first;
                return false;
            } else if (t > t3_) {
                LOG_FIRST_N(WARNING, 5) << "Cannot extrapolate in the future. Requested pose: "
                                        << t << " but the latest pose available is at time: "
                                        << (poses_.rbegin())->first;
                return false;
            }
            /* TODO: Add interpolation here */


            double coeff = (t - t0_).toNSec() / (t3_ - t0_).toNSec();

            Eigen::Vector3d p;

            p = coeff * coeff * coeff * (-p0_ + 3 * p1_ - 3 * p2_ + p3_);
            p += coeff * coeff * (3 * p0_ - 6 * p1_ + 3 * p2_);
            p += coeff * (-3 * p0_ + 3 * p2_);
            p += p0_ + 4 * p1_ + p2_;
            p /= 6;

            return true;
        }

    };
}

#endif