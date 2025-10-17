#include <stdio.h>
#include <string.h>
#include <math.h>
#pragma warning (disable:4996)
enum {
	MAX_ETUDIANTS = 100,
	MAX_NOM = 31
};
typedef struct {
	int id;// identifiant de l'étudiant
	char prenom[MAX_NOM];// prenom de l'étudiant
	char nom[MAX_NOM];// nom de l'étudiant
	int semestres;// semestres de l'étudiant
} Etudiant;
typedef struct {
	int nbEtudiants;
	Etudiant etudiants[MAX_ETUDIANTS];
} Promotion;


enum {
	MAX_ETUDIANTS = 100,
	NB_UE = 6, NB_SEMESTRES = 6,
	MAX_NOM = 31
};
const float NOTE_MIN = 0.f, NOTE_MAX = 20.f;



void EXIT() {
	char mot[100];
	while (1) {
		scanf("%s",mot);

		if (strcmp(mot,"EXIT") == 0) {
			break;
		}
	}
}
// variable qui sert à inscrire un étudiant avec son nom prenom et lui donne un id 
void INSCRIRE(Etudiant etudiants[MAX_ETUDIANTS], int* id) {
	Etudiant e;

	scanf("%s %s",e.prenom,e.nom);

	for (int i = 0; i < MAX_ETUDIANTS; ++i) {
		if (strcmp(e.prenom, etudiants[i].prenom) == 0 && strcmp(e.nom, etudiants[i].nom) == 0) {
			printf("##ERROR##\n");
			return;
		}
	}

	etudiants[*id] = e;
	++*id;
	printf("Inscription enregistree (%d)\n", *id);
}
// variable qui sert ou plutot qui servira quand elle marchera a mettre des notes aux etudiants dans un tableau de 6/6 pour les 6 semstres differents et les 3années 
void NOTE(Etudiant *p,int id,int ue,float note) {
	scanf("%d %d %f", id, ue, note);
	for (int i = 0; i < NB_SEMESTRES; ++i) {
		
	}
}


// la fonction principale qui utilise toute les autres fonctions
int main() {
	Etudiant etudiants[MAX_ETUDIANTS];
	int nb_etudiants = 0;
	char mot[30];
	Promotion p;
	p.nbEtudiants = 0;
	int note;
	int id;
	// boucle de l’ interpr´eteur de commande
	while (1) {
		scanf("%s",mot);

		if (strcmp(mot,"EXIT") == 0) {
			break;
		}
		else if (strcmp(mot, "INSCRIRE") == 0) {
			INSCRIRE(etudiants, &nb_etudiants);
		}
		else if (strcmp(mot,"NOTE") == 0) {
			NOTE(id, note ) ;
		}
	}

}

