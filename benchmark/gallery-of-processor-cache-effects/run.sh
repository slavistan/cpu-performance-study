#!/usr/bin/env zsh

# Source functions required to lock cpu frequency
source ~/.oh-my-zsh/custom/functions.zsh

# Define binaries
build_dir="../../build"

raw_data_dir="./raw_data"
csv_dir="./analysis"

##
## Measurement 1
##
# cpuclk lock
# minstructor -o "${raw_data_dir}/impact-of-cache-lines" -f -n 25 "\"${build_dir}/impact-of-cache-lines [1,2,4,8,16,32,64,128,256,512,1024]\""
# cpuclk unlock
# mcollector -f -r -o "${csv_dir}/impact-of-cache-lines.csv" "${raw_data_dir}/impact-of-cache-lines"

##
## Measurement 2
##
cpuclk lock
minstructor -o "${raw_data_dir}/l1-and-l2-cache-sizes" -f -n 25 "\"${build_dir}/l1-and-l2-cache-sizes [1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576]\""
cpuclk unlock
mcollector -f -r -o "${csv_dir}/l1-and-l2-cache-sizes.csv" "${raw_data_dir}/l1-and-l2-cache-sizes"

