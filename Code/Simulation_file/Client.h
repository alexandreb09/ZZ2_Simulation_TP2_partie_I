#pragma once


class Client {
	int id;
	int date_entree_syst;
	int date_sortie_syst;

	int date_entree_machine_1;				// Stats
	int date_entree_machine_2;				// Stats

	public:
		Client();
		Client(int id, int des);
		Client(int id, int des, int dss);

		int getId();
		void setId(int n_id);

		int getDate_entree_syst();
		void setDate_entree_syst(int new_des);

		int getDate_sortie_syst();
		void setDate_sortie_syst(int n_dss);
		
		int getDate_entree_machine_1();
		void setDate_entree_machine_1(int dem1);

		int getDate_entree_machine_2();
		void setDate_entree_machine_2(int dem2);
};
