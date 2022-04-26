#pragma once
ref class Parking
{
private:
	int total;
	int occupied;
public:
	Parking(int t, int o) {
		total = t;
		occupied = o;
	}
	int set_total_places(int tot) {
		total = tot;
		return total;
	}
	int set_occupied_places(int occ) {
		occupied = occ;
		return occupied;
	}
	void send_parametres() {
		System::IO::StreamWriter^ sa = System::IO::File::AppendText("../Interface.txt");
		sa->WriteLine("Parking:");
		sa->WriteLine("Total=" + total);
		sa->WriteLine("Free=" + (total - occupied));
		sa->Close();
	}
	int get_total_places() {
		return total;
	}
	int get_occupied_places() {
		return occupied;
	}
	int get_free_places() {
		return total - occupied;
	}
	bool park_new_car() {
		if (total - occupied > 0) {
			occupied++;
			return true;
			System::IO::StreamWriter^ sa = System::IO::File::AppendText("../Interface.txt");
			sa->WriteLine("Parking:");
			sa->WriteLine("Occupied=" + occupied);
			sa->Close();
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
		System::IO::StreamWriter^ sa = System::IO::File::AppendText("../Interface.txt");
		sa->WriteLine("Parking:");
		sa->WriteLine("Total=" + total);
		sa->Close();
	}
};

