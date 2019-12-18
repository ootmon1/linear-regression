# Program:      Project 1
# Author:       John Dixon
# Date:         17 Feb. 2019
# Description:  Linear regression using the Boston data set.

# get Boston data frame from MASS library
library(MASS)
df <- Boston[]

# explore the Boston data set
str(df) # show structure of df
summary(df) # show stats for each column
sapply(df, function(x) sum(is.na(x) == TRUE)) # count NAs in each column
head(df, n = 10) # show first 10 rows

# visualize the data set

pairs(df) # show correlation between columns
# plot rm and medv on scatterplot
plot(df$rm, df$medv, main = "Median Home Value vs Avg. Number of Rooms",
     xlab = "Avg. Number of Rooms", ylab = "Median Home Value (in $1000s)")

# separate data into train/test
train <- df[c(1:400),]
test <- df[c(401:506),]

# train linear regression model and record start/end time
start_time <- proc.time()
lm1 <- lm(medv ~ rm, data = train)
end_time <- proc.time()

# calculate elapsed time for linear regression algorithm
lr_time <- (end_time[3] - start_time[3])

# print model coefficients
summary(lm1)

# predict test values
pred <- predict(lm1, newdata = test)

# evaluate test predictions
corr <- cor(pred, test$medv)
mse <- mean((pred - test$medv)^2)
rmse <- sqrt(mse)

# print results
print(paste("Elapsed time for linear regression:", lr_time, "seconds"))
print(paste("Correlation:", corr))
print(paste("MSE:", mse))
print(paste("RMSE:", rmse))
