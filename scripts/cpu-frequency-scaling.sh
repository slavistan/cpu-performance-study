#!/usr/bin/sh

if [ "$1" = "off" ]; then
  sudo cpupower frequency-set --governor performance > /dev/null
  echo "cpupower: disabled frequency scaling."
elif [ "$1" = "on" ]; then
  sudo cpupower frequency-set --governor powersave > /dev/null
  echo "cpupower: enabled frequency scaling."
else
  echo "Usage: $0 <on|off>"
  exit 1
fi
