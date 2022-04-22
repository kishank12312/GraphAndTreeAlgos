#include<bits/stdc++.h>
using namespace std;

class Graph{
public:
    int vertices;
    vector<vector<int>> adjacencyMatrix;

    Graph(int v){
        this->vertices = v;
        vector<int> row;
        for (int i = 0; i < vertices; i++)
        {   
            row.push_back(0);
        }
        for (int i = 0; i < vertices; i++)
            this->adjacencyMatrix.push_back(row);
        
    }

    void addEdge(int x, int y, int w){
        this->adjacencyMatrix[x][y] = w;
    }

    vector<vector<int>> adjacencyList(){
        vector<vector<int>> adjacencyList(vertices);
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if(adjacencyMatrix[i][j] > 0){
                    adjacencyList[i].push_back(j);
                }
            }
            
        }

        return adjacencyList;  
    }
};

//GLOBAL VARIABLES
vector<bool> visited;
vector<bool> topologicalvisited;
vector<int> ans;
vector<vector<int>> adj;
int vertexcount;

//TRANSITIVE CLOSURE
void transitiveClosure(vector<vector<int>> graph, int V)
{
    int reach[V][V], i, j, k;
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            reach[i][j] = graph[i][j];
    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                reach[i][j] = reach[i][j] ||
                  (reach[i][k] && reach[k][j]);
            }
        }
    }
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
              if(i == j)
                printf("1 ");
              else
                printf ("%d ", reach[i][j]);
        }
        printf("\n");
    }
}

