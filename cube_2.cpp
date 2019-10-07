#include <iostream> 
#include<math.h>
#include<windows.h>
#include <conio.h>
#include<stdlib.h>
#include<thread>
using namespace std;

void print_UI(char UI[18][20])
{
	for(int i=0;i<38;i++)
	{
		for(int j=0;j<42;j++)	
		{
			if(j == 0||j == 41)
			{
				cout<<"|";
			}
			else if(i == 0||i == 37)
			{
				cout<<"-";
			}
			else if(UI[((i-1)-((i-1)%2))/2][((j-1)-((j-1)%2))/2] == '*')
			{
				cout<<"+";
			}
			else if(UI[((i-1)-((i-1)%2))/2][((j-1)-((j-1)%2))/2] == '@') 
			{
				cout<<"+";
			}
			else if(UI[((i-1)-((i-1)%2))/2][((j-1)-((j-1)%2))/2] == '#')
			{
				cout<<" ";
			}
			else if(UI[((i-1)-((i-1)%2))/2][((j-1)-((j-1)%2))/2] == '-')
			{
				cout<<"-";
			}
			else if(UI[((i-1)-((i-1)%2))/2][((j-1)-((j-1)%2))/2] == '^')
			{
				cout<<"*";
			}
		}
		cout<<endl;
	}
}

