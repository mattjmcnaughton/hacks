library("matrixStats");

# Path should be relative to root directory.
state <- read.csv(file="data/state.csv")

mean(state[["Population"]])
median(state[["Population"]])
weighted.mean(state[["Murder.Rate"]], w=state[["Population"]])
weightedMedian(state[["Murder.Rate"]], w=state[["Population"]])
