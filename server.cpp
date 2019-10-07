#include <WinSock2.h>//在windows中我们一般使用WinSock2头文件中的函数来进行网络通信
#include <iostream>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
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
int check_row(char map[10][10],int num)
{
	int counter_1=1,counter_2=1;
	for(int i=0;i<10;i++)
	{
		counter_1=1;
		counter_2=1;
		for(int j=0;j<10;j++)
		{
			if(map[i][j]=='*'&&map[i][j+1] =='*'&&j!=9)
			{
				counter_1++;
			}
			if(map[i][j]=='@'&&map[i][j+1] =='@'&&j!=9)
			{
				counter_2++;
			}
			if(counter_1==num||counter_2==num)
			{
				if(counter_1==num)
				{
					return 1;
				}
				if(counter_2==num)
				{
					return 2;
				}
			}
			if(!(map[i][j]=='*'&&map[i][j+1] =='*')&&
			   !(map[i][j]=='@'&&map[i][j+1] =='@'))
			{
				counter_1=1;
				counter_2=1;
			}
		}
	}
	return 0;
}
int check_column(char map[10][10],int num)
{
	int counter_1=1,counter_2=1;
	for(int i=0;i<10;i++)
	{
		counter_1=1;
		counter_2=1;
		for(int j=0;j<10;j++)
		{
			if(map[j][i]=='*'&&map[j+1][i] =='*'&&j!=9)
			{
				counter_1++;
			}
			if(map[j][i]=='@'&&map[j+1][i] =='@'&&j!=9)
			{
				counter_2++;
			}
			if(counter_1==num||counter_2==num)
			{
				if(counter_1==num)
				{
					return 1;
				}
				if(counter_2==num)
				{
					return 2;
				}
			}
			if(!(map[j][i]=='*'&&map[j+1][i] =='*')&&
			   !(map[j][i]=='@'&&map[j+1][i] =='@'))
			{
				counter_1=1;
				counter_2=1;
			}
		}
	}
	return 0;
}
int check_x_rd(char map[10][10],int num)
{
	int counter_1=1,counter_2=1;
	for(int i=0;i<10;i++)
	{
		counter_1=1;
		counter_2=1;
		for(int j=0;j<i+1;j++)
		{
			if(map[j][j+9-i]=='*'&&map[j+1][j-i+10] =='*'&&j!=i)
			{
				counter_1++;
			}
			if(map[j][j+9-i]=='@'&&map[j+1][j-i+10] =='@'&&j!=i)
			{
				counter_2++;
			}
			if(counter_1==num||counter_2==num)
			{
				if(counter_1==num)
				{
					return 1;
				}
				if(counter_2==num)
				{
					return 2;
				}
				
			}
			if(!(map[j][j+9-i]=='*'&&map[j+1][j-i+10] =='*')&&
			   !(map[j][j+9-i]=='@'&&map[j+1][j-i+10] =='@'))
			{
				counter_1=1;
				counter_2=1;
			}
		}
	}
	for(int i=0;i<9;i++)
	{
		counter_1=1;
		counter_2=1;
		for(int j=0;j<i+1;j++)
		{
			if(map[j+9-i][j]=='*'&&map[j-i+10][j+1] =='*'&&j!=i)
			{
				counter_1++;
			}
			if(map[j+9-i][j]=='@'&&map[j-i+10][j+1] =='@'&&j!=i)
			{
				counter_2++;
			}
			if(counter_1==num||counter_2==num)
			{
				if(counter_1==num)
				{
					return 1;
				}
				if(counter_2==num)
				{
					return 2;
				}
			}
			if(!(map[j+9-i][j]=='*'&&map[j-i+10][j+1] =='*')&&
			   !(map[j+9-i][j]=='@'&&map[j-i+10][j+1] =='@'))
			{
				counter_1=1;
				counter_2=1;
			}
		}
	}
	return 0;
}
int check_x_ld(char map[10][10],int num)
{
	int counter_1=1,counter_2=1;
	for(int i=0;i<10;i++)
	{
		counter_1=1;
		counter_2=1;
		for(int j=0;j<i+1;j++)
		{
			if(map[j][i-j]=='*'&&map[j+1][i-j-1] =='*'&&j!=i)
			{
				counter_1++;
			}
			if(map[j][i-j]=='@'&&map[j+1][i-j-1] =='@'&&j!=i)
			{
				counter_2++;
			}
			if(counter_1==num||counter_2==num)
			{
				if(counter_1==num)
				{
					return 1;
				}
				if(counter_2==num)
				{
					return 2;
				}
			}
			if(!(map[j][i+j]=='*'&&map[j+1][i-j-1] =='*')&&
			   !(map[j][i+j]=='@'&&map[j+1][i-j-1] =='@'))
			{
				counter_1=1;
				counter_2=1;
			}
		}
	}
	for(int i=0;i<9;i++)
	{
		counter_1=1;
		counter_2=1;
		for(int j=0;j<i+1;j++)
		{
			if(map[9-i+j][9-j]=='*'&&map[j-i+10][1-j] =='*'&&j!=i)
			{
				counter_1++;
			}
			if(map[9-i+j][9-j]=='@'&&map[j-i+10][1-j] =='@'&&j!=i)
			{
				counter_2++;
			}
			if(counter_1==num||counter_2==num)
			{
				if(counter_1==num)
				{
					return 1;
				}
				if(counter_2==num)
				{
					return 2;
				}
			}
			if(!(map[9-i][9]=='*'&&map[j-i+10][1-j] =='*')&&
			   !(map[9-i][9]=='@'&&map[j-i+10][1-j] =='@'))
			{
				counter_1=1;
				counter_2=1;
			}
		}
	}
	return 0;
}
int check_win(char map[10][10],int num)
{
	return max(max(check_row(map,num),check_column(map,num)),max(check_x_ld(map,num),check_x_rd(map,num)));
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
void buff_cp(char buff_1[1024],char buff_2[1024])
{
	for(int i=0;i<100;i++)
	{
		buff_2[i]=buff_1[i];
	}
}
void make_buff(char buff[1024],string str)
{
	for(int i=0;i<11;i++)
	{
		buff[i]=str[i];
	}
}
bool check_full(char map[10][10])
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(map[i][j]=='#')
			{
				return 0;
			}
		}
	}
	return 1;
}
int main() {
	char map[10][10];
	int winner=0;
	start_up(map);
    printf("这是服务器端程序！\n");
    WSADATA wsadata;//WSADATA数据类型用来存储被WSAStartup函数调用后返回的Windows Sockets数据。
    int port=8000;//设置服务器端口号
    char buff[1024];//发送缓冲区
    char recvBuf[1024];//接收缓冲区
    printf("服务器端口号设为8000\n");
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//创建用于监听的套接字
    SOCKADDR_IN addrSrv;//定义一个SOCKADDR_IN类型变量addsrv,表示服务器端的套接字描述符
    addrSrv.sin_family = AF_INET;//地址族赋值，AF_INET表示IPv4
    addrSrv.sin_port = htons(port); //端口号赋值，1024以上的端口号
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip地址赋值，INADDR_ANY表示填入本机ip地址
    bind(sockSrv, (LPSOCKADDR) & addrSrv, sizeof(SOCKADDR_IN));
    listen(sockSrv, 10);
    printf("服务器端准备完成，开始等待客户机连接请求：\n");
while(1){
        SOCKADDR_IN addrClient;//定义一个SOCKADDR_IN类型变量Client,表示客户机端的套接字描述符
        int len = sizeof(SOCKADDR);//取得SOCKADDR_IN结构体的长度
        SOCKET sockConn[2];
        int flag=0;
        while(flag !=2)
        {
        	sockConn[flag+1] = accept(sockSrv, (SOCKADDR * ) & addrClient, &len);//sockConn接收连接请求的套接字描述符
            cout<<"与客户机端"<<flag+1<<"连接成功，连接的客户机端IP为:"<<inet_ntoa(addrClient.sin_addr)<<endl;//打印客户机ip地址
        	memset(buff, 0, 1024);
        	if(flag==0)
        	{
        		Sleep(1000);
        		make_buff(buff,"$*");
        		cout<<"分配 * 子到一号玩家"<<endl; 
			}
			if(flag==1)
			{
				Sleep(1000);
				make_buff(buff,"$@");
				cout<<"分配 @ 子到二号玩家"<<endl; 
			}
        	send(sockConn[flag+1], buff, 1024, 0);
        	flag++;
		}
		make_buff(buff,"^");
		send(sockConn[1], buff, 1024, 0);
		send(sockConn[2], buff, 1024, 0);
		flag=0;
        while (1)
		{
            memset(recvBuf, 0, 1024);//初始化接收服务器端的缓冲区
            recv(sockConn[1], recvBuf, 1024, 0);  //接收数据
            cout<<"接收到客户机端1发来的信息：\n";//打印接收到的数据
            cout<<recvBuf<<endl;
            write_in_map(map,recvBuf);
            cout<<check_win(map,5);
            if(check_win(map,5)||check_full(map))
            {
            	break;
			}
            buff_cp(recvBuf,buff);
            send(sockConn[2], buff, 1024, 0);
            cout<<"信息发送完成"<<endl;
            memset(recvBuf, 0, 1024);
            recv(sockConn[2], recvBuf, 1024, 0);
            cout<<"接收到客户机端2发来的信息";
            cout<<recvBuf<<endl;
            write_in_map(map,recvBuf);
            if(check_win(map,5)||check_full(map))
            {
            	break;
			}
			buff_cp(recvBuf,buff);
            send(sockConn[1], buff, 1024, 0);
            cout<<"信息发送完成"<<endl;
        }
        winner=check_win(map,5);
        {
        	if(winner==0)
        	{
        		memset(buff, 0, 1024);
        		make_buff(buff,"-Tie       ");
        		send(sockConn[1], buff, 1024, 0);
        		send(sockConn[2], buff, 1024, 0);
			}
			else if(winner==1)
			{
				memset(buff, 0, 1024);
        		make_buff(buff,"-You win   ");
        		send(sockConn[1], buff, 1024, 0);
        		memset(buff, 0, 1024);
        		make_buff(buff,"-You lose  ");
        		send(sockConn[2], buff, 1024, 0);
			}
			else if(winner==2)
			{
				memset(buff, 0, 1024);
        		make_buff(buff,"-You win   ");
        		send(sockConn[2], buff, 1024, 0);
        		memset(buff, 0, 1024);
        		make_buff(buff,"-You lose  ");
        		send(sockConn[1], buff, 1024, 0);
			}
		}
        cout<<"关闭套接字"<<endl;
        closesocket(sockConn[1]);
        closesocket(sockConn[2]);
        int sign;
        cout<<"是否还想运行服务器端程序？输入Y或N\n";
        cin>>sign;
        if(sign=='N')
            break;
    }
    closesocket(sockSrv);
    WSACleanup();//操作成功返回值为0；否则返回值为SOCKET_ERROR，可以通过调用WSAGetLastError获取错误代码。
    system("pause");//system("pause")就是从程序里调用“pause”命令.
    return 0;
}
