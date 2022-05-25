#pragma once
#include "Gate.cpp"

using namespace System::Windows::Forms;

ref class Car
{
protected:
	//���� (����� �������� �� ��������)
	Gate^ gate;
	int number, color_id, speed, status, yPos, target_yPos, HEIGHT, goToGate_target, goThrowGate_target, goToPark_target;
private:
public:
	//�������� ��� �������
	delegate void CarEventHandler();
	delegate void CarCreatedHandler(int number, int color, int spd);
	delegate void CarChangedHandler(int number, int color, int spd);
	delegate void CarStatusHandler(int number, int status);
	delegate void CarPositionHandler(int number, int yPos);
	//������� �������.
	static event CarCreatedHandler^ CREATED;
	// ������� ��������� ���������� ������. �� ���� �������� ������ ���������.
	static event CarChangedHandler^ CHANGED;
	// ������� ����������� ������. ����������, ����� ������ �������� ������� ���������.
	static event CarStatusHandler^ KILL;
	static event CarEventHandler^ tookWaitPosEvent;
	static event CarEventHandler^ tookAfterGatePosEvent;
	static event CarPositionHandler^ yPosChangedEvent;


	Car(int n, int color, int spd, int HEIGHT) {
		//���������� ����� ������
		number = n;
		//������ ������ ������������� ���� ����
		color_id = color;
		//�������� ������ ������ ����� ����������
		speed = spd;
		//��������� ������ (0 - �� ������(������), 1 - � ���������, 2 - ����� ���������, 3 - �������� �� ��������)
		status = 0;
		yPos = HEIGHT + 500;
		goToGate_target = HEIGHT - 10;
		goThrowGate_target = 0;
		goToPark_target = -500;
		CREATED(number, color_id, speed);
		this->go_to_gate();
		gate->OPENED += gcnew Gate::GateEventHandler(this, &Car::go_throw_gate);
		gate->CLOSED += gcnew Gate::GateEventHandler(this, &Car::go_to_gate);
	}
	property int p_number {
		int get() { return number; };
		//void set(int new_number) { CHANGED(number); number = new_number; };
	}
	property int p_color {
		int get() { return color_id; };
		void set(int new_color) { CHANGED(number, color_id, speed); color_id = new_color; };
	}
	property int p_speed {
		int get() { return speed; };
		void set(int new_speed) { CHANGED(number, color_id, speed); color_id = new_speed; };
	}
	//���������� ������� �� ������ ������ ����� �������� ������
	void go_throw_gate() {
		target_yPos = goThrowGate_target;
	}
	//���������� ������� ��������� � ������� � ������������ � ���
	void go_to_gate() {
		target_yPos = goToGate_target;
	}
	void go_to_park() {
		target_yPos = goToPark_target;
	}
	//���������� ������� �� ����������� ����������
	void destroy() {
		KILL(number, -1);
	}
	void update() {
		if (yPos - speed < target_yPos) yPos = target_yPos;
		else if (yPos != target_yPos){
			yPos -= speed;
			yPosChangedEvent(number, yPos);
		}
		if (yPos == goToGate_target) {
			tookWaitPosEvent();
		}
		if (yPos == goThrowGate_target) {
			tookAfterGatePosEvent();
		}
	}
	void incoming_car_request() {
		try {
			System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
			sa->WriteLine("Car:");
			sa->WriteLine("Event=Create");
			sa->WriteLine("Direction=up");
			sa->WriteLine("Number=" + number);
			sa->Close();
		}
		catch (System::IO::IOException^ e) {
			MessageBox::Show("�������� ������ ������ ����������, ��� �� ��������� �� ���������������� ���������, ������������� ������ �������� ������������", "��������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	void leaving_car_request() {
		try{
			System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
			sa->WriteLine("Car:");
			sa->WriteLine("Event=Create");
			sa->WriteLine("Direction=down");
			sa->WriteLine("Event=Forward");
			sa->WriteLine("Number=" + number);
			sa->Close();
		}
		catch (System::IO::IOException^ e) {
			MessageBox::Show("�������� ������ ������ ����������, ��� �� ��������� �� ���������������� ���������, ������������� ������ �������� ������������", "��������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	void send_forward() {
		try {
			System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
			sa->WriteLine("Car:");
			sa->WriteLine("Event=Forward");
			sa->WriteLine("Direction=up");
			sa->WriteLine("Number=" + number);
			sa->Close();
		}
		catch (System::IO::IOException^ e) {
			MessageBox::Show("�������� ������ ������ ����������, ��� �� ��������� �� ���������������� ���������, ������������� ������ �������� ������������", "��������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
};

