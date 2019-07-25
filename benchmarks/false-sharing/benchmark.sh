#!/usr/bin/sh

if [ "$1" = "run" ]; then

  # run benchmark and store unformatted output
  bin_path="$2"
  rawcsv_path="$3"
  $bin_path \
    --benchmark_repetitions=5 \
    --benchmark_report_aggregates_only=true \
    --benchmark_out_format=csv \
    --benchmark_format=csv \
    --benchmark_out="$rawcsv_path"
  exit 0

elif [ "$1" = "format" ]; then

  # extend and format raw csv data
  raw_data="$2"
  formatted_data="$3"
  cat "$raw_data" \
    | sed '1,/^name,iteration/ s/^/#/g' \
    | sed 's/^#name,iteration/name,iteration/g' \
    | sed '/median/ d' \
    | sed 's/^name/scheme,matrixdim,metric/g' \
    | tr -d '"' \
    | sed 's:jor/\([[:digit:]]\+\)_:jor,\1,:g' \
    > "$formatted_data"
  exit 0

elif [ "$1" = "report" ]; then

  formatted_data="$2"
  out_dir="$3"
  Rscript "$(dirname $(realpath $0))/plot.R" "$formatted_data" "$out_dir"
  exit 0

else

  echo "Usage: $0 <run|format|report> <input> <output>"
  exit 0

fi
