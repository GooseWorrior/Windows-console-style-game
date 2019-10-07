#include <WinSock2.h>//在windows中我们一般使用WinSock2头文件中的函数来进行网络通信
#include <iostream>
#include <stdlib.h>
#include <windows.h> 
#include <string.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
struct Posn
{
	int i;
	int j;
};
void gotoxy(int x, int y)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(hOut, c);
}
void start_up(char UI[10][10])
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			UI[i][j]='#';
		}
	} 
}
void gamer_manip(char map[10][10],int mode)
{
	int flag =0;
	Posn pos;
	while(flag==0)
	{
		gotoxy(18,10);
		cout<<"                          ";
		gotoxy(18,10);
		cout<<"please enter row number: ";
		cin>>pos.i;
		gotoxy(18,12);
		cout<<"                          ";
		gotoxy(18,12);
		cout<<"please enter column number: ";
		cin>>pos.j ;
		if(map[pos.i][pos.j]=='#')
		{
			if(mode==1)
			{
				map[pos.i][pos.j] ='*';	
			}
			else if(mode==2)
			{
				map[pos.i][pos.j] ='@';
			}
			flag=1;
		}
		else
		{
			gotoxy(18,14);
			cout<<"invalid coordination";
			Sleep(1000);
		}
	}
}
void simple_print(char map[10][10])
{
	gotoxy(0,0);
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			cout<<map[i][j]<<" ";
		}
		cout<<endl;
	}
}
void write_in_map(char map[10][10],char buff[1024]) //when we pass array array changes.
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			map[i][j]=buff[10*i+j];
		}
	}
}
void write_in_buff(char buff[1024],char map[10][10])
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			buff[10*i+j]=map[i][j];
		}
	}
}
using namespace std;
int main() {
	char map[10][10];
	start_up(map);
	int flag=0;
    cout<<"this is client programme！"<<endl;
    WSADATA wsaData;//WSADATA数据类型用来存储被WSAStartup函数调用后返回的Windows Sockets数据。
    char buff[1024];//发送缓冲区
    char recvBuf[1024];//接收缓冲区
    memset(buff, 0, 1024);//初始化缓冲区值为0
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKADDR_IN addrSrv;//定义一个SOCKADDR_IN类型变量addsrv,表示服务器端的套接字描述符
    addrSrv.sin_family = AF_INET;//地址族赋值，AF_INET表示IPv4
    addrSrv.sin_port = htons(8000);//端口号赋值，1024以上的端口号
    addrSrv.sin_addr.S_un.S_addr = inet_addr("10.22.75.97");//ip地址赋值，INADDR_ANY表示填入本机ip地址
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);//创建客户机端套接字
    connect(sockClient, (struct sockaddr *) &addrSrv, sizeof(addrSrv));
    cout<<"客户机端已连接服务器！"<<endl<<"请等待分配棋子"<<endl;
    while(1){
    	memset(recvBuf, 0, 1024);
        recv(sockClient, recvBuf, 1024, 0);
        if(recvBuf[0]=='$')
        {
        	if(recvBuf[1]=='*')
        	{
        		flag=1;
        		cout<<"系统已分配棋子：*(先手)"<<endl;
				cout<<"请等待游戏开始......"<<endl; 
				memset(recvBuf, 0,1024);
        		recv(sockClient, recvBuf,1024, 0);
			}
			else if(recvBuf[1]=='@')
			{
				flag=2;
				cout<<"系统已分配棋子：@(后手)"<<endl;
				cout<<"请等待游戏开始......"<<endl;
				memset(recvBuf, 0, 1024);
                recv(sockClient, recvBuf, 1024, 0);
				system("cls");
				simple_print(map);
				memset(recvBuf, 0, 1024);
				cout<<endl<<"请等待对方落子"<<endl;
				recv(sockClient, recvBuf, 1024, 0); 
				write_in_map(map,recvBuf);
			}
		}
		else if(recvBuf[0]=='-')
		{
			break;
		}
		else if(recvBuf[0]=='#'||recvBuf[0]=='@'||recvBuf[0]=='*')
		{
			write_in_map(map,recvBuf);
		}
		system("cls");
		simple_print(map);
    	gamer_manip(map,flag);
    	simple_print(map);
    	write_in_buff(buff,map);
   		send(sockClient, buff,1024, 0);
    	cout<<endl<<"请等待对方落子"<<endl;
		    	
        
    }
	cout<<"关闭套接字"<<endl;
    closesocket(sockClient);//关闭客户机套接字
    WSACleanup();//操作成功返回值为0；否则返回值为SOCKET_ERROR，可以通过调用WSAGetLastError获取错误代码。
    system("pause");//system("pause")就是从程序里调用“pause”命令.
    return 0;
}
