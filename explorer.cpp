//212642

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;

struct Board;

const int DIM = 8, CNT = 4;

map<vector<pair<int, int>>, int> loc;
//vector<vector<pair<int, int>>> boards;

vector<Board> fellows(1000000);

int dmax = 0;
map<int, int> dists;

struct Board {
	vector<pair<int, int>> b;
	
	int pred, self, dist;
	Board() {
		b = vector<pair<int, int>>(4);
	}
	
	Board( vector<pair<int, int>> _b ) {
		b = _b;
	}

	void draw () {
	
		for ( int i = 0; i < DIM; ++i ) {
			for ( int j = 0; j < DIM; ++j ) {
				bool f = false;
				for ( int k = 0; k < CNT; ++k ) {
					if ( b[k].first == i && b[k].second == j ) {
						f = true;
						break;
					}
				}
				cerr << (f ? " | " : " _ " ) ;
			}
			cerr << endl;
		}
	}

	void to_string() {
		for ( auto c : b ) {
			cerr << c.first << ' ' << c.second << "; ";
		}
		
		cerr << " / pred: " << pred << "; self: "  << self << "; dist: " << dist << endl;
		cerr << endl;
	}

	void update_self() {
		sort(b.begin(), b.end());
		
		self = loc[b];
// 		
// 		
// 		bool ne = false;
// 		if ( loc.find(b) == loc.end() ) {
// 			loc[b] = loc.size();
// 			ne = true;
// 			
// 			
// 			self = loc.size();		
// 			fellows[self] = *this;	
// 			
// 			
// 		} else {
// 			self = loc[b];
// 		}
// 		
// 		
// 				
				
		//if ( ne ) boards[b] = self;
		
		
	}

	
	Board( vector<pair<int, int>>  _b, int _p, int _d) {
		b = _b;
		pred = _p;
		dist = _d;
				
		
	}
	
		
	vector<Board> neighbors (  ) {
		vector<Board> ret;
		set<pair<int, int>> sides, all;
		set<int> xs, ys;
		for (auto t : b  ) {
			if ( t.first == 0 || t.first == DIM - 1 || t.second == 0 || t.second == DIM - 1 ) sides.insert(t);
			all.insert(t);
			xs.insert(t.first);
			ys.insert(t.second);
		}
		
		bool show = ( false ); //18844 );
		
		if ( show ) {
			draw();
			for ( auto s : all  ) cerr << "have: " << s.first << ' ' << s.second << endl;
		}
		if ( show ) to_string();
		for ( int i = 0; i < CNT; ++i ) {
			
			vector<pair<int, int>> poss;
			poss.push_back( {0, b[i].second} );
			poss.push_back( {DIM - 1,b[i].second} );
			poss.push_back( {b[i].first, 0} );
			poss.push_back( {b[i].first, DIM - 1} );
			
			for ( auto p : poss ) {
				if ( sides.find(p) == sides.end() ) {
					if ( show ) cerr << "f/s: " << b[i].first << ' ' << b[i].second << endl;
					bool good = true;
					if ( p.first != b[i].first ) {
						if ( p.first < b[i].first  ) {
							for ( int w = p.first + 1; w < b[i].first; ++w ) {
								if ( all.find({w, b[i].second}) != all.end() ) {
									good = false;
									break;
								}
							}
						} else {
							for ( int w = p.first - 1; w > b[i].first; --w ) {
								if ( all.find({w, b[i].second}) != all.end() ) {
									good = false;
									break;
								}
							}						
						}
					} else if ( p.second != b[i].second ) {
						if ( p.second < b[i].second  ) {
							for ( int w = p.second + 1; w < b[i].second; ++w ) {
								if (  show ) cerr << "checking if we have " << b[i].first << ' ' << w << endl;
								if ( all.find({b[i].first, w}) != all.end() ) {
									if ( show)cerr << "Yup! " << endl;
									good = false;
									break;
								}
								if ( show )cerr << "No!" << endl;
							}
						} else {
							for ( int w = p.second - 1; w > b[i].second; --w ) {
								if (  show ) cerr << "checking if we have " << b[i].first << ' ' << w << endl;
								if ( all.find({b[i].first, w}) != all.end() ) {
									if ( show)cerr << "Yup! " << endl;
									good = false;
									break;
								}
								if ( show )cerr << "No!" << endl;
							}						
						}
					}
				if ( show ) cerr << good << ": " << b[i].first << ' ' << b[i].second << "; " << p.first <<  ' ' << p.second << endl;
					
					if ( !good ) continue;
					
					Board a(b, self, dist + 1);
					a.b[i] = p;
					a.update_self();
					if ( show) a.draw();
					ret.push_back(a);
				}
			}
			

			for ( int j = 0; j < CNT; ++j ) {
				if ( i == j ) continue;
				vector<pair<int, int>> poss;
				
				if ( b[i].first == b[j].first && abs(b[i].second- b[j].second ) > 1 ) {
					bool good = true;
					for ( int k = 0; k < CNT; ++k ) {
						if ( k == i || k == j ) continue;
						if ( b[k].first == b[i].first && (( b[k].second > b[i].second && b[k].second < b[j].second ) ||( b[k].second < b[i].second && b[k].second > b[j].second ))){
							good = false;
							break;
						}
					}
					
										
					if ( good ) { 
						if ( b[i].second < b[j].second ) {
							poss.push_back( { b[i].first, b[j].second - 1 } );
							
						} else {
							poss.push_back ( { b[i].first, b[j].second + 1 } );
						}
					
					}
					
										
				} else if ( b[i].second == b[j].second && abs(b[i].first-b[j].first ) > 1 ) {
					bool good = true;
					for ( int k = 0; k < CNT; ++k ) {
						if ( k == i || k == j ) continue;
						if ( b[k].second == b[i].second && (( b[k].first > b[i].first && b[k].first < b[j].first ) ||( b[k].first < b[i].first && b[k].first > b[j].first ))){
							good = false;
							break;
						}
					}
					
					
					if ( good ) { 
						if ( b[i].first < b[j].first ) {
							poss.push_back( { b[j].first - 1, b[j].second } );
							
						} else {
							poss.push_back ( { b[j].first + 1, b[j].second } );
						}
					
					}
					

				} 
				
				
				
				for ( auto p : poss ) {
					if ( p.first >= 0 && p.first <= DIM - 1 && p.second >= 0 && p.second <= DIM - 1 ) {
						Board a(b, self, dist + 1);
						a.b[i] = p;
						a.update_self();
						ret.push_back(a);
					}
				}
								
				
				
			}
		}
		
		
		return ret;
				
	}
	
	
	
	
	
