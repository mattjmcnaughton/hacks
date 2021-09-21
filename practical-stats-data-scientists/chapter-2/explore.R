library(boot)
library(dplyr)

loans_income <- read.csv(file="data/loans_income.csv")[,1]
glimpse(loans_income)

# Bootstrapping works as follows:
# Assume that we have a sample of size `n` - in this case, it's `loans_income`.
# We have a sample of `n` loan incomes, which is a subset of the total N loans
# income which have ever been issued.
#
# 1. Draw a sample value from the sample, record, and replace it.
# 2. Repeat n times (where n is equal to the sample size).
# 3. Calculate the sample metric (i.e. mean, median, etc...) of the n resampled
# values.
# 4. Repeat steps 1-3 R times.
# 5. Use R results to calculate std dev of sample metric (i.e mean, median,
# etc...)
stat_fun <- function(x, idx) median(x[idx])
boot_obj <- boot(loans_income, R = 1000, statistic=stat_fun)

boot_obj
