#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
graph G {
1 -- { 2 5 };
2 -- 3;
4 -- 5;
6 -- 8;
5 -- 8;
7 -- 9;
10 -- 12;
3 -- 6;
4 -- 11;
2 -- 11;
8 -- 10;
9 -- 10;
6 -- 1;
}*/

int main() {
	int n, m;
	cin >> n >> m;
	cout << "graph G {" << endl;
	cout << "graph[size=\"4,4\"];" << endl;
	cout << "node[shape=circle];" << endl;
	cout << "edge[arrowhead=\"odiamond\"];" << endl;
	cout << "node[nodesep=0.75];" << endl;
	for ( int i = 0; i < m; ++i ) {
		int a, b;
		cin >> a >> b;
		cout << a << " -- " << b << ";" << endl;
	}
	cout << "}" << endl;;
	
}