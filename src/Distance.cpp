#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Twist.h"


double turtle1_posex,turtle1_posey;
double turtle2_posex,turtle2_posey;


void turtle1PoseCallback(const turtlesim::Pose::ConstPtr& msg){
	turtle1_posex = msg->x;
	turtle1_posey = msg->y;
}


void turtle2PoseCallback(const turtlesim::Pose::ConstPtr& msg){
	turtle2_posex = msg->x;
	turtle2_posey = msg->y;
}


int main(int argc, char **argv){
	
	ros::init(argc, argv, "node2");
	ros::NodeHandle node2;

	ros::Subscriber turtle1_sub = node2.subscribe("/turtle1/pose", 10, turtle1PoseCallback);
	ros::Subscriber turtle2_sub = node2.subscribe("/turtle2/pose", 10, turtle2PoseCallback);
	ros::Publisher distance_pub = node2.advertise<std_msgs::Float32>("/turtledistance", 10);

	double distance;
	std_msgs::Float32 distance_msg;
	ros::Rate rate(10);

	while(ros::ok()){	
		ros::spinOnce();
	
		distance = sqrt(pow((turtle1_posex - turtle2_posex),2) + pow((turtle1_posey - turtle2_posey),2));
		distance_msg.data = distance;
		distance_pub.publish(distance_msg);
	
		rate.sleep();
	
	}
	
}
