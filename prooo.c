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
    float notes[NB_SEMESTRES][NB_UE];
    int hors_formation; // 0=en cours, 1=demission, 2=defaillance
} Etudiant;

// --- INSCRIRE ---
void INSCRIRE(Etudiant etudiants[MAX_ETUDIANTS], int* nb) {
    Etudiant e;
    scanf("%s %s", e.prenom, e.nom);

    for (int i = 0; i < *nb; ++i) {
        if (strcmp(e.prenom, etudiants[i].prenom) == 0 &&
            strcmp(e.nom, etudiants[i].nom) == 0) {
            printf("Nom incorrect\n");
            return;
        }
    }

    e.id = *nb + 1;
    e.semestres = 1;
    e.hors_formation = 0;

    for (int s = 0; s < NB_SEMESTRES; s++)
        for (int u = 0; u < NB_UE; u++)
            e.notes[s][u] = -1.0f;

    etudiants[*nb] = e;
    ++(*nb);
    printf("Inscription enregistree (%d)\n", *nb);
}

// --- NOTE ---
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

    Etudiant* e = &etudiants[id - 1];

    if (e->hors_formation) {
        printf("Etudiant hors formation\n");
        return;
    }

    e->notes[e->semestres - 1][ue - 1] = note;
    printf("Note enregistree\n");
}

// --- CURSUS ---
void CURSUS(Etudiant etudiants[MAX_ETUDIANTS], int nb_etudiants) {
    int id;
    scanf("%d", &id);

    if (id < 1 || id > nb_etudiants) {
        printf("Identifiant incorrect\n");
        return;
    }

    Etudiant* e = &etudiants[id - 1];

    printf("%d %s %s\n", e->id, e->prenom, e->nom);

    for (int s = 0; s < e->semestres; s++) {
        printf("S%d - ", s + 1);
        for (int ue = 0; ue < NB_UE; ue++) {
            float note = e->notes[s][ue];
            if (note < 0)
                printf("* (*)");
            else {
                float nAffiche = floorf(note * 10) / 10;  // 🔹 tronquer à 1 chiffre sans arrondir
                const char* code = (note >= 10.0f) ? "ADM" : "AJ";
                printf("%.1f (%s)", nAffiche, code);
            }
            if (ue < NB_UE - 1) printf(" - ");
        }

        // Affichage du statut à la fin du semestre
        if (e->hors_formation == 1)
            printf(" - demission\n");
        else if (e->hors_formation == 2)
            printf(" - defaillance\n");
        else
            printf(" - en cours\n");
    }
}

// --- ETUDIANTS ---
void ETUDIANTS(Etudiant etudiants[MAX_ETUDIANTS], int nb_etudiants) {
    for (int i = 0; i < nb_etudiants; i++) {
        Etudiant e = etudiants[i];
        char statut[20] = "en cours";

        if (e.hors_formation == 1)
            strcpy(statut, "demission");
        else if (e.hors_formation == 2)
            strcpy(statut, "defaillance");

        printf("%d - %s %s - S%d - %s\n", e.id, e.prenom, e.nom, e.semestres, statut);
    }
}

// --- DEMISSION ---
void DEMISSION(Etudiant etudiants[MAX_ETUDIANTS], int nb_etudiants) {
    int id;
    scanf("%d", &id);

    if (id < 1 || id > nb_etudiants) {
        printf("Identifiant incorrect\n");
        return;
    }

    Etudiant* e = &etudiants[id - 1];

    if (e->hors_formation) {
        printf("Etudiant hors formation\n");
        return;
    }

    e->hors_formation = 1;
    printf("Demission enregistree\n");
}

// --- DEFAILLANCE ---
void DEFAILLANCE(Etudiant etudiants[MAX_ETUDIANTS], int nb_etudiants) {
    int id;
    scanf("%d", &id);

    if (id < 1 || id > nb_etudiants) {
        printf("Identifiant incorrect\n");
        return;
    }

    Etudiant* e = &etudiants[id - 1];

    if (e->hors_formation) {
        printf("Etudiant hors formation\n");
        return;
    }

    e->hors_formation = 2;
    printf("Defaillance enregistree\n");
}

// --- JURY ---
void JURY(Etudiant etudiants[MAX_ETUDIANTS], int nb_etudiants) {
    int semestre_courant;
    scanf("%d", &semestre_courant);

    if (semestre_courant < 1 || semestre_courant > NB_SEMESTRES) {
        printf("Semestre incorrect\n");
        return;
    }

    int manquantes = 0;
    int etudiants_concernes = 0;

    for (int i = 0; i < nb_etudiants; i++) {
        Etudiant* e = &etudiants[i];

        if (e->hors_formation) continue;
        if (e->semestres != semestre_courant) continue;

        etudiants_concernes++;

        int complet = 1;
        for (int ue = 0; ue < NB_UE; ue++) {
            if (e->notes[semestre_courant - 1][ue] < 0) {
                complet = 0;
                break;
            }
        }

        if (!complet)
            manquantes = 1;
    }

    if (etudiants_concernes == 0) {
        printf("Aucun etudiant au semestre %d\n", semestre_courant);
        return;
    }

    if (manquantes)
        printf("Des notes sont manquantes\n");
    else
        printf("Semestre termine pour %d etudiant(s)\n", etudiants_concernes);
}

// --- MAIN ---
int main() {
    Etudiant etudiants[MAX_ETUDIANTS];
    int nbEtudiants = 0;
    char mot[30];

    while (1) {
        scanf("%s", mot);

        if (strcmp(mot, "EXIT") == 0) break;
        else if (strcmp(mot, "INSCRIRE") == 0) INSCRIRE(etudiants, &nbEtudiants);
        else if (strcmp(mot, "NOTE") == 0) NOTE(etudiants, nbEtudiants);
        else if (strcmp(mot, "CURSUS") == 0) CURSUS(etudiants, nbEtudiants);
        else if (strcmp(mot, "ETUDIANTS") == 0) ETUDIANTS(etudiants, nbEtudiants);
        else if (strcmp(mot, "DEMISSION") == 0) DEMISSION(etudiants, nbEtudiants);
        else if (strcmp(mot, "DEFAILLANCE") == 0) DEFAILLANCE(etudiants, nbEtudiants);
        else if (strcmp(mot, "JURY") == 0) JURY(etudiants, nbEtudiants);
    }
}
