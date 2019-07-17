library(tidyverse)

args <- commandArgs(trailingOnly = T)
indata <- args[1]
outfile <- args[2]

print(indata)
print(outfile)

df <- read.csv(indata, comment.char = '#', header = T)
ggplot(df %>% filter(metric == "mean")) +
  geom_line(aes(x = stride, y = cpu_time))

ggsave(outfile)