void start_up(char UI[18][20])
{
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<20;j++)
		{
			UI[i][j]='#';
		}
	}
}
int generate(char UI[18][20])
{
	
	int temp = (rand()%5);
	switch(temp)
	{
		case 0: UI[0][10] = '*'; UI[1][10] = '*'; UI[2][10] = '*'; UI[3][10] = '*'; break; 
		case 1: UI[0][10] = '*'; UI[1][10] = '*'; UI[2][10] = '*'; UI[2][11] = '*'; break;
//		case 1: UI[0][12] = '*'; UI[0][13] = '*'; UI[0][14] = '*'; UI[1][12] = '*'; break;
		case 2: UI[0][10] = '*'; UI[0][11] = '*'; UI[1][11] = '*'; UI[1][12] = '*'; break;
		case 3: UI[0][10] = '*'; UI[0][11] = '*'; UI[1][10] = '*'; UI[1][11] = '*'; break;
		case 4: UI[0][10] = '*'; UI[0][11] = '*'; UI[0][12] = '*'; UI[1][11] = '*'; break;
//		case 0: UI[0][10] = '*'; UI[0][11] = '*'; UI[0][12] = '*'; UI[0][13] = '*'; break;	
//      case 0: UI[0][10] = '*'; UI[0][11] = '*'; UI[0][12] = '*'; UI[0][13] = '*'; UI[0][14] = '*'; break;
	} 
	return temp;
}
void UI_copy(char UI[18][20], char temp_UI[18][20])
{
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<20;j++)
		{
			UI[i][j] = temp_UI[i][j]; 
		}
	}
} 
void move_on(char UI[18][20])
{
	int flag = 1;
	char temp_UI[18][20];
	start_up(temp_UI);
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(UI[i][j] == '*')
			{
				temp_UI[i+1][j] = '*'; 
			}
			else if(UI[i][j] == '@')
			{
				temp_UI[i][j] = UI[i][j];
			}
		}
	}
	UI_copy(UI,temp_UI);
}
void move_left(char UI[18][20])
{
	int flag = 1;
	char temp_UI[18][20];
	start_up(temp_UI);
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(UI[i][j] == '*')
			{
				temp_UI[i][j-1] = '*'; 
			}
			else if(UI[i][j] == '@')
			{
				temp_UI[i][j] = UI[i][j];
			}
		}
	}
	UI_copy(UI,temp_UI);
}
void move_right(char UI[18][20])
{
	int flag = 1;
	char temp_UI[18][20];
	start_up(temp_UI);
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(UI[i][j] == '*')
			{
				temp_UI[i][j+1] = '*'; 
			}
			else if(UI[i][j] == '@')
			{
				temp_UI[i][j] = UI[i][j];
			}
		}
	}
	UI_copy(UI,temp_UI);
}
void move_down(char UI[18][20])
{
	int flag = 1;
	char temp_UI[18][20];
	start_up(temp_UI);
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(UI[i][j] == '*')
			{
				temp_UI[i+1][j] = '*'; 
			}
			else if(UI[i][j] == '@')
			{
				temp_UI[i][j] = UI[i][j];
			}
		}
	}
	UI_copy(UI,temp_UI);
}
void solidize_chain(char UI[18][20], int i, int j)
{
	UI[i][j] = '@';
	if(!(UI[i-1][j] == '#'||UI[i-1][j] == '@'))
	{
		solidize_chain(UI,i-1,j);
	}
	if(!(UI[i][j-1] == '#'||UI[i][j-1] == '@'))
	{
	    solidize_chain(UI,i,j-1);
	}
	if(!(UI[i][j+1] == '#'||UI[i][j+1] == '@'))
	{
		solidize_chain(UI,i,j+1);	
	}
	if(!(UI[i+1][j] == '#'||UI[i+1][j] == '@'))
	{
		solidize_chain(UI,i+1,j);	
	}
	
}
void solidize(char UI[18][20])
{
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(i == 0 && UI[17-i][j] == '*')
			{
				UI[17-i][j] = '@';
			}
			else if(UI[17-i][j] == '*'&& UI[18-i][j] == '@')
			{
				 solidize_chain(UI,17-i,j);
			}
		}
	}
}
bool check_solid(char UI[18][20])
{
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(UI[i][j] == '*')
			{
				return 0;
			}
		}
	}
	return 1;
}
bool check_bingo(char UI[18][20])
{
	int temp = 0;
	for(int i=0;i<18;i++)
	{
		temp=1;
		for(int j=0;j<20;j++)
		{
			if(!(UI[i][j] == '@'))
			{
				temp = 0;
				break;
			}
		}
		if(temp == 1)
		{
			break;
		}
	}
	return temp;
}
void eliminate(char UI[18][20])
{
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(UI[i][j] == '@')
			{
				UI[i][j] = '*';
			}
		}
	}
}
void effect(char UI[18][20],int flag)
{
	int temp = 0;
	for(int i=0;i<18;i++)
	{
		temp=1;
		for(int j=0;j<20;j++)
		{
			if((!(UI[i][j] == '@'))&&flag == 1)
			{
				temp = 0;
				break;
			}
			if((!(UI[i][j] == '-'))&&flag == 2)
			{
				temp = 0;
				break;
			}
			if((!(UI[i][j] == '^'))&&flag == 3)
			{
				temp = 0;
				break;
			}
			
		}
		if(temp == 1)
		{
			for(int j=0;j<20;j++)
			{
				if(flag == 1)
				{
					UI[i][j] = '-';
				}
				if(flag == 2)
				{
					UI[i][j] ='^';
				}
				if(flag == 3)
				{
					UI[i][j] = '#';
				}
			}
		}
	}
	system("cls");
	print_UI(UI);
	if(flag == 3)
	{
		eliminate(UI);
	}
}
void allocate_sub(char UI[18][20], int orig_i,int orig_j, int last_i ,int last_j,int lines,int empty[4][2])
{
	empty[lines][0] = orig_i;
	empty[lines][1] = orig_j;
//	cout<<empty[lines][0]<<" "<<empty[lines][1]<<" "<<lines<<endl;
	if(UI[orig_i+1][orig_j] == '*')
	{
		if((orig_i+1!=last_i||orig_j!=last_j)||(last_i<0&&last_j<0))
		{
			lines++;
			allocate_sub(UI,orig_i+1,orig_j,orig_i,orig_j,lines,empty);
		}
	}
	if(UI[orig_i-1][orig_j] == '*')
	{
		if((orig_i-1!=last_i||orig_j!=last_j)||(last_i<0&&last_j<0))
		{
			lines++;
			allocate_sub(UI,orig_i-1,orig_j,orig_i,orig_j,lines,empty);
		}
	}
	if(UI[orig_i][orig_j-1] == '*')
	{
		if((orig_i!=last_i||orig_j-1!=last_j)||(last_i<0&&last_j<0))
		{
			lines++;//very tricky bug -> line+1 in the recursion or lines++ first?
			allocate_sub(UI,orig_i,orig_j-1,orig_i,orig_j,lines,empty);
		}
	}
	if(UI[orig_i][orig_j+1] == '*')
	{
		if((orig_i!=last_i||orig_j+1!=last_j)||(last_i<0&&last_j<0))
		{
			lines++;
			allocate_sub(UI,orig_i,orig_j+1,orig_i,orig_j,lines,empty);
		}
	}
	
}
void rotate_cw(char UI[18][20],int type)
{
	char temp[18][20];
	int empty[4][2];
	int vert_dif,horiz_dif,flag = -1,orig_i,orig_j;
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(UI[i][j] == '*')
			{
				allocate_sub(UI,i,j,-1,-1,0,empty);
//				for(int h=0;h<4;h++)
//				{
//					for(int o=0;o<2;o++)
//					{
//						cout<<empty[h][o]<<" ";
//					}
//					cout<<endl;
//				}
//				cout<<"slice"<<endl;
				vert_dif = abs(max(max(empty[0][0],empty[1][0]),max(empty[2][0],empty[3][0]))
				              -min(min(empty[0][0],empty[1][0]),min(empty[2][0],empty[3][0])));
				horiz_dif = abs(max(max(empty[0][1],empty[1][1]),max(empty[2][1],empty[3][1]))
				              -min(min(empty[0][1],empty[1][1]),min(empty[2][1],empty[3][1])));
//				cout<<vert_dif<<" "<<horiz_dif<<endl;
                orig_i= min(min(empty[0][0],empty[1][0]),min(empty[2][0],empty[3][0]));
                orig_j = min(min(empty[0][1],empty[1][1]),min(empty[2][1],empty[3][1]));
				for(int k=0;k<18;k++)
				{
					for(int l=0;l<20;l++)
					{
						if(k>=-1+min(min(empty[0][0],empty[1][0]),min(empty[2][0],empty[3][0]))
						  &&k<=3+min(min(empty[0][0],empty[1][0]),min(empty[2][0],empty[3][0]))
						  &&l>=-1+min(min(empty[0][1],empty[1][1]),min(empty[2][1],empty[3][1]))
						  &&l<=3+min(min(empty[0][1],empty[1][1]),min(empty[2][1],empty[3][1])))
						{
//							cout<<"slice";
						 	if(UI[k][l]=='@')
							  {
//							    cout<<"slice";
							  	flag = 1;
							  	break;
							  }
							else
							{
//							  	cout<<"slice";
								temp[k][l]=
								UI[3+min(min(empty[0][0],empty[1][0]),min(empty[2][0],empty[3][0]))
								-(l-(-1+min(min(empty[0][1],empty[1][1]),min(empty[2][1],empty[3][1]))))]
							  	[(k-orig_i)+orig_j];
							}	
						}
						else 
						{
							temp[k][l] = UI[k][l];
						}
					}
					if(flag == 1)
					{
						break;
					}
				}
				if(flag == -1)
				{
//					cout<<"correct";
					UI_copy(UI,temp);
					flag = 0;
					break;
				}
			}
		if(flag == 0)
		{
			break;
		}
		}
	}
}
void rotate_cw(char UI[18][20])
{
	
}
void rotate_acw(char UI[18][20])
{
	
}
int main()
{
	system("mode con cols=60 lines=100");
	char UI[18][20];
	int count = 0, effect_flag = 0, type;
    start_up(UI);
	type = generate(UI);
	print_UI(UI);
	while(1)
	{
		if(count == 100)
		{
			system("cls");
			solidize(UI);
			if(check_solid(UI))
			{
				type = generate(UI);
			}
			if(check_bingo(UI))
			{
				effect_flag = 1;
			}
			solidize(UI);
			move_on(UI);
			print_UI(UI);
			count = 0;
		}
		if(_kbhit())
		{
			switch(_getch())
			{
				case 115:
					system("cls");
					solidize(UI);
        			move_down(UI);
        			print_UI(UI);
        			break;
				case 97:
					system("cls");
					solidize(UI);
        			move_left(UI);
        			print_UI(UI);
        			break;
        		case 100:
        			system("cls");
        			solidize(UI);
        			move_right(UI);
        			print_UI(UI);
        			break;
        		case 32:
        			system("cls");
        			solidize(UI);
        			rotate_cw(UI, type);
//         			system("pause");
        			print_UI(UI);
        			break;
			}
		}
		if(count == 20&&effect_flag == 1)
		{
			effect(UI,1);
			effect_flag++;
		}
		if(count == 40&&effect_flag == 2)
		{
			effect(UI,2);
			effect_flag++;
		}
		if(count == 60&&effect_flag == 3)
		{
			effect(UI,3);
			effect_flag=0;
		}
		Sleep(10);
		count++ ;
	}
	system("pause");
	return 0;
}
