#include "bot_.h"
#include <winsock2.h>
#include <cstring>
#include <ctime>
#include <windows.h>
#include <ws2tcpip.h>

#define PORT	4567 //(239 * 11)
#define IPADDR	"10.10.10.19"

#pragma comment(lib, "Ws2_32")

WSADATA wsadata;
sockaddr_in table;
SOCKET sock;
char buffer[1024];

#ifdef  _MSC_VER
	void __send() {
		fscanf_s(stdin, "%s", buffer (unsigned)_countof(buffer));
	}

	void to_buffer(string motion) {
		strcpy_s(buffer, motion.c_str());
	}
#else
	void __send() {
		fscanf(stdin, "%s", buffer);
	}

	void to_buffer(string motion) {
		strcpy(buffer, motion.c_str());
	}
#endif

void init() {
	printf("start init\n");

	WSAStartup(MAKEWORD(1, 1), &wsadata);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == SOCKET_ERROR) {
		printf("error: socket failed %i\n", WSAGetLastError());
		WSACleanup();
		return;
	}

	table.sin_family = AF_INET;
	table.sin_port = htons(PORT);
	table.sin_addr.s_addr = inet_addr(IPADDR);
	//inet_pton(AF_INET, IPADDR, &table.sin_addr);
	printf("end of init\n");
}

void init_field() {
	for (int i = 0; i < 4; i++) field[0][i].init(white, knight);
	for (int i = 4; i < size_x; i++) field[7][i].init(black, knight);
}

void __recv() {
	printf("%s\n", buffer);

	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			printf("{%2i, %2i} ", field[i][j].color, field[i][j].form);
		} printf("\n");
	}
	printf("\n");
}

int main() {
	srand(time(NULL));

	init();
	init_field();

	printf("connect...\n");
	if (connect(sock, (struct sockaddr*) &table, sizeof(table)) == SOCKET_ERROR) {
		printf("error: failed to connect\n");
		closesocket(sock);
		WSACleanup();
	}

	string name = "name: Ldno\n";
	strcpy(buffer, name.c_str());

	cout << name << "\n";

	send(sock, buffer, strlen(buffer), 0);
	int is_err = recv(sock, buffer, strlen(buffer), 0);
	//__send();
	//__recv();

	
	if(is_err >= 0) {
		buffer[ is_err ] = '\n';
		//printf("%s", buffer);
	}

	int my_color = buffer[0] == 'w' ? white : black;
	while (true) {
		pair<pii, pii> att = must_attack(my_color);
		if (att == empty_pair) {
			att = other_motion(my_color);
			swap(field[att.second.first][att.second.second], field[att.first.first][att.first.second]);
		}
		else {
			field[att.second.first][att.second.second].delete_();
			swap(field[att.second.first][att.second.second], field[att.first.first][att.first.second]);
		}

		string motion = coord_to_string(att);
		//motion += "\n";
		cout << motion << "\n\n";

		to_buffer(motion);
		printf("buffer: %s, buffer.size() = %i\n", buffer, strlen(buffer));
		for(int i = 0; i < 7; i++) {
			printf("%i = %c\n", i + 1, buffer[ i ]);
		}

		send(sock, buffer, strlen(buffer), 0);
		//printf("%i \n", strlen(buffer));
		//__send();

		pair<pii, pii> en_att = { {buffer[1] - '0' - 1, buffer[0] - 'a'}, {buffer[4] - '0' - 1, buffer[3] - 'a'} };
		print_pair(en_att.first);
		print_pair(en_att.second);
		printf("\n");

		if (en_att == empty_pair) {
			en_att = other_motion(!my_color);
			swap(field[en_att.second.first][en_att.second.second], field[en_att.first.first][en_att.first.second]);
		}
		else {
			field[en_att.second.first][en_att.second.second].delete_();
			swap(field[en_att.second.first][en_att.second.second], field[en_att.first.first][en_att.first.second]);
		}

		recv(sock, buffer, strlen(buffer), 0);
		//Sleep(5000);
		//__recv();

		//send(sock, buffer, sizeof(buffer), 0);
		//int is_err = recv(sock, buffer, sizeof(buffer), 0);
		/*
		if(is_err >= 0) {
			buffer[ is_err ] = '\n';
			printf("%s", buffer);
		}*/
	}
}
