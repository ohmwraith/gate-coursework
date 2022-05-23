#include<iostream>
#include<stdio.h>
#include <WinSock2.h>
#include<Windows.h>
#include<ctime>
#include<cmath>
#include"Car.h"
#include"Gate.h"
#include"Parking.h"
#include <string>
#include <WS2tcpip.h>
#include <sstream>
#include <iomanip>
#include "Interface.h"

#pragma comment(lib, "ws2_32.lib")

void WriteInterface(System::String^ st) {
	try {
		System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
		sa->WriteLine(st);
		sa->Close();
	}
	catch (System::IO::IOException^ e) {
		MessageBox::Show("Возникла ошибка чтения интерфейса, это не отразится на функциональности программы, рекомендуется заново включить визуализацию", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
}

//Метод, выдающий случайное целое число
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

#pragma once


namespace GateCommander {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		Gate^ gate;
		Car^ car;
		Parking^ parking;
		Interface^ sock;
	public:
		MyForm(void)
		{	
			int TOTAL = getRandomNumber(10, 1000), FREE = getRandomNumber(1, TOTAL);
			parking = gcnew Parking(TOTAL, TOTAL - FREE);
			gate = gcnew Gate(false);
			//Инициализация переменных сокета
			sock = gcnew Interface();
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^ toggle_visualisation_checkbox;
	private: System::Windows::Forms::TrackBar^ gate_status_trackbar;
	private: System::Windows::Forms::ListBox^ log_listbox;
	private: System::Windows::Forms::Timer^ timer1;
	protected:

	protected:


	private: System::Windows::Forms::Button^ space_free_button;

	private: System::Windows::Forms::Button^ car_create_button;

	private: System::Windows::Forms::TextBox^ total_input_textbox;
	private: System::Windows::Forms::TextBox^ free_input_textbox;
	private: System::Windows::Forms::GroupBox^ settings_groupbox;



	private: System::Windows::Forms::CheckBox^ toggle_automation_checkbox;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::GroupBox^ manage_groupbox;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ apply_changes_button;
	private: System::Windows::Forms::Button^ clear_log_button;
	private: System::Windows::Forms::Button^ car_forward_button;
	private: System::Windows::Forms::Button^ close_button;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->toggle_visualisation_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->gate_status_trackbar = (gcnew System::Windows::Forms::TrackBar());
			this->log_listbox = (gcnew System::Windows::Forms::ListBox());
			this->space_free_button = (gcnew System::Windows::Forms::Button());
			this->car_create_button = (gcnew System::Windows::Forms::Button());
			this->total_input_textbox = (gcnew System::Windows::Forms::TextBox());
			this->free_input_textbox = (gcnew System::Windows::Forms::TextBox());
			this->settings_groupbox = (gcnew System::Windows::Forms::GroupBox());
			this->apply_changes_button = (gcnew System::Windows::Forms::Button());
			this->toggle_automation_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->manage_groupbox = (gcnew System::Windows::Forms::GroupBox());
			this->car_forward_button = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->clear_log_button = (gcnew System::Windows::Forms::Button());
			this->close_button = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gate_status_trackbar))->BeginInit();
			this->settings_groupbox->SuspendLayout();
			this->manage_groupbox->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// toggle_visualisation_checkbox
			// 
			this->toggle_visualisation_checkbox->AutoSize = true;
			this->toggle_visualisation_checkbox->Location = System::Drawing::Point(24, 25);
			this->toggle_visualisation_checkbox->Name = L"toggle_visualisation_checkbox";
			this->toggle_visualisation_checkbox->Size = System::Drawing::Size(217, 24);
			this->toggle_visualisation_checkbox->TabIndex = 0;
			this->toggle_visualisation_checkbox->Text = L"Включить визуализацию";
			this->toggle_visualisation_checkbox->UseVisualStyleBackColor = true;
			this->toggle_visualisation_checkbox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::toggle_visualisation_checkbox_CheckedChanged);
			// 
			// gate_status_trackbar
			// 
			this->gate_status_trackbar->Location = System::Drawing::Point(9, 52);
			this->gate_status_trackbar->Maximum = 1;
			this->gate_status_trackbar->Name = L"gate_status_trackbar";
			this->gate_status_trackbar->Size = System::Drawing::Size(185, 45);
			this->gate_status_trackbar->TabIndex = 2;
			this->gate_status_trackbar->Scroll += gcnew System::EventHandler(this, &MyForm::gate_status_trackbar_Scroll);
			// 
			// log_listbox
			// 
			this->log_listbox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->log_listbox->FormattingEnabled = true;
			this->log_listbox->ItemHeight = 20;
			this->log_listbox->Location = System::Drawing::Point(24, 152);
			this->log_listbox->Name = L"log_listbox";
			this->log_listbox->ScrollAlwaysVisible = true;
			this->log_listbox->Size = System::Drawing::Size(464, 164);
			this->log_listbox->TabIndex = 3;
			// 
			// space_free_button
			// 
			this->space_free_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->space_free_button->Location = System::Drawing::Point(9, 193);
			this->space_free_button->Name = L"space_free_button";
			this->space_free_button->Size = System::Drawing::Size(185, 47);
			this->space_free_button->TabIndex = 4;
			this->space_free_button->Text = L"Освободить";
			this->space_free_button->UseVisualStyleBackColor = true;
			this->space_free_button->Click += gcnew System::EventHandler(this, &MyForm::space_free_button_Click);
			// 
			// car_create_button
			// 
			this->car_create_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->car_create_button->Location = System::Drawing::Point(9, 140);
			this->car_create_button->Name = L"car_create_button";
			this->car_create_button->Size = System::Drawing::Size(185, 47);
			this->car_create_button->TabIndex = 5;
			this->car_create_button->Text = L"Машина";
			this->car_create_button->UseVisualStyleBackColor = true;
			this->car_create_button->Click += gcnew System::EventHandler(this, &MyForm::car_create_button_Click);
			// 
			// total_input_textbox
			// 
			this->total_input_textbox->Location = System::Drawing::Point(178, 52);
			this->total_input_textbox->Name = L"total_input_textbox";
			this->total_input_textbox->Size = System::Drawing::Size(100, 26);
			this->total_input_textbox->TabIndex = 6;
			this->total_input_textbox->TextChanged += gcnew System::EventHandler(this, &MyForm::total_input_textbox_TextChanged);
			this->total_input_textbox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::total_input_textbox_KeyPress);
			// 
			// free_input_textbox
			// 
			this->free_input_textbox->Location = System::Drawing::Point(178, 87);
			this->free_input_textbox->Name = L"free_input_textbox";
			this->free_input_textbox->Size = System::Drawing::Size(100, 26);
			this->free_input_textbox->TabIndex = 7;
			this->free_input_textbox->TextChanged += gcnew System::EventHandler(this, &MyForm::free_input_textbox_TextChanged);
			this->free_input_textbox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::free_input_textbox_KeyPress);
			// 
			// settings_groupbox
			// 
			this->settings_groupbox->Controls->Add(this->apply_changes_button);
			this->settings_groupbox->Controls->Add(this->toggle_automation_checkbox);
			this->settings_groupbox->Controls->Add(this->label2);
			this->settings_groupbox->Controls->Add(this->label1);
			this->settings_groupbox->Controls->Add(this->toggle_visualisation_checkbox);
			this->settings_groupbox->Controls->Add(this->free_input_textbox);
			this->settings_groupbox->Controls->Add(this->total_input_textbox);
			this->settings_groupbox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->settings_groupbox->Location = System::Drawing::Point(24, 12);
			this->settings_groupbox->Name = L"settings_groupbox";
			this->settings_groupbox->Size = System::Drawing::Size(464, 131);
			this->settings_groupbox->TabIndex = 8;
			this->settings_groupbox->TabStop = false;
			this->settings_groupbox->Text = L"Базовые параметры";
			// 
			// apply_changes_button
			// 
			this->apply_changes_button->Location = System::Drawing::Point(311, 52);
			this->apply_changes_button->Name = L"apply_changes_button";
			this->apply_changes_button->Size = System::Drawing::Size(114, 61);
			this->apply_changes_button->TabIndex = 11;
			this->apply_changes_button->Text = L"Изменить";
			this->apply_changes_button->UseVisualStyleBackColor = true;
			this->apply_changes_button->Click += gcnew System::EventHandler(this, &MyForm::apply_changes_button_Click);
			// 
			// toggle_automation_checkbox
			// 
			this->toggle_automation_checkbox->AutoSize = true;
			this->toggle_automation_checkbox->Enabled = false;
			this->toggle_automation_checkbox->Location = System::Drawing::Point(258, 22);
			this->toggle_automation_checkbox->Name = L"toggle_automation_checkbox";
			this->toggle_automation_checkbox->Size = System::Drawing::Size(95, 24);
			this->toggle_automation_checkbox->TabIndex = 10;
			this->toggle_automation_checkbox->Text = L"Автомат";
			this->toggle_automation_checkbox->UseVisualStyleBackColor = true;
			this->toggle_automation_checkbox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::toggle_automation_checkbox_CheckedChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(37, 87);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(135, 20);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Свободных мест";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(37, 58);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(94, 20);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Всего мест";
			// 
			// manage_groupbox
			// 
			this->manage_groupbox->Controls->Add(this->car_forward_button);
			this->manage_groupbox->Controls->Add(this->label4);
			this->manage_groupbox->Controls->Add(this->label3);
			this->manage_groupbox->Controls->Add(this->car_create_button);
			this->manage_groupbox->Controls->Add(this->space_free_button);
			this->manage_groupbox->Controls->Add(this->gate_status_trackbar);
			this->manage_groupbox->Enabled = false;
			this->manage_groupbox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->manage_groupbox->Location = System::Drawing::Point(504, 12);
			this->manage_groupbox->Name = L"manage_groupbox";
			this->manage_groupbox->Size = System::Drawing::Size(200, 304);
			this->manage_groupbox->TabIndex = 9;
			this->manage_groupbox->TabStop = false;
			this->manage_groupbox->Text = L"Сценарий";
			// 
			// car_forward_button
			// 
			this->car_forward_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->car_forward_button->Location = System::Drawing::Point(9, 246);
			this->car_forward_button->Name = L"car_forward_button";
			this->car_forward_button->Size = System::Drawing::Size(185, 47);
			this->car_forward_button->TabIndex = 8;
			this->car_forward_button->Text = L"Проехать";
			this->car_forward_button->UseVisualStyleBackColor = true;
			this->car_forward_button->Click += gcnew System::EventHandler(this, &MyForm::car_forward_button_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(147, 36);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(47, 20);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Откр";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 36);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(46, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Закр";
			// 
			// clear_log_button
			// 
			this->clear_log_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->clear_log_button->Location = System::Drawing::Point(24, 322);
			this->clear_log_button->Name = L"clear_log_button";
			this->clear_log_button->Size = System::Drawing::Size(464, 31);
			this->clear_log_button->TabIndex = 10;
			this->clear_log_button->Text = L"Очистить";
			this->clear_log_button->UseVisualStyleBackColor = true;
			this->clear_log_button->Click += gcnew System::EventHandler(this, &MyForm::clear_log_button_Click);
			// 
			// close_button
			// 
			this->close_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->close_button->Location = System::Drawing::Point(514, 322);
			this->close_button->Name = L"close_button";
			this->close_button->Size = System::Drawing::Size(184, 31);
			this->close_button->TabIndex = 11;
			this->close_button->Text = L"Закрыть";
			this->close_button->UseVisualStyleBackColor = true;
			this->close_button->Click += gcnew System::EventHandler(this, &MyForm::close_button_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(719, 363);
			this->Controls->Add(this->close_button);
			this->Controls->Add(this->clear_log_button);
			this->Controls->Add(this->manage_groupbox);
			this->Controls->Add(this->settings_groupbox);
			this->Controls->Add(this->log_listbox);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"Система управления";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gate_status_trackbar))->EndInit();
			this->settings_groupbox->ResumeLayout(false);
			this->settings_groupbox->PerformLayout();
			this->manage_groupbox->ResumeLayout(false);
			this->manage_groupbox->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

