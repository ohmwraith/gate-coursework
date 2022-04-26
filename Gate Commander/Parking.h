#pragma once
ref class Parking
{
private:
	int total = 300;
	int occupied = 280;
public:
	int set_total_places(int tot) {
		total = tot;
		return total;
	}
	int set_occupied_places() {
		return occupied;
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
};

