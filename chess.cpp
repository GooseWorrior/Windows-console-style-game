#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int X = 10;
const int Y = 10;

print(vector<pair<int, int>> chess, vector<pair<int, int>> possible, pair<int, int> self) {
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (find(chess.begin(), chess.end(), pair<int, int>(i, j)) != chess.end()) {
				cout<<"& ";
			} else if (find(possible.begin(), possible.end(), pair<int, int>(i, j)) != possible.end()) {
				cout<<"^ ";
			} else if (pair<int, int>(i, j) == self) {
				cout<<"$ ";
			} else {
				cout<<"- ";
			}
		}
		cout<<endl;
	}
}


bool check_valid(int i, int j, vector<pair<int, int>> chess, pair<int, int> self) {
	return (find(chess.begin(), chess.end(), pair<int, int>(i, j)) == chess.end()) && pair<int, int>(i, j) != self;
	
}

bool check_eat(int i, int j, vector<pair<int, int>> visited, vector<pair<int, int>> chess, vector<pair<pair<int, int>, vector<pair<int, int>>>> & eat_lst, pair<int, int> self) {
	vector<pair<int, int>>::iterator it = find(visited.begin(), visited.end(), pair<int, int>(i, j)); 
	vector<pair<int, int>> list;
	pair<int, int> pos(i, j);
	if (it == visited.end()) {
		return 0;
	} else if (self.first - i == 0) {
		for (int k = min(self.second, j) + 1; k < max(self.second, j); k++) {
			if (find(visited.begin(), visited.end(), pair<int, int>(i + 1, k)) == visited.end() &&
			    find(visited.begin(), visited.end(), pair<int, int>(i - 1, k)) == visited.end()) {
			    	return 0;
			} else if (find(chess.begin(), chess.end(), pair<int, int>(i, k)) == chess.end()) {
					return 0;
			} else {
				list.push_back(pair<int, int>(i, k));
			}
		}
		eat_lst.push_back(pair<pair<int, int>, vector<pair<int, int>>>(pos, list));
		return 1;
	} else if (self.second - j == 0) {
		for (int k = min(self.first, i) + 1; k < max(self.first, i); k++) {
			if (find(visited.begin(), visited.end(), pair<int, int>(k, j - 1)) == visited.end() &&
			    find(visited.begin(), visited.end(), pair<int, int>(k, j + 1)) == visited.end()) {
			    	return 0;
			} else if (find(chess.begin(), chess.end(), pair<int, int>(k, j)) == chess.end()) {
					return 0;
			} else {
				list.push_back(pair<int, int>(k, j));
			}
		}
		eat_lst.push_back(pair<pair<int, int>, vector<pair<int, int>>>(pos, list));
		return 1;
	} else if (abs(self.first - i) == abs(self.second - j)) {
		if ((i < self.first && j < self.second) || (i > self.first && j > self.second)) {
			for (int k = min(self.first, i) + 1, q = min(self.second, j) + 1; q < max(self.second, j); k++, q++) {
				if (!(find(visited.begin(), visited.end(), pair<int, int>(k, q - 1)) != visited.end() &&
			      find(visited.begin(), visited.end(), pair<int, int>(k + 1, q)) != visited.end()) && 
				!(find(visited.begin(), visited.end(), pair<int, int>(k, q + 1)) != visited.end() &&
			      find(visited.begin(), visited.end(), pair<int, int>(k - 1, q)) != visited.end())) {
					return 0;      	
				} else if (find(chess.begin(), chess.end(), pair<int, int>(k, q)) == chess.end()) {
					return 0;
				} else{
					list.push_back(pair<int, int>(k, q));
				}
			}
		} else if ((i < self.first && j > self.second) || (i > self.first && j < self.second)) {
			for (int k = min(self.first, i) + 1, q = max(self.second, j) - 1; q < max(self.second, j); k++, q--) {
				if (!(find(visited.begin(), visited.end(), pair<int, int>(k, q - 1)) != visited.end() &&
			      find(visited.begin(), visited.end(), pair<int, int>(k - 1, q)) != visited.end()) && 
				!(find(visited.begin(), visited.end(), pair<int, int>(k, q + 1)) != visited.end() &&
			      find(visited.begin(), visited.end(), pair<int, int>(k + 1, q)) != visited.end())) {
					return 0;      	
				} else if (find(chess.begin(), chess.end(), pair<int, int>(k, q)) == chess.end()) {
					return 0;
				} else{
					list.push_back(pair<int, int>(k, q));
				}
			}
		}
		eat_lst.push_back(pair<pair<int, int>, vector<pair<int, int>>>(pos, list));
		return 1;
	} 
	return 0;
}

