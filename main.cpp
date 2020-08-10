//PLEASE USE HW_ID = 8 TO TEST FINAL NEURAL NETWORK CODE
#define HW_ID 11

#include <iostream>
#include "MyMatrix.h"
#include "MyToolset.h"
#include "ctime"
#include "MyMatrixLibrary_MySparseMatrix.h"
#include "MyGraph.h"
#include "LeastSquaresLearner.h"

#if HW_ID == 7
#include "MyNeuralNetwork.h"
#endif

#if HW_ID == 8
#include "MyNeuralNetworkDessert.h"
#endif

#if HW_ID == 9
#include "MyNeuralNetworkBias.h"
#endif


void Test_HW1() {
#if HW_ID == 1
    ////test the sample code
    Matrix m1(3,3),m2(3,3);
    
    m1={1.,2.,3.,4.,5.,6.,7.,8.,9.};
    m2={1.,0.,0.,0.,2.,0.,0.,0.,3.};
    cout<<"m1:\n"<<m1<<endl;
    cout<<"m2:\n"<<m2<<endl;

    cout<<"m1+m2:\n"<<(m1+m2)<<endl;

    Matrix m3=m1;
    cout<<"m3=m1, m3:\n"<<m3<<endl;

    //////////////////////////////////////////////////////////////////////////
    ////start to test your implementation
    ////Notice the code will not compile before you implement your corresponding operator
    ////so uncomment them one by one if you want to test each function separately
    
    ////test subtractions
    Matrix m4=-m3;
    cout<<"m4=-m3, m4:\n"<<m4<<endl;
    
    m4=m1-m3;
    cout<<"m4=m1-m3,m4:\n"<<m4<<endl;

    m4-=m1;
    cout<<"m4-=m1, m4:\n"<<m4<<endl;

    ////test matrix-scalar products
    double s=2;
    Matrix m5=m4*s;
    cout<<"m5=m4*s, m5:\n"<<m5<<endl;
    m5*=s;
    cout<<"m5*=s, m5:\n"<<m5<<endl;

    ////check matrix-matrix multiplication
    Matrix v1(3,1);    ////column vector
    v1={1.,2.,3.};
    cout<<"column vector v1:\n"<<v1<<endl;

    Matrix v2(1,3);    ////row vector
    v2={-3.,-2.,-1.};
    cout<<"row vector v2:\n"<<v2<<endl;

    Matrix v3=v1*v2;
    cout<<"v3=v1*v2, dimension: ["<<v3.m<<", "<<v3.n<<"]"<<endl;
    cout<<"v3 values:\n"<<v3<<endl;

    Matrix v4=v2*v1;
    cout<<"v4=v2*v1, dimension: ["<<v4.m<<", "<<v4.n<<"]"<<endl;
    cout<<"v4 values:\n"<<v4<<endl;

    ////test identity, transpose, and block
    Matrix m6(3,3);
    cout<<"m6:\n"<<m6.Identity()<<endl;

    Matrix m7(4,2);
    cout<<"m7.Transpose():\n"<<m7.Transpose()<<endl;
    cout<<"m2.Block(0,0,2,2):\n"<<m2.Block(0,0,2,2)<<std::endl;
#endif
}

