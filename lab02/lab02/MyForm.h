#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <thread>
#include <Windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "WS2_32.Lib")

#define PACKET_BUFF_SIZE 10

std::string ipAddress = "127.0.0.1";  //ipAddress of the server
int port = 1111;  //listening port # on the server
//Fill in a hint structure
struct sockaddr_in hint
{
	hint.sin_family = AF_INET,
		hint.sin_port = htons(port),
};

namespace lab02 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace std;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{



	public:
		bool wf = false; //прогноз погоди
		bool sp = false; //курс акцій
		bool er = false; // курс валют
		bool isListening = false;

	public:

		MyForm(void)
		{
			InitializeComponent();
			/*	int connect_port = 1111;
				const char* server_address = "127.0.0.1";
				char packet_buff[PACKET_BUFF_SIZE];

				// Buffer for WSA and other metadata
				char buff[1024];
				// Sockets library initialisation
				WSAStartup(0x202, reinterpret_cast<WSADATA*> (&buff[0]));

				// Creating socket
				my_sock = socket(AF_INET, SOCK_STREAM, 0);

				// Creating connection
				sockaddr_in dest_addr;
				dest_addr.sin_family = AF_INET;
				dest_addr.sin_port = htons(connect_port);

				// Converting IP from symbols to networking format
				if (inet_addr(server_address) != INADDR_NONE)
					dest_addr.sin_addr.s_addr = inet_addr(server_address);

				// Trying to connect the server
				connect(my_sock,
					reinterpret_cast<sockaddr*> (&dest_addr),
					sizeof(dest_addr));
				CheckForIllegalCrossThreadCalls = false;
				*/
		}


		//MyForm(void)
		//{
		//	InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
	//	}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::RichTextBox^ tb_wf;
	private: System::Windows::Forms::Button^ btn_wf;
	protected:


	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::RichTextBox^ tb_sp;
	private: System::Windows::Forms::RichTextBox^ tb_er;




	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ btn_sp;
	private: System::Windows::Forms::Button^ btn_er;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tb_wf = (gcnew System::Windows::Forms::RichTextBox());
			this->btn_wf = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tb_sp = (gcnew System::Windows::Forms::RichTextBox());
			this->tb_er = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->btn_sp = (gcnew System::Windows::Forms::Button());
			this->btn_er = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label1->Location = System::Drawing::Point(438, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(73, 23);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Привіт!";
			// 
			// tb_wf
			// 
			this->tb_wf->Location = System::Drawing::Point(41, 145);
			this->tb_wf->Name = L"tb_wf";
			this->tb_wf->Size = System::Drawing::Size(274, 181);
			this->tb_wf->TabIndex = 1;
			this->tb_wf->Text = L"";
			// 
			// btn_wf
			// 
			this->btn_wf->BackColor = System::Drawing::Color::MediumSeaGreen;
			this->btn_wf->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_wf->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btn_wf->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btn_wf->Location = System::Drawing::Point(96, 332);
			this->btn_wf->Margin = System::Windows::Forms::Padding(0, 3, 3, 3);
			this->btn_wf->Name = L"btn_wf";
			this->btn_wf->Size = System::Drawing::Size(155, 38);
			this->btn_wf->TabIndex = 4;
			this->btn_wf->Text = L"Відписатися";
			this->btn_wf->UseVisualStyleBackColor = false;
			this->btn_wf->Click += gcnew System::EventHandler(this, &MyForm::btn_wf_Click_1);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label2->Location = System::Drawing::Point(124, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(718, 23);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Тут ти можеш підписатися на один з сервісів і отримувати дані щодекілька секунд";
			// 
			// tb_sp
			// 
			this->tb_sp->Location = System::Drawing::Point(332, 145);
			this->tb_sp->Name = L"tb_sp";
			this->tb_sp->Size = System::Drawing::Size(274, 181);
			this->tb_sp->TabIndex = 6;
			this->tb_sp->Text = L"";
			// 
			// tb_er
			// 
			this->tb_er->Location = System::Drawing::Point(624, 145);
			this->tb_er->Name = L"tb_er";
			this->tb_er->Size = System::Drawing::Size(274, 181);
			this->tb_er->TabIndex = 7;
			this->tb_er->Text = L"";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label3->Location = System::Drawing::Point(101, 119);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(148, 23);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Прогноз погоди";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label4->Location = System::Drawing::Point(421, 119);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(100, 23);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Курс акцій";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label5->Location = System::Drawing::Point(706, 119);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(107, 23);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Курс валют";
			// 
			// btn_sp
			// 
			this->btn_sp->BackColor = System::Drawing::Color::MediumSeaGreen;
			this->btn_sp->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_sp->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btn_sp->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btn_sp->Location = System::Drawing::Point(394, 332);
			this->btn_sp->Margin = System::Windows::Forms::Padding(0, 3, 3, 3);
			this->btn_sp->Name = L"btn_sp";
			this->btn_sp->Size = System::Drawing::Size(155, 38);
			this->btn_sp->TabIndex = 13;
			this->btn_sp->Text = L"Відписатися";
			this->btn_sp->UseVisualStyleBackColor = false;
			this->btn_sp->Click += gcnew System::EventHandler(this, &MyForm::btn_sp_Click);
			// 
			// btn_er
			// 
			this->btn_er->BackColor = System::Drawing::Color::MediumSeaGreen;
			this->btn_er->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_er->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btn_er->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btn_er->Location = System::Drawing::Point(687, 332);
			this->btn_er->Margin = System::Windows::Forms::Padding(0, 3, 3, 3);
			this->btn_er->Name = L"btn_er";
			this->btn_er->Size = System::Drawing::Size(155, 38);
			this->btn_er->TabIndex = 14;
			this->btn_er->Text = L"Відписатися";
			this->btn_er->UseVisualStyleBackColor = false;
			this->btn_er->Click += gcnew System::EventHandler(this, &MyForm::btn_er_Click);
			// 
			// MyForm
			// 
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->ClientSize = System::Drawing::Size(937, 430);
			this->Controls->Add(this->btn_er);
			this->Controls->Add(this->btn_sp);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->tb_er);
			this->Controls->Add(this->tb_sp);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->btn_wf);
			this->Controls->Add(this->tb_wf);
			this->Controls->Add(this->label1);
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"Сервіс розсилки";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}


