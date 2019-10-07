#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>
#include<string.h>
#include <WinSock2.h>
#define ERR_EXIT(m)\
        do \
        {\
                perror(m);\
                exit(EXIT_FAILURE);\
        }while(0)
/*信号处理函数*/
void handler(int sig)
{
        exit(EXIT_SUCCESS);
}
int main()
{
        /* 创建一个套接字*/
        int listenfd= socket(AF_INET ,SOCK_STREAM,0);
        if(listenfd==-1)
                ERR_EXIT("socket");
        /*定义一个地址结构并填充*/
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;   //协议族为ipv4
        addr.sin_port = htons(5888); //绑定端口号
        addr.sin_addr.s_addr = htonl(INADDR_ANY);//主机字节序转为网络字节序
        /*重复使用地址*/
        int on = 1;
        if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0)
        {
                ERR_EXIT("setsockopt");
        }
        /*将套接字绑定到地址上*/
        if(bind(listenfd,(const struct sockaddr *)&addr ,sizeof(addr))==-1)
        {
                ERR_EXIT("bind");
        }
        /*监听套接字，成为被动套接字*/
        if(listen(listenfd,SOMAXCONN)<0)
        {
                ERR_EXIT("Listen");
        }
        struct sockaddr_in peeraddr;
        socklen_t peerlen = sizeof(peeraddr);
        int conn ;
        conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen);
       if(conn <0)
            ERR_EXIT("accept error");
        else
            printf("连接到服务器的客户端的IP地址是：%s,端口号是：%d\n",inet_ntoa(peeraddr.sin_addr),htons(peeraddr.sin_port));
        pid_t pid ;
        pid = fork();//创建一个新进程
        if(pid == -1)
        {
                ERR_EXIT("fork");
        }
        if(pid == 0)//子进程
        {
                signal(SIGUSR1,handler);
                char sendbuf[1024] = {0};
                while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL)
                {
                        write(conn,sendbuf,sizeof(sendbuf));
                        memset(sendbuf,0,sizeof(sendbuf));
                }
                exit(EXIT_SUCCESS);
        }
        else    //父进程 用来获取数据
        {
                char recvbuf [1024]={0};
                while(1)
                {
                        memset(recvbuf,0,sizeof(recvbuf));
                        int ret = read(conn ,recvbuf,sizeof(recvbuf));
                        if(ret == -1)
                        {
                                ERR_EXIT("read");
                        }
                        if(ret == 0) //对方已关闭 
                        {
                                printf("对方关闭\n");
                                break;
                        }
                        fputs(recvbuf,stdout);
                }
                kill(pid,SIGUSR1);
                exit(EXIT_SUCCESS);
        }
        /*关闭套接字*/
        close(listenfd);
        close(conn);
        return 0;
} 
