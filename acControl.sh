#!/bin/bash

# Note: At the season, I had to run this command 1 time: sudo /etc/init.d/lircd restart
# I found that from this site: https://stackoverflow.com/questions/37897868/lirc-irsend-could-not-connect-to-socket-irsend-no-such-file-or-directory

function status(){
  now="$(date +%s)"; 
  lastMotion="$(cat /home/pi/Desktop/ac_motion.txt)"
  secondsBetween=$(($now - $lastMotion))
  if [[ secondsBetween -lt 5 ]]; then
    echo 1
  else
    echo 0 
  fi
}

function turnOn(){
  isOn="$(status)"
  #if [[ isOn -eq 0 ]]; then
    ~/dev/DogFeedScheduler/remote_command.sh haier Power 
  #fi
}

function turnOff(){
  isOn="$(status)"
  #if [[ isOn -eq 1 ]]; then
    ~/dev/DogFeedScheduler/remote_command.sh haier Power 
  #fi
}

# Check if the function exists (bash specific)
if declare -f "$1" > /dev/null
then
  # call arguments verbatim
  "$@"
else
  # Show a helpful error
  echo "***Usage***"
  echo "status"
  exit 1
fi
