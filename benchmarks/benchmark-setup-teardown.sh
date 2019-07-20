#!/usr/bin/sh

# Defines routines to be run before and after every benchmark

if [ "$1" = "setup" ]; then
  sudo cpupower frequency-set --governor performance
elif [ "$1" = "teardown" ]; then
  sudo cpupower frequency-set --governor powersave
else
  echo "Usage: $0 <setup|teardown>"
  exit 1
fi
