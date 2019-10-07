#include <iostream> 
#include<math.h>
#include<windows.h>
#include <conio.h>
#include<stdlib.h>
#include<thread>
using namespace std;
void gotoxy(int x, int y)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(hOut, c);
}
void print_UI(char UI[25][25])
{
	for(int i=0;i<27;i++)
	{
		for(int j=0;j<27;j++)	
		{
			if(j == 0||j == 26) 
			{
				gotoxy(j,i); // noted that the cursor use x-y cordination system nut not i-j coordination system.
				cout<<"|";
			}
			else if(i == 0||i == 26)
			{
				gotoxy(j,i);
				cout<<"-";
			}
			else if(UI[i-1][j-1] == '*'||UI[i-1][j-1] == '@'||UI[i-1][j-1] =='&')
			{
				gotoxy(j,i);
				cout<<"*";
			}
//			else if(UI[((i-1)-((i-1)%2))/2][((j-1)-((j-1)%2))/2] == '#')
//			{
//				cout<<" ";
//			}
		}
	}
}
void start_up(char UI[25][25])
{
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<25;j++)
		{
			UI[i][j]='#';
		}
	}
}
void generate(char UI[25][25])
{
	int flag = 0,temp =0;
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<25;j++)
		{
			if(UI[i][j] == '&')
			{
				flag = 1;
				break;
			}
		}
		if(flag == 1)
		{
			break;
		}
	}	
	if(flag == 0)
	{
		while(temp==0)
		{
			int temp_i= (rand()%10)+(rand()%10)+(rand()%5);
			int temp_j = (rand()%10)+(rand()%10)+(rand()%5);	
			if(UI[temp_i][temp_j]!='@'&&UI[temp_i][temp_j]!='*')
			{
				UI[temp_i][temp_j]='&';
				temp=1;
			}
		}
		
	}
}
int find_head(char UI[25][25])
{
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<25;j++)
		{
			if(UI[i][j] == '*')
			{
				return 100*i+j;
			}
		}
	}
}
void map_copy(char UI[25][25], char temp_UI[25][25])
{
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<25;j++)
		{
			UI[i][j] = temp_UI[i][j]; 
		}
	}
} 
void restart_empty(int empty[625][2])
{
	for(int i=0;i<625;i++)
	{
		for(int j=0;j<2;j++)
		{
			empty[i][j] =-1;
		}
	}
}
bool check_duplicate(int empty[625][2],int ref_i,int ref_j)
{
	for(int i=0;i<625;i++)
	{
		for(int j=0;j<2;j++)
		{
			if(ref_i==empty[i][0]&&ref_j == empty[i][1])
			{
				return 0;
			}
		}
	}
	return 1;
}
void move_follow(char UI[25][25],char temp_map[25][25],int orig_i,int orig_j,int last_i,int last_j,int empty[625][2],int lines)
{
	empty[lines][0] = orig_i;
	empty[lines][1] = orig_j;
	if(UI[orig_i+1][orig_j] == '@'&&check_duplicate(empty,orig_i+1,orig_j))
	{
		    lines++;
			temp_map[orig_i][orig_j] = '@';
			move_follow(UI,temp_map,orig_i+1,orig_j,orig_i,orig_j,empty,lines);
	}
	if(UI[orig_i-1][orig_j] == '@'&&check_duplicate(empty,orig_i-1,orig_j))
	{
			lines++;
			temp_map[orig_i][orig_j] = '@';
			move_follow(UI,temp_map,orig_i-1,orig_j,orig_i,orig_j,empty,lines);
		
	}
	if(UI[orig_i][orig_j-1] == '@'&&check_duplicate(empty,orig_i,orig_j-1))
	{
			lines++;
            temp_map[orig_i][orig_j] = '@';
			move_follow(UI,temp_map,orig_i,orig_j-1,orig_i,orig_j,empty,lines);
		
	}
	if(UI[orig_i][orig_j+1] == '@'&&check_duplicate(empty,orig_i,orig_j+1))
	{
			lines++;
			temp_map[orig_i][orig_j] = '@';
			move_follow(UI,temp_map,orig_i,orig_j+1,orig_i,orig_j,empty,lines);
		
	}
}
void eat(char UI[25][25])
{
	int head_i, head_j,head_data;
	head_data = find_head(UI);
	head_i = (head_data-(head_data%100))/100;
	head_j = head_data%100;
	if(UI[head_i+1][head_j] == '&')
	{
		UI[head_i+1][head_j]='*';
		UI[head_i][head_j] = '@';
	}
	else if(UI[head_i-1][head_j] == '&')
	{
		UI[head_i-1][head_j]='*';
		UI[head_i][head_j] = '@';
	}
	else if(UI[head_i][head_j+1] == '&')
	{
		UI[head_i][head_j+1]='*';
		UI[head_i][head_j] = '@';
	}
	else if(UI[head_i][head_j-1] == '&')
	{
		UI[head_i][head_j-1]='*';
		UI[head_i][head_j] = '@';
	}
}
void fil(char UI[25][25],char temp_map[25][25])
{  
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<25;j++)
		{
			if(UI[i][j]=='&')
			{
				temp_map[i][j]='&';
			}
			else if(temp_map[i][j]!='@'&&temp_map[i][j]!='*')
			{
				temp_map[i][j] = '#'; 
			}
		}
	}
	
}
void move(int direct, char UI[25][25])
{
	char temp_map[25][25];
	int head_i, head_j,head_data,empty[625][2];
	head_data = find_head(UI);
	head_i = (head_data-(head_data%100))/100;
	head_j = head_data%100;
	start_up(temp_map);
	restart_empty(empty);
	switch(direct)
	{
		case 1: temp_map[head_i-1][head_j] = '*';  break;
		case 2: temp_map[head_i+1][head_j] = '*';  break;
		case 3: temp_map[head_i][head_j-1] = '*';  break;
		case 4: temp_map[head_i][head_j+1] = '*';  break;
	}
	move_follow(UI,temp_map,head_i,head_j,-1,-1,empty,0);
	fil(UI,temp_map);
	map_copy(UI,temp_map);
}
bool check_death(char UI[25][25],int direct)
{
	int head_i, head_j,head_data;
	head_data = find_head(UI);
	head_i = (head_data-(head_data%100))/100;
	head_j = head_data%100;
	if((UI[head_i+1][head_j] == '@'&&direct==2)||
	   (UI[head_i-1][head_j] == '@'&&direct==1)||
	   (UI[head_i][head_j+1] == '@'&&direct==4)||
	   (UI[head_i][head_j-1] == '@'&&direct==3))
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}
int main()
{
	char map[25][25];
	int steady_key = 1, keylock_rl =1,keylock_ud =0;
	start_up(map);
	map[12][12] = '*';
	generate(map);
	print_UI(map);
//	system("pause");
    while(check_death(map,steady_key))
    {
    	if(_kbhit())
		{
			switch(_getch())
			{
				case 115:
					if(keylock_rl ==1)
					{
						steady_key = 2;
						keylock_ud=1;
						keylock_rl =0;
					    break;	
					}
				case 97:
					if(keylock_ud ==1)
					{
						steady_key = 3;
						keylock_rl=1;
						keylock_ud =0;
					    break;	
					}
        		case 100:
        			if(keylock_ud ==1)    // locker tricks
					{
						steady_key = 4;
						keylock_rl=1;
						keylock_ud =0;
					    break;	
					}
        		case 119:
        		    if(keylock_rl ==1)
					{
						steady_key = 1;
						keylock_ud=1;
						keylock_rl=0;
					    break;	
					}
			}
	    }
		Sleep(100);
		system("cls");
		eat(map);
		move(steady_key,map);
		generate(map);
		print_UI(map);
	}
	system("cls");
	gotoxy(18,12);
	cout<<"Game over";
	system("pause");
	return 0;
}
