#include <stdio.h>
#include <string.h>
#pragma warning (disable:4996)


enum {Max_Etudiants=100};


typedef struct {
	char prenom[30];
	char nom[30];
} Etudiant;

void EXIT() {
	char mot[100];
	while (1) {
		scanf("%s",&mot);

		if (strcmp(mot,"EXIT") == 0) {
			break;
		}
	}
}
void INSCRIRE(Etudiant etudiants[Max_Etudiants], int* nb) {
	Etudiant e;

	scanf("%s %s", e.prenom, e.nom);

	for (int i = 0; i < Max_Etudiants; ++i) {
		if (strcmp(e.prenom,etudiants[i].prenom)==0 && strcmp(e.nom, etudiants[i].nom) == 0) {
			printf("##ERROR##\n");
			return;
		}
	}

	etudiants[*nb] = e;
	printf("Inscription enregistree (%d)", *nb + 1);
	++*nb;	
}

int main() {
	Etudiant etudiants[Max_Etudiants];
	int nb_etudiants = 0;

	//EXIT();
	while(1)
		INSCRIRE(etudiants, &nb_etudiants);

}
