/*
 * Author:		John Dixon
 * Assignment:	Project 1
 * Course:		CS 4375.501
 * Date:		17 Feb. 2019
 *
 * This header file defines statistical functions that are performed
 * on data sets in the form of vectors. These functions are implemented
 * as templates, but the underlying data type must support arithmetic
 * operators (+, -, *, /, +=, etc.) and comparison operators (<, <=, !=, etc.).
 */

#ifndef STAT_FUNC_H
#define STAT_FUNC_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

/*
 * Calculate the sum of all vector elements.
 */
template<class T>
T vector_sum(const vector<T> & v) {
	typename vector<T>::const_iterator it;
	T sum = 0;

	for (it = v.begin(); it != v.end(); ++it) {
		sum += *it;
	}
	return sum;
}

/*
 * Calculate the mean of all vector elements.
 */
template<class T>
double vector_mean(const vector<T> & v) {
	return (vector_sum(v) / v.size());
}

/*
 * Find the median vector element.
 */
template<class T>
double vector_median(vector<T> v) {
	sort(v.begin(), v.end());

	size_t mid = v.size() / 2;
	if ((v.size() % 2) == 1) {	// odd number of elements (1 median)
		return v[mid];
	} else {					// even number of elements (2 medians)
		return ((v[mid - 1] + v[mid]) / 2);	// mean of the 2 medians
	}
}

/*
 * Find the range (min and max) of the vector elements
 * and store these values in range array (r[0] = min, r[1] = max).
 */
template<class T>
void vector_range(const vector<T> & v, T range[2]) {
	range[0] = v.front();
	range[1] = v.back();
	typename vector<T>::const_iterator it;

	for (it = v.begin(); it != v.end(); ++it) {
		if (*it < range[0])
			range[0] = *it;
		else if (*it > range[1])
			range[1] = *it;
	}
}

/*
 * Calculate the covariance between x and y.
 */
template<class T>
double vector_cov(const vector<T> & x, const vector<T> & y) {
	double xmean = vector_mean<T>(x);
	double ymean = vector_mean<T>(y);
	double sum = 0;
	size_t length = min<size_t>(x.size(), y.size()); 	// can only use as many elements
														// as the smallest vector has
	for (size_t i = 0; i < length; ++i) {
		sum += ((x[i] - xmean) * (y[i] - ymean));
	}
	return (sum / (length - 1));
}

/*
 * Calculate the Pearson correlation coefficient between x and y.
 */
template<class T>
double vector_corr(const vector<T> & x, const vector<T> & y) {
	double cov = vector_cov(x, y);
	double xsd = sqrt(vector_cov(x, x));	// standard deviation of x
	double ysd = sqrt(vector_cov(y, y));	// standard deviation of y
	return (cov / (xsd * ysd));
}

/*
 * Calculate the mean squared error (MSE) between actual values
 * and predicted values.
 */
template<class T>
double vector_mse(const vector<T> & actual, const vector<T> & pred) {
	size_t length = min<size_t>(actual.size(), pred.size());
	double sum = 0;

	for (size_t i = 0; i < length; ++ i) {
		sum += pow((actual[i] - pred[i]), 2.0);
	}
	return (sum / length);
}

/*
 * This algorithm uses the ordinary least squares (OLS) method to estimate the
 * slope and y-intercept of the regression line which models the relationship
 * between the predictor variable x and the target variable y. The slope and
 * y-intercept are stored in the coef array.
 */
template<class T>
void vector_ols(const vector<T> & x, const vector<T> & y, double coef[2]) {
	double xmean = vector_mean<T>(x);
	double ymean = vector_mean<T>(y);
	double numerator = 0;
	double denominator = 0;
	size_t length = min<size_t>(x.size(), y.size()); 	// can only use as many elements
														// as the smallest vector has
	for (size_t i = 0; i < length; ++i) {
		numerator += ((x[i] - xmean) * (y[i] - ymean));
		denominator += pow((x[i] - xmean), 2.0);
	}
	coef[0] = (numerator / denominator);	// slope
	coef[1] = (ymean - (coef[0] * xmean));	// y-intercept
}

#endif /* STAT_FUNC_H */
