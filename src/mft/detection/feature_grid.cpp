#include "mft/detection/feature_grid.hpp"

namespace mft {

GridCell::GridCell()
{
    features = std::vector<Feature>();
}

GridCell::GridCell(
        std::vector<Feature> _features)
{
    features = _features;
}

bool
GridCell::isOccupied(void)
{
    return features.size() > 0;
}

void
GridCell::clear(void)
{
    features.clear();
}

void
GridCell::setFeatures(
    std::vector<Feature> _features)
{
    clear();
    features = _features;
}

void
GridCell::addFeature(Feature _feature)
{
    features.push_back(_feature);
}

void
GridCell::addFeatures(
    std::vector<Feature> _features)
{
    features.reserve(features.size() + _features.size());
    features.insert(features.end(), _features.begin(), _features.end());
}



}