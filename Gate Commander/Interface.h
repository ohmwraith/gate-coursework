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
	Car^ car;
	SOCKET sock;
	bool status;
public:
	//Делегат для событий
	delegate void InterfaceEventHandler();
	//Событие СОЗДАНА. На него подписаны методы Be_korm обоих классов рыбок
	static event InterfaceEventHandler^ CREATED;
	static event InterfaceEventHandler^ SENDED;
	Interface() {
		car->CREATED += gcnew Car::CarCreatedHandler(this, &Interface::send_created_car_data);
		car->STATUS += gcnew Car::CarStatusHandler(this, &Interface::send_car_status);
		gate->CHANGED += gcnew Gate::GateChangedHandler(this, &Interface::send_universal_gate_data);
	}
	void connect_visuals() {
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
	}
	void send_created_car_data(int number, int color_id, int speed, int direction) {
		json j = json{ {"object", "car"}, {"event", "created"}, {"number", number, "color_id", color_id, "speed", speed, "direction", direction} };
		string userInput = j.dump();
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	}
	void send_changed_car_parameters(int number, int color_id, int speed, int direction) {

	}
	void send_car_status(int number, int status) {
		json j = json{ {"object", "car"}, {"event", "changingStatus"}, {"number", number, "status", status} };
		string userInput = j.dump();
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	}
	void send_universal_gate_data(bool data) {
		json j = json{ {"object", "gate"}, {"event", "changed"}, {"opened", data, "color", "static"} };
		string userInput = j.dump();
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	}	
};
