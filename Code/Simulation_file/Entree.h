#pragma once

class Entree {
	int date_prochain_event;
	int duree_inter_arrivee;

	public:
		Entree();
		Entree(int date_prochain_event, int duree_inter_arrivee);

		int getDPE();
		void setDPE(int new_dpe);
	
		int getDuree_inter_arrivee();
		void setDuree_inter_arrivee(int new_dia);
};
