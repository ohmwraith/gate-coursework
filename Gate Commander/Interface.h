#include <WinSock2.h>
#include <string>
#include <WS2tcpip.h>
#include <sstream>
#include "nlohmann/json.hpp"
#include "Gate.cpp"
#include "Car.cpp"
#include "Parking.cpp"

#pragma comment(lib, "ws2_32.lib")
using namespace System::Windows::Forms;
using namespace std;
using json = nlohmann::json;
ref class Interface
{
protected:
	Gate^ gate;
	SOCKET sock;
public:
	//������� ��� �������
	delegate void InterfaceEventHandler();
	//������� �������. �� ���� ��������� ������ Be_korm ����� ������� �����
	static event InterfaceEventHandler^ CREATED;
	static event InterfaceEventHandler^ SENDED;
	Interface() {
		string ipAddress = "127.0.0.1";			// IP Address of the server
		int port = 55000;						// Listening port # on the server

		// Initialize WinSock
		WSAData data;
		WORD ver = MAKEWORD(2, 2);
		int wsResult = WSAStartup(ver, &data);
		if (wsResult != 0)
		{
			MessageBox::Show("Error", "Can't start Winsock, Err #" + wsResult.ToString(), MessageBoxButtons::OK);
			return;
		}

		// Create socket
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET)
		{
			MessageBox::Show("Error", "Can't create socket, Err #" + WSAGetLastError().ToString(), MessageBoxButtons::OK);
			WSACleanup();
			return;
		}

		// Fill in a hint structure
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

		// Connect to server
		int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
		if (connResult == SOCKET_ERROR)
		{
			MessageBox::Show("Error", "Can't connect to server, Err #" + WSAGetLastError().ToString(), MessageBoxButtons::OK);
			closesocket(sock);
			WSACleanup();
			return;
		}
		else {
			MessageBox::Show("Congrats", "Connection established!", MessageBoxButtons::OK);
		}
		gate->OPENED += gcnew Gate::GateEventHandler(this, &Interface::send_open_gate_data);
		gate->CLOSED += gcnew Gate::GateEventHandler(this, &Interface::send_close_gate_data);
		gate->CHANGED += gcnew Gate::GateChangedHandler(this, &Interface::send_universal_gate_data);
	}
	void send_universal_gate_data(bool data) {
		json j = json{ {"object", "gate"}, {"opened", data} };
		string userInput = j.dump();
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	}
	void send_open_gate_data() {
		json j = json{ {"object", "gate"}, {"opened", "true"} };
		string userInput = j.dump();
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	}
	void send_close_gate_data() {
		json j = json{ {"object", "gate"}, {"opened", "close"} };
		string userInput = j.dump();
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	}
};