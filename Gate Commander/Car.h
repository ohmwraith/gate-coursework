#pragma once
#include "Gate.cpp"

using namespace System::Windows::Forms;

ref class Car
{
protected:
	//Поля (будут переданы по наследию)
	Gate^ gate;
	int number, color_id, speed, status, yPos, target_yPos, HEIGHT, goToGate_target, goThrowGate_target, goToPark_target;
private:
public:
	//Делегаты для событий
	delegate void CarEventHandler();
	delegate void CarCreatedHandler(int number, int color, int spd);
	delegate void CarChangedHandler(int number, int color, int spd);
	delegate void CarStatusHandler(int number, int status);
	delegate void CarPositionHandler(int number, int yPos);
	//Событие СОЗДАНА.
	static event CarCreatedHandler^ CREATED;
	// Событие изменения параметров машины. На него подписан движок отрисовки.
	static event CarChangedHandler^ CHANGED;
	// Событие уничтожения машины. Вызывается, когда машина покидает область шлагбаума.
	static event CarStatusHandler^ KILL;
	static event CarEventHandler^ tookWaitPosEvent;
	static event CarEventHandler^ tookAfterGatePosEvent;
	static event CarPositionHandler^ yPosChangedEvent;


	Car(int n, int color, int spd, int HEIGHT) {
		//Уникальный номер машины
		number = n;
		//Каждой машине присваивается свой цвет
		color_id = color;
		//Скорость каждой машины может отличаться
		speed = spd;
		//Положение машины (0 - на дороге(скрыта), 1 - у шлагбаума, 2 - после шлагбаума, 3 - скрылась на парковке)
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
	//Отправляет команду на проезд машины через открытые ворота
	void go_throw_gate() {
		target_yPos = goThrowGate_target;
	}
	//Отправляет команду подъехать к воротам и остановиться у них
	void go_to_gate() {
		target_yPos = goToGate_target;
	}
	void go_to_park() {
		target_yPos = goToPark_target;
	}
	//Отправляет команду на уничтожение экземпляра
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

