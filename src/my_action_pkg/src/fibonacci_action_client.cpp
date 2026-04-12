#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "my_action_pkg/action/fibonacci.hpp"

using namespace std::chrono_literals;
using Fibonacci = my_action_pkg::action::Fibonacci;
using GoalHandleFibonacci = rclcpp_action::ClientGoalHandle<Fibonacci>;

class FibonacciActionClient : public rclcpp::Node
{
public:
  FibonacciActionClient()
  : Node("fibonacci_action_client")
  {
    this->client_ = rclcpp_action::create_client<Fibonacci>(this, "fibonacci");

    this->timer_ = this->create_wall_timer(
      1s, std::bind(&FibonacciActionClient::send_goal, this));
  }

private:
  rclcpp_action::Client<Fibonacci>::SharedPtr client_;
  rclcpp::TimerBase::SharedPtr timer_;

  void send_goal()
  {
    this->timer_->cancel();

    if (!this->client_->wait_for_action_server())
    {
      RCLCPP_ERROR(this->get_logger(), "Action server not available");
      return;
    }

    auto goal_msg = Fibonacci::Goal();
    goal_msg.order = 10;

    RCLCPP_INFO(this->get_logger(), "Sending goal");

    auto send_goal_options = rclcpp_action::Client<Fibonacci>::SendGoalOptions();

    send_goal_options.feedback_callback =
      [this](GoalHandleFibonacci::SharedPtr,
             const std::shared_ptr<const Fibonacci::Feedback> feedback)
      {
        RCLCPP_INFO(this->get_logger(), "Feedback received");
      };

    send_goal_options.result_callback =
      [this](const GoalHandleFibonacci::WrappedResult & result)
      {
        RCLCPP_INFO(this->get_logger(), "Result received");
      };

    this->client_->async_send_goal(goal_msg, send_goal_options);
  }
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FibonacciActionClient>());
  rclcpp::shutdown();
  return 0;
}

// ros2 run my_action_pkg fibonacci_action_server
// ros2 run my_action_pkg fibonacci_action_client

// ros2 action list
// ros2 action send_goal /fibonacci my_action_pkg/action/Fibonacci "{order: 10}" --feedback
// 
