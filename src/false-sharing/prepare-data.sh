#!/usr/bin/sh

if [ -z "$2" ]; then
  outfile=/dev/stdout
else
  outfile=$2
fi

cat "$1" \
  | sed '1,/^name,iteration/ s/^/#/g' \
  | sed 's/^#name,iteration/name,iteration/g' \
  | sed '/median/ d' \
  | sed 's/^name/scheme,threads,metric/g' \
  | tr -d '"' \
  | sed 's|\([[:alnum:]]\+\)/\([[:digit:]]\+\)_\([[:alnum:]]\+\)|\1,\2,\3|g' \
  > $outfile
