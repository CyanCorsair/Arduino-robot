Arduino-robot
=============

Code for my Arduino robot.

It is a simple autonomous obstacle avoidance rover, which uses an ultrasonic sensor to ping surfaces. 
When it gets within 30cm or less of an obstacle, it will stop, reverse and use the servo the sensor is mounted on
to pick up distance data from the left and right, then store those in variables before making a decision where
to turn.

The next stages of development forsee the inclusion of legs and the abandonment of wheels.
