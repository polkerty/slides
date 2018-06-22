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
 
int main() {
	
	
	
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
		// first read in the adjacency list;
		// then read in the strongly connected components 
		int n, m;
		scanf("%d %d", &n, &m);
		
		cerr << n <<' ' << m <<  endl;
		vector<vector<int>> adjlist(n);
		for ( int i = 0; i < m; ++i ) {
			int a, b;
			scanf("%d %d", &a, &b);
			//--a; --b;
			adjlist[a].push_back(b);
		}
		
		// read in scc
		
		
		int scc_cnt;
		cerr << "read: " << scanf("%d", &scc_cnt) << endl;
		
		
		cerr << scc_cnt << endl;
		vector<vector<int>> sccs(scc_cnt);

		
		for ( int i = 0; i < scc_cnt; ++i ) {
			int comps;
			scanf("%d", &comps);
			sccs[i] = vector<int>(comps);
			for ( int j = 0; j < comps; ++j ) {
				scanf("%d", &(sccs[i][j]));
			}
		}
		
		
		cerr << "All read!" << endl;
		
		int cnt = 0;
		
		
		map<int, int> which;
		
		for ( int i = 0; i < sccs.size(); ++i ) {
			for ( int j = 0; j < sccs[i].size(); ++j ) {
			
				which[sccs[i][j]] = i;
				//cout << sccs[i][j] << ' ';
			}
			//cout << endl;
		}
		
		cerr << "Heirs assigned" << endl;
		
		vector<set<int>> alist(sccs.size());
		
		
		
		cerr << sccs.size() << endl;
		
		int t = 0;
		for ( int i = 0; i < sccs.size(); ++i ) {
			if ( !sccs[i].size() ) continue;
			for ( int j = 0; j < sccs[i].size(); ++j ) {
				//cerr << "sccs[i][j] = " << sccs[i][j] << endl;
				//cerr << "adjlist[sccs[i][j]].size() = " << adjlist[sccs[i][j]].size() << endl;
				for ( int k = 0; k < adjlist[sccs[i][j]].size(); ++k ) {
					//cerr << i << ' ' << j << ' ' << k << endl;
					//cerr << sccs[i][j] << ' ' << adjlist[sccs[i][j]][k] << endl;
					//cerr << which[adjlist[sccs[i][j]][k]] << endl;
					if ( which[adjlist[sccs[i][j]][k]] != i ) {
						alist[i].insert(which[adjlist[sccs[i][j]][k]] );
					}
					
					++t;
					if ( t % 100000 == 0 ) cerr << t << endl;
					//cerr << t << endl;
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