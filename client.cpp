#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 4096

using namespace std;

int main(int argc, char** argv){
	int sockfd, n;
	char recvline[4096], sendline[4096];
	struct sockaddr_in servaddr;

	if(argc != 2){
		cout << "you should type: ./client <serverip>"<<endl;
		return 0;
	}

	if ((sockfd = socket(AF_INET , SOCK_STREAM , 0)) < 0 ){
		cout << "creat socket error!" << endl;
		return 0;
	}

	memset(&servaddr , 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	if( inet_pton(AF_INET , argv[1], &servaddr.sin_addr) <= 0){
		cout << "inet_pton error for ip!" << endl;
		return 0;
	}

	if(connect(sockfd, (struct sockaddr*)&servaddr , sizeof(servaddr)) < 0){
		cout << "connect error!" << endl;
		return 0;
	}

	cout << "send msg to server:"<< endl;
	fgets(sendline,4096,stdin);
	if(send(sockfd,sendline,strlen(sendline),0) < 0){
		cout << "send msg error!" << endl;
		return 0;
	}

	close(sockfd);
	return 0;
}
