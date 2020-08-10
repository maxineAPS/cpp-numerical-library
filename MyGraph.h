#ifndef __MyGraph_h__
#define __MyGraph_h__

#include <iostream>
#include <utility>
#include "MyMatrix.h"
#include "MyMatrixLibrary_MySparseMatrix.h"


class Graph
{
public:
    vector<double> node_values;                ////values on nodes
    vector<double> edge_values;                ////values on edges
    vector<pair<int,int> > edges;        ////edges connecting nodes

    void Add_Node(const double& value)
    {
        node_values.push_back(value);
    }

    void Add_Edge(const int i,const int j,const double value=1.)
    {
        edges.push_back(pair<int,int>(i,j));
        edge_values.push_back(value);
    }

    ////display graph in terminal
    friend ostream & operator << (ostream &out,const Graph &graph)
    {
        cout<<"graph node values: "<<graph.node_values.size()<<endl;
        for(int i=0;i<(int)graph.node_values.size();i++){
            cout<<"["<<i<<", "<<graph.node_values[i]<<"] ";
        }
        cout<<endl;

        cout<<"graph edge values: "<<graph.edge_values.size()<<endl;
        for(int i=0;i<(int)graph.edge_values.size();i++){
            cout<<"["<<i<<", "<<graph.edge_values[i]<<"] ";
        }
        cout<<endl;

        cout<<"graph edges: "<<graph.edges.size()<<endl;
        for(int i=0;i<(int)graph.edges.size();i++){
            cout<<"["<<graph.edges[i].first<<", "<<graph.edges[i].second<<"] ";
        }
        cout<<endl;

        return out;
    }

    //////////////////////////////////////////////////////////////////////////
    ////Your homework starts

    ////HW4 Task 0: build incidence matrix
    void Incidence_Matrix(/*result*/Matrix& inc_m)
    {
                
        // initialize matrix
        Matrix M((int)node_values.size(), (int)edges.size());
        
        // for every edge in the graph, set the corresponding value for the start node to -1 and end node to 1
        for(int i=0;i<(int)edges.size();i++){
            M(edges[i].first, i) = -1;
            M(edges[i].second, i) = 1;
        }
        
        // pass this matrix to the reference
        inc_m = M;
    }

    ////HW4 Task 1: build adjancency matrix
    void Adjacency_Matrix(/*result*/Matrix& adj_m)
    {

        // calculate size now for efficiency
        int size = (int)node_values.size();
        Matrix C(size, size);
        
        // add a 1 to the (i, j)th position if i is adjacent to j
        for(int i=0;i<(int)edges.size();i++){
            C(edges[i].first, edges[i].second) = 1;
            C(edges[i].second, edges[i].first) = 1;
        }
        
        // pass this patrix to the reference
        adj_m = C;
    }

    ////HW4 Task 3: build the negative Laplacian matrix
    void Laplacian_Matrix(/*result*/Matrix& lap_m)
    {
        
        // retrieve incidence matrix
        Matrix inc_m;
        Incidence_Matrix(inc_m);
        
        // calculate laplacian = (-incidence*incidence transpose)
        lap_m = -inc_m*inc_m.Transpose();

    }
    
    void Incidence_Matrix_S(/*result*/SparseMatrix& inc_m)
    {
        SparseMatrix M((int)node_values.size(), (int)edges.size());
        
        vector<tuple<int,int,double> > elements;

        // for every edge in the graph, set the corresponding value for the start node to -1 and end node to 1
        for(int i=0;i<(int)edges.size();i++){
            elements.push_back(make_tuple<int, int, double>((int)edges[i].first, (int)i, (double)-1));
            elements.push_back(make_tuple<int, int, double>((int)edges[i].first, (int)i, (double)1));

        }
        
        M=elements;
        
        // pass this matrix to the reference
        inc_m = M;
    }

    ////HW4 Task 1: build adjancency matrix
    void Adjacency_Matrix_S(/*result*/SparseMatrix& adj_m)
    {
        // calculate size now for efficiency
        int size = (int)node_values.size();
        SparseMatrix C(size, size);
        vector<tuple<int,int,double> > elements;
        
        // add a 1 to the (i, j)th position if i is adjacent to j
        for(int i=0;i<(int)edges.size();i++){
            elements.push_back(make_tuple<int,int,double>((int)edges[i].first, (int)edges[i].second, 1));
            elements.push_back(make_tuple<int,int,double>((int)edges[i].second, (int)edges[i].first, 1));
        }
        
        C = elements;
        
        
        
        // pass this patrix to the reference
        adj_m = C;
    }

    ////HW4 Task 3: build the negative Laplacian matrix
    void Laplacian_Matrix_S(/*result*/SparseMatrix& lap_m)
    {
        
        // retrieve incidence matrix
        Matrix lap_m1;
        Laplacian_Matrix(lap_m1);
        
        SparseMatrix C(lap_m1.m, lap_m1.n);
        vector<tuple<int,int,double> > elements;
        
        cout<<"Laplacian matrix\n"<<lap_m1<<endl;

        for(int i=0;i<lap_m1.m;i++){
            for(int j=0;j<lap_m1.n;j++){
                elements.push_back(make_tuple<int, int, double>((int)i, (int)j, (double)lap_m1(i,j)));
            }
        }
        
        
        C = elements;
        
        // pass this matrix to the reference
        lap_m = C;
        
    }

    ////HW4 Task 4: calculate the Dirichlet energy
    double Dirichlet_Energy(const vector<double>& v)
    {
        double de=(double)0;
        
        // retrieve laplacian matrix
        Matrix inc_m;
        Incidence_Matrix(inc_m);
        Matrix At = inc_m.Transpose();
        
        
        
        
        // get new matrix v1 with laplacian.transpose number of rows
        Matrix v1(At.n, 1);
        v1 = v;
        


        // calculate laplacian.transpose * v1
        Matrix Atv = At*v1;

        // add the square sum of every element in Atv to result
        for (int i = 0; i < Atv.m; i++) {
            de += pow(Atv(i, 0), 2);
        }


        return de;
    }

    ////HW4 Task 5: smooth the node values on the graph by iteratively applying the Laplacian matrix
    void Smooth_Node_Values(const double dt,const int iter_num)
    {
        
        // retrieve laplacian
        Matrix lap_m;
        Laplacian_Matrix(lap_m);

        // copy node_values to local variables
        int m=(int)node_values.size();
        Matrix v(m,1);
        for(int i=0;i<m;i++){
            v(i,0)=node_values[i];
        }
        
        Matrix v2=v;

        //smooth v
        // iterate iter_num times
        for (int i=0; i<iter_num; i++) {
            
            //calculate new v by formula
            v = v + (lap_m*v)*dt;
            printf("\nDirichlet energy iteration %d: %f\n", i, Dirichlet_Energy(v.data));
        }

        //copy local variables to node_values
        for(int i=0;i<m;i++){
            node_values[i]=v(i,0);
        }
        
        printf("\n");
    }
};

#endif