#pragma endregion
	public:
		int showError(int result) {
			if (result != 0)
				System::Windows::Forms::MessageBox::Show("The error occured in starting winsock");
			else
				System::Windows::Forms::MessageBox::Show("WinSock created");
			return 0;
		}

	public:	int invalidSocket(SOCKET sock) {
		if (sock == INVALID_SOCKET) {
			System::Windows::Forms::MessageBox::Show("The socket is invalid");
			WSACleanup();
		}
		return 0;
	}
	public:
		int connectionError(int result, SOCKET sock) {
			if (result != SOCKET_ERROR)
				System::Windows::Forms::MessageBox::Show("The connection is not set");
			else
				System::Windows::Forms::MessageBox::Show("Connection is set");
			closesocket(sock);
			WSACleanup();
			return 0;
		}



		//initialize WinSock
		WSAData* data = new WSAData;
		WORD ver = MAKEWORD(2, 2);
		int wsResult = WSAStartup(ver, data);
		int ifErrorExist = showError(wsResult);

		//Create socket
		SOCKET sock = socket(AF_INET6, SOCK_STREAM, 0);
		int ifSocketIsInvalid = invalidSocket(sock);

		//fill in a hint structure 
		//filled in the header of the file
		int res = inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
		//connect to the server
		int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
		int ifConnected = connectionError(connResult, sock);


		//do-while loop to send and recieve data

	public: void obtainingData() {

		while (true) {
			char* buffer = new char[4096];
			ZeroMemory(buffer, 4096);
			recv(sock, buffer, 1000, 0);
			char version = buffer[0];
			std::string str = buffer;
			str.erase(0, 1);
			if (version == 'w') {
				tb_wf->Text = gcnew String(str.c_str());
			}
			else if (version == 'a') {
				tb_sp->Text = gcnew String(str.c_str());
			}
			else if (version == 'b') {
				tb_er->Text = gcnew String(str.c_str());
			}
			memset(buffer, '\0', 1000);
		}
		//closesocket(sock);
	}

		  void Listening() {
			  Thread^ MyThread = nullptr;
			  ThreadStart^ ThreadMethod = gcnew ThreadStart(this, &MyForm::obtainingData);
			  //ThreadStart^ ThreadMethod = gcnew ThreadStart(this, NULL);
			  MyThread = gcnew Thread(ThreadMethod);
			  MyThread->Start();
		  }

	private: System::Void btn_wf_Click(System::Object^ sender, System::EventArgs^ e) {

	}

	private: System::Void btn_wf_Click_1(System::Object^ sender, System::EventArgs^ e) {
		if (!isListening) {
			Listening();
			isListening = true;
		}
		if (wf) {
			btn_wf->Text = "Підписатися";
			tb_wf->Text = "Ви ще не підписалися";
			char* strin2 = new char[2];
			strin2 = "w";
			send(sock, strin2, 1, 0);
			wf = false;
		}
		else {
			btn_wf->Text = "Відписатися";
			tb_wf->Text = "";
			char* strin2 = new char[2];
			strin2 = "0";
			send(sock, strin2, 1, 0);
			wf = true;
		}
		closesocket(sock);
	}
	private: System::Void btn_sp_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!isListening) {
			Listening();
			isListening = true;
		}
		if (sp) {
			btn_sp->Text = "Підписатися";
			tb_sp->Text = "Ви ще не підписані";
			char* strin2 = new char[2];
			strin2 = "a";
			send(sock, "a", 1, 0);
			sp = false;
		}
		else {
			btn_sp->Text = "Відписатися";
			tb_sp->Text = "";
			char* strin2 = new char[2];
			strin2 = "0";
			send(sock, strin2, 1, 0);
			sp = true;
		}

	}
	private: System::Void btn_er_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!isListening) {
			Listening();
			isListening = true;
		}
		if (er) {
			btn_er->Text = "Підписатися";
			tb_er->Text = "Ви ще не підписані";
			char* strin2 = new char[2];
			strin2 = "b";
			send(sock, "b", 1, 0);
			er = false;
		}
		else {
			btn_er->Text = "Відписатися";
			tb_er->Text = "";
			char* strin2 = new char[2];
			strin2 = "0";
			send(sock, strin2, 1, 0);
			er = true;
		}


	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

	}
	};
}