void solve(vector<pair<int, int>> visited, vector<pair<int, int>> chess, vector<pair<int, int>> & possible, pair<int, int> self, vector<pair<pair<int, int>, vector<pair<int, int>>>> & eat_lst) {
	possible.clear();
	eat_lst.clear();
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (check_valid(i, j, chess, self)) {
			    if (max(abs(i - self.first), abs(j - self.second)) == 1 ) {
					possible.push_back(pair<int, int>(i, j));    	
				} else if (check_eat(i, j, visited, chess, eat_lst, self)) {
					possible.push_back(pair<int, int>(i, j)); 
				}
			}
		}
	}
}
int main() {
	vector<pair<int, int>> chess;
	vector<pair<int, int>> possible;
	vector<pair<int, int>> visited;
	vector<pair<pair<int, int>, vector<pair<int, int>>>> eat_lst;
	pair<int, int> self;
	int i = 0, j = 0;
	bool mv = false;
	cout<<"plz input self:";
	cin>>self.first>>self.second;
	visited.push_back(self);
	/*while(1) {
		cout<<"plz input chess (100end):"<<endl;
		cin>>i>>j;
		if (i == 100 || j == 100) break;
		if (self != pair<int, int>(i, j) && find(chess.begin(), chess.end(), pair<int, int>(i, j)) == chess.end())
		chess.push_back(pair<int, int>(i, j)); 
		else cout<<"this is not valid"<<endl;
	}*/
	srand(time(0));
	for (int k = 0; k < 20; k++) {
		while (1) {
			i = rand() % 10;
			j = rand() % 10;
			cout<< i <<" "<< j<< endl;
			if (self != pair<int, int>(i, j) && find(chess.begin(), chess.end(), pair<int, int>(i, j)) == chess.end()) {
				chess.push_back(pair<int, int>(i, j));
				break;	
			} 
		}
	}
	system("cls");
	solve(visited, chess, possible, self, eat_lst);
	print(chess, possible, self);
	while (1) {
		if (mv) {
			system("cls");
			if (possible.empty()) {
				cout<<"there is no way to go"<<endl;
				Sleep(1000);
				return 0;
			}
			self.first = i; self.second = j;
			visited.push_back(pair<int, int>(i, j)); 
			for (auto q : eat_lst) {
				if (q.first == pair<int, int>(i, j)) {
					for (auto p : q.second) {
						chess.erase(find(chess.begin(), chess.end(), p)); 
					}
					break;
				}
			}
			solve(visited, chess, possible, self, eat_lst); 
			print(chess, possible, self);
			mv = false;	
		}
		if(_kbhit()) {
			switch(_getch()) {
				case 99: 
					for (int p = self.first, q = self.second; p < Y && q < X; p++, q++) {
						if (find(possible.begin(), possible.end(), pair<int, int>(p, q)) != possible.end()){
							i = p; j = q; mv = true; break;		
						}
					}
					break;
				case 101:
					for (int p = self.first, q = self.second; p >= 0 && q < X; p--, q++) {
						if (find(possible.begin(), possible.end(), pair<int, int>(p, q)) != possible.end()){
							i = p; j = q; mv = true; break;		
						}
					}
					break;
				case 122:
					for (int p = self.first, q = self.second; p < Y && q >= 0; p++, q--) {
						if (find(possible.begin(), possible.end(), pair<int, int>(p, q)) != possible.end()){
							i = p; j = q; mv = true; break;		
						}
					}
					break;
				case 113:
					for (int p = self.first, q = self.second; p >= 0 && q >= 0; p--, q--) {
						if (find(possible.begin(), possible.end(), pair<int, int>(p, q)) != possible.end()){
							i = p; j = q; mv = true; break;		
						}
					}
					break;
				case 119:
					for (int p = self.first; p >= 0; p--) {
						if (find(possible.begin(), possible.end(), pair<int, int>(p, self.second)) != possible.end()){
							i = p; j = self.second; mv = true; break;		
						}
					}
					break;
				case 115:
					for (int p = self.first; p < Y; p++) {
						if (find(possible.begin(), possible.end(), pair<int, int>(p, self.second)) != possible.end()){
							i = p; j = self.second; mv = true; break;		
						} 
					}
					break;
				case 97:
					for (int p = self.second; p >= 0; p--) {
						if (find(possible.begin(), possible.end(), pair<int, int>(self.first, p)) != possible.end()){
							i = self.first; j = p; mv = true; break;		
						}
					}
					break;
        		case 100:
        			for (int p = self.second; p < X; p++) {
						if (find(possible.begin(), possible.end(), pair<int, int>(self.first, p)) != possible.end()){
							i = self.first; j = p; mv = true; break;		
						}
					}
					break;
        		default:
        			mv = false; break;
			}
		}	
	}
	
	/*for (int k = 0; k < 1000; k++) {
		solve(visited, chess, possible, self, eat_lst);
		print(chess, possible, self);
		while (1){
			cout<<"plz input your step:";
			cin>>i>>j;
			if (find(possible.begin(), possible.end(), pair<int, int>(i, j)) != possible.end()) {
				self.first = i; self.second = j;
				visited.push_back(pair<int, int>(i, j)); 
				for (auto q : eat_lst) {
					if (q.first == pair<int, int>(i, j)) {
						for (auto p : q.second) {
							chess.erase(find(chess.begin(), chess.end(), p)); 
						}
						break;
					}
				}
				break;
			} else {
				cout<<"invalid position"<<endl;
			}
		}
	}*/
	return 0;
}
