#include "File.h"

File::File() :pt_Depart(1), pt_Fin(1), date_event_prec(0), duree_occupation(0), nb_elem(0) {
}


void File::ajout_file(Client & client) {
	if (pt_Depart != (pt_Fin + 1) % (taille_file + 1)) {
		ListeElements[pt_Fin] = client;
		pt_Fin = (pt_Fin + 1) % (taille_file + 1);
		nb_elem++;
	}
}

void File::suppression_file(Client & client) {
	if (pt_Depart != pt_Fin) {
		client = ListeElements[pt_Depart];
		pt_Depart = (pt_Depart + 1) % (taille_file + 1);
		nb_elem--;
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

int File::getDate_event_prec() {
	return date_event_prec;
}
void File::setDate_event_prec(int dep) {
	date_event_prec = dep;
}

int File::getDuree_occupation() {
	return duree_occupation;
}
void File::setDuree_occupation(int duree_occ) {
	duree_occupation = duree_occ;
}

int File::getTaille() {
	return nb_elem;
}


void File::MAJDuree_Occupation(int date_courante) {
	duree_occupation += nb_elem*(date_courante - date_event_prec);
	date_event_prec = date_courante;
}