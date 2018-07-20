# DogFeedScheduler

Experiment with Raspberry Pi and hardware. A python prototype is included. Rewriting in C++.
Works with Raspberry Pi to track dog feeding schedule.
Monitors signal from hall sensor linked to a cabinet drawer.
Each time drawer is opened, a feeding event is tracked.
Single LED lights when feeding is due. Blinks when drawer is open, reminding you to shut.
Lights LED 7 segment display showing number of feedings completed so far today.
Button to decrement feeding events if you open the the drawer but didn't do a feeding.

