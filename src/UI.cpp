#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"

int main(int argc, char **argv){

	ros::NodeHandle node1;

	ros::ServiceClient client1 = node1.serviceClient<turtlesim::Spawn>("/spawn");

	turtlesim::Spawn turtle2;

	turtle2.request.x = 1.0;
	turtle2.request.y = 1.0;
	turtle2.request.theta = 0.0;

	turtle2.request.name = "turtle2";

	client1.call(turtle2);

}
