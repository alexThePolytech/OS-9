#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <winsock2.h>
#include <windows.h>
#include <list>
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <stdlib.h> 
#pragma comment(lib, "WS2_32.Lib")
#define PACKET_BUFF_SIZE 100
#define THREADS_NUMBER 3
int server(int connect_port);
std::string randomWeather();
std::string randomRate();
std::string randomShares();

DWORD WINAPI client_service(LPVOID client_socket);
DWORD WINAPI  sentWeather(LPVOID lpParam);
DWORD WINAPI  sentAction(LPVOID lpParam);
DWORD WINAPI  sentBank(LPVOID lpParam);
CRITICAL_SECTION section1;
CRITICAL_SECTION section2;
CRITICAL_SECTION section3;
std::list<SOCKET> userWeather;
std::list<SOCKET> userShares;
std::list<SOCKET> userExchange;

int main()
{
	int port = 1111;
	server(port);

	return 0;
}

int test_func()
{
	printf("This is a test func to commit");
}

#pragma warning (disable:4996);
int server(int connect_port)
{
	// Buffer for WSA and other data
	char buff[1024];

	std::cout << "\nSERVER STARTED\n";
	// Sockets library initialisation
	if (WSAStartup(0x0202, reinterpret_cast<WSADATA*> (&buff[0])) != 0) {
		// Error
		std::cerr << " Error WSA-Startup! ";
		return -1;
	}

	// Creating socket
	// AF_INET - internet socket
	// SOCK_STREAM - stream socket (with creating a connection)
	// 0 - default TCP protocol
	SOCKET mysocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mysocket == INVALID_SOCKET) {
		std::cerr << " Error create socket! ";
		// Socket library deinitialisation
		WSACleanup();
		return -1;
	}

	// Binding the socket with local address
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(connect_port);
	local_addr.sin_addr.s_addr = 0;

	// Binding for accepting connections
	if (bind(mysocket,
		reinterpret_cast<sockaddr*> (&local_addr),
		sizeof(local_addr))) 
	 {
		// Error
		std::cerr << " Error bind! ";
		// Closing the socket
		closesocket(mysocket);
		WSACleanup();
		return -1;
	}

	// Waiting for connections
	// Size of queue 0x100
	if (listen(mysocket, 0x100)) 
	{
		// Error
		std::cerr << " Error listen! ";
		// Closing the socket
		closesocket(mysocket);
		WSACleanup();
		return -1;
	}

	std::cout << "Waiting for connections\n";

	// Socket for client
	SOCKET client_socket;
	// Address of client
	sockaddr_in client_addr;
	// Size of client address
	int client_addr_size = sizeof(client_addr);

	DWORD thID1, thID2, thID3;
	InitializeCriticalSection(&section1);
	CreateThread(NULL, NULL, sentWeather, &mysocket, NULL, &thID1);
	InitializeCriticalSection(&section2);
	CreateThread(NULL, NULL, sentAction, &mysocket, NULL, &thID2);
	InitializeCriticalSection(&section3);
	CreateThread(NULL, NULL, sentBank, &mysocket, NULL, &thID3);
	
	// Cycle for accepting connections
	for (;;) 
	{
		client_socket = accept(mysocket,
			reinterpret_cast<sockaddr*> (&client_addr),
			&client_addr_size);

		// Printing the client info
		std::cout << " " << __TIME__ << " ";
		std::cout << " [" << inet_ntoa(client_addr.sin_addr) << "] ";

		// Creating new thread for client service
		DWORD thID;
		CreateThread(NULL, NULL, client_service, &client_socket, NULL, &thID);
	}
	closesocket(mysocket);
	closesocket(client_socket);
	WSACleanup();
	return 0;
}
DWORD WINAPI client_service(LPVOID client_socket)
{
	// Buffer for sending and receiving data
	char packet_buff;
	bool subscribe[3] = { false,false,false };
	//bool subscribe[3] = { true,true,true };
	// Creating socket
	SOCKET my_sock = (reinterpret_cast<SOCKET*> (client_socket))[0];
	int bytes_recv = 0;
	while (true) {
		try {
			if (bytes_recv = recv(my_sock, &packet_buff, sizeof(packet_buff), 0) < 0) 
			{
				EnterCriticalSection(&section1);
				userWeather.remove(my_sock);
				LeaveCriticalSection(&section1);
				EnterCriticalSection(&section2);
				userShares.remove(my_sock);
				LeaveCriticalSection(&section2);
				EnterCriticalSection(&section3);
				userExchange.remove(my_sock);
				LeaveCriticalSection(&section3);
				return 0;
			}
			std::cout << "data from client: " << packet_buff << std::endl;
			if (packet_buff == 'w') {
				EnterCriticalSection(&section1);
				if (!subscribe[0]) {
					userWeather.push_back(my_sock);
					subscribe[0] = true;
				}
				else if (subscribe[0]) {
					userWeather.remove(my_sock);
					subscribe[0] = false;
				}
				LeaveCriticalSection(&section1);
			}

			if (packet_buff == 'a') 
			{
				EnterCriticalSection(&section2);
				if (!subscribe[1]) 
				{
					userShares.push_back(my_sock);
					subscribe[1] = true;
				}
				else if (subscribe[1]) {
					userShares.remove(my_sock);
					subscribe[1] = false;
				}
				LeaveCriticalSection(&section2);
			}

			if (packet_buff == 'b') 
			{
				EnterCriticalSection(&section3);
				if (!subscribe[2]) {
					userExchange.push_back(my_sock);
					subscribe[2] = true;
				}
				else if (subscribe[2]) {
					userExchange.remove(my_sock);
					subscribe[2] = false;
				}
				LeaveCriticalSection(&section3);
			}


		}
		catch (...) {
			std::cout << " " << __TIME__ << " error convert";
		}

	}
	closesocket(my_sock);
	return 0;
}

