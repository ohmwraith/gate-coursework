#pragma once
#include "Car.cpp"
#include "Parking.cpp"
using namespace System::Windows::Forms;

ref class Gate
{
protected:

private:
	bool opened;
	Car^ car;
	Parking^ parking;
public:
	//Делегат для событий
	delegate void GateEventHandler();
	delegate void GateChangedHandler(bool NewStatus);
	static event GateChangedHandler^ CHANGED;
	//Событие СОЗДАН
	static event GateEventHandler^ CREATED;
	//Событие ОТКРЫТО. Подписан метот проезда у машины
	static event GateEventHandler^ OPENED;
	//Событие ЗАКРЫТО. На него подписан метод остановки машины
	static event GateEventHandler^ CLOSED;
	// Событие изменения состояния экземпляра. На него подписан движок отрисовки.
	static event GateEventHandler^ TOGGLED;

	Gate(int open) {
		opened = open;
		CREATED();
		car->tookAfterGatePosEvent += gcnew Car::CarEventHandler(this, &Gate::close);
		parking->letCarIn += gcnew Parking::ParkEventHandler(this, &Gate::open);
	}
	property bool p_opened{
		bool get() { return opened; };
	}
	double is_opened() {
		return (opened ? true : false);
	}
	void open() {
		opened = true;
		CHANGED(opened);
	}
	void close() {
		opened = false;
		CHANGED(opened);
	}
	bool toggle() {
		opened ? opened = false : opened = true;
		return true;
	}
	void send_parametres() {
		try {
			System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
			sa->WriteLine("Gate:");
			sa->WriteLine("Opened=" + opened);
			sa->Close();
		}
		catch (System::IO::IOException^ e) {
			MessageBox::Show("Возникла ошибка чтения интерфейса, это не отразится на функциональности программы, рекомендуется заново включить визуализацию", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
};

