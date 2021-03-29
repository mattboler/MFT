#ifndef MFT_FEATURE_GRID_HPP
#define MFT_FEATURE_GRID_HPP

#include <vector>

#include "mft/common/feature.hpp"

namespace mft {

/**
 * Class representing a subsection of an image
 */
class GridCell {
public:
    std::vector<Feature> features;

    GridCell();
    GridCell(std::vector<Feature> _features);

    // Check if there are active features in this cell
    bool isOccupied(void);
    // Remove all data in this cell
    void clear(void);
    // Assign features and their ids to the cell
    void setFeatures(std::vector<Feature> _features);
    // Get features in the cell
    std::vector<Feature> getFeatures(void);
    // Add a new feature to the cell
    void addFeature(Feature _feature);
    // Add multiple new features to the cell
    void addFeatures(std::vector<Feature> _features);
    
private:

};
/** Class representing an occupancy grid for features in an image
 * Notes:
 *  - Feature locations are in global image coordinates, not cell coordinates
 *  - Cells are indexed in row-major order
 */
class FeatureGrid {
public:

    FeatureGrid();
    FeatureGrid(
        cv::Size _image_size,
        cv::Size _grid_size,
        cv::Size _image_border_size);
    
    // Divide image into sub-images
    std::vector<cv::Mat> generateCellImages(const cv::Mat& _img);
    // Extract active features from grid
    std::vector<Feature> getFeatures();
    // Update grid with new feature locations
    void setFeatures(std::vector<Feature> _new_features);

private:
    // List of current features
    std::vector<GridCell> grid_cells;

    // Pixel boundaries of each cell
    std::vector<cv::Rect> grid_cell_coords;

    // Parameters
    cv::Size image_size;
    cv::Size grid_size;
    cv::Size image_border_size;
    

};

}

#endif