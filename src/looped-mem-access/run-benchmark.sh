#!/usr/bin/sh

[ -z "$2" ] && echo "Usage: $0 /path/to/binary /path/to/out.csv" && exit 1

bin_path="$1" # benchmark binary
csv_path="$2" # benchmark's csv output

# Hack: Disable CPU frequency scaling. This requires that the cpupower command
# does not require a sudo password.
sudo cpupower frequency-set --governor performance
sleep 3

# run benchmark and store output verbatim into buffer file 
$bin_path \
  --benchmark_repetitions=5 \
  --benchmark_report_aggregates_only=true \
  --benchmark_out_format=csv \
  --benchmark_out=$csv_path"_raw"

# format output into a suitable form
cat $csv_path"_raw" \
  | sed '1,/^name,iteration/ s/^/#/g' \
  | sed 's/^#name,iteration/name,iteration/g' \
  | sed '/median/ d' \
  | sed 's/^name/stride,metric/g' \
  | sed 's:^\(".*/\)\([0-9]\+\)_\(.*\)":\2,\3:g' \
  > $csv_path

sudo cpupower frequency-set --governor powersave
