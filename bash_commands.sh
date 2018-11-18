alias update="cd ~/dev/DogFeedScheduler; git --git-dir ~/dev/DogFeedScheduler/.git pull"
alias build="cd ~/dev/DogFeedScheduler; g++ -Wall -std=c++11 -o DogFeeder ~/dev/DogFeedScheduler/DogFeedScheduler/DogFeedScheduler/*.cpp -lwiringPi;"
alias run="cd ~/dev/DogFeedScheduler; ./DogFeeder dog"
