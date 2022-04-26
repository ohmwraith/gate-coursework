#pragma once
ref class Gate
{
private:
	bool opened = false;
public:
	double is_opened() {
		return (opened ? true : false);
	}
	bool open() {
		opened = true;
		System::IO::StreamWriter^ sa = System::IO::File::AppendText("../Interface.txt");
		sa->WriteLine("Gate:");
		sa->WriteLine("Opened=" + opened);
		sa->Close();
		return true;
	}
	bool close() {
		opened = false;
		System::IO::StreamWriter^ sa = System::IO::File::AppendText("../Interface.txt");
		sa->WriteLine("Gate:");
		sa->WriteLine("Opened=" + opened);
		sa->Close();
		return true;
	}
};

