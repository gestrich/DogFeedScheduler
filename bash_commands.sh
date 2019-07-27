
alias dogdir="cd ~/dev/DogFeedScheduler;"
alias update="cd ~/dev/DogFeedScheduler; git --git-dir ~/dev/DogFeedScheduler/.git pull"
alias build="cd ~/dev/DogFeedScheduler; g++ -Wall -std=c++11 -o DogFeeder ~/dev/DogFeedScheduler/*.cpp ~/dev/DogFeedScheduler/libraries/RaspberryPi-mcp3008Spi/mcp3008Spi.cpp -lwiringPi;"
alias run="cd ~/dev/DogFeedScheduler; ./DogFeeder $1"