//BIPARTITE GRAPH CHECK
bool isBipartite(vector<vector<int>> G,int V)
{
    int colorArr[V];
    for (int i = 0; i < V; ++i)
        colorArr[i] = -1;
    colorArr[0] = 1;
    queue <int> q;
    q.push(0);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (G[u][u] == 1)
        return false;
        for (int v = 0; v < V; ++v)
        {
            if (G[u][v] && colorArr[v] == -1)
            {
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
            else if (G[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }
    return true;
}

//CHECK COLOURING
bool colouring(Graph graph, vector<int> colours){
    bool ans = true;
    for (int i = 0; i < graph.vertices; i++)
    {
        for (int j = 0; j < graph.vertices; j++)
        {
            if(graph.adjacencyMatrix[i][j] > 0){
                if(colours[i] == colours[j]){
                    return false;
                }
            }
        }
    }
    return ans;
    
}

//BFS
vector<int> bfs(vector<vector<int>> adj, int n, int s){
    queue<int> q;
    vector<bool> used(n);
    vector<int> d(n), p(n);

    vector<int> path;
    q.push(s);
    used[s] = true;
    p[s] = -1;
    while (!q.empty()) {
        int v = q.front();
        path.push_back(v);
        q.pop();
        for (int u : adj[v]) {
            if (!used[u]) {
                used[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
                p[u] = v;
            }
        }
    }
    
    return path;
}

//DFS
void dfs(int v) {
    visited[v] = true;
    cout << v << " ";
    for (int u : adj[v]) {
        if (!visited[u])
            dfs(u);
    }
}

//TOPOLOGICAL SORTING
void topologicaldfs(int v) {
    topologicalvisited[v] = true;
    for (int u : adj[v]) {
        if (!topologicalvisited[u])
            topologicaldfs(u);
    }
    ans.push_back(v);
}
void topological_sort(int n) {
    topologicalvisited.assign(n, false);
    ans.clear();
    for (int i = 0; i < n; ++i) {
        if (!topologicalvisited[i])
            topologicaldfs(i);
    }
    reverse(ans.begin(), ans.end());
}

// CHECKING CYCLIC
bool isCyclicUtil(int v, bool vis[], bool *recStack)
{
    if(vis[v] == false)
    {
        vis[v] = true;
        recStack[v] = true;
        list<int>::iterator i;
        for (int u : adj[v])
        {
            if ( !vis[u] && isCyclicUtil(u, vis, recStack) )
                return true;
            else if (recStack[u])
                return true;
        }
 
    }
    recStack[v] = false;
    return false;
}

bool isCyclic()
{
    bool *visit = new bool[vertexcount];
    bool *recStack = new bool[vertexcount];
    for(int i = 0; i < vertexcount; i++)
    {
        visit[i] = false;
        recStack[i] = false;
    }
    for(int i = 0; i < vertexcount; i++)
        if ( !visit[i] && isCyclicUtil(i, visit, recStack))
            return true;
 
    return false;
}

//MINIMUM SPANNING TREE
int mstUtil(int key[], bool mstSet[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < vertexcount; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}


void primMST(vector<vector<int>> graph)
{
    int parent[vertexcount];
    int key[vertexcount];
    bool mstSet[vertexcount];
    for (int i = 0; i < vertexcount; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < vertexcount - 1; count++)
    {
        int u = mstUtil(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < vertexcount; v++)

            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    cout<<"Edge \tWeight\n";
    int totalweight = 0;
    for (int i = 1; i < vertexcount; i++){
        cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n";
        totalweight += graph[i][parent[i]];
    }
    cout << '\n';
    cout << "The total weight of the minimum spanning tree is: " << totalweight << '\n';
}

bool isDirected(vector<vector<int>> graph){
    for (int i = 0; i < vertexcount; i++)
    {
        for (int j = 0; j < vertexcount; j++)
            {
                if(graph[i][j] != graph[j][i])
                    return true;
            }
    }
    return false; 
}

bool isConnected(vector<vector<int>> graph){
    Graph newG(vertexcount);
    newG.adjacencyMatrix = graph;
    for (int i = 0; i < vertexcount; i++)
    {
        for (int j = 0; j < vertexcount; j++)
        {
            if((newG.adjacencyMatrix[i][j] == 0) && (newG.adjacencyMatrix[j][i] != 0))
                newG.adjacencyMatrix[i][j] = newG.adjacencyMatrix[j][i];
            else if((newG.adjacencyMatrix[i][j] != 0) && (newG.adjacencyMatrix[j][i] == 0))
                newG.adjacencyMatrix[j][i] = newG.adjacencyMatrix[i][j];
        }
    }
    
    vector<int> traversal = bfs(newG.adjacencyList(),vertexcount,0);
    return traversal.size() == vertexcount;
}


int main(){

    int n;
    cout << "\n\n";
    cout << "Welcome to the Graph AlgoSimulator ADT" <<'\n';
    int weighted = -1;
    while(!(weighted == 1 || weighted == 0)){
        cout << "Enter 1 to input a weighted graph, 0 to input an unweighted graph: ";
        cin >> n;
        
        if(n==0){
            weighted = 0;
            break;
        }
                
        else if(n==1){
            weighted = 1;
            break;
        }
        
        else
            cout << "Invalid Input, please try again. \n";
            continue;
    }

        
    //Unweighted Graph
    if (weighted == 0){
        cout << "Enter number of vertices in unweighted graph: ";
        cin >> vertexcount;
        Graph g(vertexcount);
        visited.assign(vertexcount,false);
        bool checks = true;
        while (checks){
            int from, to;
            cout << "Enter space-seperated vertex from and vertex to: ";
            cin >> from >> to;
            g.addEdge(from,to,1);
            cout << "Do you want to add another edge? (y/n): ";
            char check;
            cin >> check;
            if (check=='y'){
                continue;
            }
            else{checks=false;}
        }

        adj = g.adjacencyList();
    
        while(true){
            cout << '\n';
            cout << "Choose an option to proceed: " << '\n';
            cout << "option 1: Check if a graph colouring is valid: " << '\n';
            cout << "option 2: Check if the graph is bipartite: " << '\n';
            cout << "option 3: Generate a topological sorting of the vertices of the graph: " << '\n';
            cout << "option 4: Find the transitive closure of the graph: " << '\n';
            cout << "option 5: Traverse from a chosen starting point using Breadth-First Search: " << '\n';
            cout << "option 6: Traverse from a chosen starting point using Depth-First Search: " << '\n';
            
            int option;
            cin >> option;


            //Colouring
            if(option == 1){
                vector<int> colours(vertexcount);
                for (int i = 0; i < vertexcount; i++)
                {
                    cout << "Please enter the colour for the vertex " << i << ": ";
                    cin >> colours[i];
                }
                if(colouring(g, colours)){
                    cout << "The given colouring is a valid Colouring \n";}
                else{
                    cout << "The given colouring is a invalid Colouring \n";}
                }
            
            //Bipartite
            else if(option == 2){
                if(isBipartite(g.adjacencyMatrix,vertexcount)){
                    cout << "The graph is bipartite. \n";}
                else{
                    cout << "The graph is not bipartite. \n";}
            }

            //Topological Sorting
            else if(option == 3){
                if(isConnected(g.adjacencyMatrix) && isDirected(g.adjacencyMatrix) && !isCyclic()){
                    topological_sort(vertexcount);
                    cout << "The topological ordering of vertices is: ";
                    for (int i = 0; i < ans.size(); i++)
                    {
                        cout << ans[i] << " ";
                    }
                    topologicalvisited.assign(n,false);
                    ans.clear();
                    cout << '\n';
                }
                else{
                    cout << "The input graph is not a directed acyclic graph, hence no topological sorting can be found.\n";
                }
            }

            //Transitive Closure
            else if(option == 4){
                cout << "The transitive closure of the graph is: \n";
                transitiveClosure(g.adjacencyMatrix,vertexcount);
            }

            //BFS
            else if(option == 5){
                int root;
                cout << "Input starting vertex for BFS: ";
                cin >> root;
                
                vector<int> traversal = bfs(adj,vertexcount,root);
                cout << "The BFS-ordering of the graph is: ";
                for (int i = 0; i < traversal.size(); i++)
                {
                    cout << traversal[i] << " ";
                }
                cout << '\n';
            }

            //DFS
            else if(option == 6){
                int root;
                cout << "Input starting vertex for DFS: ";
                cin >> root;
                cout << "The DFS-ordering of the graph is: ";
                dfs(root);
                visited.assign(n,false);
                for (int i = 0; i < ans.size(); i++)
                {
                    cout << ans[i] << " ";
                }
                cout << '\n';
            }

            //Invalid
            else{
                cout << "Invalid option selected \n";
            }
            char cont;
            cout <<"Do you want to continue? (y/n) ";
            cin >> cont;
            if (cont == 'y'){
                continue;
            }
            else{return 0;}
        }
    }


    //Weighted Graph 
    else if (weighted == 1){
            cout << "Enter number of vertices in weighted graph: ";
            cin >> vertexcount;
            Graph g(vertexcount);
            visited.assign(vertexcount,false);
            bool checks = true; 
            while (checks){
                int from, to, weight;
                cout << "Enter space-seperated vertex from, vertex to and weight of edge: ";
                cin >> from >> to >> weight;
                g.addEdge(from,to,weight);
                cout << "Do you want to add another edge? (y/n): ";
                char check;
                cin >> check;
                if (check=='y'){
                    continue;
                }
                else{checks=false;}
            }
            adj = g.adjacencyList();
        while (true){
            cout << "Choose an option to proceed: " << '\n';
            cout << "option 1: Check if a graph colouring is valid: " << '\n';
            cout << "option 2: Check if the graph is bipartite: " << '\n';
            cout << "option 3: Generate a topological sorting of the vertices of the graph: " << '\n';
            cout << "option 4: Find the transitive closure of the graph: " << '\n';
            cout << "option 5: Traverse from a chosen starting point using Breadth-First Search: " << '\n';
            cout << "option 6: Traverse from a chosen starting point using Depth-First Search: " << '\n';
            cout << "option 7: find the mininmum spanning path of the graph: "<<'\n';

            int option;
            cin >> option;

            //Colouring
            if(option == 1){
                vector<int> colours(vertexcount);
                for (int i = 0; i < vertexcount; i++)
                {
                    cout << "Please enter the colour for the vertex " << i << ": ";
                    cin >> colours[i];
                }
                if(colouring(g, colours)){
                    cout << "Valid Colouring \n";}
                else{
                    cout << "Invalid Colouring \n";}
            }

            //Bipartite    
            else if(option == 2){
                if(isBipartite(g.adjacencyMatrix,vertexcount)){
                    cout << "The graph is bipartite. \n";}
                else{
                    cout << "The graph is not bipartite. \n";}
            }
            
            //Topological Sorting
            else if(option == 3){
                if(isDirected(g.adjacencyMatrix) ){
                    topological_sort(vertexcount);
                    cout << "The topological ordering of vertices is: ";
                    for (int i = 0; i < ans.size(); i++)
                    {
                        cout << ans[i] << " ";
                    }
                    topologicalvisited.assign(n,false);
                    ans.clear();
                    cout << '\n';
                }
                else{
                    cout << "The input graph is not a directed acyclic graph, hence no topological sorting can be found.\n";
                }
            }

            //Transitive Closure
            else if(option == 4){
                cout << "The transitive closure of the graph is: \n";
                transitiveClosure(g.adjacencyMatrix,vertexcount);

            }

            //BFS
            else if(option == 5){
                int root;
                cout << "Input starting vertex for BFS: ";
                cin >> root;
                vector<int> traversal = bfs(adj,vertexcount,root);
                cout << "The BFS-ordering of the graph is: ";
                for (int i = 0; i < traversal.size(); i++)
                {
                    cout << traversal[i] << " ";
                }
                cout << '\n';
                
            }

            //DFS
            else if(option == 6){
                int root;
                cout << "Input starting vertex for DFS: ";
                cin >> root;
                cout << "The DFS-ordering of the graph is: ";
                dfs(root);
                visited.assign(n,false);
                for (int i = 0; i < ans.size(); i++)
                {
                    cout << ans[i] << " ";
                }
                cout << '\n';

            }

            //Prim's        
            else if (option == 7){
                    cout << "\n\n";
                    primMST(g.adjacencyMatrix);
            }

            //Invalid option
            else{
                cout << "Invalid option selected \n";
            }
            char cont;
            cout <<"Do you want to continue? (y/n) ";
            cin >> cont;
            if (cont == 'y'){
                continue;
            }
            else{return 0;}
        }
        }

}