DWORD WINAPI sentWeather(LPVOID lpParam) {
	while (true) {
		EnterCriticalSection(&section1);
		if (userWeather.size() != 0) {
			std::string str = randomWeather();
			const char* cstr = str.c_str();
			for (std::list<SOCKET>::iterator it = userWeather.begin(); it != userWeather.end(); it++) {
				try {
					send(*it, cstr, str.length() + 1, 0);
				}
				catch (...) {
					userWeather.remove(*it);
				}

			}
			std::cerr << " \nsend client " + str;
		}
		LeaveCriticalSection(&section1);
		Sleep(1000);
	}
	return 0;
}
DWORD WINAPI  sentAction(LPVOID lpParam) {
	while (true) {
		EnterCriticalSection(&section2);
		if (userShares.size() != 0) {
			std::string str = randomShares();
			const char* cstr = str.c_str();
			for (std::list<SOCKET>::iterator it = userShares.begin(); it != userShares.end(); it++) {
				try {
					send(*it, cstr, str.length() + 1, 0);
				}
				catch (...) {
					userWeather.remove(*it);
				}
			}
			std::cerr << " \nsend client " + str;
		}
		LeaveCriticalSection(&section2);
		Sleep(3000);
	}
	return 0;
}
DWORD WINAPI  sentBank(LPVOID lpParam) {
	while (true) {
		EnterCriticalSection(&section3);
		if (userExchange.size() != 0) {
			std::string str = randomRate();
			const char* cstr = str.c_str();
			for (std::list<SOCKET>::iterator it = userExchange.begin(); it != userExchange.end(); it++) {
				try {
					send(*it, cstr, str.length() + 1, 0);
				}
				catch (...) {
					userWeather.remove(*it);
				}
			}
			std::cerr << " \nsend client " + str;
		}
		LeaveCriticalSection(&section3);
		Sleep(6000);
	}
	return 0;
}
std::string randomWeather() {
	std::string str = "Temperature: -" + std::to_string(rand() % 18 + 1) + " °C";
	std::ofstream myfile;
	myfile.open("Weather.txt", std::ios_base::app);
	myfile << __TIME__ + '\n' + str + '\n';
	myfile.close();
	return "0" + str;
}
std::string randomRate() {
	std::string str = "Dollar rate: " + std::to_string(rand() % 35 + 25) + "\nEuro rate: " + std::to_string(rand() % 40 + 29) + "\nKrone rate: " + std::to_string(rand() % 50 + 36);
	std::ofstream myfile;
	myfile.open("Rate.txt", std::ios_base::app);
	myfile << __TIME__ + '\n' + str + '\n';
	myfile.close();
	return "2" + str;
}
std::string randomShares() {
	std::string str = "Shares Microsoft: -" + std::to_string(rand() % 280 + 260) + " USD";
	std::ofstream myfile;
	myfile.open("Shares.txt", std::ios_base::app);
	myfile << __TIME__ + '\n' + str + '\n';
	myfile.close();
	return "1" + str;
}


