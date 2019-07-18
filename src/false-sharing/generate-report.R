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
  geom_point(aes(x = threads, y = cpu_time)) +
  facet_wrap(~scheme, scales="free") +
  theme(axis.ticks.y = element_blank(),
        axis.text.y = element_blank())

ggsave(outfile)
