#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <winsock2.h>

using namespace std;

void ShowErrorMessage(string message) //������ �߻��ϸ� �޽����� ����ϰ� ����
{
	cout << "[���� �߻�]: " << message << '\n';
	system("pause");
	exit(1);
}

int main()
{
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN serverAddress;

	int serverPort = 9876; //��Ʈ��ȣ�� ������ ���ƾ� ��û�� ����
	char received[256]; //ũ�� ����
	string sent;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //winsock �ʱ�ȭ
		ShowErrorMessage("WSAStartup()");

	clientSocket = socket(PF_INET, SOCK_STREAM, 0); //TCP ���� ����

	if (clientSocket == INVALID_SOCKET) //����ó��
		ShowErrorMessage("socket()");

	memset(&serverAddress, 0, sizeof(serverAddress)); //serverAddress 0���� �ʱ�ȭ
	serverAddress.sin_family = AF_INET; //IPv4
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); //���ڿ� ip�� ��Ʈ��ũ ����Ʈ ��������
	serverAddress.sin_port = htons(serverPort); //2����Ʈ ���� ��Ʈ��ũ ����Ʈ ��������
	if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("connect()");
	cout << "[���� ����] connect()\n";

	while (1) {
		cout << "[�޽��� ����]: ";
		getline(cin, sent);
		if (sent == "") continue;
		send(clientSocket, sent.c_str(), sent.length(), 0);
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = '\0';
		if (strcmp(received, "[exit]") == 0) {
			cout << "[���� ����]\n";
			break;
		}
		cout << "[���� �޽���]: " << received << '\n';
	}

	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
}