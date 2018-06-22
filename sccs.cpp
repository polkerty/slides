#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <string>
#include <utility>
#include <functional>
#include <queue>
#include <stack>
#include <list>

using namespace std;

#define MOD 1000000007
#define ULL	unsigned long long
#define LL long long
typedef vector<ULL> vi;
typedef vector<ULL> vu;
#define AVI(n) vector<ULL>a(n);rvi(a);
#define AVU vector<ULL>b(n);rvi(b);
#define RNI ULL n;scanf("%llu",&n);
#define RNU ULL n;scanf("%llu", &n);
#define WR(a) for(auto b:a)cout << b << ' '; cout << endl;


inline void rvi(vi& a) { for ( ULL i = 0; i <a.size(); ++i) scanf("%llu", &a[i]); }
inline void rvu(vu& a) { for ( ULL i = 0; i <a.size(); ++i) scanf("%llu", &a[i]); }

using namespace std;
 
 int depth = 0;
 
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // An array of adjacency lists
 
    // Fills Stack with vertices (in increasing order of finishing
    // times). The top element of stack has the maximum finishing 
    // time
    
        
    
    void fillOrder(int v, bool visited[], stack<int> &Stack);
    void fillOrder2(int v, bool visited[], stack<int> &Stack);
 
    // A recursive function to print DFS starting from v
    void DFSUtil(int v, bool visited[]);
public:
    vector<int> cur_scc;
	vector<vector<int>> sccs;
    Graph(int V);
    void addEdge(int v, int w);
 
    // The main function that finds and prints strongly connected
    // components
    vector<vector<int>> getSCCs();
 
    // Function that returns reverse (or transpose) of this graph
    Graph getTranspose();
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cur_scc.push_back(v);
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}
 
Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
	++depth;
	cerr << depth << endl;
    // Mark the current node as visited and print it
    visited[v] = true;
 	
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i) {
        if(!visited[*i]) {
            fillOrder(*i, visited, Stack);
            
        }
        
            
    }
 
    // All vertices reachable from v are processed by now, push v 
    Stack.push(v);
	
	--depth;
}
 
 
// The main function that finds and prints all strongly connected 
// components
vector<vector<int>> Graph::getSCCs()
{

	vector<vector<int>> sccs;
	vector<int> cur_scc;
    stack<int> Stack;
 
 
    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
 
    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < V; i++) {
        if(visited[i] == false)
            fillOrder(i, visited, Stack);
    }
 
 
 
    // Create a reversed graph
    Graph gr = getTranspose();
 
    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();
 
        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
        	if ( gr.cur_scc.size() ){
            gr.sccs.push_back(gr.cur_scc);
            }
            gr.cur_scc.clear();
            gr.DFSUtil(v, visited);
        }
    }
    
    if ( gr.cur_scc.size() ) {
    	gr.sccs.push_back(gr.cur_scc);
    }
    return gr.sccs;
}
 
// Driv
int main() {
	
	
	
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
	int t;
	scanf("%d", &t);
	
	while(t--){
		int n, m;
		scanf("%d %d", &n, &m);
		
		vector<vector<int>> adjlist(n);
		Graph g(n);
		for ( int i = 0; i < m; ++i ) {
			int a, b;
			scanf("%d %d", &a, &b);
			//--a; --b;
			g.addEdge(a, b);
			adjlist[a].push_back(b);
		}
		
		vector<vector<int>> sccs = g.getSCCs();
		
		int cnt = 0;
		
		vector<int> guys(sccs.size(), 1);
		
		map<int, int> which;
		
		for ( int i = 0; i < sccs.size(); ++i ) {
			for ( int j = 0; j < sccs[i].size(); ++j ) {
			
				which[sccs[i][j]] = i;
				//cout << sccs[i][j] << ' ';
			}
			//cout << endl;
		}
		
		vector<set<int>> alist;
		
		
		
		for ( int i = 0; i < sccs.size(); ++i ) {
			if ( !sccs[i].size() ) continue;
			for ( int j = 0; j < sccs[i].size(); ++j ) {
				for ( int k = 0; k < adjlist[sccs[i][j]].size(); ++k ) {
					if ( which[adjlist[sccs[i][j]][k]] != i ) {
						alist[i].insert(which[adjlist[sccs[i][j]][k]] );
					}
				}
			}
			
		}
		
		int i = 0;
		for ( auto a : alist ) {
			for ( auto b : a ) {
				cout << i << ' ' << b << endl;
			}
			++i;
		}
	
	}
	
}