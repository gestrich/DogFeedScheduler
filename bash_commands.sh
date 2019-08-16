alias dogdir="cd ~/dev/DogFeedScheduler;"
alias update="cd ~/dev/DogFeedScheduler; git --git-dir ~/dev/DogFeedScheduler/.git pull"
if [ "$SPI_DISABLED" = "1" ]; then
	alias build="cd ~/dev/DogFeedScheduler; g++ -Wall -std=c++11 -o DogFeeder ~/dev/DogFeedScheduler/*.cpp -D"WIRING_PI_DISABLED=${WIRING_PI_DISABLED}" -D"SPI_DISABLED=${SPI_DISABLED}";"
else
	#This part -D"WIRING_PI_DISABLED=${WIRING_PI_DISABLED} is still setting WIRING_PI_DISABLED even when not defined
	#alias build="cd ~/dev/DogFeedScheduler; g++ -Wall -std=c++11 -o DogFeeder ~/dev/DogFeedScheduler/*.cpp ~/dev/DogFeedScheduler/libraries/RaspberryPi-mcp3008Spi/mcp3008Spi.cpp -lwiringPi -D"WIRING_PI_DISABLED=${WIRING_PI_DISABLED}";"
	alias build="cd ~/dev/DogFeedScheduler; g++ -Wall -std=c++11 -o DogFeeder ~/dev/DogFeedScheduler/*.cpp ~/dev/DogFeedScheduler/libraries/RaspberryPi-mcp3008Spi/mcp3008Spi.cpp -lwiringPi;"
fi 

alias run="cd ~/dev/DogFeedScheduler; ./DogFeeder $1"
