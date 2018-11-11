#pragma once

#ifndef FILE
#define FILE

#include "Client.h"

const int taille_file = 8;
const int duree_attente_max = 30;

class File {
	int nb_elem;
	int pt_Depart;
	int pt_Fin;
	Client ListeElements[taille_file+1];

	int date_event_prec;				// Stats
	int duree_occupation;				// Stats
	int DPE;							// QT 2

	public :
		File();

		bool test_File_pleine();
		void vider_File();
		bool test_File_Vide();
		void ajout_file(Client & client);
		void suppression_file(Client & client);

		int getDate_event_prec();
		void setDate_event_prec(int dep);
		int getDuree_occupation();
		void setDuree_occupation(int duree_occ);
		int getTaille();

		void MAJDuree_Occupation(int date_courante);

		int File::getDPE();
		void setDPE(int n_dpe);
		void File::MAJDPE();
		Client File::getSommet();
};


#endif