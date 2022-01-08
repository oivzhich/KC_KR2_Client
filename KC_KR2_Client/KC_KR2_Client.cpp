#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

using namespace std;

int main() {
	//Структура WSADATA содержит информацию о реализации сокетов Windows.
	WSAData wsaData;
	WORD wVersionRequested;
	//----Запрашиваем и загружаем библиотеку------//
	//Создает значение WORD путем объединения указанных значений.
	wVersionRequested = MAKEWORD(2, 2);
	//Функция WSAStartup инициирует использование Winsock DLL процессом.
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		cout << "Error! Cannot load library!" << endl;
		return 1;
	}

	cout << "___CLIENT___" << endl;

	//----Заполняем информацию об адресе сокета---//
	//Создаем сокет, который привязан к определенному поставщику транспортных услуг.
	//AF_INET - The Internet Protocol version 4 (IPv4) address family.
	//SOCK_DGRAM - Тип сокета, который поддерживает дейтаграммы, которые представляют собой 
	//ненадежные буферы без установления соединения с фиксированной (обычно небольшой) максимальной длиной. 
	//Этот тип сокета использует протокол дейтаграмм пользователя (UDP) для семейства интернет-адресов (AF_INET или AF_INET6).
	SOCKET socket1 = socket(AF_INET, SOCK_DGRAM, 0);

	//Структура SOCKADDR_IN определяет транспортный адрес и порт для семейства адресов AF_INET.
	struct sockaddr_in socketAddress;
	//Семейство адресов для транспортного адреса. Этот член всегда должен иметь значение AF_INET.
	socketAddress.sin_family = AF_INET;
	//Номер порта транспортного протокола.
	socketAddress.sin_port = htons(1024);
	//Функция inet_addr преобразует строку, содержащую десятичный адрес IPv4 с точками, в правильный адрес для структуры IN_ADDR .
	socketAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	char buf[256] = {}, output[256] = {};

	int lengthadd = sizeof(socketAddress);
	cout << "Enter string: ";
	cin.getline(buf, 100, '\n');

	cout << "Entered string: " << buf << endl;

	//отправляем данные на сервер
	sendto(socket1, buf, sizeof(buf), 0, (struct sockaddr*)&socketAddress, sizeof(socketAddress));
	//получаем данные с сервера и записываем в переменную output
	recvfrom(socket1, output, sizeof(output), 0, (struct sockaddr*)&socketAddress, &lengthadd);

	cout << "Result: " << output << endl;

	//закрываем соединение
	closesocket(socket1);
	WSACleanup();
}