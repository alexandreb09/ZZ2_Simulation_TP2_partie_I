#include "Entree.h"


Entree::Entree() :date_prochain_event(0), dernier_numero(0) {
}

Entree::Entree(int dpe, int dia, int dn) : date_prochain_event(dpe), duree_inter_arrivee(dia), dernier_numero(dn) {
}

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

int Entree::getDernier_numero() {
	return dernier_numero;
}
void Entree::setDernier_numero(int n_dn) {
	dernier_numero = n_dn;
}