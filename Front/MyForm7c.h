#pragma once
#include "static_library.h"
#include "stdafx7c.h"

namespace OSlab7c {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm7c
	/// </summary>
	public ref class MyForm7c : public System::Windows::Forms::Form
	{
		array<String^>^ prioritiesText;
	public:
		MyForm7c(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm7c()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label_Result;
	protected:
	private: System::Windows::Forms::Button^ button_terminate;
	private: System::Windows::Forms::Label^ label_timeTaken;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ comboBox_synchronizations;
	private: System::Windows::Forms::TextBox^ box_numOfThreads;
	private: System::Windows::Forms::Button^ button_setPriority;
	private: System::Windows::Forms::ComboBox^ comboBox_Priorities;
	private: System::Windows::Forms::DataGridView^ dataGridView_Main;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ColumnPID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ColumnStatus;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
	private: System::Windows::Forms::Button^ button_resume;
	private: System::Windows::Forms::Button^ button_sus;
	private: System::Windows::Forms::Button^ button_CreateThread;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label_Result = (gcnew System::Windows::Forms::Label());
			this->button_terminate = (gcnew System::Windows::Forms::Button());
			this->label_timeTaken = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox_synchronizations = (gcnew System::Windows::Forms::ComboBox());
			this->box_numOfThreads = (gcnew System::Windows::Forms::TextBox());
			this->button_setPriority = (gcnew System::Windows::Forms::Button());
			this->comboBox_Priorities = (gcnew System::Windows::Forms::ComboBox());
			this->dataGridView_Main = (gcnew System::Windows::Forms::DataGridView());
			this->ColumnPID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnStatus = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button_resume = (gcnew System::Windows::Forms::Button());
			this->button_sus = (gcnew System::Windows::Forms::Button());
			this->button_CreateThread = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_Main))->BeginInit();
			this->SuspendLayout();
			// 
			// label_Result
			// 
			this->label_Result->AutoSize = true;
			this->label_Result->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 10));
			this->label_Result->Location = System::Drawing::Point(762, 531);
			this->label_Result->Name = L"label_Result";
			this->label_Result->Size = System::Drawing::Size(69, 23);
			this->label_Result->TabIndex = 68;
			this->label_Result->Text = L"Result";
			// 
			// button_terminate
			// 
			this->button_terminate->Location = System::Drawing::Point(795, 317);
			this->button_terminate->Name = L"button_terminate";
			this->button_terminate->Size = System::Drawing::Size(103, 53);
			this->button_terminate->TabIndex = 67;
			this->button_terminate->Text = L"Terminate Thread";
			this->button_terminate->UseVisualStyleBackColor = true;
			// 
			// label_timeTaken
			// 
			this->label_timeTaken->AutoSize = true;
			this->label_timeTaken->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 9));
			this->label_timeTaken->Location = System::Drawing::Point(842, 509);
			this->label_timeTaken->Name = L"label_timeTaken";
			this->label_timeTaken->Size = System::Drawing::Size(0, 22);
			this->label_timeTaken->TabIndex = 66;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 10));
			this->label3->Location = System::Drawing::Point(777, 466);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(124, 23);
			this->label3->TabIndex = 65;
			this->label3->Text = L"Time taken:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 10));
			this->label2->Location = System::Drawing::Point(777, 80);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(133, 23);
			this->label2->TabIndex = 64;
			this->label2->Text = L"Sync method";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 10));
			this->label1->Location = System::Drawing::Point(767, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(159, 23);
			this->label1->TabIndex = 63;
			this->label1->Text = L"Num of threads";
			// 
			// comboBox_synchronizations
			// 
			this->comboBox_synchronizations->FormattingEnabled = true;
			this->comboBox_synchronizations->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"None", L"Interlock", L"Monitor" });
			this->comboBox_synchronizations->Location = System::Drawing::Point(766, 106);
			this->comboBox_synchronizations->Name = L"comboBox_synchronizations";
			this->comboBox_synchronizations->Size = System::Drawing::Size(154, 28);
			this->comboBox_synchronizations->TabIndex = 62;
			// 
			// box_numOfThreads
			// 
			this->box_numOfThreads->Location = System::Drawing::Point(795, 39);
			this->box_numOfThreads->Name = L"box_numOfThreads";
			this->box_numOfThreads->Size = System::Drawing::Size(99, 26);
			this->box_numOfThreads->TabIndex = 61;
			// 
			// button_setPriority
			// 
			this->button_setPriority->Location = System::Drawing::Point(795, 410);
			this->button_setPriority->Name = L"button_setPriority";
			this->button_setPriority->Size = System::Drawing::Size(103, 53);
			this->button_setPriority->TabIndex = 60;
			this->button_setPriority->Text = L"Set Priority";
			this->button_setPriority->UseVisualStyleBackColor = true;
			// 
			// comboBox_Priorities
			// 
			this->comboBox_Priorities->FormattingEnabled = true;
			this->comboBox_Priorities->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Realtime", L"High", L"Above normal",
					L"Normal", L"Below normal", L"Low"
			});
			this->comboBox_Priorities->Location = System::Drawing::Point(766, 376);
			this->comboBox_Priorities->Name = L"comboBox_Priorities";
			this->comboBox_Priorities->Size = System::Drawing::Size(154, 28);
			this->comboBox_Priorities->TabIndex = 59;
			// 
			// dataGridView_Main
			// 
			this->dataGridView_Main->AllowUserToAddRows = false;
			this->dataGridView_Main->AllowUserToDeleteRows = false;
			this->dataGridView_Main->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView_Main->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_Main->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->ColumnPID,
					this->Column3, this->ColumnStatus, this->Column4
			});
			this->dataGridView_Main->Location = System::Drawing::Point(1, -1);
			this->dataGridView_Main->Name = L"dataGridView_Main";
			this->dataGridView_Main->ReadOnly = true;
			this->dataGridView_Main->RowHeadersVisible = false;
			this->dataGridView_Main->RowHeadersWidth = 62;
			this->dataGridView_Main->RowTemplate->Height = 28;
			this->dataGridView_Main->Size = System::Drawing::Size(748, 629);
			this->dataGridView_Main->TabIndex = 58;
			// 
			// ColumnPID
			// 
			this->ColumnPID->HeaderText = L"Thread ID";
			this->ColumnPID->MinimumWidth = 120;
			this->ColumnPID->Name = L"ColumnPID";
			this->ColumnPID->ReadOnly = true;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Priority";
			this->Column3->MinimumWidth = 8;
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			// 
			// ColumnStatus
			// 
			this->ColumnStatus->HeaderText = L"Status";
			this->ColumnStatus->MinimumWidth = 8;
			this->ColumnStatus->Name = L"ColumnStatus";
			this->ColumnStatus->ReadOnly = true;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Execution Time";
			this->Column4->MinimumWidth = 155;
			this->Column4->Name = L"Column4";
			this->Column4->ReadOnly = true;
			// 
			// button_resume
			// 
			this->button_resume->Location = System::Drawing::Point(795, 258);
			this->button_resume->Name = L"button_resume";
			this->button_resume->Size = System::Drawing::Size(103, 53);
			this->button_resume->TabIndex = 57;
			this->button_resume->Text = L"Resume Thread";
			this->button_resume->UseVisualStyleBackColor = true;
			// 
			// button_sus
			// 
			this->button_sus->Location = System::Drawing::Point(795, 199);
			this->button_sus->Name = L"button_sus";
			this->button_sus->Size = System::Drawing::Size(103, 53);
			this->button_sus->TabIndex = 56;
			this->button_sus->Text = L"Suspend Thread";
			this->button_sus->UseVisualStyleBackColor = true;
			// 
			// button_CreateThread
			// 
			this->button_CreateThread->Location = System::Drawing::Point(795, 140);
			this->button_CreateThread->Name = L"button_CreateThread";
			this->button_CreateThread->Size = System::Drawing::Size(103, 53);
			this->button_CreateThread->TabIndex = 55;
			this->button_CreateThread->Text = L"Create Threads";
			this->button_CreateThread->UseVisualStyleBackColor = true;
			this->button_CreateThread->Click += gcnew System::EventHandler(this, &MyForm7c::button_CreateThread_Click);
			// 
			// MyForm7c
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(969, 625);
			this->Controls->Add(this->label_Result);
			this->Controls->Add(this->button_terminate);
			this->Controls->Add(this->label_timeTaken);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox_synchronizations);
			this->Controls->Add(this->box_numOfThreads);
			this->Controls->Add(this->button_setPriority);
			this->Controls->Add(this->comboBox_Priorities);
			this->Controls->Add(this->dataGridView_Main);
			this->Controls->Add(this->button_resume);
			this->Controls->Add(this->button_sus);
			this->Controls->Add(this->button_CreateThread);
			this->Name = L"MyForm7c";
			this->Text = L"MyForm7c";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm7c::MyForm7c_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MyForm7c::MyForm7c_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_Main))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		String^ getTime(HANDLE Thread)
		{
			FILETIME ft[4];
			SYSTEMTIME st;
			LPSYSTEMTIME stlp;
			GetThreadTimes(Thread, &ft[0], &ft[1], &ft[2], &ft[3]);
			FileTimeToSystemTime(&ft[3], &st);

			String^ time = gcnew String(Convert::ToString(st.wMinute) + ":" + Convert::ToString(st.wSecond) + ":" + Convert::ToString(st.wMilliseconds));
			return time;
		}

	private: System::Void button_CreateThread_Click(System::Object^ sender, System::EventArgs^ e) {
		auto start = std::chrono::high_resolution_clock::now();
		if (comboBox_synchronizations->Text == "None") {
			numOfThreads = Convert::ToInt32(box_numOfThreads->Text);
			datas = new info * [numOfThreads];
			arrOfSums = new double[numOfThreads]();

			//int* arrays = new int[10];
			//arrays[0] = 5;
			//int** arrays = new int*[10]
			//arrays[0] = new int(10);

			int numOfSteps = 100000000 / numOfThreads;

			for (int i = 0; i < numOfThreads; i++) {
				datas[i] = new info;
				datas[i]->indexOut = i;
				datas[i]->numOfSteps = numOfSteps;
				datas[i]->startPos = numOfSteps * i;
			}

			hThread = new HANDLE[numOfThreads];

			// time!!

			for (int i = 0; i < numOfThreads; i++) {
				hThread[i] = CreateThread(NULL, 0, ThreadFunction, datas[i], CREATE_SUSPENDED, 0);
				dataGridView_Main->Rows->Add(GetThreadId(hThread[i]), GetThreadPriority(hThread[i]), "Suspended", getTime(hThread[i]));
				//dataGridView_Main[0, i]->Value = GetThreadId(hThread[i]);
				//dataGridView_Main[1, i]->Value = GetThreadPriority(hThread[i]);
				//dataGridView_Main[2, i]->Value = "Suspended";
				//dataGridView_Main[3, i]->Value = getTime(hThread[i]);
			}

			//WaitForMultipleObjects(numOfThreads, hThread, TRUE, INFINITE);
			//for (int i = 0; i < numOfThreads; i++) {
			//	*mainSum += arrOfSums[i];
			//}
			label_Result->Text += " " + Convert::ToString(LibSyncFunc::DllFunction(mainArr, 10000));
		}
		else if (comboBox_synchronizations->Text == "Interlock") {
			numOfThreads = Convert::ToInt32(box_numOfThreads->Text);
			datas = new info * [numOfThreads];


			int numOfSteps = 100000000 / numOfThreads;

			for (int i = 0; i < numOfThreads; i++) {
				datas[i] = new info;
				datas[i]->indexOut = i;
				datas[i]->numOfSteps = numOfSteps;
				datas[i]->startPos = numOfSteps * i;
			}

			hThread = new HANDLE[numOfThreads];

			for (int i = 0; i < numOfThreads; i++) {
				hThread[i] = CreateThread(NULL, 0, ThreadFunctionInterlock, datas[i], CREATE_SUSPENDED, 0);
				dataGridView_Main->Rows->Add(GetThreadId(hThread[i]), GetThreadPriority(hThread[i]), "Suspended", getTime(hThread[i]));
			}
			WaitForMultipleObjects(numOfThreads, hThread, TRUE, INFINITE);
		}
		else if (comboBox_synchronizations->Text == "Monitor") {
			numOfThreads = Convert::ToInt32(box_numOfThreads->Text);
			datas = new info * [numOfThreads];


			int numOfSteps = 100000000 / numOfThreads;

			for (int i = 0; i < numOfThreads; i++) {
				datas[i] = new info;
				datas[i]->indexOut = i;
				datas[i]->numOfSteps = numOfSteps;
				datas[i]->startPos = numOfSteps * i;
			}

			hThread = new HANDLE[numOfThreads];

			for (int i = 0; i < numOfThreads; i++) {
				hThread[i] = CreateThread(NULL, 0, ThreadFunctionMonitor, datas[i], CREATE_SUSPENDED, 0);
				dataGridView_Main->Rows->Add(GetThreadId(hThread[i]), GetThreadPriority(hThread[i]), "Suspended", getTime(hThread[i]));
			}

		}

		// time!!
		auto stop = std::chrono::high_resolution_clock::now();


		// time !!
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		label_timeTaken->Text = Convert::ToString(duration.count());
		//box_numOfThreads->Text = Convert::ToString(*mainSum);

		for (int i = 0; i < numOfThreads; i++) {
			dataGridView_Main[3, i]->Value = getTime(hThread[i]);
		}
	}
private: System::Void MyForm7c_Load(System::Object^ sender, System::EventArgs^ e) {
	comboBox_synchronizations->SelectedItem = 0;
	comboBox_synchronizations->SelectedText = "None";

	//mainArr = gcnew array<double>(10000);
	mainArr = new long double[10000];
	mainArr[0] = 2;
	for (int i = 1; i < 10000; i++) {
		mainArr[i] = (mainArr[i - 1] + i) * sin(i);
	}

	prioritiesText = gcnew array<String^> { "Realtime", "High", "Above Normal",
		"Normal", "Below Normal", "Low" };
}
private: System::Void MyForm7c_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	delete mainSum;
	delete[] mainArr;
	delete[] arrOfSums;

	for (int i = 0; i < numOfThreads; i++) {
		delete datas[i];
		//if (hThread != NULL)
		//	CloseHandle(hThread[i]);
	}
	delete[]hThread;
	delete[] datas;
}
};
}
