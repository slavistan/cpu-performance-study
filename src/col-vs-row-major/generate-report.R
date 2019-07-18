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
  geom_line(aes(x = matrixdim, y = cpu_time, color = scheme)) +
  scale_y_log10(breaks = 10 ^ (0:11)) +
  scale_x_log10(breaks = 2 ^ (0:30))

ggsave(outfile)