//Инициализация переменных
int TOTAL = NULL, FREE = NULL;
bool AUTOMATE = false, VISUALS = false, INIT = true, WAITING_CAR = false;

private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{

}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	try {
		System::IO::FileStream^ sa = System::IO::File::Create("./Interface.txt");
		sa->Close();
	}
	catch (System::IO::IOException^ e) {
		MessageBox::Show("Возникла ошибка чтения интерфейса, это не отразится на функциональности программы, рекомендуется заново включить визуализацию", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
}
private: System::Void apply_changes_button_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!AUTOMATE) {
		try {
			TOTAL = Convert::ToInt32(total_input_textbox->Text);
			FREE = Convert::ToInt32(free_input_textbox->Text);
			if (TOTAL >= FREE) {
				parking->p_total = TOTAL;
				parking->p_free = FREE;
				log_listbox->Items->Add("[НАСТРОЙКИ] Установлено: Всего - " + TOTAL.ToString() + ", Свободно - " + FREE.ToString());
				if (VISUALS) parking->send_parametres();
				manage_groupbox->Enabled = true;
				INIT = true;
				toggle_automation_checkbox->Enabled = true;
			} 
			else {
				TOTAL = NULL;
				FREE = NULL;
				MessageBox::Show("Общее количество мест должно быть больше количества свободных мест", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}
		catch (...) {
			MessageBox::Show("Не удалось преобразовать введенные данные, проверьте правильность ввода", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	else {
		MessageBox::Show("Невозможно изменить параметры пока включен автомат", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
}
private: System::Void toggle_visualisation_checkbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
	sa->WriteLine("Global:");
	sa->WriteLine("Event=Clear");
	sa->Close();
	if (toggle_visualisation_checkbox->Checked) {
		VISUALS = true;
		log_listbox->Items->Add("[НАСТРОЙКИ] Визуализация включена.");
		parking->send_parametres();
		gate->send_parametres();
		if (WAITING_CAR) {
			Car^ car = gcnew Car(11, 1, 2, 3);
			car->incoming_car_request();
		}
		return;
	}
	VISUALS = false;
	log_listbox->Items->Add("[НАСТРОЙКИ] Визуализация выключена.");
}
private: System::Void toggle_automation_checkbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (toggle_automation_checkbox->Checked && INIT) {
		AUTOMATE = true;
		log_listbox->Items->Add("[НАСТРОЙКИ] Автоматизация включена.");
		total_input_textbox->Enabled = false;
		free_input_textbox->Enabled = false;
		gate_status_trackbar->Enabled = false;
		car_forward_button->Enabled = false;
		if (WAITING_CAR) {
			gate_status_trackbar->Value = 1;
			gate->open();
			log_listbox->Items->Add("[АВТОМАТ] Открытие шлагбаума");
			gate->send_parametres();
			Car^ car = gcnew Car(1, 1, 2, 3);
			car->send_forward();
			log_listbox->Items->Add("[АВТОМАТ] Машина проезжает на парковку");
			Sleep(1000);
			gate_status_trackbar->Value = 0;
			gate->close();
			log_listbox->Items->Add("[АВТОМАТ] Закрытие шлагбаума");
			gate->send_parametres();
			FREE--;
			free_input_textbox->Text = FREE.ToString();
			parking->p_free = FREE;
			parking->send_parametres();
			WAITING_CAR = false;
		}
		return;
	}
	else if (!toggle_automation_checkbox->Checked && !INIT) {
		MessageBox::Show("Сначала введите информацию о парковке", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
		toggle_automation_checkbox->Checked = false;
		return;
	}
	AUTOMATE = false;
	log_listbox->Items->Add("[НАСТРОЙКИ] Автоматизация выключена.");
	total_input_textbox->Enabled = true;
	free_input_textbox->Enabled = true;
	gate_status_trackbar->Enabled = true;
	car_forward_button->Enabled = true;
}
private: System::Void clear_log_button_Click(System::Object^ sender, System::EventArgs^ e) {
	log_listbox->Items->Clear();
	
}
private: System::Void car_create_button_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!WAITING_CAR) {
		Random^ rand = gcnew Random;
		int random_car_number = rand->Next(0, 999);
		Car^ car = gcnew Car(rand->Next(0, 999), 1, 2, 3);

		log_listbox->Items->Add("[СОБЫТИЕ] Машина " + car->p_number + " у шлагбаума");
		WAITING_CAR = true;
		if (VISUALS) {
			car->incoming_car_request();
			parking->send_parametres();
		}
		if (AUTOMATE) {
			if (parking->is_parking_avaliable()) {
				gate_status_trackbar->Value = 1;
				gate->open();
				log_listbox->Items->Add("[АВТОМАТ] Открытие шлагбаума");
				gate->send_parametres();
				car->send_forward();
				log_listbox->Items->Add("[АВТОМАТ] Машина проезжает на парковку");
				Sleep(1000);
				gate_status_trackbar->Value = 0;
				gate->close();
				log_listbox->Items->Add("[АВТОМАТ] Закрытие шлагбаума");
				gate->send_parametres();
				FREE--;
				free_input_textbox->Text = FREE.ToString();
				parking->p_free = FREE;
				parking->send_parametres();
				WAITING_CAR = false;
			}
			else {
				log_listbox->Items->Add("[АВТОМАТ] Машина ожидает свободного места");
			}
		}
	}
	else {
		log_listbox->Items->Add("[ВНИМАНИЕ] Другая машина уже стоит у входа");
		MessageBox::Show("Невозможно создать машину, пока у шлагбаума стоит другая машина", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}
}
private: System::Void gate_status_trackbar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	if (gate_status_trackbar->Value == 1) {
		gate->open();
		log_listbox->Items->Add("[ШЛАГБАУМ] Проезд ОТКРЫТ");
	}
	else {
		gate->close();
		log_listbox->Items->Add("[ШЛАГБАУМ] Проезд ЗАКРЫТ");
	}
	if (VISUALS) gate->send_parametres();
}
private: System::Void space_free_button_Click(System::Object^ sender, System::EventArgs^ e) {
	if (FREE != TOTAL) {
		Car^ car = gcnew Car(11, 1, 2, 3);
		FREE++;
		free_input_textbox->Text = FREE.ToString();
		parking->p_free = FREE;
		parking->send_parametres();
		log_listbox->Items->Add("[ПАРКОВКА] Место освобождено");
		if (VISUALS) {
			car->leaving_car_request();
			parking->send_parametres();
		}
		if (AUTOMATE && WAITING_CAR && parking->is_parking_avaliable()) {
			gate_status_trackbar->Value = 1;
			gate->open();
			log_listbox->Items->Add("[АВТОМАТ] Ворота ОТКРЫТЫ");
			gate->send_parametres();
			car->send_forward();
			log_listbox->Items->Add("[АВТОМАТ] Машина проезжает на парковку");
			Sleep(1000);
			gate_status_trackbar->Value = 0;
			gate->close();
			log_listbox->Items->Add("[АВТОМАТ] Ворота ЗАКРЫТЫ");
			gate->send_parametres();
			FREE--;
			free_input_textbox->Text = FREE.ToString();
			parking->p_free = FREE;
			parking->send_parametres();
			WAITING_CAR = false;
		}
	}
	else {
		log_listbox->Items->Add("[ВНИМАНИЕ] На парковке нет машин, все существующие места свободны");
		MessageBox::Show("На парковке нет машин, все существующие места свободны", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}
}
private: System::Void car_forward_button_Click(System::Object^ sender, System::EventArgs^ e) {
	if (WAITING_CAR) {
		if (gate->is_opened()) {
			if (parking->is_parking_avaliable()) {
				Car^ car = gcnew Car(11, 1, 2, 3);
				if (VISUALS) car->send_forward();
				FREE--;
				free_input_textbox->Text = FREE.ToString();
				parking->p_free = FREE;
				parking->send_parametres();
				WAITING_CAR = false;
				log_listbox->Items->Add("[ПАРКОВКА] Машина припаркована");
			}
			else {
				log_listbox->Items->Add("[ВНИМАНИЕ] На парковке нет свободного места!");
				MessageBox::Show("Парковка полностью занята, невозможно проехать", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
			}
		}
		else {
			log_listbox->Items->Add("[ВНИМАНИЕ] Невозможно проехать, дорога закрыта");
			MessageBox::Show("Путь закрыт, невозможно проехать", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
		}
	}
	else {
		log_listbox->Items->Add("[ВНИМАНИЕ] Проехать может только машина стоящая у въезда");
		MessageBox::Show("Проехать может только машина стоящая у въезда", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}
}
	private: System::Void total_input_textbox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if ((e->KeyChar < 48 || e->KeyChar > 57) && e->KeyChar != '\b') // 48-57 [A-Z + символы #,@,< и тд]
			e->Handled = true;

		// ограничение нажатия двойного 0
		if (e->KeyChar == (char)Keys::D0 || e->KeyChar == (char)Keys::NumPad0)  // Если нажата клавиша 0
			if (total_input_textbox->Text->Length >= 1)        // Если строка не пустая
				if (total_input_textbox->Text[0] == '0' && total_input_textbox->SelectionStart < 2)
					e->Handled = true;
	}
	private: System::Void free_input_textbox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if ((e->KeyChar < 48 || e->KeyChar > 57) && e->KeyChar != '\b') // 48-57 [A-Z + символы #,@,< и тд]
			e->Handled = true;

		// ограничение нажатия двойного 0
		if (e->KeyChar == (char)Keys::D0 || e->KeyChar == (char)Keys::NumPad0)  // Если нажата клавиша 0
			if (free_input_textbox->Text->Length >= 1)        // Если строка не пустая
				if (free_input_textbox->Text[0] == '0' && free_input_textbox->SelectionStart < 2)
					e->Handled = true;
	}
private: System::Void total_input_textbox_TextChanged(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void free_input_textbox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void close_button_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}
};
}
