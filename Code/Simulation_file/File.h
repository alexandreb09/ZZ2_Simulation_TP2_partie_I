#pragma once

#ifndef FILE
#define FILE

#include "Client.h"

const int taille_file = 8;

class File {
	int pt_Depart;
	int pt_Fin;
	Client ListeElements[taille_file+1];

	public :
		File();

		bool test_File_pleine();
		void vider_File();
		bool test_File_Vide();
		void ajout_file(Client & client);
		void suppression_file(Client & client);
};


#endif