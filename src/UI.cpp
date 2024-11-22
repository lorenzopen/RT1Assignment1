#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"

int main(int argc, char **argv){

	
	ros::init(argc, argv, "node1");
	ros::NodeHandle node1;

	ros::ServiceClient client1 = node1.serviceClient<turtlesim::Spawn>("/spawn");

	turtlesim::Spawn turtle2;

	turtle2.request.x = 3.0;
	turtle2.request.y = 3.0;
	turtle2.request.theta = 0.0;

	turtle2.request.name = "turtle2";

	client1.call(turtle2);

	ros::Publisher turtle1_pub = node1.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
	ros::Publisher turtle2_pub = node1.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);
	ros::Rate rate(1); 
	int turtlechoice;
	float lin_vel, ang_vel;
	while (ros::ok()) {
		
		std::cout << "Select a turtle to move: " << std::endl;
		std::cout << "1. turtle1 " << std::endl;
		std::cout << "2. turtle2 " << std::endl;
		std::cout << "3. quit " << std::endl;
		std::cin >> turtlechoice;
		
		if (turtlechoice == 3){break;}
		
		std::cout << "Enter linear velocity: ";
		std::cin >> lin_vel;
		std::cout << "Enter angular velocity: "; 
		std::cin >> ang_vel;


		geometry_msgs::Twist vel_msg;
	        vel_msg.linear.x = lin_vel;
	        vel_msg.angular.z = ang_vel;

	        if (turtlechoice == 1) {
	            turtle1_pub.publish(vel_msg);
	        } else if (turtlechoice == 2) {
	            turtle2_pub.publish(vel_msg);	        
	        } else {
	            ROS_WARN("Invalid turtle name! Enter 'turtle1' or 'turtle2'.");
	     	}
        
        	ros::Duration(1.0).sleep();
        
        	vel_msg.linear.x = 0.0;
		vel_msg.angular.z = 0.0;
	
		if (turtlechoice == 1) {
	            turtle1_pub.publish(vel_msg);
	        } else if (turtlechoice == 2) {
	            turtle2_pub.publish(vel_msg);
	        }
	}

}
