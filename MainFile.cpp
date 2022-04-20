#include<bits/stdc++.h>
using namespace std;

class Graph{
    int vertices;
    vector<vector<int>> adjacenyMatrix;

public:
    Graph(int v){
        this->vertices = v;
        vector<int> row;
        for (int i = 0; i < vertices; i++)
        {   
            row.push_back(0);
        }
        for (int i = 0; i < vertices; i++)
            this->adjacenyMatrix.push_back(row);
        
    }

    void addEdge(int x, int y, int w){
        this->adjacenyMatrix[x][y] = w;
    }

    vector<vector<int>> adjacencyList(){
        vector<vector<int>> adjacencyList;
        for (int i = 0; i < vertices; i++)
        {
            vector<int> List;
            for (int j = 0; j < vertices; j++)
            {
                if(adjacenyMatrix[i][j] > 0){
                    List.push_back(j);
                }
            }
            adjacencyList.push_back(List);
            
        }

        return adjacencyList;
        
    }
};

