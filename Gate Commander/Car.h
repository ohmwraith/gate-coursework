#pragma once
ref class Car
{
private:
	int number;
public:
	
	Car(int n) {
		number = n;
	}
	int get_car_number() {
		return number;
	}
	void incoming_car_request() {
		System::IO::StreamWriter^ sa = System::IO::File::AppendText("../Interface.txt");
		sa->WriteLine("Car:");
		sa->WriteLine("Event=Create");
		sa->WriteLine("Direction=up");
		sa->WriteLine("Number=" + number);
		sa->Close();
	}
	void leaving_car_request() {
		System::IO::StreamWriter^ sa = System::IO::File::AppendText("../Interface.txt");
		sa->WriteLine("Car:");
		sa->WriteLine("Event=Create");
		sa->WriteLine("Direction=down");
		sa->WriteLine("Event=Forward");
		sa->WriteLine("Number=" + number);
		sa->Close();
	}
	void send_forward() {
		System::IO::StreamWriter^ sa = System::IO::File::AppendText("../Interface.txt");
		sa->WriteLine("Car:");
		sa->WriteLine("Event=Forward");
		sa->WriteLine("Direction=up");
		sa->WriteLine("Number=" + number);
		sa->Close();
	}
};

