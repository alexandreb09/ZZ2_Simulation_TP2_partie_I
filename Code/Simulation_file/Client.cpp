#include "Client.h"

int Client::nb_cl = 0;

Client::Client() :id(-1), date_entree_syst(0), date_sortie_syst(-1), date_entree_machine_1(-1), date_entree_machine_2(-1){}

Client::Client(int des) : id(nb_cl++), date_entree_syst(des), date_sortie_syst(-1), date_entree_machine_1(-1), date_entree_machine_2(-1) {}

Client::Client(int des, int dss):id(nb_cl++), date_entree_syst(des), date_sortie_syst(dss), date_entree_machine_1(-1), date_entree_machine_2(-1) {}


int Client::getId() {
	return id;
}
void Client::setId(int n_id) {
	id = n_id;
};

int Client::getDate_entree_syst() {
	return date_entree_syst;
};
void Client::setDate_entree_syst(int new_des) {
	date_entree_syst = new_des;
}

int Client::getDate_sortie_syst() {
	return date_sortie_syst;
}
void Client::setDate_sortie_syst(int n_dss) {
	date_sortie_syst = n_dss;
};

int Client::getDate_entree_machine_1() {
	return date_entree_machine_1;
}
void Client::setDate_entree_machine_1(int dem1) {
	date_entree_machine_1 = dem1;
}

int Client::getDate_entree_machine_2() {
	return date_entree_machine_2;
}
void Client::setDate_entree_machine_2(int dem2) {
	date_entree_machine_2 = dem2;
}

