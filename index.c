#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <locale.h>  
typedef struct {
    int jour;    
    int mois;    
    int annee;   
} Date;

typedef struct {
    int secteur;       
    char ville[30];
} Residence;

typedef struct Etudiant {
    char nom[30];           
    char prenom[30];        
    int code;               
    Date naissance;         
    char telephone[8];      
    Residence residence;    
    struct Etudiant *next;  
} Etudiant;


void pause();


int genererID() {
    srand(time(NULL));
    return 20250000 + (rand() % 10000); 
}

Etudiant *creerEtudiant() {
    Etudiant *e = (Etudiant*)malloc(sizeof(Etudiant));
    
    printf("\n--- Nouvel Étudiant ---\n");
    printf("Nom: "); scanf("%s", e->nom);
    printf("Prénom: "); scanf("%s", e->prenom);
    
    e->code = genererID(); 
    printf("-> ID généré: %d\n", e->code); 
    
    printf("Téléphone: "); scanf("%s", e->telephone);
    
    printf("Date de naissance (JJ MM AAAA): ");
    scanf("%d %d %d", &e->naissance.jour, &e->naissance.mois, &e->naissance.annee);
    
    printf("Ville: "); scanf("%s", e->residence.ville);
    printf("Secteur: "); scanf("%d", &e->residence.secteur);
    
    e->next = NULL; 
    return e;
}

void ajouterDebut(Etudiant **tete) {
    Etudiant *nouveau = creerEtudiant();  
    nouveau->next = *tete;                
    *tete = nouveau;                      
    printf("✅ Étudiant ajouté en tête (ID: %d)\n", nouveau->code);
}

void ajouterFin(Etudiant **tete) {
    Etudiant *nouveau = creerEtudiant();  
    if (*tete == NULL) {                 
        *tete = nouveau;                 
    } else {
        Etudiant *temp = *tete;           
        while (temp->next != NULL) {     
            temp = temp->next;            
        }
        temp->next = nouveau;             
    }
    printf("✅ Étudiant ajouté à la fin (ID: %d)\n", nouveau->code);
}

void afficherEtudiant(Etudiant *e) {
    printf("\n─────── FICHE ÉTUDIANT ───────\n");
    printf("│ ID: %-20d │\n", e->code);
    printf("│ Nom: %-18s %s │\n", e->prenom, e->nom);
    printf("│ Tél: %-19s │\n", e->telephone);
    printf("│ Naissance: %02d/%02d/%-10d │\n", e->naissance.jour, e->naissance.mois, e->naissance.annee);
    printf("│ Ville: %-15s (Secteur %d) │\n", e->residence.ville, e->residence.secteur);
    printf("───────────────────────────────\n");
}

void afficherListeEtudiants(Etudiant *tete) {
    if (tete == NULL) {
        printf("\n📢 La liste est vide, chef !\n");
        return;
    }

    printf("\n📋 LISTE DES ÉTUDIANTS :\n");
    printf("┌──────────┬────────────┬────────────┐\n");
    printf("│   ID     │    Nom     │  Prénom    │\n");
    printf("├──────────┼────────────┼────────────┤\n");

    Etudiant *actuel = tete;
    while (actuel != NULL) {
        printf("│ %-8d │ %-10s │ %-10s │\n", 
               actuel->code, actuel->nom, actuel->prenom);
        actuel = actuel->next;
    }
    printf("└──────────┴────────────┴────────────┘\n");
}

int nombreEtudiants(Etudiant *tete) {
    int count = 0;
    Etudiant *actuel = tete;

    while (actuel != NULL) {
        count++;
        actuel = actuel->next; 
    }

    return count;
}

Etudiant* rechercherEtudiantParID(Etudiant *tete, int id) {
    Etudiant *actuel = tete;

    while (actuel != NULL) {
        if (actuel->code == id) {
            return actuel; 
        }
        actuel = actuel->next;
    }

    return NULL; 
}

void afficherMenu() {
    system("clear || cls"); 

    printf("\n\033[1;36m"); 
    printf("┌───────────────────────────────────┐\n");
    printf("│    📚 GESTION ÉTUDIANTS PRO       │\n");
    printf("├───────────────────────────────────┤\n");
    printf("│ 1. Inscrir étudiant (début)       │\n");
    printf("│ 2. Inscrir étudiant (fin)         │\n");
    printf("│ 3. Afficher la liste              │\n");
    printf("│ 4. Nombre d'étudiants             │\n");
    printf("│ 5. Rechercher par ID              │\n");
    printf("│ 6. Supprimer un étudiant          │\n");
    printf("│ 7. Fermer                         │\n");
    printf("└───────────────────────────────────┘\n");
    printf("\033[0m"); 
    printf("Choix : ");
}

void gererMenu(Etudiant **liste) {
    int choix;
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            ajouterDebut(liste);
            break;
        case 2:
            ajouterFin(liste);
            break;
        case 3:
            afficherListeEtudiants(*liste);
            break;
        case 4:
            printf("\nNombre d'étudiants : %d\n", nombreEtudiants(*liste));
            break;
        case 5: {
            int id;
            printf("ID à rechercher : ");
            scanf("%d", &id);
            Etudiant *trouve = rechercherEtudiantParID(*liste, id);
            if (trouve) afficherEtudiant(trouve);
            else printf("❌ ID non trouvé.\n");
            break;
        }
        case 6:
            printf("\n🚧 Fonction en construction...\n");
            break;
        case 7:
            printf("\nÀ bientôt, chef ! 👋\n");
            exit(0);
        default:
            printf("\n❌ Option invalide !\n");
    }
}


void pause() {
    printf("\nAppuyez sur Entrée pour continuer...");
    while (getchar() != '\n'); 
    getchar();
}

int main() {
    system("chcp 65001 > nul");  // Pour Windows (force UTF-8)



    while (1) { 
        afficherMenu();      
        gererMenu(&liste);   
        pause();           
    }

    return 0;
}