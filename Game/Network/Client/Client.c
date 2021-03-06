// Client.c: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

void ErrorHandling(char *message);
void SendData(SOCKET *hSocket, char *msg);
char* RecvData(SOCKET *hSocket);

int main(){

	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char recvmsg[30];
	char sendmsg[30] = { '\0' };

	int strLen;

	char ip_addr[16];

	printf("IP Address : ");
	scanf("%s", ip_addr);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //소켓 라이브러리를 초기화

		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0); //소켓을 생성

	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ip_addr); // 입력받은 ip주소
	servAddr.sin_port = htons(9511); // 포트번호 9511
	
	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //생성된 소켓으로 연결 요청
		ErrorHandling("connect() error!");

	while (1) {
		SendData(&hSocket, sendmsg);
		printf("send data!\n");
		strcpy(recvmsg, RecvData(&hSocket));
	}
	closesocket(hSocket); //소켓 라이브러리 해제
	
	WSACleanup();

	return 0;

}



void ErrorHandling(char *message){

	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);

}

void SendData(SOCKET *hSocket, char *msg) {

	if (msg[0] != '\0') {
		strcat(msg, "\n");
		send(*hSocket, msg, strlen(msg), 0);
	}

}

char* RecvData(SOCKET *hSocket) {
	char recvmsg[30];
	int timeout;
	DWORD recvTimeout = 1000;  // timeout 시간 1초.
	timeout = setsockopt(*hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&recvTimeout, sizeof(recvTimeout));
	int strLen = recv(*hSocket, recvmsg, sizeof(recvmsg), 0); // 서버로부터 데이터를 수신
	if (strLen == -1) { // read error일 경우
		if (timeout == 0) { // timeout인 경우
			printf("Timeout!\n");
			recvmsg[0] = '\0';
			return recvmsg;
		}
		ErrorHandling("read() error");
	}

	if (strLen == 0) {
		recvmsg[0] = '\0'; // 받은 문자열이 없는 경우 recvmsg를 null로 초기화 한 후 반환
		return recvmsg;
	}
	else {
		recvmsg[strLen] = '\0'; // 문자열의 끝에 null문자 추가
		return recvmsg;
	}
}