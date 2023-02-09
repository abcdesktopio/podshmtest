#!/bin/bash
cd /src/sysv
do=true
while $do
do
  H=$(./receiver)
  exit_code=$?
  if [ $exit_code -eq 0 ]; then
	echo $H
	do=false
	exit 0
  else
	echo "waiting 0.5s"
	sleep 0.5
  fi
done
exit 1
