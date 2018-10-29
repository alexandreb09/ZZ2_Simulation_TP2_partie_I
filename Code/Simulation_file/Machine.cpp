#include "Machine.h"


Machine::Machine() :Etat(0), date_prochain_event(infini) {
}

Machine::Machine(int Etat, int dpe, int dt) : Etat(Etat), date_prochain_event(dpe), duree_traitement(dt) {
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