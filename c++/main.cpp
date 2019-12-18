/*
 * Author:		John Dixon
 * Assignment:	Project 1
 * Course:		CS 4375.501
 * Date:		17 Feb. 2019
 *
 * This program performs simple linear regression on data from a file
 * named "Boston.csv" located in the same directory. The first line of
 * the input file will contain the names of two vectors, and each
 * subsequent line will contain two floating point numbers separated
 * by a comma.
 */

#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

#include "stat_func.h"

int main() {
	char buffer[128];			// buffer for reading lines from input_file
	size_t i = 0;
	double d1, d2;
	clock_t start, stop, total;	// start, stop, and total times for clocking
	double coef[2];				// array for holding estimated coefficients of the model
	ifstream input_file;		// the input file stream
	vector<double> train_rm, test_rm;		// train and test vectors for rm column
	vector<double> train_medv, test_medv;	// train and test vectors for medv column
	vector<double> predict_medv;		// holds predicted medv values
	vector<double>::const_iterator it;	// vector iterator

	// open file
	input_file.open("Boston.csv");
	if (!input_file.is_open()) {
		cerr << "Error opening file\n";
		exit(0);
	}

	input_file.getline(buffer, sizeof(buffer));	// discard first line

	// read the first 400 rows as training data
	while (i < 400 && input_file.getline(buffer, sizeof(buffer))) {
		sscanf(buffer, "%lf,%lf", &d1, &d2);
		train_rm.push_back(d1);
		train_medv.push_back(d2);
		i++;
	}
	// read remaining rows as test data
	while (input_file.getline(buffer, sizeof(buffer))) {
		sscanf(buffer, "%lf,%lf", &d1, &d2);
		test_rm.push_back(d1);
		test_medv.push_back(d2);
	}

	// close file
	input_file.close();

	// train model using ols method (and clock it)
	start = clock();
	vector_ols(train_rm, train_medv, coef);
	stop = clock();
	total = (stop - start);

	// print the estimated coefficients
	printf("Coefficients\n");
	printf("\t(Intercept)\t%f\n", coef[1]);
	printf("\trm\t\t%f\n", coef[0]);

	// use the model to predict medv of test data
	for (it = test_rm.begin(); it != test_rm.end(); ++it) {
		d1 = coef[0] * (*it) + coef[1];		// y = mx + b
		predict_medv.push_back(d1);
	}

	// print time
	printf("\nElapsed time for linear regression: %f seconds\n",
			((double)total) / CLOCKS_PER_SEC);

	// print correlation, mse, and rmse between predicted medv and actual medv
	printf("Correlation:\t%f\n", vector_corr(test_medv, predict_medv));
	d1 = vector_mse(test_medv, predict_medv);
	printf("MSE:\t\t%f\n", d1);
	printf("RMSE:\t\t%f\n", sqrt(d1));

	return 0;
}
