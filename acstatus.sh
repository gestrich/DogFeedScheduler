#!/bin/bash

now="$(date +%s)"; 
lastMotion="$(cat /home/pi/Desktop/ac_motion.txt)"
secondsBetween=$(($now - $lastMotion))
if [[ secondsBetween -lt 5 ]]; then
  echo 1
else
  echo 0 
fi
