library(dplyr)
library(ggplot2)
library(hexbin)
library(matrixStats)

# When creating images, don't generate PDF.
pdf(NULL)

# Path should be relative to root directory.
state <- read.csv(file="data/state.csv")
sp500_px <- read.csv(file="data/sp500_px.csv")
sp500_sym <- read.csv(file="data/sp500_sym.csv", stringsAsFactors = FALSE)
kc_tax <- read.csv(file="data/kc_tax.csv")

glimpse(state)
glimpse(sp500_px)
glimpse(sp500_sym)
glimpse(kc_tax)

# Sample exploratory stats
mean(state[["Population"]])
median(state[["Population"]])
weighted.mean(state[["Murder.Rate"]], w=state[["Population"]])
weightedMedian(state[["Murder.Rate"]], w=state[["Population"]])

# Code for plotting telecoms
telecom <- sp500_px[, sp500_sym[sp500_sym$sector=="telecommunications_services", 'symbol']]
telecom <- telecom[row.names(telecom)>"2021-07-01", ]
png("/tmp/telecom_plot.png")
plot(telecom$T, telecom$VZ, xlab="T", ylab="VZ")
dev.off()

# Code for examining multiple facets
## Similar to kc_tax[kc_tax$TaxAssessedValue < 750000 ...] or `filter` from the
## dplyr library.
kc_tax0 <- subset(kc_tax, TaxAssessedValue < 750000 & SqFtTotLiving > 100 & SqFtTotLiving < 3500)
png("/tmp/kc_living_facet.png")
ggplot(subset(kc_tax0, ZipCode %in% c(98188, 98105, 98108, 98126)), aes(x=SqFtTotLiving, y=TaxAssessedValue)) +
  stat_binhex(colour="white") +
  theme_bw() +
  scale_fill_gradient(low="white", high="blue") +
  labs(x="Finished Square Feet", y="Tax Assessed Value") +
  facet_wrap("ZipCode")
dev.off()
