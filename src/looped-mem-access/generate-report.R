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
ggplot(df %>% filter(metric == "mean")) +
  geom_point(aes(x = stride, y = cpu_time)) +
  scale_x_continuous(breaks = c(1, seq(8, 64, 8)))

ggsave(outfile)
