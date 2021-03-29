#ifndef MFT_DETECTOR_HPP
#define MFT_DETECTOR_HPP

#include <yaml-cpp/yaml.h>

#include <opencv2/features2d.hpp>

#include "mft/common/camera.hpp"

#include "mft/detection/detector_config.hpp"
#include "mft/detection/feature_grid.hpp"

namespace mft {

/**
 * Implementation of grid-based sampling for feature detection
 */

class Detector {
public:
    Detector(
        DetectorConfig _config,
        Camera _cam);
private:
    DetectorConfig config;
    Camera cam;
    FeatureGrid grid;

    cv::Ptr<cv::FastFeatureDetector> fast;

};

} // namespace mft

#endif