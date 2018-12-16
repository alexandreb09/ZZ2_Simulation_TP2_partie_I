#include "Entree.h"


Entree::Entree() :date_prochain_event(0){
}

Entree::Entree(int dpe, int dia) : date_prochain_event(dpe), duree_inter_arrivee(dia){}

int Entree::getDPE() {
	return date_prochain_event;
}
void Entree::setDPE(int dpe) {
	date_prochain_event = dpe;
}

int Entree::getDuree_inter_arrivee() {
	return duree_inter_arrivee;
}
void Entree::setDuree_inter_arrivee(int new_dia) {
	duree_inter_arrivee = new_dia;
}