#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <winsock2.h>
#include <windows.h>
#include <list>
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <stdlib.h> 
#pragma comment(lib, "WS2_32.Lib")
#define PACKET_BUFF_SIZE 100
#define THREADS_NUMBER 3
int server(int connect_port);
std::string randomWeather();
std::string randomRate();
std::string randomShares();

DWORD WINAPI client_service(LPVOID client_socket);
DWORD WINAPI  sentWeather(LPVOID lpParam);
DWORD WINAPI  sentAction(LPVOID lpParam);
DWORD WINAPI  sentBank(LPVOID lpParam);
CRITICAL_SECTION section1;
CRITICAL_SECTION section2;
CRITICAL_SECTION section3;
std::list<SOCKET> userWeather;
std::list<SOCKET> userShares;
std::list<SOCKET> userExchange;

int main()
{
	int port = 1111;
	server(port);

	return 0;
}


#pragma warning (disable:4996);
int server(int connect_port)
{
	// Buffer for WSA and other data
	char buff[1024];

	std::cout << "\nSERVER STARTED\n";
	// Sockets library initialisation
	if (WSAStartup(0x0202, reinterpret_cast<WSADATA*> (&buff[0])) != 0) {
		// Error
		std::cerr << " Error WSA-Startup! ";
		return -1;
	}

	// Creating socket
	// AF_INET - internet socket
	// SOCK_STREAM - stream socket (with creating a connection)
	// 0 - default TCP protocol
	SOCKET mysocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mysocket == INVALID_SOCKET) {
		std::cerr << " Error create socket! ";
		// Socket library deinitialisation
		WSACleanup();
		return -1;
	}

	// Binding the socket with local address
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(connect_port);
	local_addr.sin_addr.s_addr = 0;

	// Binding for accepting connections
	if (bind(mysocket,
		reinterpret_cast<sockaddr*> (&local_addr),
		sizeof(local_addr))) 
	 {
		// Error
		std::cerr << " Error bind! ";
		// Closing the socket
		closesocket(mysocket);
		WSACleanup();
		return -1;
	}

	// Waiting for connections
	// Size of queue 0x100
	if (listen(mysocket, 0x100)) 
	{
		// Error
		std::cerr << " Error listen! ";
		// Closing the socket
		closesocket(mysocket);
		WSACleanup();
		return -1;
	}

	std::cout << "Waiting for connections\n";

	// Socket for client
	SOCKET client_socket;
	// Address of client
	sockaddr_in client_addr;
	// Size of client address
	int client_addr_size = sizeof(client_addr);

	DWORD thID1, thID2, thID3;
	InitializeCriticalSection(&section1);
	CreateThread(NULL, NULL, sentWeather, &mysocket, NULL, &thID1);
	InitializeCriticalSection(&section2);
	CreateThread(NULL, NULL, sentAction, &mysocket, NULL, &thID2);
	InitializeCriticalSection(&section3);
	CreateThread(NULL, NULL, sentBank, &mysocket, NULL, &thID3);
	
	// Cycle for accepting connections
	for (;;) 
	{
		client_socket = accept(mysocket,
			reinterpret_cast<sockaddr*> (&client_addr),
			&client_addr_size);

		// Printing the client info
		std::cout << " " << __TIME__ << " ";
		std::cout << " [" << inet_ntoa(client_addr.sin_addr) << "] ";

		// Creating new thread for client service
		DWORD thID;
		CreateThread(NULL, NULL, client_service, &client_socket, NULL, &thID);
	}
	closesocket(mysocket);
	closesocket(client_socket);
	WSACleanup();
	return 0;
}
DWORD WINAPI client_service(LPVOID client_socket)
{
	// Buffer for sending and receiving data
	char packet_buff;
	bool subscribe[3] = { false,false,false };
	// Creating socket
	SOCKET my_sock = (reinterpret_cast<SOCKET*> (client_socket))[0];
	int bytes_recv = 0;
	while (true) {
		try {
			if (bytes_recv = recv(my_sock, &packet_buff, sizeof(packet_buff), 0) < 0) 
			{
				EnterCriticalSection(&section1);
				userWeather.remove(my_sock);
				LeaveCriticalSection(&section1);
				EnterCriticalSection(&section2);
				userShares.remove(my_sock);
				LeaveCriticalSection(&section2);
				EnterCriticalSection(&section3);
				userExchange.remove(my_sock);
				LeaveCriticalSection(&section3);
				return 0;
			}
			std::cout << "data from client: " << packet_buff << std::endl;
			if (packet_buff == 'w')
			{
				EnterCriticalSection(&section1);
				if (!subscribe[0]) {
					userWeather.push_back(my_sock);
					subscribe[0] = true;
				}
				else if (subscribe[0]) {
					userWeather.remove(my_sock);
					subscribe[0] = false;
				}
				LeaveCriticalSection(&section1);
			}

			if (packet_buff == 'a') 
			{
				EnterCriticalSection(&section2);
				if (!subscribe[1]) 
				{
					userShares.push_back(my_sock);
					subscribe[1] = true;
				}
				else if (subscribe[1]) {
					userShares.remove(my_sock);
					subscribe[1] = false;
				}
				LeaveCriticalSection(&section2);
			}

			if (packet_buff == 'b') 
			{
				EnterCriticalSection(&section3);
				if (!subscribe[2]) {
					userExchange.push_back(my_sock);
					subscribe[2] = true;
				}
				else if (subscribe[2]) {
					userExchange.remove(my_sock);
					subscribe[2] = false;
				}
				LeaveCriticalSection(&section3);
			}

			if (packet_buff == 'u') {
				for (int i = 0; i < 3; i++) {
					if (subscribe[i]) {
						subscribe[i] == false;
					}
				}
			}

		}
		catch (...) {
			std::cout << " " << __TIME__ << " error convert";
		}

	}
	closesocket(my_sock);
	return 0;
}