	void trail() {
		if ( pred > -1 ) {
			fellows[pred].trail();
		}
		to_string();
		draw();
	}
};

int main () {
	
	queue<Board> current;
	
	
	vector<pair<int, int>> c;
	c.push_back({0,0});
	c.push_back({0, DIM - 1});
	c.push_back({DIM - 1,0});
	c.push_back({DIM - 1, DIM - 1});
	
	loc[c] = 0;
	//boards[0] = (c);
	dists[0] = 0;
	
	Board start(c, -1, 0 );
	
	fellows[0] = start;
	start.update_self();
	
	current.push(start);
	
	
	vector<pair<int, int>> magic;
	magic.push_back({1,5});
	magic.push_back({1,6});
	magic.push_back({6,1});
	magic.push_back({6,6});
	
	
	int num = 0;
	
	int item = -1;


	//establish these items.

	int tot = 0;
	for ( int i = 0; i < 61; ++i ) {
		for ( int j = i + 1; j < 62; ++j )  {
			for ( int k = j + 1; k < 63; ++k ) {
				for ( int l = k + 1; l < 64; ++l, ++tot ) {
					if ( tot % 1000 == 0 ) cerr << "a" << tot << endl;
					vector<pair<int, int>> coords;
					coords.push_back({i/8, i%8});
					coords.push_back({j/8, j%8});
					coords.push_back({k/8, k%8});
					coords.push_back({l/8, l%8});
					loc[coords] = tot;
					fellows[tot] = Board(coords);
				}
			}
		}
	}

	vector<vector<int>> adjlist(tot);
	
	tot = 0;


	while ( true ) {
	
		int id;
		cin >> id;
	
		fellows[id].to_string();
	
		fellows[id].draw();
	
	}
		
	
// 	int i = 0;
// 	for ( auto a : adjlist ) {
// 		
// 		for ( auto b : a ) {
// 			cout << i << ' ' << b <<  endl;
// 		}
// 		++i;
// 	}
// 	
	
	
// 	vector<int> deads(34);
// 	
// 	int tough = 0;
// 	for ( int i = 0; i < dists.size(); ++i ) {
// 		
// 		auto n = fellows[i].neighbors(true);
// 		bool is_deadend = true;
// 		for ( auto s : n ) {
// 			s.update_self();
// 			if ( fellows[i].dist == 31 ) cerr << "self: " << s.self << endl;
// 			if ( dists[s.self] > fellows[i].dist ) {
// 				is_deadend = false;
// 				break;
// 			}
// 			if ( fellows[i].dist == 31 ) cerr << dists[s.self] << ' '; 
// 		}
// 		if ( fellows[i].dist == 31 ) cerr << endl;
// 		if ( is_deadend ) ++deads[fellows[i].dist];
// 		
// 	}
// 	for ( auto d : deads ) cerr << d << '\t'; cerr << endl;
// 	
		
	//cerr << dists.size() << ' ' <<  dmax << ' ' << tough <<  endl;	
// 	if ( item > -1 ){ 
// 		fellows[item].trail();
// 	} else {
// 		cerr << "Not found!" << endl;
// 	}
	
	
	
	
	
}