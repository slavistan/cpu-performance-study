#!/usr/bin/sh

[ -z "$2" ] && echo "Usage: $0 /path/to/binary /path/to/out.csv" && exit 1

bin_path="$1" # benchmark binary
rawcsv_path="$2" # benchmark's csv output

# Hack: Disable CPU frequency scaling. This requires that the cpupower command
# does not require a sudo password.
sudo cpupower frequency-set --governor performance
sleep 3

# run benchmark and store output verbatim into buffer file
$bin_path \
  --benchmark_repetitions=5 \
  --benchmark_report_aggregates_only=true \
  --benchmark_out_format=csv \
  --benchmark_format=csv \
  --benchmark_out="$rawcsv_path"

sudo cpupower frequency-set --governor powersave
