#ifndef MFT_TRACKER_HPP
#define MFT_TRACKER_HPP

#include "mft/common/camera.hpp"
#include "mft/common/feature.hpp"

#include "mft/tracking/tracker_config.hpp"

namespace mft
{

/**
 * Implementation of a KLT-based sparse feature tracker
 */

class Tracker {
public:
    Tracker(
        TrackerConfig _config,
        Camera _cam);
private:
    TrackerConfig config;
    Camera cam;

};

} // namespace mft


#endif