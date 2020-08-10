#ifndef __MySparseMatrix_h__
#define __MySparseMatrix_h__

#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <tuple>
#include <algorithm>
#include "MyMatrix.h"

using namespace std;

class SparseMatrix
{
public:
    int m;                        ////number of rows
    int n;                        ////number of columns

    ////HW3 Task 0: memory storage for a sparse matrix
    /*Your implementation starts*/
    vector<tuple<int,int,double> > elements;
    vector<double> values;
    vector<int> col_indices;
    vector<int> row_total;


    /*Your implementation ends*/

    ////matrix constructor
    SparseMatrix(const int _m=1,const int _n=1)
    {
        Resize(_m,_n);
        values.resize(m*n);
        col_indices.resize(m*n);
        row_total.resize(m + 1);
    }

    void Resize(const int _m,const int _n)
    {
        m=_m;
        n=_n;
        
        values.resize(m*n);
        col_indices.resize(m*n);
        row_total.resize(m + 1);
    }

    ////A=B
    void operator = (const SparseMatrix& B)
    {
        Resize(B.m,B.n);

        ////HW3 Task 0: copy the data from another sparse matrix
        /*Your implementation starts*/
        values.resize(B.m*B.n);
        col_indices.resize(B.m*B.n);
        row_total.resize(B.m + 1);

        for(int i=0;i<(int)values.size();i++){
            values[i]=B.values[i];
            col_indices[i]=B.col_indices[i];

        }
        
        for(int i=0;i<(int)row_total.size();i++){
            row_total[i]=B.row_total[i];
        }
        /*Your implementation ends*/
    }

    ////display matrix in terminal
    friend ostream & operator << (ostream &out,const SparseMatrix &mtx)
    {
        for(int i=0;i<mtx.m;i++){
            for(int j=0;j<mtx.n;j++){
                out<<mtx(i,j)<<", ";
            }
            out<<std::endl;
        }
        return out;
    }

    //////////////////////////////////////////////////////////////////////////
    ////HW3 Task 1: initialize the three arrays using an array of tuples
    void operator = (vector<tuple<int,int,double> >& elements)
    {
        ////sort the elements by 1) row index i; 2) col index j
        sort(elements.begin(),elements.end(),
        [](const tuple<int,int,double>& a,const tuple<int,int,double>& b)->bool
        {return get<0>(a)<get<0>(b)||(get<0>(a)==get<0>(b)&&get<1>(a)<=std::get<1>(b));});


        
        
        values.resize(elements.size());
        col_indices.resize(elements.size());
        row_total.resize(m + 1);
        ////Using the information in elements to initialize row, col, val
        ////You may uncomment the following code to start or implement your own
        int prev_i = 0;
        
        int p = 0;
        
        while (p < elements.size()) {
            int i=get<0>(elements[p]);        ////access row index i in tuple
            int j=get<1>(elements[p]);        ////access j in tuple
            double v=get<2>(elements[p]);    ////access value in tuple

        //    /*Your code starts*/
            if (prev_i != i) {
                row_total[i] = p;
            }
            prev_i = i;
            values[p] = v;
            col_indices[p] = j;
            p++;
        //    /*Your code ends*/
        }
        
        
        row_total[m] = p;
 
        //printf("elements");
        //for(auto& tuple: elements) {
            //cout << get<0>(tuple) << " " << get<1>(tuple)<< " " << get<2>(tuple) << endl;
        //}
        
        //printSparse();
        
        ///*Your code starts: for the last element!*/
        ///*Your code ends*/
    }
    
    ////HW3, Task 2: random access of a matrix element
    ////notice that we are not using a reference in this case
    double operator() (int i,int j) const {
        assert(i>=0&&i<m&&j>=0&&j<n);
        ////HW3: your implementation, random access element (i,j) by using row,col,val
        /*Your code starts*/
        
        int start_index = row_total[i];
        int end_index = row_total[i + 1];
        for (int count = start_index; count < end_index; count++) {
            
            //printf("current count index %d \n", count);
            //printf("col indices count %d \n", col_indices[start_index + count] );
            if (col_indices[count] == j) {
                return values[count];
            }
        }
        /*Your code ends*/
        return 0;
    }

    ////HW3, Task 3: sparse matrix-vector multiplication
    ////implement sparse prod=Ax, assuming x is a vector (with n==1)
    Matrix operator * (const Matrix& x)
    {
        assert(x.n==1);
        Matrix prod(x.m,1);
        /*Your code starts*/
        for (int i = 0; i < m; i++) {
            int sum = 0;
            int start_index = row_total[i];
            int end_index = row_total[i + 1];
            for (int count = start_index; count < end_index; count++) {
                sum += values[count] * x(col_indices[count], 0);
            }
            prod(i, 0) = sum;
           
        }
        /*Your code ends*/

        return prod;
    }
    
    void printSparse() {
        printf("elements");
        for(auto& tuple: elements) {
            cout << get<0>(tuple) << " " << get<1>(tuple)<< " " << get<2>(tuple) << endl;
        }
        
        printf("\nvalues \n");
        for(int i = 0; i < values.size(); i ++) {
            printf("%f,  ", values[i]);
        }
        
        printf("\nrow totals \n");
        for(int i = 0; i < row_total.size(); i ++) {
            printf("%d,  ", row_total[i]);
        }
        
        printf("\ncol indices \n");
        for(int i = 0; i < col_indices.size(); i ++) {
            printf("%d,  ", col_indices[i]);
        }
    }
    
};

#endif

