#!/bin/bash

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
  if [[ isOn -eq 0 ]]; then
    ~/dev/DogFeedScheduler/remote_command.sh haier Power 
  fi
}

function turnOff(){
  isOn="$(status)"
  if [[ isOn -eq 1 ]]; then
    ~/dev/DogFeedScheduler/remote_command.sh haier Power 
  fi
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