void Test_HW2() {
#if HW_ID == 2
    ////test Gaussian Elimination
    Matrix A1(3, 3);
    Matrix b1(3, 1);
    Matrix x1(3, 1);
    A1 = { 1.,1.,1.,2.,2.,5.,4.,6.,8. };
    b1 = { 1.,2.,3. };
    Solve(A1, b1, x1);
    if ((A1*x1) == b1) cout << "Solve A1x=b1:\n " << x1 << endl;
    else cout << "Wrong Answer for A1x=b1" << endl;
    Matrix A2(3, 3);
    Matrix b2(3, 1);
    Matrix x2(3, 1);
    A2 = { 5.,1.,3.,4.,5.,3.,1.,5.,2. };
    b2 = { 3.,6.,-1. };
    Solve(A2, b2, x2);
    if (A2*x2 == b2) cout << "Solve A2x=b2:\n " << x2 << endl;
    else cout << "Wrong Answer for A2x=b2" << endl;
    Matrix A3(5, 5);
    Matrix b3(5, 1);
    Matrix x3(5, 1);
    A3 = { 2.,4.,5.,3.,2.,
        4.,8.,3.,4.,3.,
        3.,3.,2.,7.,2.,
        1.,2.,2.,1.,3.,
        3.,4.,2.,5.,7. };
    b3 = { 7.,-4.,-15.,14.,16. };
    Solve(A3, b3, x3);
    if (A3*x3 == b3) cout << "Solve A3x=b3:\n " << x3 << endl;
    else cout << "Wrong Answer for A3x=b3" << endl;
    Matrix A4(1000, 1000);
    Matrix b4(1000, 1);
    Matrix x4(1000, 1);
    for (int i = 1; i < A4.m -1; i++) {
        A4(i, i) = 2.;
        A4(i, i + 1) = -1.;
        A4(i, i - 1) = -1.;
    }
    A4(0, 0) = A4(A4.m-1, A4.n-1) = 2.;
    A4(0, 1) = A4(A4.m - 1, A4.n - 2) = -1.;
    for (int i = 0; i < b4.m; i++) { b4(i, 0) = (double)i/(double)(b4.m*b4.m); }
    Solve(A4, b4, x4);
    if (A4*x4 == b4) cout << "Solve A4x=b4:\n " << x4 << endl;
    else cout << "Wrong Answer for A4x=b4" << endl;
#endif
}

void Test_HW3() {
#if HW_ID == 3
    std::cout<<"Test sparse matrix"<<std::endl;
    SparseMatrix mtx(6,6);
    vector<tuple<int,int,double> > elements;
    elements.push_back(make_tuple<int,int,double>(0,0,7));
    elements.push_back(make_tuple<int,int,double>(0,1,5));
    elements.push_back(make_tuple<int,int,double>(1,0,1));
    elements.push_back(make_tuple<int,int,double>(1,2,3));
    elements.push_back(make_tuple<int,int,double>(2,3,5));
    elements.push_back(make_tuple<int,int,double>(2,4,4));
    elements.push_back(make_tuple<int,int,double>(3,3,1));
    elements.push_back(make_tuple<int,int,double>(4,1,7));
    elements.push_back(make_tuple<int,int,double>(4,4,3));
    mtx=elements;

    cout<<"sparse matrix:\n"<<mtx<<endl;

    Matrix v(5,1);v={1,2,3,4,5};
    Matrix prod(5,1);
    prod=mtx*v;
    cout<<"sparse matrix-vector multiplication:\n";
    cout<<prod<<endl;
#endif
}

void Test_HW4() {
#if HW_ID ==4
    std::cout<<"Test graph matrix"<<std::endl;
    Graph g;
    g.Add_Node(0.);
    g.Add_Node(1.);
    g.Add_Node(2.);
    g.Add_Node(3.);
    g.Add_Node(4.);
    g.Add_Node(5.);

    g.Add_Edge(0,1);
    g.Add_Edge(1,2);
    g.Add_Edge(1,3);
    g.Add_Edge(2,3);
    g.Add_Edge(2,4);
    g.Add_Edge(3,4);
    g.Add_Edge(4,5);

    Matrix adj_m;g.Adjacency_Matrix(adj_m);
    Matrix inc_m;g.Incidence_Matrix(inc_m);
    Matrix lap_m;g.Laplacian_Matrix(lap_m);
    double energy=g.Dirichlet_Energy(g.node_values);

    cout<<g<<endl;
    cout<<"Adjacency matrix\n"<<adj_m<<endl;
    cout<<"Incidency matrix\n"<<inc_m<<endl;
    cout<<"Laplacian matrix\n"<<lap_m<<endl;
    cout << "Dirichlet energy before smoothing: "<<energy<<endl;

    g.Smooth_Node_Values(.1,10);
    energy=g.Dirichlet_Energy(g.node_values);
    cout<<"Dirichlet energy after smoothing: "<<energy<<endl;
#endif
}


