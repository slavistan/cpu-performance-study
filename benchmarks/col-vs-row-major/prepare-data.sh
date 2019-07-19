#!/usr/bin/sh

[ -z "$2" ] && echo "Usage: $0 /path/to/raw.csv /path/to/prepared.csv" && exit 1

cat "$1" \
  | sed '1,/^name,iteration/ s/^/#/g' \
  | sed 's/^#name,iteration/name,iteration/g' \
  | sed '/median/ d' \
  | sed 's/^name/scheme,matrixdim,metric/g' \
  | tr -d '"' \
  | sed 's:jor/\([[:digit:]]\+\)_:jor,\1,:g' \
  > "$2"
