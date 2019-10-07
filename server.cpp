#include <WinSock2.h>//��windows������һ��ʹ��WinSock2ͷ�ļ��еĺ�������������ͨ��
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
    printf("���Ƿ������˳���\n");
    WSADATA wsadata;//WSADATA�������������洢��WSAStartup�������ú󷵻ص�Windows Sockets���ݡ�
    int port=8000;//���÷������˿ں�
    char buff[1024];//���ͻ�����
    char recvBuf[1024];//���ջ�����
    printf("�������˿ں���Ϊ8000\n");
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//�������ڼ������׽���
    SOCKADDR_IN addrSrv;//����һ��SOCKADDR_IN���ͱ���addsrv,��ʾ�������˵��׽���������
    addrSrv.sin_family = AF_INET;//��ַ�帳ֵ��AF_INET��ʾIPv4
    addrSrv.sin_port = htons(port); //�˿ںŸ�ֵ��1024���ϵĶ˿ں�
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip��ַ��ֵ��INADDR_ANY��ʾ���뱾��ip��ַ
    bind(sockSrv, (LPSOCKADDR) & addrSrv, sizeof(SOCKADDR_IN));
    listen(sockSrv, 10);
    printf("��������׼����ɣ���ʼ�ȴ��ͻ�����������\n");
while(1){
        SOCKADDR_IN addrClient;//����һ��SOCKADDR_IN���ͱ���Client,��ʾ�ͻ����˵��׽���������
        int len = sizeof(SOCKADDR);//ȡ��SOCKADDR_IN�ṹ��ĳ���
        SOCKET sockConn[2];
        int flag=0;
        while(flag !=2)
        {
        	sockConn[flag+1] = accept(sockSrv, (SOCKADDR * ) & addrClient, &len);//sockConn��������������׽���������
            cout<<"��ͻ�����"<<flag+1<<"���ӳɹ������ӵĿͻ�����IPΪ:"<<inet_ntoa(addrClient.sin_addr)<<endl;//��ӡ�ͻ���ip��ַ
        	memset(buff, 0, 1024);
        	if(flag==0)
        	{
        		Sleep(1000);
        		make_buff(buff,"$*");
        		cout<<"���� * �ӵ�һ�����"<<endl; 
			}
			if(flag==1)
			{
				Sleep(1000);
				make_buff(buff,"$@");
				cout<<"���� @ �ӵ��������"<<endl; 
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
            memset(recvBuf, 0, 1024);//��ʼ�����շ������˵Ļ�����
            recv(sockConn[1], recvBuf, 1024, 0);  //��������
            cout<<"���յ��ͻ�����1��������Ϣ��\n";//��ӡ���յ�������
            cout<<recvBuf<<endl;
            write_in_map(map,recvBuf);
            cout<<check_win(map,5);
            if(check_win(map,5)||check_full(map))
            {
            	break;
			}
            buff_cp(recvBuf,buff);
            send(sockConn[2], buff, 1024, 0);
            cout<<"��Ϣ�������"<<endl;
            memset(recvBuf, 0, 1024);
            recv(sockConn[2], recvBuf, 1024, 0);
            cout<<"���յ��ͻ�����2��������Ϣ";
            cout<<recvBuf<<endl;
            write_in_map(map,recvBuf);
            if(check_win(map,5)||check_full(map))
            {
            	break;
			}
			buff_cp(recvBuf,buff);
            send(sockConn[1], buff, 1024, 0);
            cout<<"��Ϣ�������"<<endl;
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
        cout<<"�ر��׽���"<<endl;
        closesocket(sockConn[1]);
        closesocket(sockConn[2]);
        int sign;
        cout<<"�Ƿ������з������˳�������Y��N\n";
        cin>>sign;
        if(sign=='N')
            break;
    }
    closesocket(sockSrv);
    WSACleanup();//�����ɹ�����ֵΪ0�����򷵻�ֵΪSOCKET_ERROR������ͨ������WSAGetLastError��ȡ������롣
    system("pause");//system("pause")���Ǵӳ�������á�pause������.
    return 0;
}
