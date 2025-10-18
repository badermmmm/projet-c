#include <stdio.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)

enum {
    MAX_ETUDIANTS = 100,
    MAX_NOM = 31,
    NB_UE = 6,
    NB_SEMESTRES = 6
};

const float NOTE_MIN = 0.f, NOTE_MAX = 20.f;

typedef struct {
    int id;
    char prenom[MAX_NOM];
    char nom[MAX_NOM];
    int semestres;
} Etudiant;

void INSCRIRE(Etudiant etudiants[MAX_ETUDIANTS], int* nb) {
    Etudiant e;
    scanf("%s %s", e.prenom, e.nom);

    // Vérifie si l'étudiant existe déjà
    for (int i = 0; i < *nb; ++i) {
        if (strcmp(e.prenom, etudiants[i].prenom) == 0 &&
            strcmp(e.nom, etudiants[i].nom) == 0) {
            printf("Nom incorrect\n");
            return;
        }
    }

    e.id = *nb;
    e.semestres = 0; // initialisation
    etudiants[*nb] = e;
    ++(*nb);
    printf("Inscription enregistree (%d)\n", *nb);
}

void NOTE(Etudiant etudiants[MAX_ETUDIANTS], int nb_etudiants) {
    int id, ue;
    float note;
    scanf("%d %d %f", &id, &ue, &note);

    if (id < 1 || id > nb_etudiants) {
        printf("Identifiant incorrect\n");
        return;
    }
    if (ue < 1 || ue > NB_UE) {
        printf("UE incorrecte\n");
        return;
    }
    if (note < NOTE_MIN || note > NOTE_MAX) {
        printf("Note incorrecte\n");
        return;
    }
    printf("Note enregistree\n");
}

int main() {
    Etudiant etudiants[MAX_ETUDIANTS];
    int nbEtudiants = 0;
    char mot[30];

    while (1) {
        scanf("%s", mot);

        if (strcmp(mot, "EXIT") == 0) {
            break;
        }
        else if (strcmp(mot, "INSCRIRE") == 0) {
            INSCRIRE(etudiants, &nbEtudiants);
        }
        else if (strcmp(mot, "NOTE") == 0) {
            NOTE(etudiants, &nbEtudiants);
        }
    }

}



