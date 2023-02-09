#!/bin/bash
cd /src/sysv
do=true
while $do
do
  H=$(./receiver)
  exit_code=$?
  if [ $exit_code -eq 0 ]; then
	do=false
	exit 0
  else
	sleep 0.5
  fi
done
exit 1
