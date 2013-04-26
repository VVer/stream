/*************************************************************************
    > File Name: autolog.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2013年03月11日 星期一 18时55分04秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

int main(int argc, const char **argv)
{
	struct sockaddr_in addr;
	struct hostent	*host;
	char buf[1024],body[200];
	int len;
	int socket_fd;
	char* return_code="HTTP/1.1 200 OK\r\n";
		
	host =gethostbyname("nic.bjut.edu.cn");
	if(argc!=3)
	{
		fprintf(stderr,"Usage: %s <username> <password>\n",argv[0]);
		exit(0);
	}

	if(-1==(socket_fd=socket(AF_INET,SOCK_STREAM,0)))
	{
		fprintf(stderr,"Can't connect to Server!\n");
		exit(0);
	}
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr =*((struct in_addr *)host->h_addr);
	addr.sin_port =htons(80);
	len =sizeof(addr);

	if(-1==connect(socket_fd,(struct sockaddr*)&addr,len))
	{
		fprintf(stderr,"Connnect Failure!\n");
		exit(0);

	}
	sprintf(body,"DDDDD=%s&upass=%s&0MKKey=%%C1%%AC%%BD%%D3%%CD%%F8%%C2%%E7",argv[1],argv[2]);

	sprintf(buf,"POST / HTTP/1.1\r\n");
	sprintf(buf,"%sAccept: text/html, application/xhtml+xml, */*\r\n",buf);
	sprintf(buf,"%sReferer: http://nic.bjut.edu.cn/\r\n",buf);
	sprintf(buf,"%sAccept-Language: zh-CN\r\n",buf);
	sprintf(buf,"%sUser_Agent: Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)\r\n",buf);
	sprintf(buf,"%sContent-Type: application/x-www-form-urlencoded\r\n",buf);
	sprintf(buf,"%sAccept-Encodeing: gzip, deflate\r\n",buf);
	sprintf(buf,"%sHost: nic.bjut.edu.cn\r\n",buf);
	sprintf(buf,"%sContent-Length: %d\r\n",buf,strlen(body));
	sprintf(buf,"%sDNT: 1\r\n",buf);
	sprintf(buf,"%sConnection: Keep-Alive\r\n",buf);
	sprintf(buf,"%sCache-Control: no-cache\r\n",buf);
	sprintf(buf,"%sCookie: __gads=ID=bc3ce0b1b60a6291:T=1362717557:S=ALNI_MbeohhDgbcrzHAvNztfRR81_qSJBg; iPlanetDirectoryPro=AQIC5wM2LY4SfcwhAmf5MgTyP9HKekrhF5c%%2BM%%2FOXVHiTpQk%%3D%%40AAJTSQACMDI%%3D%%23\r\n\r\n",buf);
//	printf("%s\n",buf);
//	printf("%s\n",body);
	write(socket_fd,buf,strlen(buf));
	write(socket_fd,body,strlen(body));

//	sleep(1);
//	while(0!=(read(socket_fd,buf,1000)))
//	{
	len=read(socket_fd,buf,sizeof(buf));
//	printf("read %d\n",len);
	if(strncmp(buf,return_code,strlen(return_code))==0)
	{
		fprintf(stderr,"Connection Ok!\n");
//		break;
	}else{
		printf("Failed!\n%s\n",buf);
	}
//	}
	return 0;

}
