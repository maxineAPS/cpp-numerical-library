#include <iostream>
#include "MyMatrix.h"
#include "MyToolset.h"
#include "ctime"
#include "MyMatrixLibrary_MySparseMatrix.h"
#include "MyGraph.h"
#include <cmath>


// Create Polynomial A up to max degree
Matrix CreatePolynomialA(const Matrix& xData, int degree) {
    Matrix A(xData.m, degree + 1);
    
    // For each value up to max degree
    for (int i = 0; i < xData.m; i ++) {
        for (int j = 0; j < degree + 1; j ++) {
            // Raise x to that power
            A(i, j) = pow(xData(i, 0), j);
        }
    }
    return A;
}


// Approximate thetas based on input data and a max degree
Matrix ApproximateFunction(Matrix& Data, int degree) {
    
    // Obtain values and labels
    Matrix xData = Data.Block(0, 0, Data.m, 1);
    Matrix yData = Data.Block(0, 1, Data.m, 1);
    
    // Train the thetas
    Matrix A = CreatePolynomialA(xData, degree);
    Matrix theta(degree + 1, 1);
    SolveQR1(A, yData, theta);
    return theta;
}


// Output fX = 3x^3 + x^2 + 4
double fX(double x) {
    return 3 * pow(x, 3) + pow(x, 2) + 4;
}


// Populate training data
Matrix createFunctionData(int num_rows) {
    Matrix data(num_rows, 2);
    for (int i = 0; i < num_rows; i ++) {
        int x = rand() % 10;
        data(i, 0) = x;
        data(i, 1) = fX(x);
    }
    return data;
}


// Return mean squared error
double MSE(Matrix &a, Matrix &b) {
    Matrix c = a-b;
    double total = 0;
    for (int i = 0; i < c.m; i ++) {
        for (int j = 0; j < c.n; j ++) {
            total += pow(c(i, j), 2);
        }
    }
    return total/c.data.size();
}


