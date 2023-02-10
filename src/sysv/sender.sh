#!/bin/bash
if [ ! -z "$FTOK_PATH" ]; then
 	touch $FTOK_PATH
fi
/src/sysv/sender
# ipcs -m -i 0
