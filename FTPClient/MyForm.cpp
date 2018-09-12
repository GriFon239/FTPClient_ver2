#include "MyForm.h"


using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void main(array<String^>^ arg) {
	setlocale(LC_ALL, "Russian");
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	FTPClient::MyForm form; 
	Application::Run(%form);
}

