#include "Gate.cpp"
using namespace System::Windows::Forms;
#pragma once
ref class Car
{
protected:
	//Поля (будут переданы по наследию)
	Gate^ gate;
	int number, color_id, speed, direction, status;
private:

public:
	//Делегаты для событий
	delegate void CarEventHandler();
	delegate void CarCreatedHandler(int number, int color, int spd, int dir);
	delegate void CarChangedHandler(int number, int color, int spd, int dir);
	delegate void CarStatusHandler(int number, int status);
	//Событие СОЗДАНА.
	static event CarCreatedHandler^ CREATED;
	// Событие изменения параметров машины. На него подписан движок отрисовки.
	static event CarChangedHandler^ CHANGED;
	// Событие изменения статуса машины
	static event CarStatusHandler^ STATUS;
	// Событие уничтожения машины. Вызывается, когда машина покидает область шлагбаума.
	static event CarStatusHandler^ KILL;

	Car(int n, int color, int spd, int dir) {
		//Уникальный номер машины
		number = n;
		//Каждой машине присваивается свой цвет
		color_id = color;
		//Скорость каждой машины может отличаться
		speed = spd;
		//Направление движения машины (0 - на парковку, 1 - с парковки)
		direction = dir;
		//Положение машины (0 - на дороге(скрыта), 1 - у шлагбаума, 2 - после шлагбаума, 3 - скрылась на парковке)
		status = 0;
		CREATED(number, color_id, speed, direction);
		gate->OPENED += gcnew Gate::GateEventHandler(this, &Car::go_throw_gate);
		gate->CLOSED += gcnew Gate::GateEventHandler(this, &Car::stop_near_gate);
	}
	property int p_number {
		int get() { return number; };
		//void set(int new_number) { CHANGED(number); number = new_number; };
	}
	property int p_color {
		int get() { return color_id; };
		void set(int new_color) { CHANGED(number, color_id, speed, direction); color_id = new_color; };
	}
	property int p_speed {
		int get() { return speed; };
		void set(int new_speed) { CHANGED(number, color_id, speed, direction); color_id = new_speed; };
	}
	property int p_direction {
		int get() { return direction; };
		void set(int new_direction) { CHANGED(number, color_id, speed, direction); color_id = new_direction; };
	}
	//Отправляет команду на проезд машины через открытые ворота
	void go_throw_gate() {
		STATUS(number, 2);
	}
	//Отправляет команду подъехать к воротам и остановиться у них
	void stop_near_gate() {
		STATUS(number, 1);
	}
	//Отправляет команду на уничтожение экземпляра
	void destroy() {
		KILL(number, -1);
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

