#include "Machine.h"


Machine::Machine() :Etat(0), date_prochain_event(infini),date_entree_etat_bloque(0),duree_etat_bloquee(0) {
}

Machine::Machine(int Etat, int dpe, int dt) : Etat(Etat), date_prochain_event(dpe), duree_traitement(dt),date_entree_etat_bloque(0), duree_etat_bloquee(0) {
}

int Machine::getEtat() {
	return Etat;
}
void Machine::setEtat(int n_Etat) {
	Etat = n_Etat;
}

int Machine::getDPE() {
	return date_prochain_event;
}
void Machine::setDPE(int new_des) {
	date_prochain_event = new_des;
}

int Machine::getDuree_traitement() {
	return duree_traitement;
}
void Machine::setDuree_traitement(int dt) {
	duree_traitement = dt;
}

Client Machine::getClient_present() {
	return client_present;
}
void Machine::setClient_present(Client n_cl) {
	client_present = n_cl;
}


void Machine::MAJ_duree_etat_bloquee(int date_courante) {
	duree_etat_bloquee += date_courante - date_entree_etat_bloque;
}
int Machine::getDuree_etat_bloquee() {
	return duree_etat_bloquee;
}

void Machine::setDate_entree_etat_bloque(int detb) {
	date_entree_etat_bloque = detb;
}