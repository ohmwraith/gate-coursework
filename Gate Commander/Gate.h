using namespace System::Windows::Forms;
#pragma once
ref class Gate
{
protected:
	void open() {
		opened = true;
		CHANGED(opened);
		OPENED();
	}
	void close() {
		opened = false;
		CHANGED(opened);
		CLOSED();
	}
private:
	bool opened;

public:
	//������� ��� �������
	delegate void GateEventHandler();
	delegate void GateChangedHandler(bool NewStatus);
	static event GateChangedHandler^ CHANGED;
	//������� ������
	static event GateEventHandler^ CREATED;
	//������� �������. �������� ����� ������� � ������
	static event GateEventHandler^ OPENED;
	//������� �������. �� ���� �������� ����� ��������� ������
	static event GateEventHandler^ CLOSED;
	// ������� ��������� ��������� ����������. �� ���� �������� ������ ���������.
	static event GateEventHandler^ TOGGLED;

	Gate(int open) {
		opened = open;
		CREATED();
	}
	property bool p_opened{
		bool get() { return opened; };
	}
	double is_opened() {
		return (opened ? true : false);
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
			MessageBox::Show("�������� ������ ������ ����������, ��� �� ��������� �� ���������������� ���������, ������������� ������ �������� ������������", "��������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
};

