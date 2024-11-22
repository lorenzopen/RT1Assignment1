UI.cpp: 

    Creation of a second turtle:
    At launch, a second turtle is created in the simulation (turtle2) positioned at specific coordinates, with a defined initial angle.

    Interactive user interface:
    The user can choose which turtle to control (turtle1 or turtle2) and specify the linear and angular velocities to move it, 
    after each movement command the velocities are reset to stop the turtle.

How to Use

    - Start the ROS node and the turtlesim simulation.
    - Run the UI.cpp by using rosrun assignment1_rt node1
    Options will be shown in the terminal for:
        Select the turtle to control.
        Enter speed to move the chosen turtle.
    After entering the commands, the turtle will perform the required movement in the simulation.
