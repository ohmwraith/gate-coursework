#pragma once
#include "Car.cpp"
using namespace System::Windows::Forms;

ref class Parking
{
private:
	int total;
	int occupied;
	Car^ car;
public:
	delegate void ParkEventHandler();
	static event ParkEventHandler^ letCarIn;
	Parking(int t, int o) {
		total = t;
		occupied = o;
		car->tookWaitPosEvent += gcnew Car::CarEventHandler(this, &Parking::can_car_enter);
	}
	property int p_total {
		int get() { return total; };
		void set(int tot) { total = tot; }

	}
	property int p_occupied {
		int get() { return occupied; }
		void set(int occ) { occupied = occ; }
	}
	property int p_free {
		int get() { return total - occupied; }
		void set(int fr) { occupied = total - fr; }
	}
	void can_car_enter() {
		if (total > occupied) letCarIn();
	}
	void send_parametres() {
		try{
			System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
			sa->WriteLine("Parking:");
			sa->WriteLine("Total=" + total);
			sa->WriteLine("Free=" + (total - occupied));
			sa->Close();
		}
		catch (System::IO::IOException^ e) {
			MessageBox::Show("Возникла ошибка чтения интерфейса, это не отразится на функциональности программы, рекомендуется заново включить визуализацию", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	bool park_new_car() {
		if (total - occupied > 0) {
			occupied++;
			return true;
			try {
				System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
				sa->WriteLine("Parking:");
				sa->WriteLine("Occupied=" + occupied);
				sa->Close();
			}
			catch (System::IO::IOException^ e) {
				MessageBox::Show("Возникла ошибка чтения интерфейса, это не отразится на функциональности программы, рекомендуется заново включить визуализацию", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}
		return false;

	}
	bool free_parking_place() {
		if (occupied > 0) {
			occupied--;
			return true;
		}
		return false;
	}
	bool is_parking_avaliable() {
		return(total - occupied > 0 ? true : false);
	}
	void WriteInterface() {
		try{
			System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
			sa->WriteLine("Parking:");
			sa->WriteLine("Total=" + total);
			sa->Close();
		}
		catch (System::IO::IOException^ e) {
			MessageBox::Show("Возникла ошибка чтения интерфейса, это не отразится на функциональности программы, рекомендуется заново включить визуализацию", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
};

