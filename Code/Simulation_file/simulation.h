#pragma once

#include <string>

#include "File.h"
#include "Machine.h"
#include "Entree.h"
#include "Affichage.h"

const int libre = 0;
const int occupe = 1;
const int bloque = 2;
const int ENTREE = 0;
const int MACHINE1 = 1;
const int MACHINE2 = 2;
const int FILE1 = 3;

//==============================================

void afficherTextbox(std::string str, System::Windows::Forms::RichTextBox^  richTextBox1);
void gererEntrer(File & file_m1, Machine &serveur1, Entree & entree, int & date_courante, std::vector<Client> & sortie);
void gererMachine1(File & file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Entree & entree, int & date_courante);
void gererMachine2(File &file_m2, Machine &serveur1, Machine &serveur2, std::vector<Client> & sortie, int & date_courante);
void gererFile1(File &file_m1, int &date_courante, std::vector<Client> &);
void simuler(int duree_sim, int duree_entre_2_cl, int duree_traitement_cl_m1, int duree_traitement_cl_m2, System::Windows::Forms::RichTextBox^  richTextBox1, System::Windows::Forms::DataVisualization::Charting::Chart^ chart);

int getProchainEven(const Machine serveur1, const Machine serveur2, const Entree entree, const File file_m1);

/*
float temps_moyen_bloque_m1(Machine machine_2, std::vector<Client> solution);
float temps_moyen_bloque_m2(Machine machine_2, std::vector<Client> solution);
*/
bool sortByID(Client &lhs, Client &rhs);
