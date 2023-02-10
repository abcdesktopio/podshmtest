#!/bin/bash
# ipcs -m -i 0
cd /src/sysv
./receiver
while [ $? -ne 0 ]; do
    echo "this is an unlimited loop, waiting 5s"
    sleep 5
    ./receiver
done