void Test_HW5()
{
#if HW_ID == 5
    
    Matrix A1(3, 2);
    Matrix b1(3, 1);
    Matrix x1(2, 1);
    A1 = { 1.,0.,1.,1.,1.,2.};
    b1 = { 6.,0.,0. };
    
    cout << "A1; \n" << A1 << endl;
    cout << "b1; \n " << b1 << endl;
    SolveLeastSquares(A1, b1, x1);
    cout << "Solve Least Squares A1x=b1:\n " << x1 << endl;
    
    Matrix A2(30, 10);
    Matrix b2(30, 1);
    Matrix x2(10, 1);
    Matrix x3(10, 1);
    Matrix x4(10, 1);
    Matrix x5(10, 1);

    A2 = A2.Random();
    b2 = b2.Random();
    x3 = x3.Random();
    x4 = x4.Random();
    x5 = x5.Random();
    
    cout << "A2; \n" << A2 << endl;
    cout << "b2; \n " << b2 << endl;
    SolveLeastSquares(A2, b2, x2);
    cout << "Solve Least Squares A2x=b2:\n " << x2 << endl;
    
    double norm2 = ResidualNorm(A2, b2, x2);
    double norm3 = ResidualNorm(A2, b2, x3);
    double norm4 = ResidualNorm(A2, b2, x4);
    double norm5 = ResidualNorm(A2, b2, x5);
    
    printf("Norm x2 = %f \n", norm2);
    printf("Norm x3 = %f \n", norm3);
    printf("Norm x4 = %f \n", norm4);
    printf("Norm x5 = %f \n\n", norm5);
    
    if (norm2 <= norm3 && norm2 <= norm4 && norm2 <= norm5) cout << "Success, least squares residual is the smallest: \nx = \n " << x2 << endl;
       else cout << "Failure, least squares result is not optimal" << endl;
    
    Matrix A6(20, 10);
    A6 = A6.Random();
    Matrix b6(20, 1);
    b6 = b6.Random();
    Matrix x6(10, 1);
    SolveLeastSquares(A6, b6, x6);
    Matrix x7(10, 1);
    SolveRichardsonAutomatic(A6, b6, x6, x7);
#endif
}

void Test_HW6() {
#if HW_ID == 6
    
    Matrix A1(4, 3);
    A1 = { -1.,-1.,1.,
            1.,3.,3.,
            -1.,-1.,5.,
            1.,3.,7.,};
       
    Matrix Q1(4,3);
    Matrix R1(3, 3);
    cout << "A1 =\n" << A1 << endl;
    SolveQR(A1, Q1, R1);
    cout << "SolveQR Q1=:\n " << Q1 << endl;
    cout << "SolveQR R1=:\n " << R1 << endl;
    
    Matrix A2(20, 10);
    A2 = A2.Random();
    Matrix b2(20, 1);
    b2 = b2.Random();
       
    Matrix x2(10, 1);
    SolveQR1(A2, b2, x2);
    cout << "SOLVE QR x: \n" << x2 << endl;
    
    Matrix x3(10, 1);
    SolveLeastSquares(A2, b2, x3);
    cout << "SOLVE LEAST SQUARES x: \n" << x3 << endl;
    Matrix Q2(20,10);
    Matrix R2(10, 10);
    
    SolveQR(A2, Q2, R2);
    Matrix Ax = A2*x2;
    cout << "Ax = \n" << Ax << endl;
    
    Matrix Q2_trans = Q2.Transpose();
    Matrix QQTb = Q2*Q2_trans*b2;
    cout << "Q*Q_transpose*b = \n" << QQTb << endl;
#endif
}

void Test_Extra_Credit_1() {
#if HW_ID == 10
    
    Matrix A1(4, 4);
       A1 = { 2.,1.,1.,0.,
           4.,3.,3.,1.,
           8.,7.,9.,5.,
           6.,7.,8.,9. };
    
    Matrix L1(4,4);
    Matrix U1(4, 4);
        
    SolveLU(A1, L1, U1);
    cout << "SolveLU L1=:\n " << L1 << endl;
    cout << "SolveLU U1=:\n " << U1 << endl;
#endif
}

void Test_Extra_Credit_3() {
#if HW_ID == 30
    
    std::cout<<"Test sparse matrix"<<std::endl;
    SparseMatrix s1(100000, 100000);
    Matrix m1(100000, 100000);
    Matrix v(100000, 1);
    clock_t start1 = clock();
    Matrix sresult = s1*v;
    clock_t end1 = clock();
    cout << "Time cost for sparse matrix multiplication:" << (double)(end1 - start1) / CLOCKS_PER_SEC << "s" << endl;
    
    clock_t start2 = clock();
    Matrix mresult = s1*v;
    clock_t end2 = clock();
    cout << "Time cost for matrix multiplication:" << (double)(end2 - start2) / CLOCKS_PER_SEC << "s" << endl;
#endif
}

