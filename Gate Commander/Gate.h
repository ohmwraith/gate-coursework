using namespace System::Windows::Forms;
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
		return true;
	}
	bool close() {
		opened = false;
		return true;
	}
	bool toggle() {
		opened ? opened = false : opened = true;
		return true;
	}
	void send_parametres() {
		try {
			System::IO::StreamWriter^ sa = System::IO::File::AppendText("../Interface.txt");
			sa->WriteLine("Gate:");
			sa->WriteLine("Opened=" + opened);
			sa->Close();
		}
		catch (System::IO::IOException^ e) {
			MessageBox::Show("�������� ������ ������ ����������, ��� �� ��������� �� ���������������� ���������, ������������� ������ �������� ������������", "��������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
};

