#include<iostream>
#include<stdio.h>
#include<Windows.h>
#include<ctime>
#include<cmath>
#include"Car.h"
#include"Gate.h"
#include"Parking.h"
//#include"Classes.cpp"


void WriteInterface(System::String^ st) {
	System::IO::StreamWriter^ sa = System::IO::File::AppendText("Interface.txt");
	sa->WriteLine(st);
	sa->Close();
}
#pragma once


namespace GateCommander {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
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
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->clear_log_button = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gate_status_trackbar))->BeginInit();
			this->settings_groupbox->SuspendLayout();
			this->manage_groupbox->SuspendLayout();
			this->SuspendLayout();
			// 
			// toggle_visualisation_checkbox
			// 
			this->toggle_visualisation_checkbox->AutoSize = true;
			this->toggle_visualisation_checkbox->Location = System::Drawing::Point(27, 19);
			this->toggle_visualisation_checkbox->Name = L"toggle_visualisation_checkbox";
			this->toggle_visualisation_checkbox->Size = System::Drawing::Size(151, 17);
			this->toggle_visualisation_checkbox->TabIndex = 0;
			this->toggle_visualisation_checkbox->Text = L"Включить визуализацию";
			this->toggle_visualisation_checkbox->UseVisualStyleBackColor = true;
			this->toggle_visualisation_checkbox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::toggle_visualisation_checkbox_CheckedChanged);
			// 
			// gate_status_trackbar
			// 
			this->gate_status_trackbar->Location = System::Drawing::Point(39, 42);
			this->gate_status_trackbar->Maximum = 1;
			this->gate_status_trackbar->Name = L"gate_status_trackbar";
			this->gate_status_trackbar->Size = System::Drawing::Size(122, 45);
			this->gate_status_trackbar->TabIndex = 2;
			this->gate_status_trackbar->Scroll += gcnew System::EventHandler(this, &MyForm::gate_status_trackbar_Scroll);
			// 
			// log_listbox
			// 
			this->log_listbox->FormattingEnabled = true;
			this->log_listbox->Location = System::Drawing::Point(24, 131);
			this->log_listbox->Name = L"log_listbox";
			this->log_listbox->Size = System::Drawing::Size(464, 95);
			this->log_listbox->TabIndex = 3;
			// 
			// space_free_button
			// 
			this->space_free_button->Location = System::Drawing::Point(39, 163);
			this->space_free_button->Name = L"space_free_button";
			this->space_free_button->Size = System::Drawing::Size(122, 38);
			this->space_free_button->TabIndex = 4;
			this->space_free_button->Text = L"Освободить";
			this->space_free_button->UseVisualStyleBackColor = true;
			this->space_free_button->Click += gcnew System::EventHandler(this, &MyForm::space_free_button_Click);
			// 
			// car_create_button
			// 
			this->car_create_button->Location = System::Drawing::Point(39, 119);
			this->car_create_button->Name = L"car_create_button";
			this->car_create_button->Size = System::Drawing::Size(122, 38);
			this->car_create_button->TabIndex = 5;
			this->car_create_button->Text = L"Машина";
			this->car_create_button->UseVisualStyleBackColor = true;
			this->car_create_button->Click += gcnew System::EventHandler(this, &MyForm::car_create_button_Click);
			// 
			// total_input_textbox
			// 
			this->total_input_textbox->Location = System::Drawing::Point(143, 42);
			this->total_input_textbox->Name = L"total_input_textbox";
			this->total_input_textbox->Size = System::Drawing::Size(100, 20);
			this->total_input_textbox->TabIndex = 6;
			// 
			// free_input_textbox
			// 
			this->free_input_textbox->Location = System::Drawing::Point(143, 68);
			this->free_input_textbox->Name = L"free_input_textbox";
			this->free_input_textbox->Size = System::Drawing::Size(100, 20);
			this->free_input_textbox->TabIndex = 7;
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
			this->settings_groupbox->Location = System::Drawing::Point(24, 12);
			this->settings_groupbox->Name = L"settings_groupbox";
			this->settings_groupbox->Size = System::Drawing::Size(464, 102);
			this->settings_groupbox->TabIndex = 8;
			this->settings_groupbox->TabStop = false;
			this->settings_groupbox->Text = L"Базовые параметры";
			// 
			// apply_changes_button
			// 
			this->apply_changes_button->Location = System::Drawing::Point(264, 42);
			this->apply_changes_button->Name = L"apply_changes_button";
			this->apply_changes_button->Size = System::Drawing::Size(116, 46);
			this->apply_changes_button->TabIndex = 11;
			this->apply_changes_button->Text = L"Изменить";
			this->apply_changes_button->UseVisualStyleBackColor = true;
			this->apply_changes_button->Click += gcnew System::EventHandler(this, &MyForm::apply_changes_button_Click);
			// 
			// toggle_automation_checkbox
			// 
			this->toggle_automation_checkbox->AutoSize = true;
			this->toggle_automation_checkbox->Location = System::Drawing::Point(184, 19);
			this->toggle_automation_checkbox->Name = L"toggle_automation_checkbox";
			this->toggle_automation_checkbox->Size = System::Drawing::Size(69, 17);
			this->toggle_automation_checkbox->TabIndex = 10;
			this->toggle_automation_checkbox->Text = L"Автомат";
			this->toggle_automation_checkbox->UseVisualStyleBackColor = true;
			this->toggle_automation_checkbox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::toggle_automation_checkbox_CheckedChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(40, 71);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(91, 13);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Свободных мест";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(40, 49);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(65, 13);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Всего мест";
			// 
			// manage_groupbox
			// 
			this->manage_groupbox->Controls->Add(this->label4);
			this->manage_groupbox->Controls->Add(this->label3);
			this->manage_groupbox->Controls->Add(this->car_create_button);
			this->manage_groupbox->Controls->Add(this->space_free_button);
			this->manage_groupbox->Controls->Add(this->gate_status_trackbar);
			this->manage_groupbox->Location = System::Drawing::Point(504, 12);
			this->manage_groupbox->Name = L"manage_groupbox";
			this->manage_groupbox->Size = System::Drawing::Size(200, 214);
			this->manage_groupbox->TabIndex = 9;
			this->manage_groupbox->TabStop = false;
			this->manage_groupbox->Text = L"Сценарий";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(162, 49);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(32, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Откр";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 49);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(32, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Закр";
			// 
			// clear_log_button
			// 
			this->clear_log_button->Location = System::Drawing::Point(24, 233);
			this->clear_log_button->Name = L"clear_log_button";
			this->clear_log_button->Size = System::Drawing::Size(464, 23);
			this->clear_log_button->TabIndex = 10;
			this->clear_log_button->Text = L"Очистить";
			this->clear_log_button->UseVisualStyleBackColor = true;
			this->clear_log_button->Click += gcnew System::EventHandler(this, &MyForm::clear_log_button_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(719, 277);
			this->Controls->Add(this->clear_log_button);
			this->Controls->Add(this->manage_groupbox);
			this->Controls->Add(this->settings_groupbox);
			this->Controls->Add(this->log_listbox);
			this->Name = L"MyForm";
			this->Text = L"Система управления";
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
bool AUTOMATE = false, VISUALS = false, INIT = false, WAITING_CAR = false;
Parking^ parking = gcnew Parking(300, 100);
Gate^ gate = gcnew Gate();

private: System::Void apply_changes_button_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		TOTAL = Convert::ToInt32(total_input_textbox->Text);
		FREE = Convert::ToInt32(free_input_textbox->Text);
		parking->set_total_places(TOTAL);
		parking->set_occupied_places(TOTAL - FREE);
		if (VISUALS) parking->send_parametres();
		INIT = true;
	}
	catch (...) {
		MessageBox::Show("Не удалось преобразовать введенные данные", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
private: System::Void toggle_visualisation_checkbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (toggle_visualisation_checkbox->Checked) {
		VISUALS = true;
		log_listbox->Items->Add("Визуализация включена.");
		parking->send_parametres();
		gate->send_parametres();
		if (WAITING_CAR) {
			Car^ car = gcnew Car(11);
			car->incoming_car_request();
			WAITING_CAR = false;
		}
		return;
	}
	VISUALS = false;
	log_listbox->Items->Add("Визуализация выключена.");
}
private: System::Void toggle_automation_checkbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (toggle_automation_checkbox->Checked && INIT) {
		AUTOMATE = true;
		log_listbox->Items->Add("Автоматизация включена.");
		total_input_textbox->Enabled = false;
		free_input_textbox->Enabled = false;
		return;
	}
	else if (!toggle_automation_checkbox->Checked && !INIT) {
		MessageBox::Show("Сначала введите информацию о парковке", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
		toggle_automation_checkbox->Checked = false;
		return;
	}
	AUTOMATE = false;
	log_listbox->Items->Add("Автоматизация выключена.");
	total_input_textbox->Enabled = true;
	free_input_textbox->Enabled = true;
}
private: System::Void clear_log_button_Click(System::Object^ sender, System::EventArgs^ e) {
	log_listbox->Items->Clear();
	
}
private: System::Void car_create_button_Click(System::Object^ sender, System::EventArgs^ e) {
	Random^ rand = gcnew Random;
	int random_car_number = rand->Next(0, 999);
	Car^ car = gcnew Car(rand->Next(0, 999));
	
	FREE--;
	free_input_textbox->Text = FREE.ToString();
	parking->set_occupied_places(TOTAL - FREE);
	log_listbox->Items->Add("Машина с номером " + car->get_car_number() + " у шлагбаума");
	if (VISUALS) {
		car->incoming_car_request();
		parking->send_parametres();
	}
	else {
		WAITING_CAR = true;
	}
}
private: System::Void gate_status_trackbar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	if (gate_status_trackbar->Value == 1) {
		gate->open();
	}
	else {
		gate->close();
	}
	if (VISUALS) gate->send_parametres();
}
private: System::Void space_free_button_Click(System::Object^ sender, System::EventArgs^ e) {
	Car^ car = gcnew Car(11);
	FREE++;
	free_input_textbox->Text = FREE.ToString();
	parking->set_occupied_places(TOTAL - FREE);
	log_listbox->Items->Add("Парковочное место освобождено");
	if (VISUALS) {
		log_listbox->Items->Add("Проверка отрисовки");
		car->leaving_car_request();
		parking->send_parametres();
	}
}
};
}
