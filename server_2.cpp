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
/*�źŴ�����*/
void handler(int sig)
{
        exit(EXIT_SUCCESS);
}
int main()
{
        /* ����һ���׽���*/
        int listenfd= socket(AF_INET ,SOCK_STREAM,0);
        if(listenfd==-1)
                ERR_EXIT("socket");
        /*����һ����ַ�ṹ�����*/
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;   //Э����Ϊipv4
        addr.sin_port = htons(5888); //�󶨶˿ں�
        addr.sin_addr.s_addr = htonl(INADDR_ANY);//�����ֽ���תΪ�����ֽ���
        /*�ظ�ʹ�õ�ַ*/
        int on = 1;
        if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0)
        {
                ERR_EXIT("setsockopt");
        }
        /*���׽��ְ󶨵���ַ��*/
        if(bind(listenfd,(const struct sockaddr *)&addr ,sizeof(addr))==-1)
        {
                ERR_EXIT("bind");
        }
        /*�����׽��֣���Ϊ�����׽���*/
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
            printf("���ӵ��������Ŀͻ��˵�IP��ַ�ǣ�%s,�˿ں��ǣ�%d\n",inet_ntoa(peeraddr.sin_addr),htons(peeraddr.sin_port));
        pid_t pid ;
        pid = fork();//����һ���½���
        if(pid == -1)
        {
                ERR_EXIT("fork");
        }
        if(pid == 0)//�ӽ���
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
        else    //������ ������ȡ����
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
                        if(ret == 0) //�Է��ѹر� 
                        {
                                printf("�Է��ر�\n");
                                break;
                        }
                        fputs(recvbuf,stdout);
                }
                kill(pid,SIGUSR1);
                exit(EXIT_SUCCESS);
        }
        /*�ر��׽���*/
        close(listenfd);
        close(conn);
        return 0;
} 
