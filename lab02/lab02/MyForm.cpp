#include "MyForm.h"
#pragma hdrstop



using namespace System;
using namespace System::Windows::Forms;


[STAThreadAttribute]
void Main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    //WinformCDemo is your project name
    lab02::MyForm form;
    Application::Run(% form);
}

