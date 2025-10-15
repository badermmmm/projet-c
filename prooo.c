#include <stdio.h>
#include <string.h>
#pragma warning (disable:4996)

typedef struct {
	char prenom[30];
	char nom[30];
	int id;
} Etudiant;

void EXIT() {
	char mot[100];
	while (1) {
		printf("action:");
		scanf("%s", &mot);

		if (strcmp(mot, "EXIT") == 0) {
			printf("Fin du programme.\n");
		}

	}

}
void INSCRIRE(Etudiant etudiants[]) {


}
int main() {
	EXIT();
}