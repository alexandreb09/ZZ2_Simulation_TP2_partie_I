// Simulation_file.cpp : fichier projet principal.

#include "form_main.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]

int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Simulation_file::form_main form;
	Application::Run(%form);

	return 0;
}
