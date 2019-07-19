# Generate a report from CSV data

args <- commandArgs(trailingOnly = T)
if (length(args) < 2) {
  stop(paste0("Usage: Rscript generate-report.R ",
               " \"/path/to/data.csv\"",
               " \"/path/to/report.pdf\""))
}

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
