#include <iostream> 
#include<math.h>
#include<windows.h>
#include <conio.h>
#include<stdlib.h>
using namespace std; 
void left(int a[4][4])
{
	int flag=0;
	int pin=0;
	for(int i=0;i<4;i++)
	{
		flag=0;
		pin=0;
		while(flag!=1)
		{
			for(int j=0;j<3;j++)
			{
				if(a[i][3-j]!=0&&a[i][3-j]!=a[i][2-j]&&a[i][2-j]!=0)
				{
					
				}
			    else if(a[i][3-j]!=0&&a[i][3-j]==a[i][2-j]&&a[i][2-j]!=0&&pin==0)
				{
					a[i][2-j]=a[i][3-j]+a[i][2-j];
					a[i][3-j]=0;
					pin=1;
				}
			    else if(a[i][3-j]!=0&&a[i][2-j]==0)
			    {
					
					a[i][2-j]=a[i][3-j]+a[i][2-j];
					a[i][3-j]=0;
				}
			}
			for(int j=0;j<3;j++)
			{
				if(a[i][3-j]!=0&&a[i][2-j]==0)
				{
					flag=0;
					break;
				}
				else
				{
					flag=1;
				}
			}
			
		}
	}
}
void right(int a[4][4])
{
	int flag=0;
	int pin=0;
	for(int i=0;i<4;i++)
	{
		flag=0;
		pin=0;
		while(flag!=1)
		{
			for(int j=0;j<3;j++)
			{
				if(a[i][j]!=0&&a[i][j]!=a[i][j+1]&&a[i][j+1]!=0)
				{
					
				}
			    else if(a[i][j]!=0&&a[i][j]==a[i][j+1]&&a[i][j+1]!=0&&pin==0)
				{
					a[i][j+1]=a[i][j]+a[i][j+1];
					a[i][j]=0;
					pin=1;
				}
			    else if(a[i][j]!=0&&a[i][j+1]==0)
			    {
					
					a[i][j+1]=a[i][j]+a[i][j+1];
					a[i][j]=0;
				}
			}
			for(int j=0;j<3;j++)
			{
				if(a[i][j]!=0&&a[i][j+1]==0)
				{
					flag=0;
					break;
				}
				else
				{
					flag=1;
				}
			}
			
		}
	}
}
void up (int a[4][4])
{
	int flag=0;
	int pin=0;
	for(int j=0;j<4;j++)
	{
		flag=0;
		pin=0;
		while(flag!=1)
		{
			for(int i=0;i<3;i++)
			{
				if(a[3-i][j]!=0&&a[3-i][j]!=a[2-i][j]&&a[2-i][j]!=0)
				{
					
				}
			    else if(a[3-i][j]!=0&&a[3-i][j]==a[2-i][j]&&a[2-i][j]!=0&&pin==0)
				{
					a[2-i][j]=a[3-i][j]+a[2-i][j];
					a[3-i][j]=0;
					pin=1;
				}
			    else if(a[3-i][j]!=0&&a[2-i][j]==0)
			    {
					
					a[2-i][j]=a[3-i][j]+a[2-i][j];
					a[3-i][j]=0;
				}
			}
			for(int i=0;i<3;i++)
			{
				if(a[3-i][j]!=0&&a[2-i][j]==0)
				{
					flag=0;
					break;
				}
				else
				{
					flag=1;
				}
			}
			
		}
	}
}
void down(int a[4][4])
{
		int flag=0;
	int pin=0;
	for(int j=0;j<4;j++)
	{
		flag=0;
		pin=0;
		while(flag!=1)
		{
			for(int i=0;i<3;i++)
			{
				if(a[i][j]!=0&&a[i][j]!=a[i+1][j]&&a[i+1][j]!=0)
				{
					
				}
			    else if(a[i][j]!=0&&a[i][j]==a[i+1][j]&&a[i+1][j]!=0&&pin==0)
				{
					a[i+1][j]=a[i][j]+a[i+1][j];
					a[i][j]=0;
					pin=1;
				}
			    else if(a[i][j]!=0&&a[i+1][j]==0)
			    {
					
					a[i+1][j]=a[i][j]+a[i+1][j];
					a[i][j]=0;
				}
			}
			for(int i=0;i<3;i++)
			{
				if(a[i][j]!=0&&a[i+1][j]==0)
				{
					flag=0;
					break;
				}
				else
				{
					flag=1;
				}
			}
			
		}
	}
}
void generate(int a[4][4])
{
	int m,n,flag=1,tin=16;
   	while(flag!=0)
   	{
		m=rand()%4;
		n=rand()%4;
  	    if(a[m][n]==0)
		{
			a[m][n]=2;
			flag=0;
		}
		tin--;
		if(tin==0)
		{
			break;
		}
	}

}
void start(int a[4][4])
{
	for (int p=0; p<4; p++) 
	{
		for(int q=0;q<4;q++)
		{
			a[p][q]=0;
		}
       
	 } 
}
void printbg(int a[4][4])
{
	int m=0,n=0;
	int l=0;
   for(int k=0;k<4;k++)
   {
	   	for (int i=0;i<41;i++)
		{
			cout<<"-";
		}
		cout<<endl;
	    for(int i=0;i<5;i++)
	   	{
	    	for(int j=0;j<4;j++)
			{
			   	cout<<"|    ";
			   	l=log10(a[m][n])+1;
				if(i==2)
				{

					if(a[m][n]==0)
					{
						cout<<"0    ";
					}
					else
					{
						cout<<a[m][n];
						for(int h=0;h<5-l;h++)
						{
							cout<<" ";
						}
					}
					n++;
					
				}
				else
				{
					cout<<"     ";
				}
			}
	     	cout<<"|"<<endl;
	     	if(i==2)
	     	{
	     		m++;
	     		n=0;
			}
		}
		
   }
   for (int i=0;i<41;i++)
    {
		cout<<"-";
	}
	cout<<endl;
   
}
int main() 
{
    int a[4][4],ch;
/*	system("color 41"); */
	system("mode con cols=42 lines=32") ;
	start(a);
	generate(a);
	printbg(a);
	while(1)
	{
		if(_kbhit()){
            ch = _getch();
        	switch(ch)
        	{
        		case 119:
        			up(a);
        			generate(a);
        			system("cls");
        			printbg(a);
        			break;
        		case 115:
        			down(a);
        			generate(a);
        			system("cls");
        			printbg(a);
        			break;
        		case 97:
        			left(a);
        			generate(a);
        			system("cls");
        			printbg(a);
        			break;
        		case 100:
        			right(a);
        			generate(a);
        			system("cls");
        			printbg(a);
        			break;
        			
			}

        }
	}
/*	printbg(a);
	for(int i=0;i<16;i++)
	{
		system("cls");
		generate(a);
		printbg(a);
		Sleep(1000);
		left(a);
		system("cls");
		printbg(a);
		Sleep(1000);
	}*/
	return 0; 
}


/*     while(1)
	 {
        if(_kbhit()&&_getch()==13) 
        {
        	break;
		}

    }
 */   
