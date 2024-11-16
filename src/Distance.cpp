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

	ros::Subscriber turtle1_pose = node2.subscribe("/turtle1/pose", 10, turtle1PoseCallback);
	ros::Subscriber turtle2_pose = node2.subscribe("/turtle2/pose", 10, turtle2PoseCallback);
	ros::Publisher distance_pub = node2.advertise<std_msgs::Float32>("/turtledistance", 10);
	
	ros::Publisher turtle1_pub = node2.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
	ros::Publisher turtle2_pub = node2.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);
	
	
	geometry_msgs::Twist vel_msg;      

	double distance;
	std_msgs::Float32 distance_msg;
	ros::Rate rate(10);

	while(ros::ok()){	
		ros::spinOnce();
	
		distance = sqrt(pow((turtle1_posex - turtle2_posex),2) + pow((turtle1_posey - turtle2_posey),2));
		distance_msg.data = distance;
		distance_pub.publish(distance_msg);
			
		if (distance <= 1.0){
		
			vel_msg.linear.x = 0.0;
			vel_msg.angular.z = 0.0;
			
			turtle1_pub.publish(vel_msg);
			turtle2_pub.publish(vel_msg);
			
		}
		
		if (turtle1_posex < 1.0 || turtle1_posey < 1.0 || turtle1_posex > 10.0 || turtle1_posey > 10.0) {
			
			vel_msg.linear.x = 0.0;
			vel_msg.angular.z = 0.0;
			
			turtle1_pub.publish(vel_msg);	
		}
		
		if (turtle2_posex < 1.0 || turtle2_posey < 1.0 || turtle2_posex > 10.0 || turtle2_posey > 10.0){
		
			vel_msg.linear.x = 0.0;
			vel_msg.angular.z = 0.0;
			
			turtle2_pub.publish(vel_msg);
			
		}
		
		rate.sleep();
	
	}
	
	
	
	
}