// Tester code for function approximation with cubic function
double testFunction() {
    
    // Generate Data
    Matrix train_data = createFunctionData(1000);
    Matrix theta = ApproximateFunction(train_data, 3);
    Matrix test_data = createFunctionData(200);
    
    // Train
    Matrix test_xs = test_data.Block(0, 0, 200, 1);
    Matrix test_ys = test_data.Block(0, 1, 200, 1);
    Matrix A = CreatePolynomialA(test_xs, 3);
    
    // Get results
    Matrix results = A*theta;
    double mse = MSE(test_ys, results);
    return mse;
    
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Read in training data from directory
Matrix GenerateData(const string& data_dict, int num_data_rows) {
    Matrix train_data(num_data_rows, 785);
    int tempint;
    ifstream file(data_dict+"/train_data.txt");
    if (!file.is_open()) std::cout<<"file does not exist"<<std::endl;
    
    // For every row in file, get value
    for(int i=0;i<num_data_rows;i++) {
        for (int j = 0; j < 784; j ++) {
            if(file >> tempint) {
                train_data(i, j)=(double)tempint/255.0;
            }
        }
    }
    file.close();
    
    // Add random value to each to prevent singularity
    for (int i = 0; i < train_data.m; i ++) {
        for (int j = 0; j < train_data.n; j ++) {
            train_data(i, j) += rand()%10 * 0.011;
        }
        train_data(i, 784) = 1;
    }
    return train_data;
}


// Read in test data
Matrix GetTestData(const string& data_dict, int num_data_rows) {
    
    Matrix train_data(num_data_rows, 785);
    int tempint;
    ifstream file(data_dict+"/test_data.txt");
    if (!file.is_open()) std::cout<<"file does not exist"<<std::endl;
    
    // For each line, get value
    for(int i=0;i<num_data_rows;i++) {
        for (int j = 0; j < 784; j ++) {
            if(file >> tempint) {
                train_data(i, j)=(double)tempint/255.0;
            }
        }
        
    }
    file.close();
    
    // Add random value to prevent singularity
    for (int i = 0; i < train_data.m; i ++) {
        for (int j = 0; j < train_data.n; j ++) {
            train_data(i, j) = train_data(i, j) + rand()%10 * 0.011;
        }
        // Add bias
        train_data(i, 784) = 1;
    }
    return train_data;
}
        

// Get labels from file
Matrix Get_Labels(const string& data_dict, int num_data_rows) {
    
    Matrix label_matrix(num_data_rows, 10);
    for (int i = 0; i < label_matrix.m; i ++) {
        for (int j = 0; j < label_matrix.n; j ++) {
            label_matrix(i, j) = - 1;
        }
    }
    
    vector<int> train_labels;
    int tempint;
    ifstream file(data_dict+"/train_labels.txt");
    if (!file.is_open()) std::cout<<"file does not exist"<<std::endl;
    for(int i=0;i<num_data_rows;i++) if(file >> tempint) train_labels.push_back(tempint);
    file.close();
       
    // One_hot encoding
    for (int i = 0; i < train_labels.size(); i ++) {
        label_matrix(i, train_labels[i]) = 1;
    }
    return label_matrix;
}


// Train theta for images
Matrix TrainThetaImages(const string& data_dict, int num_data_rows) {

    // Get all data
    Matrix Data = GenerateData(data_dict, num_data_rows);
    Matrix Labels = Get_Labels(data_dict, num_data_rows);
    Matrix theta(Data.n, 10);
    
    // Train theta columns one by one
    for (int i = 0; i < 10; i ++) {
        Matrix labels_column = Labels.Block(0, i, Labels.m, 1);
        Matrix theta_column(Data.n, 1);
        
        clock_t start = clock();
        SolveLeastSquares(Data, labels_column, theta_column);
        clock_t end = clock();
        cout << "\nTime cost for SolveLeastSquares (which calculates A^TA and A^Tb and solves A^TAx = A^b): " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
        
        // Copy over theta column to master theta
        for (int i_ = 0; i_ < theta.m; i_ ++) {
            theta(i_, i) = theta_column(i_, 0);
        }
    }
    return theta;
}


// Get testing labels, same as get training labels
Matrix Get_Test_Labels(const string& data_dict, int num_data_rows) {
    
    Matrix label_matrix(num_data_rows, 10);
    for (int i = 0; i < label_matrix.m; i ++) {
        for (int j = 0; j < label_matrix.n; j ++) {
            label_matrix(i, j) = - 1;
        }
    }
    
    vector<int> train_labels;
    int tempint;
    ifstream file(data_dict+"/test_labels.txt");
    if (!file.is_open()) std::cout<<"file does not exist"<<std::endl;
    for(int i=0;i<num_data_rows;i++) if(file >> tempint) train_labels.push_back(tempint);
    file.close();
       
    for (int i = 0; i < train_labels.size(); i ++) {
        label_matrix(i, train_labels[i]) = 1;
    }
    return label_matrix;
}


// Convert one_hot encoded back to real values
Matrix getRealVals(Matrix& encoded) {
    Matrix real(encoded.m, 1);
    for (int i = 0; i < real.m; i ++) {
        double max = -100;
        int index = 0;
        
        // value = argmax(matrix row)
        for (int j = 0; j < encoded.n; j ++) {
            if (encoded(i, j) > max) {
                index = j;
                max = encoded(i, j);
            }
        }
        real(i, 0) = index;
    }
    return real;
}


// Check how many are correct
double GetAccuracy(Matrix& A, Matrix& B) {
    double total = 0;
    for (int i = 0; i < A.m; i ++) {
        if (A(i, 0) == B(i, 0)) {
            total += 1;
        }
    }
    return total/A.m;
}


// Driver for images
double testImages(string data_dir) {
    
    // Get all data
    Matrix theta = TrainThetaImages(data_dir, 1000);
    Matrix test_data = GetTestData(data_dir, 200);
    Matrix test_ys = Get_Test_Labels(data_dir, 200);
    Matrix results = test_data*theta;
    
    // Get results
    Matrix real_ys = getRealVals(test_ys);
    Matrix result_ys = getRealVals(results);
    double accuracy = GetAccuracy(real_ys, result_ys);
    //double mse = MSE(test_ys, results);
    return accuracy;
    
    
}




