#ifndef MFT_DETECTOR_CONFIG_HPP
#define MFT_DETECTOR_CONFIG_HPP

#include <opencv2/core.hpp>

namespace mft {

/**
 * Configuration for a feature detector
 */
struct DetectorConfig {
    // --- Grid parameters ---
    // Grid dimensions
    size_t grid_width = 8;
    size_t grid_height = 8;
    // Features within this distance of the image border are discarded
    size_t horizontal_border = 0;
    size_t vertical_border = 0;

    // --- FAST parameters ---
    // Attempt to detect features at init, fall back to min if too few detected
    int init_fast_threshold = 10; 
    int min_fast_threshold = 2;
};

} // namespace mft

#endif