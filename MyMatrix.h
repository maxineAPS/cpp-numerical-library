//////////////////////////////////////////////////////////////////////////
////Dartmouth CS70.01 sample code
////http://www.dartmouth.edu/~boolzhu/cosc70.01.html
////Linear algebra and vector math library
//////////////////////////////////////////////////////////////////////////
#ifndef __MyMatrix_h__
#define __MyMatrix_h__
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>


using namespace std;

class Matrix
{
public:
    int m;                        ////number of rows
    int n;                        ////number of columns
    vector<double> data;        ////element values, we use double for the data type

    ////matrix constructor
    Matrix(const int _m=1,const int _n=1)
    {
        Resize(_m,_n);
    }

    void Resize(const int _m,const int _n)
    {
        m=_m;
        n=_n;
        
        //resize data list and set every element to 0
        data.resize(m*n);
        for(int i=0;i<m*n;i++){
            data[i]=0.;
        }
    }

    ////A=B
    void operator = (const Matrix& B)
    {
        // resize matrix and copy over data
        Resize(B.m,B.n);
        for(int i=0;i<(int)data.size();i++){
            data[i]=B.data[i];
        }
    }

    ////A={1.,4.,2.,...}, assigning a std::vector to A. A should initialized beforehand
    void operator = (const vector<double>& input_data)
    {
        assert(input_data.size()<=data.size());
        for(int i=0;i<(int)input_data.size();i++){
            data[i]=input_data[i];
        }
    }
    
    ////return whether A==B
    bool operator == (const Matrix& B)
    {
        // compare each element in A and B one by one
        assert(m == B.m&&n == B.n);
        for (int i = 0; i < (int)data.size(); i++) {
            if (abs(data[i] - B.data[i]) > 1e-6) return false;
        }
        return true;
    }

    ////return -A
    Matrix operator - ()
    {
        //multiply each element by -1
        Matrix C(m,n);
        for(int i=0;i<(int)data.size();i++){
            C.data[i]=-data[i];
        }
        return C;
    }

    ////random access of a matrix element
    double& operator() (int i,int j)
    {
        //access ith row, jth column element
        assert(i>=0&&i<m&&j>=0&&j<n);
        return data[i*n+j];
    }

    const double& operator() (int i,int j) const
    {
        assert(i>=0&&i<m&&j>=0&&j<n);
        return data[i*n+j];
    }

