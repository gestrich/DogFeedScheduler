irsend SEND_ONCE $1 $2 &
sleep 2
killall irsend #Hack for irsend locking up
#irsend SEND_ONCE $1 $2 &
#screen -d -m -S "AC script" bash -c "sleep 10; killall irsend;"
