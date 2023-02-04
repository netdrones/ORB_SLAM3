#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/numpy.h>
#include "System.h"

namespace orbslam3::python
{
  namespace py = ::pybind11;

  struct System
  {
    System(const std::string &vocFile, const std::string &settingsFile, const int sensor, bool useViewer, int initFr);

    py::array_t<double> TrackStereo(const py::array_t<uint8_t> &imLeft,
                                    const py::array_t<uint8_t> &imRight,
                                    double timestamp,
                                    const py::array_t<double> &imuMeas);

    bool MapChanged();

    void Reset();
    void ResetActiveMap();

    void Shutdown();
    bool IsShutdown();

    int GetTrackingState();
    bool IsLost();
    bool IsFinished();
    float GetImageScale();

  private:
    ORB_SLAM3::System slam_;
  };

  System::System(const std::string &vocFile, const std::string &settingsFile, const int sensor, bool useViewer = false, int initFr = 0)
      : slam_(vocFile, settingsFile, static_cast<ORB_SLAM3::System::eSensor>(sensor), useViewer, initFr)
  {
  }

  py::array_t<double> System::TrackStereo(const py::array_t<uint8_t> &imLeft,
                                          const py::array_t<uint8_t> &imRight,
                                          double timestamp,
                                          const py::array_t<double> &imuMeas_)
  {
    auto bil = imLeft.request(), bir = imRight.request();
    if (bil.format != py::format_descriptor<uint8_t>::format())
    {
      throw std::runtime_error("left image data type is not uint8");
    }
    if (bir.format != py::format_descriptor<uint8_t>::format())
    {
      throw std::runtime_error("right image datat type is not uint8");
    }

    std::vector<::ORB_SLAM3::IMU::Point> imuMeas;
    if (slam_.sensor() == ORB_SLAM3::System::IMU_STEREO)
    {
      auto bi_imu = imuMeas_.request();
      if (bi_imu.shape[1] != 7)
      {
        throw std::runtime_error("IMU measurement must have 7 cols");
      }

      imuMeas.reserve(bi_imu.shape[0]);
      for (auto i = 0; i < bi_imu.shape[0]; i++)
      {
        auto data = static_cast<double *>(bi_imu.ptr);
        auto timestamp = static_cast<double>(data[7 * i] / 1e9);
        auto acc_x = static_cast<float>(data[7 * i + 1]);
        auto acc_y = static_cast<float>(-data[7 * i + 2]);
        auto acc_z = static_cast<float>(data[7 * i + 3]);
        auto vel_x = static_cast<float>(data[7 * i + 4]);
        auto vel_y = static_cast<float>(-data[7 * i + 5]);
        auto vel_z = static_cast<float>(data[7 * i + 6]);
        imuMeas.push_back(::ORB_SLAM3::IMU::Point(
            acc_x,
            acc_y,
            acc_z,
            vel_x,
            vel_y,
            vel_z,
            timestamp));
      }
    }

    auto Tcw = slam_.TrackStereo(
        cv::Mat(bil.shape[0], bil.shape[1], CV_8UC1, reinterpret_cast<uint8_t *>(bil.ptr)),
        cv::Mat(bir.shape[0], bir.shape[1], CV_8UC1, reinterpret_cast<uint8_t *>(bir.ptr)),
        timestamp,
        imuMeas);

    auto tcw = Tcw.translation();
    auto q = Tcw.unit_quaternion();

    auto ret = py::array_t<double>(7);
    auto bi_ret = ret.request();
    auto p = static_cast<double *>(bi_ret.ptr);
    p[0] = tcw(0);
    p[1] = tcw(1);
    p[2] = tcw(2);
    p[3] = q.x();
    p[4] = q.y();
    p[5] = q.z();
    p[6] = q.w();

    return ret;
  }

  bool System::MapChanged()
  {
    return slam_.MapChanged();
  }

  void System::Reset()
  {
    slam_.Reset();
  }

  void System::ResetActiveMap()
  {
    slam_.ResetActiveMap();
  }

  void System::Shutdown()
  {
    slam_.Shutdown();
  }

  bool System::IsShutdown()
  {
    return slam_.isShutDown();
  }

  int System::GetTrackingState()
  {
    return slam_.GetTrackingState();
  }

  bool System::IsLost()
  {
    return slam_.isLost();
  }

  bool System::IsFinished()
  {
    return slam_.isFinished();
  }

  float System::GetImageScale()
  {
    return slam_.GetImageScale();
  }

  PYBIND11_MODULE(_orb_slam3, m)
  {
    m.doc() = "ORB-SLAM3 Python binding";

    // Expose System::eSensor
    // m.attr("SENSOR_MONOCULAR") = ORB_SLAM3::System::eSensor::MONOCULAR;
    // m.attr("SENSOR_STEREO") = ORB_SLAM3::System::eSensor::STEREO;
    // m.attr("SENSOR_RGBD") = ORB_SLAM3::System::eSensor::RGBD;
    // m.attr("SENSOR_IMU_MONOCULAR") = ORB_SLAM3::System::eSensor::IMU_MONOCULAR;
    // m.attr("SENSOR_IMU_STEREO") = ORB_SLAM3::System::eSensor::IMU_STEREO;
    // m.attr("SENSOR_IMU_RGBD") = ORB_SLAM3::System::eSensor::IMU_RGBD;

    // Expose orb_slam3.System class
    py::class_<System>(m, "System")
        .def(py::init<const std::string &, const std::string &, int, bool, int>())
        .def("track_stereo", &System::TrackStereo)
        .def("map_changed", &System::MapChanged)
        .def("reset", &System::Reset)
        .def("reset_active_map", &System::ResetActiveMap)
        .def("shutdown", &System::Shutdown)
        .def("is_shutdown", &System::IsShutdown)
        .def("get_tracking_state", &System::GetTrackingState)
        .def("is_lost", &System::IsLost)
        .def("is_finished", &System::IsFinished)
        .def("get_image_scale", &System::GetImageScale);
  }

} // namespace orbslam3::python
