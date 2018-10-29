#pragma once

#include "Client.h"

const int infini = 9999;

class Machine{
	int Etat;
	int date_prochain_event;
	int duree_traitement;
	Client client_present;

	public:
		Machine();
		Machine(int Etat, int date_prochain_event, int dt);

		int getEtat();
		void setEtat(int n_Etat);

		int getDPE();
		void setDPE(int new_des);

		int getDuree_traitement();
		void setDuree_traitement(int dt);

		Client getClient_present();
		void setClient_present(Client n_cl);

};