#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <visualization_msgs/msg/marker.hpp>

class RobotMarkerPublisher : public rclcpp::Node {
 public:
  RobotMarkerPublisher() : Node("robot_marker_publisher") {
    rclcpp::QoS qos = rclcpp::SystemDefaultsQoS();
    qos.keep_last(1);

    robot_marker_.header.frame_id = "map";
    robot_marker_.type = robot_marker_.MESH_RESOURCE;
    robot_marker_.ns = "bluerov";
    robot_marker_.color.b = 0.9;
    robot_marker_.color.g = 0.5;
    robot_marker_.color.r = 0.1;
    robot_marker_.color.a = 1.0;
    robot_marker_.scale.x = 1.0;
    robot_marker_.scale.y = 1.0;
    robot_marker_.scale.z = 1.0;
    robot_marker_.mesh_resource =
        "package://hippo_sim/models/bluerov/meshes/bluerov.dae";

    tank_marker_.header.frame_id = "map";
    tank_marker_.type = tank_marker_.MESH_RESOURCE;
    tank_marker_.ns = "tank";
    tank_marker_.pose.position.x = 1.0;
    tank_marker_.pose.position.y = 2.0;
    tank_marker_.pose.position.z = -1.5;
    tank_marker_.color.g = 0.725;
    tank_marker_.color.b = 1.0;
    tank_marker_.color.a = 1.0;
    tank_marker_.scale.x = 1.0;
    tank_marker_.scale.y = 1.0;
    tank_marker_.scale.z = 1.0;
    tank_marker_.mesh_resource =
        "package://hippo_sim/models/pool/meshes/pool.dae";

    marker_pub_ =
        create_publisher<visualization_msgs::msg::Marker>("robot_marker", qos);

    pose_sub_ =
        create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
            "vision_pose_cov", qos,
            [this](
                const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr
                    msg) {
              robot_marker_.pose = msg->pose.pose;
              robot_marker_.header.stamp = msg->header.stamp;
              marker_pub_->publish(robot_marker_);
            });

    timer_ = create_timer(std::chrono::seconds(1), [this]() {
      tank_marker_.header.stamp = now();
      marker_pub_->publish(tank_marker_);
    });
  }

 private:
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
  rclcpp::Subscription<
      geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr pose_sub_;
  rclcpp::TimerBase::SharedPtr timer_;
  visualization_msgs::msg::Marker robot_marker_;
  visualization_msgs::msg::Marker tank_marker_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RobotMarkerPublisher>());
  return 0;
}
