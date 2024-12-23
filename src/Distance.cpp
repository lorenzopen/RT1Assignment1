#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Twist.h"


double turtle1_posex, turtle1_posey, turtle1_theta;
double turtle2_posex, turtle2_posey, turtle2_theta;

void turtle1PoseCallback(const turtlesim::Pose::ConstPtr& msg){
    turtle1_posex = msg->x;
    turtle1_posey = msg->y;
    turtle1_theta = msg->theta;
}

void turtle2PoseCallback(const turtlesim::Pose::ConstPtr& msg){
    turtle2_posex = msg->x;
    turtle2_posey = msg->y;
    turtle2_theta = msg->theta;
}

double InvertVelIfTurtleFlipped(double theta, double min_Ang, double max_Ang){
	if(theta > min_Ang && theta < max_Ang){ return 0.3; }
	else{ return -0.3; }	
}

void moveBackToSafeZone(double& pos_x, double& pos_y, double& theta, ros::Publisher &pub, double boundary_min, double boundary_max) {
    geometry_msgs::Twist vel_msg;
    bool is_out_of_bounds = false;
   

    if (pos_y < boundary_min) {
    	vel_msg.linear.x = InvertVelIfTurtleFlipped(theta, 0.0, 3.14);
        is_out_of_bounds = true;
    }
    else if (pos_x < boundary_min) {
    	vel_msg.linear.x = InvertVelIfTurtleFlipped(theta, -1.57, 1.57);
        is_out_of_bounds = true;
    }
    else if (pos_x > boundary_max) {
    	vel_msg.linear.x = InvertVelIfTurtleFlipped(theta, 1.57, -1.57);
        is_out_of_bounds = true;
    }
    else if (pos_y > boundary_max) {
        vel_msg.linear.x = InvertVelIfTurtleFlipped(theta, 3.14, 0.0);
        is_out_of_bounds = true;
    }

    if (is_out_of_bounds) {
        vel_msg.angular.z = 0.0;
        pub.publish(vel_msg);
        ros::Duration(1.0).sleep();
    }
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
		
			vel_msg.linear.x= -0.1;
			turtle1_pub.publish(vel_msg);
			turtle2_pub.publish(vel_msg);
			
			ros::Duration(1.0).sleep();
			
			vel_msg.linear.x = 0.0;
			vel_msg.angular.z = 0.0;
			
			turtle1_pub.publish(vel_msg);
			turtle2_pub.publish(vel_msg);
			
		}
		
		moveBackToSafeZone(turtle1_posex, turtle1_posey, turtle1_theta, turtle1_pub, 1.0, 10.0);
       	moveBackToSafeZone(turtle2_posex, turtle2_posey, turtle2_theta, turtle2_pub, 1.0, 10.0);

		
		rate.sleep();
	
	}
	
	
	
	
}
