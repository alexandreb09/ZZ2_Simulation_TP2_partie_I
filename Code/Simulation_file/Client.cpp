#include "Client.h"

Client::Client() :id(0), date_entree_syst(0) {}

Client::Client(int id, int des) : id(id), date_entree_syst(des) {}

Client::Client(int id, int des, int dss):id(id), date_entree_syst(des), date_sortie_syst(dss) {}


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
