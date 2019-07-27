alias dogdir="cd ~/dev/DogFeedScheduler;"
alias update="cd ~/dev/DogFeedScheduler; git --git-dir ~/dev/DogFeedScheduler/.git pull"
if [ "$SPI_DISABLED" = "1" ]; then
  alias build="cd ~/dev/DogFeedScheduler; g++ -Wall -std=c++11 -o DogFeeder ~/dev/DogFeedScheduler/*.cpp -D"WIRING_PI_DISABLED=${WIRING_PI_DISABLED}" -D"SPI_DISABLED=${SPI_DISABLED}";"
  else
  alias build="cd ~/dev/DogFeedScheduler; g++ -Wall -std=c++11 -o DogFeeder ~/dev/DogFeedScheduler/*.cpp ~/dev/DogFeedScheduler/libraries/RaspberryPi-mcp3008Spi/mcp3008Spi.cpp -lwiringPi -D"WIRING_PI_DISABLED=${WIRING_PI_DISABLED}";"
fi 

alias run="cd ~/dev/DogFeedScheduler; ./DogFeeder $1"
