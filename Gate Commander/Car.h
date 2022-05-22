#include "Gate.cpp"
using namespace System::Windows::Forms;
#pragma once
ref class Car
{
protected:
	//Поля (будут переданы по наследию)
	Gate^ gate;
private:
	int number, color_id, speed, direction;
public:
	//Делегат для событий
	delegate void CarEventHandler();
	//Событие СОЗДАНА. На него подписаны методы Be_korm обоих классов рыбок
	static event CarEventHandler^ CREATED;
	//Событие РЯДОМ С ВОРОТАМИ. На него подписан метод проверки парковки и открытия ворот
	static event CarEventHandler^ NEARGATE;
	//Событие ЗА ВОРОТАМИ. На него подписан метод закрытия ворот
	static event CarEventHandler^ AFTERGATE;
	// Событие изменения состояния экземпляра. На него подписан движок отрисовки.
	static event CarEventHandler^ CHANGED;
	Car(int n, int color, int spd, int dir) {
		number = n;
		color_id = color;
		speed = spd;
		direction = dir;
		CREATED();
		gate->OPENED += gcnew Gate::GateEventHandler(this, &Car::go_throw_gate);
		gate->CLOSED += gcnew Gate::GateEventHandler(this, &Car::stop_near_gate);
	}
	property int p_number {
		int get() { return number; };
		void set(int new_number) { CHANGED(); number = new_number; };
	}
	property int p_color {
		int get() { return color_id; };
		void set(int new_color) { CHANGED(); color_id = new_color; };
	}
	property int p_speed {
		int get() { return speed; };
		void set(int new_speed) { CHANGED(); color_id = new_speed; };
	}
	property int p_direction {
		int get() { return direction; };
		void set(int new_direction) { CHANGED(); color_id = new_direction; };
	}
	void go_throw_gate() {

	}
	void stop_near_gate() {
		NEARGATE();
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
			MessageBox::Show("Возникла ошибка чтения интерфейса, это не отразится на функциональности программы, рекомендуется заново включить визуализацию", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
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
			MessageBox::Show("Возникла ошибка чтения интерфейса, это не отразится на функциональности программы, рекомендуется заново включить визуализацию", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
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
			MessageBox::Show("Возникла ошибка чтения интерфейса, это не отразится на функциональности программы, рекомендуется заново включить визуализацию", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
};

