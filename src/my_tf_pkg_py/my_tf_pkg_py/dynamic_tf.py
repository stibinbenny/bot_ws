import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TransformStamped
from tf2_ros import TransformBroadcaster
import tf_transformations
import math

class DynamicTF(Node):
    def __init__(self):
        super().__init__('dynamic_tf_broadcaster')

        self.br = TransformBroadcaster(self)
        self.timer = self.create_timer(0.05, self.broadcast)
        self.angle = 0.0

    def broadcast(self):
        t = TransformStamped()

        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = 'base_link'
        t.child_frame_id = 'moving_frame'

        r = 0.45

        t.transform.translation.x = r * math.cos(self.angle)
        t.transform.translation.y = r * math.sin(self.angle)
        t.transform.translation.z = 0.0

        q = tf_transformations.quaternion_from_euler(0, 0, self.angle)

        t.transform.rotation.x = q[0]
        t.transform.rotation.y = q[1]
        t.transform.rotation.z = q[2]
        t.transform.rotation.w = q[3]

        self.br.sendTransform(t)

        self.angle += 1

def main():
    rclpy.init()
    node = DynamicTF()
    rclpy.spin(node)
    rclpy.shutdown()

## ros2 run my_tf_pkg_py dynamic_tf
## rviz2