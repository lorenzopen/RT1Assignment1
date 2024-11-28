UI.cpp: 

    Creation of a second turtle:
    At launch, a second turtle is created in the simulation (turtle2) positioned at specific coordinates, with a defined initial angle.

    Interactive user interface:
    The user can choose which turtle to control (turtle1 or turtle2) and specify the linear and angular velocities to move it, 
    after each movement command the velocities are reset to stop the turtle.
    
Distance.cpp 

    What it is done in this second node is to control and monitor the behavior of two turtles. The goal is to calculate the distance 
    between the turtles, managing their movements to prevent collisions, and ensuring they remain within a defined safe zone inside 
    the simulation window.

    It monitors the positions of both turtles by subscribing to their respective pose topics, it calculates the distance between 
    the turtles and publishes this data to a dedicated topic /turtledistance. If the turtles come too close to each other they are stopped by 
    publishing their velocities 0.0 and back off to not be stucked.

    If the turtle moves outside these limits, it is automatically guided back to the safe zone, based on its current position 
    and orientation.
    
How to Use

    - Start the ROS node and the turtlesim simulation.
    - Run the UI.cpp by using rosrun assignment1_rt node1
    - Run the Distance.cpp by using rosrun assignment1_rt node2
    - check the distance published rostopic echo /turtledistance
    
    Options will be shown in the terminal for:
        Select the turtle to control.
        Enter speed to move the chosen turtle.
    After entering the commands, the turtle will perform the required movement in the simulation and the node2 will 
    constantly check the distance and the margines.
