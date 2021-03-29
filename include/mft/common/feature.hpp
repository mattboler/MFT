#ifndef MFT_FEATURE_HPP
#define MFT_FEATURE_HPP

#include <opencv2/core.hpp>

namespace mft {

struct Feature {
    cv::KeyPoint point;
    size_t id;
};

}

#endif