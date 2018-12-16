#pragma once


#include <ostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <msclr\marshal_cppstd.h>

#include "Client.h"
#include "Machine.h"
#include "File.h"

void afficherTextbox(std::string str, System::Windows::Forms::RichTextBox^  richTextBox1);
void afficher_resultats(std::vector<Client> sortie, std::vector<Client> liste_cl_ayant_quitte, Machine serveur1,
	Machine serveur2,
	File file_m1, File file_m2,
	int duree_simulation,
	System::Windows::Forms::RichTextBox^  richTextBox1,
	System::Windows::Forms::DataVisualization::Charting::Chart^ chart);
void piece_dans_machine(std::ostringstream & oss, Machine serveur, File file, int numero_machine);

void client_dans_vecteur(std::ostringstream & oss, std::vector<Client> liste);
void affichage_graph(std::vector<Client> liste, System::Windows::Forms::DataVisualization::Charting::Chart^ chart);


bool sortByID(Client &lhs, Client &rhs);