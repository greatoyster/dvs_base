#ifndef DVS_BASE_EXP_SYS
#define DVS_BASE_EXP_SYS

#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <chrono>
#include <Eigen/Eigen>
#include <glog/logging.h>
#include <random>

namespace dvs_base
{
    namespace utils
    {
        template <typename Scalar>
        Eigen::Matrix<Scalar, -1, 1> getNormalDistribution(Scalar mean, Scalar scale, size_t n)
        {
            Eigen::Matrix<Scalar, -1, 1> dist_vec(n, 1);

            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine gen(seed);
            std::normal_distribution<Scalar> dis(mean, scale);

            for (auto i = 0; i < n; ++i)
                dist_vec[i] = dis(gen);

            return dist_vec;
        }

    }
    namespace exp_sys
    {
        static boost::filesystem::path root_dir_;
        static boost::filesystem::path output_dir_;

        void setRootDir(const char *root)
        {
            using namespace boost::filesystem;
            root_dir_ = root;
            CHECK(exists(root_dir_)) << "Project root directory does not exist: " << root_dir_.string();
            boost::filesystem::path exps_path = root_dir_;
            exps_path.append("exps");
            LOG(INFO) << root_dir_.string();

            if (!exists(exps_path))
                create_directory(exps_path);

            directory_iterator end;
            directory_iterator pos(exps_path);
            int max_id = 0;

            for (; pos != end; pos++)
            {
                int exp_id = std::atoi(pos->path().filename().c_str());
                if (exp_id >= max_id)
                    max_id = exp_id;
            }

            path exp_path = exps_path.append((boost::format("%03d") % (max_id + 1)).str());
            create_directory(exp_path);
            output_dir_ = exp_path;
        }

        boost::filesystem::path currentRootDir()
        {
            return root_dir_;
        }

        boost::filesystem::path currentOutputDir()
        {
            return output_dir_;
        }

        boost::filesystem::path appendByRoot(const char *relative_path)
        {
            auto ret = root_dir_;
            ret.append(relative_path);

            return ret;
        }

        std::string filenameBySeq(const char *prefix, int seq, const char *suffix)
        {
            return (boost::format("%s%06d%s") % prefix % seq % suffix).str();
        }

        std::string filepathBySeq(const char *prefix, int seq, const char *suffix)
        {
            auto filename = (boost::format("%s%06d%s") % prefix % seq % suffix).str();
            auto filepath = output_dir_;
            filepath.append(filename);

            return filepath.string();
        }

    }
}

#endif