void Test_Extra_Credit_4() {
#if HW_ID == 40
    std::cout<<"Test graph matrix"<<std::endl;
        Graph g;
        g.Add_Node(0.);
        g.Add_Node(1.);
        g.Add_Node(2.);
        g.Add_Node(3.);
        g.Add_Node(4.);
        g.Add_Node(5.);

        g.Add_Edge(0,1);
        g.Add_Edge(1,2);
        g.Add_Edge(1,3);
        g.Add_Edge(2,3);
        g.Add_Edge(2,4);
        g.Add_Edge(3,4);
        g.Add_Edge(4,5);

        SparseMatrix adj_m;
        g.Adjacency_Matrix_S(adj_m);
        SparseMatrix inc_m;
        g.Incidence_Matrix_S(inc_m);
        SparseMatrix lap_m;
        g.Laplacian_Matrix_S(lap_m);

        cout<<g<<endl;
        cout<<"Sparse Adjacency matrix\n"<<adj_m<<endl;
        cout<<"Sparse Incidency matrix\n"<<inc_m<<endl;
        cout<<"Sparse Laplacian matrix\n"<<lap_m<<endl;
#endif
    }



double data_function(const double x)  {return pow(x,3)+pow(x,2)+1.;}

void Test_Final()
{
#if HW_ID == 7
    vector<pair<int, int>> regressor_feature_sizes={{1, 16}, {16, 16}, {16, 16}, {16, 1}};
    Regressor reg(regressor_feature_sizes,&data_function);
    reg.Train();
    vector<pair<int, int>> classifier_feature_sizes={{28*28, 256}, {256, 256}, {256, 256}, {256, 10}};
    Classifier cls(".", classifier_feature_sizes);
    cls.Train();
#endif
}

void Test_Final_Dessert()
{
#if HW_ID == 8
    vector<pair<int, int>> regressor_feature_sizes={{1, 16}, {16, 16}, {16, 16}, {16, 1}};
    Regressor reg(regressor_feature_sizes,&data_function);
    reg.Train();
    vector<pair<int, int>> classifier_feature_sizes={{28*28, 256}, {256, 256}, {256, 256}, {256, 10}};
    Classifier cls(".", classifier_feature_sizes);
    cls.Train();
#endif
}


void Test_Final_Bias()
{
#if HW_ID == 9
    vector<pair<int, int>> regressor_feature_sizes={{1, 16}, {16, 16}, {16, 16}, {16, 1}};
    Regressor reg(regressor_feature_sizes,&data_function);
    reg.Train();
    vector<pair<int, int>> classifier_feature_sizes={{28*28 + 1, 256}, {256, 256}, {256, 256}, {256, 10}};
    Classifier cls(".", classifier_feature_sizes);
    cls.Train();
#endif
}

void Test_Final_Least_Squares() {
#if HW_ID == 11
    Matrix x1(5, 1);
    x1 = {1.,2.,3.,4.,5.};
    Matrix A = CreatePolynomialA(x1, 3);
    cout << "Checking Data Matrix Generation: \n" << 
    A << endl;
    
    Matrix dataPairs1(4, 2);
    dataPairs1 = {1., 1., 2., 4., 3., 9., 4., 16};
    Matrix theta1(3, 1);
    theta1 = ApproximateFunction(dataPairs1, 2);
    printf("Approximate quadratic function thetas: \n");
    
    cout << "Testing function approximator..." << endl;
    double mse = testFunction();
    printf("MSE for function approximator (train data and test data all generated via real function so MSE should be 0):\n MSE = %f\n\n", mse);

    
    printf("Testing image classification...");
    double accuracy = testImages(".");
    printf("Image Classification accuracy using least squares: %f\n\n", accuracy);
#endif

}

int main()
{
    std::cout<<"Hello CS70!"<<std::endl;

    Test_HW1();
    Test_HW2();
    Test_HW3();
    Test_HW4();
    Test_HW5();
    Test_HW6();
    
    Test_Extra_Credit_1();
    Test_Extra_Credit_3();
    Test_Extra_Credit_4();
        
    
    // ID = 11
    Test_Final_Least_Squares();
    
    // ID = 7
    Test_Final();
    
    // ID = 8
    //BEST ALGORITHM: 80.5% accuracy at epoch 200
    Test_Final_Dessert();
    
    // ID = 9
    //IMPLEMENTED BIAS: However this did not improve the algorithm and it actually had a lower accuracy
    Test_Final_Bias();
    
    system("PAUSE");
}





