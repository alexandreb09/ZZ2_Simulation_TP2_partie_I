#include "Affichage.h"

using namespace msclr;
using namespace msclr::interop;
using namespace System;


void afficherTextbox(std::string str, System::Windows::Forms::RichTextBox^  richTextBox1) {
	std::ostringstream oss;
	oss << str;
	std::string ch = oss.str();
	String^ result = marshal_as<String^>(ch);
	richTextBox1->AppendText(result);
}


void afficher_resultats(std::vector<Client> sortie, std::vector<Client> liste_cl_ayant_quitte,
		Machine serveur1, Machine serveur2,
		File file_m1, File file_m2,
		int duree_simulation,
		System::Windows::Forms::RichTextBox^  richTextBox1, 
		System::Windows::Forms::DataVisualization::Charting::Chart^ chart) {

	std::ostringstream oss;

	std::sort(sortie.begin(), sortie.end(), sortByID);

	oss << "Client traités : \n";
	client_dans_vecteur(oss, sortie);

	oss << "\nClient ayant quitté (durée attente > 30s) : \n";
	client_dans_vecteur(oss, liste_cl_ayant_quitte);

	piece_dans_machine(oss, serveur1, file_m1, 1);
	piece_dans_machine(oss, serveur2, file_m2, 2);

	oss << "\n\nNombre moyen client file1 : " << (float)file_m1.getDuree_occupation() / duree_simulation;
	oss << "\nNombre moyen client file2 : " << (float)file_m2.getDuree_occupation() / duree_simulation;
	oss << "\n\nTemps moyen mach1 bloquee : " << (float)100 * serveur1.getDuree_etat_bloquee() / duree_simulation << "%";

	afficherTextbox(oss.str(), richTextBox1);

	affichage_graph(sortie, chart);
}


void client_dans_vecteur(std::ostringstream & oss, std::vector<Client> liste) {
	for (Client cl : liste) {
		oss << "    id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
	}
}

void affichage_graph(std::vector<Client> liste, System::Windows::Forms::DataVisualization::Charting::Chart^ chart) {
	int nb_piece = 0, temps_moyen = 0;
	for (Client cl : liste) {
		nb_piece++;
		temps_moyen += cl.getDate_sortie_syst()-cl.getDate_entree_syst();
		chart->Series[0]->Points->AddXY(nb_piece, temps_moyen / nb_piece);
	}
}

void piece_dans_machine(std::ostringstream & oss, Machine serveur, File file, int numero_machine) {
	oss << "\nListe des pièces dans la machine " << numero_machine << ": \n";
	Client cl = serveur.getClient_present();
	oss << "    id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
	oss << "File :\n";
	while (!file.test_File_Vide()) {
		file.suppression_file(cl);
		oss << "    id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
	}
}


bool sortByID(Client &lhs, Client &rhs) { return lhs.getId() < rhs.getId(); }