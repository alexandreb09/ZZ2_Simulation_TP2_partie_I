#pragma once

class Entree {
	int date_prochain_event;
	int duree_inter_arrivee;
	int dernier_numero;

	public:
		Entree();
		Entree(int date_prochain_event, int duree_inter_arrivee, int dernier_numero);

		int getDPE();
		void setDPE(int new_dpe);
	
		int getDuree_inter_arrivee();
		void setDuree_inter_arrivee(int new_dia);

		int getDernier_numero();
		void setDernier_numero(int n_dn);
};
