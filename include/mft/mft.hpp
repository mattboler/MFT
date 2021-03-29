#ifndef MFT_MFT_HPP
#define MFT_MFT_HPP

#include "mft/common/camera.hpp"

#include "mft/detection/detector_config.hpp"
#include "mft/tracking/tracker.hpp"

namespace mft {

class MFT {
public:
    MFT(std::string _path_to_config);
    MFT(
        Camera _cam,
        DetectorConfig _det,
        TrackerConfig _track);
private:
    Detector detector;
    Tracker tracker;
};

} // namespace mft

#endif