#!/usr/bin/sh

# Pre-format CSV output.

bin="$1"
outfile="$2"

$bin \
  --benchmark_repetitions=2 \
  --benchmark_report_aggregates_only=true \
  --benchmark_format=csv | \
  sed '2,/median/ d' | \
  sed '1,1 s/^name/stride,metric/g' | \
  sed 's:^\(".*/\)\(.\)_\(.*\)":\2,\3:g' \
  > $outfile
