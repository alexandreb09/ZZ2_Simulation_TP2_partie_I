#pragma once

#ifndef FILE
#define FILE

#include "Client.h"

const int taille_file = 8;

class File {
	int nb_elem;
	int pt_Depart;
	int pt_Fin;
	int date_event_prec;
	int duree_occupation;
	Client ListeElements[taille_file+1];

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
};


#endif