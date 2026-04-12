#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"

class DynamicTF : public rclcpp::Node {
public:
  DynamicTF() : Node("dynamic_tf_broadcaster"), angle_(0.0) {
    broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);

    timer_ = this->create_wall_timer(std::chrono::milliseconds(50),
                                     std::bind(&DynamicTF::broadcast_tf, this));
  }

private:
  void broadcast_tf() {
    geometry_msgs::msg::TransformStamped t;

    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "base_link";
    t.child_frame_id = "moving_frame";

    double radius = 0.2;

    t.transform.translation.x = radius * cos(angle_);
    t.transform.translation.y = radius * sin(angle_);
    t.transform.translation.z = 0.0;

    tf2::Quaternion q;
    q.setRPY(0, 0, angle_); // rotating with motion

    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    broadcaster_->sendTransform(t);

    angle_ += 0.05;
  }

  rclcpp::TimerBase::SharedPtr timer_;
  std::shared_ptr<tf2_ros::TransformBroadcaster> broadcaster_;
  double angle_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DynamicTF>());
  rclcpp::shutdown();
  return 0;
}


// ros2 run my_tf_pkg dynamic_tf_broadcaster
