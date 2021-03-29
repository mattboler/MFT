#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud.h>

#include "mft/feature_tracker.hpp"

namespace mft {

class FeatureTrackerNode {
public:
    FeatureTrackerNode(ros::NodeHandle& nh);
    void init();
    void imageCallback(const sensor_msgs::ImageConstPtr& msg);
    sensor_msgs::PointCloudPtr buildFeatureMsg(
        const Frame& f,
        const std_msgs::Header& h);
    sensor_msgs::ImagePtr buildVisualizationMsg(
        const Frame& f,
        const std_msgs::Header& h);
private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    ros::Publisher feature_pub_; // Point cloud
    ros::Publisher vis_pub_; // visualization

    FeatureTracker tracker_;

    Frame prev_frame_;
    bool is_first_;

};

FeatureTrackerNode::FeatureTrackerNode(
    ros::NodeHandle& nh) 
    : nh_(nh), it_(nh), is_first_(true) {}

void FeatureTrackerNode::init()
{
    std::string image_topic;
    this->nh_.getParam("image_topic", image_topic);
    ROS_INFO("Image topic: %s", image_topic.c_str());
    this->image_sub_ = this->it_.subscribe(image_topic, 1, &FeatureTrackerNode::imageCallback, this);

    std::string feature_topic;
    this->nh_.getParam("feature_topic", feature_topic);
    ROS_INFO("Feature topic: %s", feature_topic.c_str());
    this->feature_pub_ = this->nh_.advertise<sensor_msgs::PointCloud>(feature_topic, 1);

    std::string visualization_topic;
    this->nh_.getParam("visualization_topic", visualization_topic);
    ROS_INFO("Visualization topic: %s", visualization_topic.c_str());
    this->vis_pub_ = this->nh_.advertise<sensor_msgs::Image>(visualization_topic, 1);

    std::string camera_path;
    this->nh_.getParam("camera_path", camera_path);
    ROS_INFO("Camera path: %s", camera_path.c_str());
    Camera cam = buildCamera(camera_path);

    std::string tracker_path;
    this->nh_.getParam("tracker_path", tracker_path);
    ROS_INFO("Tracker path: %s", tracker_path.c_str());
    FeatureTrackerParams params = buildTrackerParams(tracker_path);
    
    this->tracker_ = FeatureTracker(params, cam);
}

sensor_msgs::PointCloudPtr
FeatureTrackerNode::buildFeatureMsg(
    const Frame& f,
    const std_msgs::Header& h)
{
    sensor_msgs::PointCloudPtr features(new sensor_msgs::PointCloud);
    sensor_msgs::ChannelFloat32 id, age, u, v;

    features->header = h;
    features->header.frame_id = "world";

    for(size_t i = 0; i < f.ids.size(); ++i) {
        auto point_id = f.ids[i];
        auto point_coords = f.points_und[i];

        geometry_msgs::Point32 p;
        p.x = point_coords.x;
        p.y = point_coords.y;
        p.z = 1;

        features->points.push_back(p);
        id.values.push_back(point_id);
        u.values.push_back(p.x);
        v.values.push_back(p.y);
    }

    features->channels.push_back(id);
    features->channels.push_back(u);
    features->channels.push_back(v);

    return features;
}

sensor_msgs::ImagePtr
FeatureTrackerNode::buildVisualizationMsg(
    const Frame& f,
    const std_msgs::Header& h)
{
    cv::Mat vis = tracker_.annotateFrame(f);
    return cv_bridge::CvImage(h, "bgr8", vis).toImageMsg();
}

void FeatureTrackerNode::imageCallback(
    const sensor_msgs::ImageConstPtr& msg)
{   
    std_msgs::Header header = msg->header;
    cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(msg);
    cv::Mat img = cv_ptr->image;
    cv::Mat vis;

    Frame f;

    if (is_first_) {
        f = tracker_.buildFirstFrame(img);
        is_first_ = false;
    } else {
        f = tracker_.buildNextFrame(img, prev_frame_);
    }

    sensor_msgs::PointCloudPtr feature_msg = buildFeatureMsg(f, header);
    feature_pub_.publish(feature_msg);

    sensor_msgs::ImagePtr vis_msg = buildVisualizationMsg(f, header);
    vis_pub_.publish(vis_msg);

    prev_frame_ = f;
}

} // namespace mft

int main(int argc, char** argv) {
    ros::init(argc, argv, "FeatureTracker");
    ros::NodeHandle nh("~");

    ROS_INFO("main: instantiating FeatureTrackerNode");
    mft::FeatureTrackerNode node(nh);
    node.init();
    ROS_INFO("main: Spinning FeatureTrackerNode");
    ros::spin();
    return 0;
}