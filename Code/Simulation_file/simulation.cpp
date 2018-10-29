#include "simulation.h"


using namespace msclr;
using namespace msclr::interop;
using namespace System;

const int libre = 0;
const int occupe = 1;
const int bloque = 2;

void simuler(int duree_sim, int duree_entre_2_cl, int duree_traitement_cl_m1, int duree_traitement_cl_m2, System::Windows::Forms::RichTextBox^  richTextBox1, System::Windows::Forms::DataVisualization::Charting::Chart^ chart) {
	File file_m1;
	File file_m2;
	std::vector<Client> sortie;
	Machine serveur1(libre, infini, duree_traitement_cl_m1);
	Machine serveur2(libre, infini, duree_traitement_cl_m2);
	Entree entree(libre, duree_entre_2_cl, 0);

	int date_courante = 0;

	while (date_courante <= 990) {
		/* Recherche DPE la plus petite */
		int P = getProchainEven(serveur1, serveur2, entree);					// Si PDE entree plus petite	

		switch (P){
			case 1: gererEntrer(file_m1, serveur1, entree, date_courante, sortie);
				break;
			case 2: gererMachine1(file_m1, file_m2, serveur1, serveur2, entree, date_courante);
				break;
			default: gererMachine2(file_m2, serveur1, serveur2, sortie, date_courante);
				break;
		}
	}


	while (date_courante <= 1010) {
		/* Recherche DPE la plus petite */
		int P = getProchainEven(serveur1, serveur2, entree);					// Si PDE entree plus petite	

		switch (P) {
		case 1: gererEntrer(file_m1, serveur1, entree, date_courante, sortie);
			break;
		case 2: gererMachine1(file_m1, file_m2, serveur1, serveur2, entree, date_courante);
			break;
		default: gererMachine2(file_m2, serveur1, serveur2, sortie, date_courante);
			break;
		}
	}
	

	std::ostringstream oss;
	std::string res;

	Client cl;
	int nb_piece = 0, temps_moyen = 0;

	std::sort(sortie.begin(), sortie.end(), sortByID);

	for (Client cl : sortie) {
		nb_piece++;
		oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
		temps_moyen += cl.getDate_sortie_syst(); // -cl.getDate_entree_syst();
		chart->Series[0]->Points->AddXY(nb_piece, temps_moyen / nb_piece);
	}

	oss << "\nListe des pièces dans la machine 1: \n";
	cl = serveur1.getClient_present();
	oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
	while (file_m1.test_File_Vide()) {
		file_m1.ajout_file(cl);
		oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
	}

	oss << "\nListe des pièces dans la machine 2: \n";
	cl = serveur2.getClient_present();
	oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
	while (file_m2.test_File_Vide()) {
		file_m2.ajout_file(cl);
		oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
	}

	res = oss.str();
	afficherTextbox(res, richTextBox1);
}

void gererMachine1(File & file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Entree & entree, int & date_courante) {
	date_courante = serveur1.getDPE();
	if (file_m2.test_File_pleine()) {									// Si file m2 pleine
		serveur1.setEtat(bloque);
		serveur1.setDPE(infini);
	}
	else {
		Client piece = serveur1.getClient_present();					// La piece sort de la machine 1
		if (serveur2.getEtat() == libre) {								// si m2 libre
			serveur2.setClient_present(piece);							// Et rentre sur la machine 2
			serveur2.setDPE(date_courante + serveur2.getDuree_traitement());
			serveur2.setEtat(occupe);
		}
		else {
			file_m2.ajout_file(piece);
		}
		if (!file_m1.test_File_Vide()) {
			Client piece_new;											// Recupération piece file_m1
			file_m1.suppression_file(piece_new);
			serveur1.setClient_present(piece_new);
			serveur1.setDPE(date_courante + serveur1.getDuree_traitement());
			serveur1.setEtat(occupe);
		}
		else{
			serveur1.setEtat(libre);
			serveur1.setDPE(infini);
		}
	}
}

void gererMachine2(File &file_m2, Machine &serveur1, Machine &serveur2, std::vector<Client> & sortie, int & date_courante) {
	date_courante = serveur2.getDPE();
	Client cl = serveur2.getClient_present();
	cl.setDate_sortie_syst(date_courante);
	sortie.push_back(cl);
	if (!file_m2.test_File_Vide()) {
		Client cl;
		file_m2.suppression_file(cl);
		serveur2.setClient_present(cl);
		serveur2.setDPE(date_courante + serveur2.getDuree_traitement());
		if (serveur1.getEtat() == bloque) {
			serveur1.setEtat(occupe);
			serveur1.setDPE(date_courante);
		}
	}
	else {
		serveur2.setEtat(libre);
		serveur2.setDPE(infini);
	}
}


void gererEntrer(File & file_m1, Machine &serveur1, Entree & entree, int & date_courante, std::vector<Client> & sortie) {
	date_courante = entree.getDPE();
	Client cl(entree.getDernier_numero(),date_courante);
	entree.setDernier_numero(entree.getDernier_numero()+1);
	entree.setDPE(date_courante + entree.getDuree_inter_arrivee());
	if (file_m1.test_File_pleine()) {
		cl.setDate_sortie_syst(date_courante);
		sortie.push_back(cl);
	}
	else {
		if (libre == serveur1.getEtat()) {
			serveur1.setEtat(occupe);
			serveur1.setClient_present(cl);
			serveur1.setDPE(date_courante + serveur1.getDuree_traitement());
		}
		else {
			file_m1.ajout_file(cl);
		}
	}
	entree.setDPE(date_courante + entree.getDuree_inter_arrivee());
}

int getProchainEven(Machine serveur1, Machine serveur2, Entree entree) {
	int rep = 1; //entree
	if ((serveur2.getDPE() <= serveur1.getDPE()) & (serveur2.getDPE() <= entree.getDPE())) {
		rep = 3;
	}
	else {
		if (serveur1.getDPE() <= entree.getDPE()) {
			rep = 2;
		}
	}
	return rep;
}

void afficherTextbox(std::string str, System::Windows::Forms::RichTextBox^  richTextBox1) {
	std::ostringstream oss;
	oss << str;
	std::string ch = oss.str();
	String^ result = marshal_as<String^>(ch);
	richTextBox1->AppendText(result);
}



bool sortByID(Client &lhs, Client &rhs) { return lhs.getId() < rhs.getId(); }