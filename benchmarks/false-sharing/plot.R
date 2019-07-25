# Generate a report from CSV data

csv.path <- args[1]
outfile <- args[2]

# TODO: Add errorbars
library(tidyverse)
df <- read.csv(csv.path, comment.char = '#', header = T)
ggplot(df %>% filter(metric == "mean", scheme == "nosharing")) +
  geom_line(aes(x = threads, y = cpu_time)) +
  theme(aspect.ratio = 9/16)

ggsave(paste0(outfile,"1.png"),   height=4.5, width=8)

df <- read.csv(csv.path, comment.char = '#', header = T)
ggplot(df %>% filter(metric == "mean", scheme == "falsesharing")) +
  geom_line(aes(x = threads, y = cpu_time)) +
  theme(aspect.ratio = 9/16)

ggsave(paste0(outfile,"2.png"),   height=4.5, width=8)
