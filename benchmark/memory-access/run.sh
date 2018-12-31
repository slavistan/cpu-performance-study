#!/usr/bin/env zsh

source ~/.oh-my-zsh/custom/functions.zsh

binary_release="../../build/memory-access"
binary_debug="../../build_debug/memory-access"

raw_data_dir="./raw_data"
csv_dir="./analysis/data.csv"

cpuclk lock
minstructor -o ${raw_data_dir} -f -n 25 "${binary_release} [1,2,4,8,16,32,64,128,256,512,1024]"
cpuclk unlock
mcollector -f -r -o ./analysis/data.csv ${raw_data_dir}

