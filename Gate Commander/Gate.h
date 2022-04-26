#pragma once
ref class Gate
{
private:
	bool Closed = true;
public:
	double is_opened() {
		return (Closed ? false : true);
	}
	bool open() {
		Closed = false;
		return true;
	}
	bool close() {
		Closed = true;
		return true;
	}
};

