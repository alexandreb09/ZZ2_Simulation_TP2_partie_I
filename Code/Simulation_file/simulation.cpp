#include "simulation.h"


/*
using namespace msclr;
using namespace msclr::interop;
using namespace System;
*/

void simuler(int duree_sim, int duree_entre_2_cl, int duree_traitement_cl_m1, int duree_traitement_cl_m2, System::Windows::Forms::RichTextBox^  richTextBox1, System::Windows::Forms::DataVisualization::Charting::Chart^ chart) {
	File file_m1;
	File file_m2;
	std::vector<Client> sortie, liste_cl_ayant_quitte;
	Machine serveur1(libre, infini, duree_traitement_cl_m1);
	Machine serveur2(libre, infini, duree_traitement_cl_m2);
	Entree entree(libre, duree_entre_2_cl);

	int date_courante = 0;

	while (date_courante <= duree_sim) {
		/* Recherche DPE la plus petite */
		int P = getProchainEven(serveur1, serveur2, entree,file_m1);	

		switch (P){
			case ENTREE: gererEntrer(file_m1, serveur1, entree, date_courante, sortie);
				break;
			case MACHINE1: gererMachine1(file_m1, file_m2, serveur1, serveur2, entree, date_courante);
				break;
			case MACHINE2: gererMachine2(file_m2, serveur1, serveur2, sortie, date_courante);
				break;
			case FILE1: gererFile1(file_m1, date_courante, liste_cl_ayant_quitte);
				break;
			default: break;
		}
	}
	afficher_resultats(sortie, liste_cl_ayant_quitte, serveur1, serveur2, file_m1, file_m2, duree_sim, richTextBox1, chart);
}

void gererMachine1(File & file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Entree & entree, int & date_courante) {
	date_courante = serveur1.getDPE();
	if (file_m2.test_File_pleine()) {									// Si file m2 pleine
		serveur1.setEtat(bloque);
		serveur1.setDPE(infini);
		serveur1.setDate_entree_etat_bloque(date_courante);
	}
	else {
		Client piece = serveur1.getClient_present();					// La piece sort de la machine 1
		if (serveur2.getEtat() == libre) {								// si m2 libre
			serveur2.setClient_present(piece);							// Et rentre sur la machine 2
			serveur2.setDPE(date_courante + serveur2.getDuree_traitement());
			serveur2.setEtat(occupe);

			piece.setDate_entree_machine_2(date_courante);
		}
		else {
			file_m2.ajout_file(piece);
		}
		file_m2.MAJDuree_Occupation(date_courante);


		if (!file_m1.test_File_Vide()) {
			Client piece_new;											// Recupération piece file_m1
			file_m1.suppression_file(piece_new);
			file_m1.MAJDPE();
			serveur1.setClient_present(piece_new);
			serveur1.setDPE(date_courante + serveur1.getDuree_traitement());
			serveur1.setEtat(occupe);
		}
		else{
			serveur1.setEtat(libre);
			serveur1.setDPE(infini);
			file_m1.setDPE(infini);
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
			serveur1.MAJ_duree_etat_bloquee(date_courante);
		}
	}
	else {
		serveur2.setEtat(libre);
		serveur2.setDPE(infini);
	}
	file_m2.MAJDuree_Occupation(date_courante);
}


void gererEntrer(File & file_m1, Machine &serveur1, Entree & entree, int & date_courante, std::vector<Client> & sortie) {
	date_courante = entree.getDPE();
	Client cl(date_courante);
	entree.setDPE(date_courante + entree.getDuree_inter_arrivee());
	if (file_m1.test_File_pleine()) {
		// cl.setDate_sortie_syst(date_courante);			// On ne s'occupe pas des clients qui sortent
		// sortie.push_back(cl);
	}
	else {
		if (libre == serveur1.getEtat()) {						// Si serveur libre
			serveur1.setEtat(occupe);
			serveur1.setClient_present(cl);
			serveur1.setDPE(date_courante + serveur1.getDuree_traitement());

			cl.setDate_entree_machine_1(date_courante);				// Stats
		}
		else {													// si serveur occupe
			file_m1.ajout_file(cl);								// Ajout dans la file
			if (1 == file_m1.getTaille()) {						// Si c'est le premier element
				file_m1.MAJDPE();								// MAJ DPE file
			}
		}
		file_m1.MAJDuree_Occupation(date_courante);
	}
	entree.setDPE(date_courante + entree.getDuree_inter_arrivee());
}


void gererFile1(File & file1, int & date_courante, std::vector<Client> & liste_cl_quittes) {
	date_courante = file1.getDPE();
	Client client;
	file1.suppression_file(client);
	liste_cl_quittes.push_back(client);
	if (file1.test_File_Vide()) {
		file1.setDPE(infini);
	}
	else {
		file1.MAJDPE();
	}
	// oss << "Sortie du client " << client.getId() << " arrivé à la date " << client.getDate_entree_syst() << " et sortie à la date " << date_courante << "\n";
}


int getProchainEven(Machine serveur1, Machine serveur2, Entree entree, File file_m1) {
	int rep = ENTREE; //entree
	if ((serveur2.getDPE() <= serveur1.getDPE()) & (serveur2.getDPE() <= file_m1.getDPE()) & (serveur2.getDPE() <= entree.getDPE()) ) {
		rep = MACHINE2;
	}
	else {
		if ((serveur1.getDPE() <= entree.getDPE()) & (serveur1.getDPE() <= file_m1.getDPE())) {
			rep = MACHINE1;
		}
		else {
			if (file_m1.getDPE() <= entree.getDPE()) {
				rep = FILE1;
			}
		}
	}
	return rep;
}