    ////display matrix in terminal
    friend ostream & operator << (ostream &out,const Matrix &mtx)
    {
        //print every element in matrix in rows
        for(int i=0;i<mtx.m;i++){
            for(int j=0;j<mtx.n;j++){
                out<<mtx(i,j)<<", ";
            }
            out<<std::endl;
        }
        return out;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////overloaded operators
    
    //return C = A + B
    Matrix operator + (const Matrix& B) {
        //check two matrices are same size
        assert(m==B.m&&n==B.n);
        Matrix C(m,n);
        
        //add each pair of elements in the matrices
        for(int i=0;i<(int)data.size();i++){
            C.data[i]=data[i]+B.data[i];
        }
        return C;
    }

    //A+=B
    void operator += (const Matrix& B) {
        //same as prev
        assert(m==B.m&&n==B.n);
        for(int i=0;i<(int)data.size();i++){
            data[i]+=B.data[i];
        }
    }
    
    //return A-B
    Matrix operator - (const Matrix& B) {
        //check matrices are the same size
        assert(m==B.m&&n==B.n);
        Matrix C(m,n);
        
        //subtract each pair of elements in the matrices
        for(int i=0;i<(int)data.size();i++){
            C.data[i]=data[i]-B.data[i];
        }
        return C;
    }

    //A=A-B
    void operator -= (const Matrix& B) {
        //same as prev
        assert(m==B.m&&n==B.n);
        for(int i=0;i<(int)data.size();i++){
            data[i]-=B.data[i];
        }
    }

    //return A*s, with s as a scalar
    Matrix operator * (const double& s) {
        Matrix C(m,n);
        //multiply each element in matrix by this scalar
        for(int i=0;i<(int)data.size();i++){
            C.data[i]=data[i]*s;
        }
        return C;
    }

    //A=A*s, with s as a scalar
    void operator *= (const double& s) {
        //same as prev
        for(int i=0;i<(int)data.size();i++){
            data[i] = data[i] * s;
        }
    }

    // A = A * B
    Matrix operator * (const Matrix& B)
    {
        assert(n==B.m);
        Matrix C(m, B.n);
        for (int i = 0; i<m; i++) {             //for every row of A
            for (int j = 0; j < B.n; j++) {     //for every column of B
                double sum = 0;
                // sum up products of relevant row and column
                for (int k = 0; k<n; k++) {     //for every element in row of B
                    sum += (*this)(i, k)*B(k, j);
                }
                C(i, j) = sum;
            }
        }
        return C;
    }
        
    //return identity matrix
    Matrix Identity()
    {
        assert(m == n);
        Matrix C(m, n);
        //1s on diagonal 0s everywhere else
        for (int i=0; i < m; i ++ ) {
            C(i, i) = 1;
        }
        return C;
    }

    //return A^T
    Matrix Transpose() {
        Matrix C(n, m);
        // mirror elements along diagonal
        for (int i=0; i < m; i ++) {
            for (int j=0; j < n; j++) {
                C(j,i) = (*this)(i, j);
            }
        }
        return C;
    }

    //return a submatrix block A_ijab,
    //with i,j as the starting element and a,b as the block size
    Matrix Block(const int i,const int j,const int a,const int b) {
        Matrix C(a, b);
        // start at 0 up to a, b and add to index to compensate for offset
        for (int _i=0; _i < a; _i ++) {
            for (int _j = 0; _j < b; _j ++) {
                C(_i, _j) = (*this)(_i + i, _j +j);
            }
        }
        return C;
    }

    //swap the ith and jth row
    Matrix Rowswap(const int i,const int j) {
        assert(i < m && j <m);
        Matrix C(m, n);
        
        // copy over data
        for (int _i=0; _i < m; _i ++) {
            for (int _j=0; _j < n; _j++) {
                C(_i,_j) = (*this)(_i, _j);
            }
        }
        
        //swap row data
        for (int _j=0; _j < n; _j ++) {
            C(i, _j) = (*this)(j, _j);
        }
        for (int _j=0; _j < n; _j ++) {
            C(j, _j) = (*this)(i, _j);
        }
        return C;
    }
    
    // return the max element in the ith row of the matrix A
    double MaxRow(int i) const {
        assert(i < m);
        double max = (*this)(i, 0);
        for (int j = 0; j < n; j ++) {
            if ((*this)(i, j) > max) {
                max = (*this)(i, j);
            }
        }
        return max;
        
        
    }
    
    //return a random matrix
    Matrix Random() {
        Matrix C(m, n);
            for (int i=0; i < n; i ++) {
                for (int j=0; j < m; j++) {
                    C(j,i) = rand() % 100;
                }
            }
            return C;
    }
};
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//return the solution of linear equations Ax=b using Gaussian elimination
void Solve(const Matrix& A, const Matrix& b, Matrix& x) {
    assert(A.m == b.m && b.n == 1);
    int swap_list[2*A.n];
    Matrix C = A;
    Matrix D = b;

    //1. Search for the maximum element in current column
    for (int i = 0; i < A.m; i++) {
        double max = abs(C(i, i));
        int maxi = i;
        for (int _i = i; _i < A.m; _i ++) {
            if (abs(C(_i, i)) > max) {
                max = abs(C(_i, i));
                maxi = _i;
            }
        }
        
        //2. Swap maximum row with current row
        C = C.Rowswap(i, maxi);
        D = D.Rowswap(i, maxi);
        swap_list[2*i] = i;
        swap_list[2*i + 1] = maxi;
           
        for (int k = i + 1; k < A.m; k ++) {
            if (C(k, i) != 0 && C(i, i ) != 0) {
                double multiplier = C(k, i)/C(i, i);
                D(k, 0) -= D(i, 0)*multiplier;
                for (int t = 0; t < A.n; t ++) {
                    C(k, t) -= C(i, t)*multiplier;
                }
            }
        }
    }

    //3. Make all of the element 0 below current row in current column
    Matrix R(A.m, 1);
    for (int i = A.m - 1; i > -1; i --) {
        double sum = 0;
        for (int _i = A.m - 1; _i > i; _i --) {
            sum += R(_i, 0)* C(i, _i);
        }
        if (C(i, i) != 0) {
            R(i, 0) = (D(i, 0) - sum)/C(i, i);
        }
    }
    
    //4. Undo Swaps
    for (int s = 0; s < A.n; s++) {
        R.Rowswap(swap_list[2*s], swap_list[2*s + 1]);
    }
    x = R;
}
  
//Least sqyares solution using AA^Tx = A^Tb
void SolveLeastSquares(const Matrix& A, const Matrix& b, Matrix& x) {
    Matrix A_  = A;
    Matrix NewA = A_.Transpose() * A;
    Matrix NewB = A_.Transpose() * b;
    Matrix x1(x.m, 1);
    
    Solve(NewA, NewB, x1);
    
    x = x1;
}

//square norm of matrix
double Norm(Matrix& A) {
    double norm = 0;
    for (int i = 0; i < A.m; i++) {
        for (int j = 0; j < A.n; j ++) {
        norm += pow(A(i, j), 2);
        }
    }
    return norm;
}

//residual norm given A, b and x
double ResidualNorm(Matrix& A, Matrix& b, const Matrix& x) {
    Matrix Result(b.m, 1);
    Result = A*x - b;
    double norm = 0;
    for (int i = 0; i < b.m; i++) {
        norm += pow(Result(i, 0), 2);
    }
    return norm;
}

//Solve richardson with variable parameters
void SolveRichardson(const Matrix& A, Matrix& b, Matrix& x, const int iternum, const double mew) {
    Matrix A_ = A;
    Matrix x_ = x;
    for (int i = 0; i < iternum; i ++) {
        x_ = x_ - (A_.Transpose())*mew*(A_*x_ - b);
    }
    x = x_;
}

//Solve Richardson with fixed parameters and print statements for HW7
void SolveRichardsonAutomatic(const Matrix& A, Matrix& b, const Matrix& x_compare, Matrix& x) {
    
    Matrix A_ = A;
    double mew = 1/Norm(A_);
    Matrix x_ = x;
    Matrix normM(x.m, x.n);
    double norm = 0;
    
    for (int i = 0; i < 500; i ++) {
        x_ = x_ - (A_.Transpose())*mew*(A_*x_ - b);
        normM = x_ - x_compare;
        norm = Norm(normM);
        cout<<""<<norm<<endl;
    }
    x = x_;
}


//LU decomposition
void SolveLU(const Matrix& A, Matrix& L, Matrix& U)
{
    Matrix C = A;
    L = L.Identity();
    for (int i = 0; i < A.m; i++) {
        for (int k = i + 1; k < A.m; k ++) {
            if (C(k, i) != 0 && C(i, i ) != 0) {
                double multiplier = C(k, i)/C(i, i);
                for (int t = 0; t < A.n; t ++) {
                    C(k, t) -= C(i, t)*multiplier;
                }
                L(k, i) = multiplier;
            }
        }
    }
    U = C;
}

//QR Decomposition
void SolveQR(Matrix& A, Matrix& Q, Matrix& R) {
    
    //for every column of A, calculate column of Q
    for (int j = 0; j < A.n; j ++) {
        Matrix a_j = A.Block(0, j, A.m, 1);
        Matrix a_j_trans = a_j.Transpose();
        Matrix q_hat = a_j;
        
        //upper triangular (we need to calculate rows up to the current column number)
        for (int k = 0; k < j; k ++) {
            Matrix q_k = Q.Block(0, k, Q.m, 1);
            Matrix q_k_trans = q_k.Transpose();
            q_hat -= q_k * (q_k_trans*a_j)(0, 0);
            R(k, j) = (a_j_trans * q_k)(0,0);
        }
        
        double q_norm = pow (Norm(q_hat), 0.5);
        for (int i = 0; i < Q.m; i ++) {
            Q(i, j) = q_hat(i, 0)/q_norm;
        }
        R(j, j) = q_norm;
    }
}

void SolveQR1(const Matrix& A, const Matrix& b, Matrix& x)
{
    Matrix A_  = A;
    Matrix Q(A.m, A.n);
    Matrix R(A.n, A.n);
    Matrix x_(x.m, 1);
    SolveQR(A_, Q, R);
    
    Matrix Q_trans = Q.Transpose();
    Matrix y = Q_trans * b;
    Solve(R, y, x_);
    x = x_;
}

#endif
