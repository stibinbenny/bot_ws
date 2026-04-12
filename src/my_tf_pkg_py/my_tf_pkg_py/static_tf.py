import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TransformStamped
from tf2_ros.static_transform_broadcaster import StaticTransformBroadcaster
import tf_transformations

class StaticTF(Node):
    def __init__(self):
        super().__init__('static_tf_broadcaster')

        self.broadcaster = StaticTransformBroadcaster(self)

        t = TransformStamped()

        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = 'base_link'
        t.child_frame_id = 'fixed_frame'

        t.transform.translation.x = 0.0
        t.transform.translation.y = 0.0
        t.transform.translation.z = 0.35

        q = tf_transformations.quaternion_from_euler(0, 0, 0.707)

        t.transform.rotation.x = q[0]
        t.transform.rotation.y = q[1]
        t.transform.rotation.z = q[2]
        t.transform.rotation.w = q[3]

        self.broadcaster.sendTransform(t)

def main():
    rclpy.init()
    node = StaticTF()
    rclpy.spin(node)
    rclpy.shutdown()

## ros2 run my_tf_pkg_py static_tf
## rviz2
## pip install "numpy<2.0"