DWORD WINAPI sentWeather(LPVOID lpParam) {
	while (true) {
		EnterCriticalSection(&section1);
		if (userWeather.size() != 0) {
			std::string str = randomWeather();
			const char* cstr = str.c_str();
			for (std::list<SOCKET>::iterator it = userWeather.begin(); it != userWeather.end(); it++) {
				try {
					send(*it, cstr, str.length() + 1, 0);
				}
				catch (...) {
					userWeather.remove(*it);
				}

			}
			std::cerr << " \nsend client " + str;
		}
		LeaveCriticalSection(&section1);
		Sleep(1000);
	}
	return 0;
}
DWORD WINAPI  sentAction(LPVOID lpParam) {
	while (true) {
		EnterCriticalSection(&section2);
		if (userShares.size() != 0) {
			std::string str = randomShares();
			const char* cstr = str.c_str();
			for (std::list<SOCKET>::iterator it = userShares.begin(); it != userShares.end(); it++) {
				try {
					send(*it, cstr, str.length() + 1, 0);
				}
				catch (...) {
					userWeather.remove(*it);
				}
			}
			std::cerr << " \nsend client " + str;
		}
		LeaveCriticalSection(&section2);
		Sleep(3000);
	}
	return 0;
}
DWORD WINAPI  sentBank(LPVOID lpParam) {
	while (true) {
		EnterCriticalSection(&section3);
		if (userExchange.size() != 0) {
			std::string str = randomRate();
			const char* cstr = str.c_str();
			for (std::list<SOCKET>::iterator it = userExchange.begin(); it != userExchange.end(); it++) {
				try {
					send(*it, cstr, str.length() + 1, 0);
				}
				catch (...) {
					userWeather.remove(*it);
				}
			}
			std::cerr << " \nsend client " + str;
		}
		LeaveCriticalSection(&section3);
		Sleep(6000);
	}
	return 0;
}
std::string randomWeather() {
	std::string str = "Temperature: -" + std::to_string(rand() % 18 + 1) + " °C";
	std::ofstream myfile;
	myfile.open("Weather.txt", std::ios_base::app);
	myfile << __TIME__ + '\n' + str + '\n';
	myfile.close();
	return "0" + str;
}
std::string randomRate() {
	std::string str = "Dollar rate: " + std::to_string(rand() % 35 + 25) + "\nEuro rate: " + std::to_string(rand() % 40 + 29) + "\nKrone rate: " + std::to_string(rand() % 50 + 36);
	std::ofstream myfile;
	myfile.open("Rate.txt", std::ios_base::app);
	myfile << __TIME__ + '\n' + str + '\n';
	myfile.close();
	return "2" + str;
}
std::string randomShares() {
	std::string str = "Shares Microsoft: -" + std::to_string(rand() % 280 + 260) + " USD";
	std::ofstream myfile;
	myfile.open("Shares.txt", std::ios_base::app);
	myfile << __TIME__ + '\n' + str + '\n';
	myfile.close();
	return "1" + str;
}


