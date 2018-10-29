#include "File.h"

File::File():pt_Depart(1),pt_Fin(1){
}


void File::ajout_file(Client & client) {
	if (pt_Depart != (pt_Fin + 1) % (taille_file + 1)) {
		ListeElements[pt_Fin] = client;
		pt_Fin = (pt_Fin + 1) % (taille_file + 1);
	}
}

void File::suppression_file(Client & client) {
	if (pt_Depart != pt_Fin) {
		client = ListeElements[pt_Depart];
		pt_Depart = (pt_Depart + 1) % (taille_file + 1);
	}
}

bool File::test_File_Vide() {
	bool res = false;
	if (pt_Depart == pt_Fin) {
		res = true;
	}
	return res;
}

bool File::test_File_pleine() {
	bool res = false;
	if (pt_Depart == (pt_Fin + 1) % (taille_file + 1)) {
		res = true;
	}
	return res;
}

void File::vider_File() {
	pt_Depart = 1;
	pt_Fin = 1;
}
