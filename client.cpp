#include <WinSock2.h>//��windows������һ��ʹ��WinSock2ͷ�ļ��еĺ�������������ͨ��
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
    cout<<"this is client programme��"<<endl;
    WSADATA wsaData;//WSADATA�������������洢��WSAStartup�������ú󷵻ص�Windows Sockets���ݡ�
    char buff[1024];//���ͻ�����
    char recvBuf[1024];//���ջ�����
    memset(buff, 0, 1024);//��ʼ��������ֵΪ0
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKADDR_IN addrSrv;//����һ��SOCKADDR_IN���ͱ���addsrv,��ʾ�������˵��׽���������
    addrSrv.sin_family = AF_INET;//��ַ�帳ֵ��AF_INET��ʾIPv4
    addrSrv.sin_port = htons(8000);//�˿ںŸ�ֵ��1024���ϵĶ˿ں�
    addrSrv.sin_addr.S_un.S_addr = inet_addr("10.22.75.97");//ip��ַ��ֵ��INADDR_ANY��ʾ���뱾��ip��ַ
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);//�����ͻ������׽���
    connect(sockClient, (struct sockaddr *) &addrSrv, sizeof(addrSrv));
    cout<<"�ͻ����������ӷ�������"<<endl<<"��ȴ���������"<<endl;
    while(1){
    	memset(recvBuf, 0, 1024);
        recv(sockClient, recvBuf, 1024, 0);
        if(recvBuf[0]=='$')
        {
        	if(recvBuf[1]=='*')
        	{
        		flag=1;
        		cout<<"ϵͳ�ѷ������ӣ�*(����)"<<endl;
				cout<<"��ȴ���Ϸ��ʼ......"<<endl; 
				memset(recvBuf, 0,1024);
        		recv(sockClient, recvBuf,1024, 0);
			}
			else if(recvBuf[1]=='@')
			{
				flag=2;
				cout<<"ϵͳ�ѷ������ӣ�@(����)"<<endl;
				cout<<"��ȴ���Ϸ��ʼ......"<<endl;
				memset(recvBuf, 0, 1024);
                recv(sockClient, recvBuf, 1024, 0);
				system("cls");
				simple_print(map);
				memset(recvBuf, 0, 1024);
				cout<<endl<<"��ȴ��Է�����"<<endl;
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
    	cout<<endl<<"��ȴ��Է�����"<<endl;
		    	
        
    }
	cout<<"�ر��׽���"<<endl;
    closesocket(sockClient);//�رտͻ����׽���
    WSACleanup();//�����ɹ�����ֵΪ0�����򷵻�ֵΪSOCKET_ERROR������ͨ������WSAGetLastError��ȡ������롣
    system("pause");//system("pause")���Ǵӳ�������á�pause������.
    return 0;
}
