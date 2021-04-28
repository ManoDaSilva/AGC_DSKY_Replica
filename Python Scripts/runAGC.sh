#!/bin/bash
echo "Enabling numlock"
/usr/bin/setleds +num

echo "Starting VirtualAGC"
screen -dm bash -c "cd /home/pi/virtualagc/yaAGC/; ./yaAGC --port=19697 --core=../Colossus249/Colossus249.bin"

echo "Starting DSKY"
cd /home/pi/virtualagc/piPeripheral/
python2 manoDSKY.py
