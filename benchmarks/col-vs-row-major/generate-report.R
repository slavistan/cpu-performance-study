# Generate a report from CSV data

args <- commandArgs(trailingOnly = T)
csv.path <- args[1]

library(tidyverse)
df <- read.csv(csv.path, comment.char = '#', header = T) %>% 
  as_tibble %>%
  select(c(scheme, matrixdim, metric, cpu_time)) %>%
  spread(scheme, cpu_time) %>%
  rename(colmaj_time = colmajor) %>%
  rename(rowmaj_time = rowmajor) %>%
  mutate(rel_time = colmaj_time / rowmaj_time) %>%
  mutate(size_in_mega_bytes = (matrixdim ^ 2 * 8) / 1E6)

plt <- ggplot(df %>% filter(metric == "mean")) +
  geom_line(aes(x = size_in_mega_bytes, y = rel_time), color="darkgreen", size=1) +
  scale_y_continuous(limits=c(1,10), breaks=0:13, minor_breaks = c()) +
  scale_x_log10(breaks = 10 ^ seq(-6, 14)) +
  labs(x = "Image Size [MB]", y = "Slowdown") +
  theme(aspect.ratio = 9/16)

ggsave(args[2], height=4.5, width=8)
