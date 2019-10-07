#include<stdio.h>
#include<stdlib.h>
#include <iostream> 
#include<math.h>
#include<windows.h>
#include <conio.h>
#include<stdlib.h>
#include<thread>
#include<string.h>
#include<time.h>
using namespace std;
int failcode = 0;
int mine_sofar = 0;
void gotoxy(int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(hOut, c);
}

void print_UI (int map[10][10][2]) {
	gotoxy(12, 6);
	cout<<" 1 2 3 4 5 6 7 8 9 10";
	gotoxy(11, 7);
	for (int i = 0; i < 10; i++) {
	   cout<<i + 1; 
	   for (int j = 0; j < 10; j++) {
	   	if (map[i][j][0] == 0) {
	   		cout<<" *";
	    } 
		else if (map[i][j][0] == 2) {
			cout<<" ^";
		}else if (map[i][j][0] == 1 && map[i][j][1] == -1) {
	    	cout<<" #";
		} else {
			cout<<" "<<map[i][j][1]; 
		}
	   }
	   if(i == 8) {
	   	gotoxy(10, 8 + i);
	   } else {
	   	gotoxy(11, 8 + i);
	   }
	}
}

bool check_rand(int rand_list[][2],int x, int y, int curlen) {
	for (int i = 0; i < curlen; i++) {
		if (rand_list[i][0] == x && rand_list[i][1] == y) {
			return true;
		} 
	}
	return false;
}

void explore(int map[10][10][2],int x, int y, int pos, int visited[100][2]) {
	if(map[x][y][1] == -1) {
		return;
	} else if (!check_rand(visited, x, y, pos) && x >= 0 && x <= 9 && y >= 0 && y <= 9) {
		map[x][y][0] = 1;
		if (map[x][y][1] == 0) {
			visited[pos][0] = x;
			visited[pos][1] = y;
			pos++;
			explore(map, x - 1, y - 1, pos, visited);
			explore(map, x - 1, y , pos, visited);
			explore(map, x - 1, y + 1, pos, visited);
			explore(map, x, y - 1, pos, visited);
			explore(map, x, y + 1, pos, visited);
			explore(map, x + 1, y - 1, pos, visited);
			explore(map, x + 1, y, pos, visited);
			explore(map, x + 1, y + 1, pos, visited);
		}
	} else {
		return;
	}
} 
void manip_UI(int map[10][10][2], char mode, int x, int y) {
  switch(mode) {
  	case 'c':
        if (map[x][y][0] == 1) {
        	gotoxy(12, 28);
			cout<<"this point has already been explored";
		} else {
			map[x][y][0] = 1; 
			if (map[x][y][1] == -1) {
				failcode  = 1;
			} else if (map[x][y][1] == 0) {
				int visited[100][2];
				int pos = 0;
				explore(map, x, y, pos, visited);
			}
		} 
		break;
	case 'm':
		if (map[x][y][0] == 1) {
			gotoxy(12, 28);
			cout<<"no need to mark                     ";
		} else if (map[x][y][0] == 2) {
			gotoxy(12, 28);
			cout<<"this point has been marked          ";
		} else {
		   	map[x][y][0] = 2; 
		   	mine_sofar++;
		}
		break;
	case 'd':
		if (map[x][y][0] != 2) {
			gotoxy(12, 28);
			cout<<"this point has not been marked          ";
		} else {
			map[x][y][0] = 0;
			mine_sofar--; 
		}
		break;
  }
}


void startup_UI(int map[10][10][2]) {
    int temp[10][2], curlen = 0;
    srand((unsigned) time(NULL));
    int cord_x = 0; int cord_y =  0;
    for (int i = 0; i < 10; i++) {
    	do {
    	cord_x = rand() % 10;
    	cord_y = rand() % 10;		
		}
		while (check_rand(temp, cord_x, cord_y, curlen));
        temp[curlen][0] = cord_x;
        temp[curlen][1] = cord_y;
        curlen++;
        map[cord_x][cord_y][1] = -1;
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j][1] != -1) {
				map[i][j][1] = ((i >= 1 && j >= 1) ? !(map[i - 1][j - 1][1] + 1) : 0) +
				               ((i >= 1 ) ? !(map[i - 1][j][1] + 1) : 0) + 
							   ((i >= 1 && j <= 8) ? !(map[i - 1][j + 1][1] + 1) : 0) +
				               ((j >= 1) ? !(map[i][j - 1][1] + 1) : 0) +
							   ((j <= 8) ? !(map[i][j + 1][1] + 1) : 0) +
				               ((i <= 8 && j >= 1) ? !(map[i + 1][j - 1][1] + 1) : 0) +
							   ((i <= 8) ? !(map[i + 1][j][1] + 1) : 0) +
				               ((i <= 8 && j <= 8) ? !(map[i + 1][j + 1][1] + 1) : 0);
			} 
			map[i][j][0] = 0;
		}
	}
}

int main(int argc, char * argv[]) {
	   int escape = 0, x = 0, y = 0, map[10][10][2];
	   char command = '$';
	   cout<<"***************************"<<endl
	       <<"welcome to minesweeper"<<endl
	       <<"by: Derek Jiang"<<endl
	       <<"2019:5:18"<<endl
		   <<"***************************";
	   Sleep(1000);
	   startup_UI(map);
		print_UI(map);
	   while(!failcode)  {
	   	gotoxy(50, 2);
	   	cout<<"has find "<<mine_sofar<<" mines";
		gotoxy(50, 3);
		cout<<"remaining:  ";
		gotoxy(60, 3);
		cout<<10 - mine_sofar;
	   	gotoxy(12, 19);
	   	printf(">>>                 ");
	   	gotoxy(15, 19);
	   	cin>>command>>x>>y;
	   	manip_UI(map, command, y - 1, x - 1);
		print_UI(map);
	   }
}
