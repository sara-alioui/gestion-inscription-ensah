#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include  <stdbool.h>
#define MAX_LIGNE 256

#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"
#define BLACK   "\033[30m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"


typedef struct datenaisse {
    int jour;
    int mois;
    int annee;
} datenaisse;
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;
typedef struct etudiant {
    char nom[20];
    char prenom[20];
    datenaisse date;
    char ville[20];
    char num_tele[15];
    char mot_de_passe[100];
    char nv[200];
    char gmail[200];
    char cne[200];
    int note1;
    int note2;
    int note3;
    float moyenne;  // Moyenne calculée
    char sex[200];
} etudiant;
// Structure pour représenter un administrateur
void aafficherCentre(const char *message) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    int largeur_terminal = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    int largeur_message = strlen(message);

    int espacement_gauche = (largeur_terminal - largeur_message) / 2;
    for (int i = 0; i < espacement_gauche; i++) {
        printf(" ");
    }
    printf("%s\n", message);
}
typedef struct {
    char nom[50];
    char motDePasse[50];
} Admin;
typedef struct Etudiant {
    char nv[200];           // Niveau
    char nom[20];           // Nom
    char prenom[20];        // Prénom
    Date date;              // Date de naissance
    char ville[20];         // Ville
    char num_tele[20];      // Numéro de téléphone
    char mot_de_passe[100]; // Mot de passe
    char gmail[200];        // Adresse Gmail
    char cne[200];
    int absences;
    char sexe[200];         // CNE
} Etudiant;
void afficherCadreCentree(char *titre) {
    // Calcul de la longueur de la ligne de la console
    int longueur = 80;  // Taille standard de la console, à ajuster selon votre écran
    int titleLen = strlen(titre);
    int espacesAvant = (longueur - titleLen - 4) / 2;  // Calculer les espaces pour centrer

    // Afficher les astérisques avant et après le titre
    for (int i = 0; i < longueur; i++) {
        printf("*");
    }
    printf("\n");

    // Affichage centré du titre avec des espaces avant et après
    for (int i = 0; i < espacesAvant; i++) {
        printf(" ");
    }
    printf("* %s *\n", titre);

    // Affichage des astérisques après le titre
    for (int i = 0; i < longueur; i++) {
        printf("*");
    }
    printf("\n");
}
void afficheerCentre(const char *message) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    int largeur_terminal = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    int largeur_message = strlen(message);

    int espacement_gauche = (largeur_terminal - largeur_message) / 2;
    for (int i = 0; i < espacement_gauche; i++) {
        printf(" ");
    }
    printf("%s\n", message);
}
void afficherDansCadre(const char *message) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    int largeur_terminal = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;

    int largeur_message = strlen(message) + 4; // 4 pour les bords et espaces
    int espacement_gauche = (largeur_terminal - largeur_message) / 2;

    // Déplacer le curseur en haut du terminal
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hConsole, coord);

    // Effacer la première ligne (facultatif)
    for (int i = 0; i < largeur_terminal; i++) {
        printf(" ");
    }
    SetConsoleCursorPosition(hConsole, coord);

    // Bord supérieur du cadre
    for (int i = 0; i < espacement_gauche; i++) printf(" ");
    printf("+");
    for (int i = 0; i < largeur_message - 2; i++) printf("-");
    printf("+\n");

    // Contenu du cadre
    for (int i = 0; i < espacement_gauche; i++) printf(" ");
    printf("| %s |\n", message);

    // Bord inférieur du cadre
    for (int i = 0; i < espacement_gauche; i++) printf(" ");
    printf("+");
    for (int i = 0; i < largeur_message - 2; i++) printf("-");
    printf("+\n");
}
int cheercherEtudiant(char *cneRecherche, Etudiant *etu) {
    FILE *fichier = fopen("eleve_ensah.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier eleve_ensah.txt.\n");
        return 0;
    }

    char ligne[300];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%s %s %s %d %d %d %s %s %s %s %s",
               etu->nv, etu->nom, etu->prenom,
               &etu->date.jour, &etu->date.mois, &etu->date.annee,
               etu->ville, etu->num_tele,
               etu->mot_de_passe, etu->gmail, etu->cne);
        if (strcmp(etu->cne, cneRecherche) == 0) {
            fclose(fichier);
            return 1; // Étudiant trouvé
        }
    }

    fclose(fichier);
    return 0; // Étudiant non trouvé
}
void rechercherEtudiantParCNE(const char *nomFichier, const char *cneRecherche) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", nomFichier);
        return;
    }

    char ligne[MAX_LIGNE];
    int trouve = 0;

    // Lecture ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        // Découper la ligne en champs (en supposant que les champs sont séparés par des espaces)
        char nv[20], nom[50], prenom[50], date[20], ville[50], numTele[20], motDePasse[50], gmail[50], cne[20], sexe[10];
        sscanf(ligne, "%s %s %s %s %s %s %s %s %s %s", nv, nom, prenom, date, ville, numTele, motDePasse, gmail, cne, sexe);

        // Comparer le CNE
        if (strcmp(cne, cneRecherche) == 0) {
            printf("Etudiant trouve !\n");
            printf("Niveau : %s\n", nv);
            printf("Nom : %s\n", nom);
            printf("Prenom : %s\n", prenom);
            printf("Date de naissance : %s\n", date);
            printf("Ville : %s\n", ville);
            printf("Numero de telephone : %s\n", numTele);
            printf("Mot de passe : %s\n", motDePasse);
            printf("Gmail : %s\n", gmail);
            printf("CNE : %s\n", cne);
            printf("Sexe : %s\n", sexe);
            trouve = 1;
            break; // Quitter la boucle après avoir trouvé l'étudiant
        }
    }

    if (!trouve) {
        printf("Erreur : Aucun etudiant trouve avec le CNE : %s\n", cneRecherche);
    }

    fclose(fichier);
}

void afficherHistorique(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r"); // Ouvre le fichier en mode lecture
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier '%s'.\n", nomFichier);
        return;
    }

    char ligne[256]; // Tampon pour lire les lignes
    printf("\n--- Historique ---\n");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne); // Affiche chaque ligne
    }

    fclose(fichier); // Ferme le fichier
    printf("\n--- Fin de l'historique ---\n");
}


// Fonction pour rechercher un étudiant dans le fichier
int chercherEtudiantt(char *cneRecherche, Etudiant *etu) {
    FILE *fichier = fopen("eleve_ensahh.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier eleve_ensah.txt.\n");
        return 0;
    }

    char ligne[300];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%s %s %s %d %d %d %s %s %s %s %s",
               etu->nv, etu->nom, etu->prenom,
               &etu->date.jour, &etu->date.mois, &etu->date.annee,
               etu->ville, etu->num_tele,
               etu->mot_de_passe, etu->gmail, etu->cne);
        if (strcmp(etu->cne, cneRecherche) == 0) {
            fclose(fichier);
            return 1; // Étudiant trouvé
        }
    }

    fclose(fichier);
    return 0; // Étudiant non trouvé
}
// Fonction pour générer une attestation d'inscription
void genererAttestation(Etudiant etu) {
    changerCouleur(MAGENTA);

    printf("\n\t\t\t\t\t*******************************************\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**    === Attestation d'inscription ===  **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t*******************************************\n");
        changerCouleur(WHITE);
        effacerEcranAvecAttenteEntree();
        changerCouleur(BLUE);
    printf("L'Ecole Nationale des Sciences Appliquees d'AL HOCIEMA delivre cette attestation a :\n\n\n\n");
        changerCouleur(MAGENTA);

    printf("Nom         : %s\n", etu.nom);
    printf("Prenom      : %s\n", etu.prenom);
    printf("CNE         : %s\n", etu.cne);
    printf("Niveau      : %s\n", etu.nv);
    printf("\nSignature : _________\n");
        changerCouleur(BLACK);

}



// Fonction pour générer un diplôme
void genererDiplome(Etudiant etu) {
   changerCouleur(MAGENTA);

    printf("\n\t\t\t\t\t*******************************************\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**        === D I P L O M E ===          **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t*******************************************\n");
        changerCouleur(WHITE);
        effacerEcranAvecAttenteEntree();
        changerCouleur(BLUE);
    if (strcmp(etu.nv, "cp1") == 0 || strcmp(etu.nv, "cp2") == 0) {
            changerCouleur(RED);
        printf("\n\n\n\t\t\t\tAucun diplome n'existe pour le moment pour l'etudiant %s %s (%s).\n", etu.nom, etu.prenom, etu.nv);
        changerCouleur(BLUE);
    } else if (strstr(etu.nv, "GC1") || strstr(etu.nv, "GEER1") || strstr(etu.nv, "GEAU1") ||
               strstr(etu.nv, "GMEC1") || strstr(etu.nv, "GI1") || strstr(etu.nv, "ID1") || strstr(etu.nv, "TDIA1")) {
        printf("\n\n\n\t\t\t %s %s (%s) a termine les deux annees de classes preparatoires.\n", etu.nom, etu.prenom, etu.nv);

    } else if (strstr(etu.nv, "GC2") || strstr(etu.nv, "GEER2") || strstr(etu.nv, "GEAU2") ||
               strstr(etu.nv, "GMEC2") || strstr(etu.nv, "GI2") || strstr(etu.nv, "ID2") || strstr(etu.nv, "TDIA2")) {
        printf("\n\n\n\t\t\t %s %s (%s) a obtenu une licence dans sa filiere.\n", etu.nom, etu.prenom, etu.nv);
    } else if (strstr(etu.nv, "GC3") || strstr(etu.nv, "GEER3") || strstr(etu.nv, "GEAU3") ||
               strstr(etu.nv, "GMEC3") || strstr(etu.nv, "GI3") || strstr(etu.nv, "ID3") || strstr(etu.nv, "TDIA3")) {
        printf(" \n\n\n\t\t\t%s %s (%s) a obtenu le diplome d'ingenieur d'Etat.\n", etu.nom, etu.prenom, etu.nv);
    } else {
          changerCouleur(RED);
        printf("\n\n\n\t\t\t Niveau inconnu pour l'etudiant %s %s (%s).\n", etu.nom, etu.prenom, etu.nv);
         changerCouleur(WHITE);
        effacerEcranAvecAttenteEntree();
        changerCouleur(BLACK);
}}



// Fonction pour générer un relevé de notes
void genererReleve(Etudiant etu) {
    FILE *fichier = fopen("deliberation.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier deliberation.txt.\n");
        return;
    }

    char ligne[300];
    char nv[50], nom[50], prenom[50], cne[50];
    float note1, note2, note3;

    int trouve = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%s %s %s %s %f %f %f", nv, nom, prenom, cne, &note1, &note2, &note3);
        if (strcmp(cne, etu.cne) == 0) {
            trouve = 1;
            changerCouleur(BLUE);
            afficherDansCadre(" Releve de notes ");
            changerCouleur(MAGENTA);
            printf("Nom : ");
            changerCouleur(BLACK);
            printf("%s %s\n", nom, prenom);
            changerCouleur(MAGENTA);
            printf("Niveau ");
            changerCouleur(BLACK);
            printf(" %s\n", nv);
            changerCouleur(MAGENTA);
            printf("CNE ");
            changerCouleur(BLACK);
            printf(" %s\n", cne);

            effacerEcranAvecAttenteEntree();
            changerCouleur(BLUE);
            afficherDansCadre("Notes");
              changerCouleur(MAGENTA);
            printf("  - Matiere 1 : ");
            changerCouleur(BLACK);
            printf(" %.2f\n", note1);
              changerCouleur(MAGENTA);
            printf("  - Matiere 2 : ");
            changerCouleur(BLACK);
            printf(" %.2f\n", note2);
              changerCouleur(MAGENTA);
            printf("  - Matiere 3 : ");
            changerCouleur(BLACK);
            printf(" %.2f\n", note3);
              changerCouleur(MAGENTA);
            printf("Moyenne generale : ");
            changerCouleur(BLACK);
            printf(" %.2f\n", (note1 + note2 + note3) / 3);
            break;
        }
    }

    if (!trouve) {
            changerCouleur(RED);
        printf("\nAucun releve de notes trouve pour l'etudiant %s %s (%s).\n", etu.nom, etu.prenom, etu.cne);
    }

    fclose(fichier);
}
























#define MAX_NIVEAU 100
#define MAX_LIGNE 500
// Définition des couleurs
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"
#define BLACK   "\033[30m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>

#define MAX_NIVEAU 100
#define MAX_LIGNE 500
#define MAX_NIVEAU_STR 10 // Taille pour les noms de niveau (ex: cp1, cp2, GI1, etc.)
#define MAX_CNE_LENGTH 10





char _getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

#define MAX_LIGNE 100
#define LARGEUR_ECRAN 80
#define LARGEUR_CASE 50

void effacerEcranAvecAttenteEntree() {
    char ch;
    changerCouleur(WHITE);
    printf("\nAppuyez sur Entree pour passer...\n");
     changerCouleur(BLACK);

    // Attente que l'utilisateur appuie sur la touche Entrée
    do {
        ch = getchar();  // Lire un caractère
    } while (ch != '\n');  // Si ce n'est pas Entrée, continue à attendre

    // Effacer l'écran sous Windows
    system("cls");  // Pour Windows
    // Si tu utilises Linux, tu peux utiliser : system("clear");

}
// Fonction pour créer le fichier binaire contenant les administrateurs


// Fonction pour créer le fichier binaire contenant les administrateurs
void creerFichierAdmins(const char *nomFichier) {
    // Les administrateurs à enregistrer
    Admin admins[] = {
        {"sara alioui", "sarasara"},
        {"fatima aznadi", "fatimafatima"},
        {"fatima zahra akioul", "akioulakioul"}
    };

    // Ouvrir le fichier binaire en mode écriture
    FILE *fichier = fopen(nomFichier, "wb");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    // Écrire les administrateurs dans le fichier
    size_t nbAdmins = sizeof(admins) / sizeof(Admin);
    fwrite(admins, sizeof(Admin), nbAdmins, fichier);

    fclose(fichier);

}

int verifierAdmin(const char *nomFichier) {
    char nom[50], motDePasse[50];
    Admin admin;
    int estAdmin = 0;

    // Demander les informations d'identification à l'utilisateur

    changerCouleur(MAGENTA);
    printf("Nom           : ");
     changerCouleur(BLACK);
    scanf(" %[^\n]s", nom);
 changerCouleur(MAGENTA);
    printf("Mot de passe : ");
    int i = 0;
    char ch;
    while ((ch = getch()) != '\n' && ch != '\r') {
        if (ch == '\b' && i > 0) { // Gestion du backspace
            i--;
            printf("\b \b");
        } else if (ch != '\b') {
            motDePasse[i++] = ch;
            printf("*");
        }
    }
    motDePasse[i] = '\0';
    printf("\n");

    // Ouvrir le fichier binaire des administrateurs
    FILE *fichier = fopen(nomFichier, "rb");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    // Parcourir le fichier pour vérifier les informations
    while (fread(&admin, sizeof(Admin), 1, fichier)) {
        if (strcmp(nom, admin.nom) == 0 && strcmp(motDePasse, admin.motDePasse) == 0) {
            estAdmin = 1;
            break;
        }
    }

    fclose(fichier);

    if (estAdmin) {
        printf("Connexion reussie. Bienvenue, %s !\n", nom);
    } else {
        printf("echec de la connexion. Nom ou mot de passe incorrect.\n");
    }

    return estAdmin;
}

void bibliotheque() {
    int option;
    char nom[50], prenom[50], CNE[11];
    int jourp, moisp, jourr, moisr;
    char livre[100];
    int livreTrouve = 0;

    do {
        // Affichage du menu
          printf("\n");
          changerCouleur(YELLOW);
   printf("\n\t\t\t\t\t==============================\n");
   changerCouleur(BLUE);
    printf("\t\t\t\t\t   Menu Bibliotheque\n");
      changerCouleur(YELLOW);
    printf("\t\t\t\t\t==============================\n");
    printf("\n\n\n");

       changerCouleur(MAGENTA);
    printf("\t \t \t \t \t [1]: ");
    changerCouleur(BLACK);
    printf("Reserver un livre\n");

       changerCouleur(MAGENTA);
    printf("\t \t \t \t \t [2]: ");
 changerCouleur(BLACK);
    printf("Liste des livres\n");

    changerCouleur(MAGENTA);
    printf("\t \t \t \t \t [3]: ");
 changerCouleur(BLACK);
    printf("quitter\n");
changerCouleur(BLUE);
        printf("\n\n\t \t \t \t \t Choisir une option : ");
        scanf("%d", &option);
        changerCouleur(BLACK);
        effacerEcranAvecAttenteEntree();
    } while (option < 1 || option > 3);

    if (option == 1) {
        // Réservation d'un livre
         changerCouleur(MAGENTA);
            printf("Entrer votre nom et prenom                            :\n");
         changerCouleur(BLACK);
        scanf("%s %s", nom, prenom);
 changerCouleur(MAGENTA);
            printf("Entrer le CNE                                         :\n ");
         changerCouleur(BLACK);
  scanf("%s", CNE);
   changerCouleur(MAGENTA);


        changerCouleur(MAGENTA);
        printf("Entrer le nom du livre                                :\n");
        changerCouleur(BLACK);
        scanf(" %[^\n]s", livre);
            FILE *file = fopen("liste_livres.txt", "r");
        if (file == NULL) {
            printf("Erreur lors de l'ouverture de la liste des livres.\n");
            exit(1); // Quitter le programme en cas d'erreur
        }


        char ligne[100];
        while (fgets(ligne, sizeof(ligne), file)) {
            // Supprimer les caractères de nouvelle ligne
            ligne[strcspn(ligne, "\n")] = 0;
            if (strcmp(ligne, livre) == 0) {
                livreTrouve = 1;
                break;
            }
        }
        fclose(file);

    /*    if (!livreTrouve) {
            changerCouleur(RED);
            printf("\nLe livre \"%s\" n'est pas disponible. Veuillez entrer un autre livre.\n", livre);
            changerCouleur(BLACK);
        } else {
            changerCouleur(GREEN);
            printf("\nLe livre \"%s\" est disponible.\n", livre);
            changerCouleur(BLACK);
        }

    } while (!livreTrouve);*/
do{
   changerCouleur(MAGENTA);
            printf("Entrer la date pour prendre le livre (format JJ/MM)   :\n ");
             changerCouleur(BLACK);
            scanf("%d/%d", &jourp, &moisp);
   changerCouleur(MAGENTA);
            printf("Entrer la date pour retourner le livre (format JJ/MM) :\n ");
             changerCouleur(BLACK);
            scanf("%d/%d", &jourr, &moisr);

            // Vérification des dates (simple)
           } while((moisp < 1 && moisp > 12) && (moisr < 1 && moisr > 12) &&
                (jourp < 1 && jourp > 31) && (jourr < 1 && jourr > 31)) ;

effacerEcranAvecAttenteEntree();
changerCouleur(GREEN);
       printf("\n");
    printf("\t\t\t\t\t\t**                          **\n");
    printf("\t\t\t\t\t\t*                            *\n");
    printf("\t\t\t\t\t\t*  Reservation effectuee     *\n");
    printf("\t\t\t\t\t\t*      avec succes !         *\n");
    printf("\t\t\t\t\t\t*                            *\n");
    printf("\t\t\t\t\t\t**                          ** \n");
    printf("\n");
          changerCouleur(BLACK);
        /*
        printf("Nom : %s %s\n", nom, prenom);
        printf("CNE : %s\n", CNE);
        printf("Date de prise : %02d/%02d\n", jourp, moisp);
        printf("Date de retour : %02d/%02d\n", jourr, moisr);
        printf("le nom de livre: %s",livre);*/

        FILE *e = fopen("reservelivre.txt", "a"); // Mode ajout
   if (e == NULL) {
            printf("Erreur lors de l'ouverture du fichier.\n");
            exit(1);
        }

        fprintf(e, "Nom: %s %s, CNE: %s, Livre: %s, Date prise: %02d/%02d, Date retour: %02d/%02d\n",
                nom, prenom, CNE, livre, jourp, moisp, jourr, moisr);

        fclose(e); // Fermer le fichier


    } else if (option == 2) {
        // Liste des livres
          FILE *file;
    char ch;

    // Ouvrir le fichier en mode lecture
    file = fopen("liste_livres.txt", "r");

    // Vérifier si le fichier s'est ouvert correctement
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1); // Sortir du programme en cas d'erreur
    }

    // Lire et afficher chaque caractère jusqu'à la fin du fichier
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch); // Afficher chaque caractère
    }

    // Fermer le fichier après la lecture
    fclose(file);

}}
void afficherDeliberation() {
    char niv[50];            // Niveau à rechercher
    etudiant etu;
    char ligne[300];         // Tampon pour lire les lignes du fichier
    FILE *p;
    int continuer = 1; // Variable pour contrôler la répétition

    while (continuer) {
        p = fopen("deliberation.txt", "r"); // Ouvrir le fichier en mode lecture

        if (p == NULL) {
            printf("Erreur d'ouverture du fichier.\n");
            exit(1);
        }

        // Demander à l'utilisateur de saisir le niveau
        changerCouleur(BLUE);
        printf("\t\t\t\tDonner le niveau que tu veux afficher sa delieration : ");
        scanf(" %[^\n]s", niv);
         printf("\n\n\n");
         effacerEcranAvecAttenteEntree();

        // Afficher l'en-tête du tableau en magenta
        changerCouleur(MAGENTA); // Couleur magenta pour les titres
        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("Nom               | Prenom           | CNE               | Note1  | Note2  | Note3  | Moyenne  | Resultat\n");
        printf("-------------------------------------------------------------------------------------------------------------\n");
        changerCouleur(BLACK); // Revenir à la couleur noire pour les données

        // Lire chaque ligne du fichier
        while (fgets(ligne, sizeof(ligne), p) != NULL) {
            // Lire et analyser chaque ligne avec sscanf
            // Format de lecture : niveau, nom, prénom, cne, note1, note2, note3
            int nb_scanned = sscanf(ligne, "%s %s %s %s %d %d %d", etu.nv, etu.nom, etu.prenom, etu.cne,
                                     &etu.note1, &etu.note2, &etu.note3);

            // Si on a bien récupéré les 7 informations, on continue
            if (nb_scanned == 7) {
                // Calculer la moyenne
                etu.moyenne = (etu.note1 + etu.note2 + etu.note3) / 3.0;

                // Comparer le niveau de l'étudiant avec celui demandé
                if (strcmp(etu.nv, niv) == 0) {
                    // Afficher les informations de l'étudiant sous forme de tableau (en noir)
                    printf("%-18s| %-17s| %-17s| %-8d| %-8d| %-8d| %-8.2f| ", etu.nom, etu.prenom, etu.cne,
                           etu.note1, etu.note2, etu.note3, etu.moyenne);

                    // Afficher le résultat en vert (Admis) ou rouge (Échoué)
                    if (etu.moyenne >= 10) {
                        changerCouleur(GREEN); // Couleur verte pour "Admis"
                        printf("Admis\n");
                    } else {
                        changerCouleur(RED); // Couleur rouge pour "Échoué"
                        printf("Echoue\n");
                    }
                    changerCouleur(BLACK); // Revenir à la couleur noire après avoir affiché le résultat
                }
            }
        }

        fclose(p);  // Fermer le fichier après la lecture


        // Demander à l'utilisateur s'il souhaite afficher la délibération d'un autre niveau
        char reponse;

         changerCouleur(BLUE);
         effacerEcranAvecAttenteEntree();

        printf("\n\n\t\t\tVoulez-vous afficher la deliberation d'un autre niveau ? (o/n) : ");
        scanf(" %c", &reponse);
         effacerEcranAvecAttenteEntree();
         changerCouleur(BLACK);

        if (reponse != 'o' && reponse != 'O') {
            continuer = 0; // Si la réponse n'est pas "o", on arrête la boucle
        }
    }
}

void effacerEcran() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void changerCouleur(const char *couleur) {
    printf("%s", couleur);
}

void afficherTexteCentreeDansCadre(const char *texte) {
    int longueur = strlen(texte);
    int espace = (LARGEUR_ECRAN - longueur) / 2;

    printf("\n   \t\t\t= ======================================================================= =\n");
    printf(" ");
    for (int i = 0; i < espace; i++) printf(" ");
    printf("%s", texte);
    for (int i = 0; i < espace; i++) printf(" ");
    if (longueur % 2 != 0) printf(" ");
    printf(" ");
    printf("\n");
    printf("    \t\t\t= ======================================================================= =\n");
}

void afficherOptionCase(const char *texte, const char *couleur) {
    int longueur = strlen(texte);
    int espace = (LARGEUR_CASE - longueur) / 2;

    changerCouleur(couleur);

    printf("\n\t\t\t\t         ==================================\n");
    printf("    ");
    for (int i = 0; i < espace; i++) printf(" ");
    printf("%s", texte);
    for (int i = 0; i < espace; i++) printf(" ");
    if (longueur % 2 != 0) printf(" ");
    printf("    ");
    printf("\n");
    printf("    \t\t\t\t\t ==================================\n");

    changerCouleur(BLACK);
}
int verifiermdp() {
    char cnee[100];
    char mdp[100];

    effacerEcran();
    changerCouleur(MAGENTA);

    // Demander le CNE
    printf("                    Entrez le CNE : ");
     changerCouleur(WHITE);

    scanf("%99s", cnee); // Limiter à 99 caractères pour éviter les débordements

    // Consommer le retour à la ligne restant dans le buffer
    getchar();
changerCouleur(MAGENTA);
    // Demander le mot de passe
    printf("                    Entrez le mot de passe : ");
     changerCouleur(WHITE);

    scanf("%99s", mdp); // Limiter à 99 caractères pour éviter les débordements

    // Ouvrir le fichier contenant les étudiants
    FILE *e = fopen("eleve_ensah.txt", "r");
    if (e == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(0);
    }

    char ligne[MAX_LIGNE];
    etudiant etu;
    int trouve = 0;

    // Lire chaque ligne du fichier
    while (fgets(ligne, sizeof(ligne), e) != NULL) {
        // Extraire le CNE et le mot de passe depuis la ligne
          sscanf(ligne, "%s %s %s %d %d %d %s %d %s %s %s",
               etu.nv, etu.nom, etu.prenom, &etu.date.jour, &etu.date.mois, &etu.date.annee,
               etu.ville, &etu.num_tele, etu.mot_de_passe, etu.gmail, etu.cne);

        // Supprimer les éventuels caractères de nouvelle ligne ou espaces
        etu.cne[strcspn(etu.cne, "\n")] = '\0';
        etu.mot_de_passe[strcspn(etu.mot_de_passe, "\n")] = '\0';

        // Vérifier si le CNE et le mot de passe correspondent
        if (strcmp(etu.cne, cnee) == 0 && strcmp(etu.mot_de_passe, mdp) == 0) {
            printf("Vous avez acces.\n");
            changerCouleur(GREEN);
            printf("Acces autorise.\n");
            trouve = 1;
            break;
        }
    }

    // Si les informations n'ont pas été trouvées
    if (!trouve) {
        changerCouleur(RED);
        printf("Mot de passe ou CNE incorrect.\n");
    }

    fclose(e);
    return trouve;
} bool verifierEmail(const char *email) {
    const char *at = strchr(email, '@'); // Chercher '@'
    if (at == NULL) return false;       // Pas de '@'

    const char *dot = strchr(at, '.');  // Chercher '.' après '@'
    if (dot == NULL) return false;      // Pas de '.'

    // Vérifier que '@' n'est ni au début ni à la fin
    if (at == email || *(at + 1) == '\0') return false;

    // Vérifier que '.' n'est pas immédiatement après '@'
    if (dot == at + 1) return false;

    // Vérifier que '.' n'est pas à la fin
    if (*(dot + 1) == '\0') return false;

    return true;

}
int afficherMenuAvecNavigation(char *options[], int nombreOptions) {
    int selection = 0;
    char touche = '\0';

    while (1) {
        effacerEcran();

        for (int i = 0; i < nombreOptions; i++) {
            if (i == selection) {
                afficherOptionCase(options[i], BLUE);
            } else {
                afficherOptionCase(options[i], WHITE);
            }
        }

 touche = _getch();

if (touche == 27) { // Échap
    return -1;
} else if (touche == 72) { // Flèche haut
    // Action spécifique pour "haut"
    if (selection > 0) {
        selection--;
    }
} else if (touche == 80) { // Flèche bas
    // Action spécifique pour "bas"
    if (selection < nombreOptions - 1) {
        selection++;
    }
} else if (touche == 75) { // Flèche gauche
    // Action spécifique pour "gauche"
    selection = (selection == 0) ? nombreOptions - 1 : selection - 1;
} else if (touche == 77) { // Flèche droite
    // Action spécifique pour "droite"
    selection = (selection == nombreOptions - 1) ? 0 : selection + 1;
} else if (touche == 13) { // Entrée
    return selection;
}
    }
}
void afficherStages() {
    effacerEcran();
    changerCouleur(BLUE);
    afficherDansCadre("Liste des Stages");


    FILE *fichier = fopen("stages.txt", "r");
    if (fichier == NULL) {
        printf("\n\tErreur : Impossible d'ouvrir le fichier des stages.\n");
        return;
    }

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichier)) {
            changerCouleur(BLACK);
        printf("%s", ligne);
    }

    fclose(fichier);

    printf("\n\tAppuyez sur une touche pour revenir au menu...");
    _getch();
}
#define MAX_NIVEAU 100
#define MAX_LIGNE 500
#define MAX_NIVEAU_STR 10 // Taille pour les noms de niveau (ex: cp1, cp2, GI1, etc.)
#define MAX_CNE_LENGTH 10
void afficher_mention(float moyenne) {
    if (moyenne >= 16) {
            changerCouleur(GREEN);
        printf("Mention: Tres Bien\n");
    } else if (moyenne >= 14) {
        changerCouleur(GREEN);
        printf("Mention: Bien\n");
    } else if (moyenne >= 12) {
        changerCouleur(YELLOW);
        printf("Mention: Assez Bien\n");
    } else if (moyenne >= 10) {
        changerCouleur(YELLOW);
        printf("Mention: Passable\n");
    } else {
        changerCouleur(RED);
        printf("Mention: Echec\n");
    }
}


void afficher_notes_et_moyenne() {
    char cne_entre[MAX_CNE_LENGTH];
    int found = 0;
    FILE *file = fopen("deliberation.txt", "r");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Demander le CNE à l'utilisateur
    changerCouleur(MAGENTA);
    printf("Entrez votre CNE : ");
    changerCouleur(BLACK);
    scanf("%s", cne_entre);
    effacerEcranAvecAttenteEntree();

    etudiant etu;
    // Lire les données des étudiants et chercher celui correspondant au CNE
    while (fscanf(file, "%s %s %s %s %d %d %d", etu.nv, etu.nom, etu.prenom, etu.cne, &etu.note1, &etu.note2, &etu.note3) != EOF) {
        if (strcmp(etu.cne, cne_entre) == 0) {
            found = 1;
            // Calcul de la moyenne des notes
            float moyenne = (etu.note1 + etu.note2 + etu.note3) / 3.0;

            // Affichage des notes et de la moyenne
            changerCouleur(MAGENTA);
            printf("Nom    :" );
            changerCouleur(BLACK);
            printf("%s\n", etu.nom);
            changerCouleur(MAGENTA);
            printf("Prenom :" );
            changerCouleur(BLACK);
            printf("%s\n", etu.prenom);
            changerCouleur(BLUE);
            afficherDansCadre("LES NOTES :");
            changerCouleur(MAGENTA);
            printf("  Note 1 : ");
            changerCouleur(BLACK);
            printf(" %d\n", etu.note1);
            changerCouleur(MAGENTA);
            printf("  Note 2 : ");
            changerCouleur(BLACK);
            printf(" %d\n", etu.note2);
            changerCouleur(MAGENTA);
            printf("  Note 3 : ");
            changerCouleur(BLACK);
            printf(" %d\n", etu.note3);
            changerCouleur(BLUE);
            printf("la moyenne du semestre :");
            changerCouleur(BLACK);
            printf(" %.2f          ", moyenne);
changerCouleur(BLUE);
            // Afficher la mention
            afficher_mention(moyenne);
            effacerEcranAvecAttenteEntree();
            break;
        }
    }

    if (!found) {
            changerCouleur(RED);
        printf("CNE non trouve.\n");
    effacerEcranAvecAttenteEntree();
    }

    fclose(file);
    changerCouleur(BLACK);
}





void demanderCNE(char *cneRecherche) {
    changerCouleur(BLUE);
    printf("\n\t\t\t\t\t=== Generation de documents pour un etudiant ===\n");
        changerCouleur(BLACK);
changerCouleur(MAGENTA);
    printf("\n\n\nEntrez le CNE de l'etudiant : ");
            changerCouleur(BLACK);

    fgets(cneRecherche, 50, stdin);
    cneRecherche[strcspn(cneRecherche, "\n")] = '\0'; // Supprimer le '\n'
}

void affichefiliere(){
char c;
FILE *n=fopen("filiere.txt","r");
if(n==NULL){
    printf("error");
    exit(1);
}

printf("\n  \n \n");
changerCouleur(BLUE);
afficherDansCadre("les filieres qui existes dans  l ecole nationalle des sciences appliquees d alhoceima :");
while((c=fgetc(n))!=EOF){
        changerCouleur(BLACK);
    printf("%c",c);

}
fclose(n);
effacerEcranAvecAttenteEntree();
}



void Menuinfo_sur_etudiant(){

while (1) {
char cne[20];
Etudiant etu;
char cneRecherche[20];
        printf("\n\n");

        char *options[] = {
            "\t\t\t\t stage               ",
            "\t\t\t\t profil               ",
            "\t\t\t\t afficher notification",
            "\t\t\t\t bibliotheque         ",
            "\t\t\t\t demande attestation ",
             "\t\t\t\t affiher delibiration ",
            "\t\t\t\t retour"



        }; int choix = afficherMenuAvecNavigation(options, 7);

        switch (choix) {
            case 0:
                effacerEcran();
                afficherStages("stages.txt");


                printf("\nAppuyez sur une touche pour continuer...");
                _getch();
                break;
                case 1:

               afficherUnEtudiant();
               effacerEcranAvecAttenteEntree();
                break;
                case 2:
                    effacerEcranAvecAttenteEntree();
               afficherNotification();
                _getch();
                break;
                            case 3:
                effacerEcran();
            bibliotheque();
                printf("\nAppuyez sur une touche pour continuer...");
                _getch();
                break;
                            case 4:
                effacerEcran();
                  // Étape 3 : Afficher le menu et générer le document
                changerCouleur(BLUE);
                afficherDansCadre("Generation de documents pour un etudiant");
                changerCouleur(MAGENTA);
                printf("Entrez le CNE de l'etudiant : ");
                changerCouleur(BLACK);
                scanf("%49s", cneRecherche);
                effacerEcranAvecAttenteEntree();  // Lire jusqu'à 49 caractères maximum

// Consommer le '\n' restant dans le tampon après scanf
               int c;
              while ((c = getchar()) != '\n' && c != EOF) {
    // Rien à faire, on consomme juste les caractères
              } // Supprimer le '\n'

               if (chercherEtudiant(cneRecherche, &etu)) {
               int choix;
               changerCouleur(GREEN);
            printf("\n\n\t\t\t\t\t\t\tEtudiant trouvee :\n ");
            changerCouleur(WHITE);
            effacerEcranAvecAttenteEntree();
           changerCouleur(BLUE);
             printf("\t\t\t\t\t\t\Quel document voulez-vous generer ?\n\n\n");
            changerCouleur(MAGENTA);
    printf("\t\t\t[1]  Attestation d'inscription\n");
    printf("\t\t\t[2]  Releve de notes\n");
    printf("\t\t\t[3]  Diplome\n");
    changerCouleur(BLACK);
    printf("\nEntrez votre choix : ");
    changerCouleur(MAGENTA);
    scanf("%d", &choix);


        switch (choix) {
            case 1:
                genererAttestation(etu);
                break;
            case 2:
                genererReleve(etu);
                break;
            case 3:
                genererDiplome(etu);
                break;
            default:
                printf("Choix invalide.\n");
  }
    } else {
        printf("Erreur : Aucun étudiant trouvé avec le CNE : %s\n", cneRecherche);
    }






















                _getch();
                break;
               case 5:
                effacerEcran();
                afficherDeliberation();
                printf("\nAppuyez sur une touche pour continuer...");
                _getch();
                break;
            case 6:
                return; // Quitter le menu étudiant

            default:
                break;

        }

        }
}
//******************* khdama wfiha lwinat *****************************************************************

void modifierUnEtudiant() {
    effacerEcran();
    int v, opt;
    etudiant etu;
    char cne_cherche[20]; // Utilisation du CNE pour rechercher l'étudiant
    int trouve = 0;
    char choix;

    do {
        FILE *f = fopen("eleve_ensah.txt", "r");
        FILE *c = fopen("temp.txt", "w");

        if (f == NULL || c == NULL) {
            changerCouleur(RED);
            afficherTitreEncadre("ERREUR D'OUVERTURE DES FICHIERS");
            changerCouleur(BLACK);
            printf("\n\t\t\tImpossible d'ouvrir les fichiers. Veuillez réessayer.\n");
            exit(1);
        }

        // Demander le CNE de l'étudiant à modifier
        changerCouleur(BLUE);
        afficherTitreEncadre("MODIFIER UN ETUDIANT");
        changerCouleur(MAGENTA);
        printf("\n\t\t\tEntrez le CNE de l'étudiant à modifier : ");
        changerCouleur(BLACK);
        scanf(" %s", cne_cherche);

        char ligne[300];

        // Parcourir le fichier pour trouver l'étudiant
        while (fgets(ligne, sizeof(ligne), f) != NULL) {
            sscanf(ligne, "%s %s %s %d %d %d %s %s %s %s %s %s", etu.nv, etu.nom, etu.prenom,
                   &etu.date.jour, &etu.date.mois, &etu.date.annee, etu.ville,
                   etu.num_tele, etu.mot_de_passe, etu.gmail, etu.cne, etu.sex);

            if (strcmp(etu.cne, cne_cherche) == 0) { // Recherche par CNE
                trouve = 1;

                // Afficher les informations de l'étudiant dans un cadre
                effacerEcran();
                changerCouleur(BLUE);
                afficherTitreEncadre("INFORMATIONS DE L'ETUDIANT");
                changerCouleur(MAGENTA);
                printf("\n\t\t\tNiveau              : ");
                changerCouleur(BLACK);
                printf("%s\n", etu.nv);
                changerCouleur(MAGENTA);
                printf("\t\t\tNom                 : ");
                changerCouleur(BLACK);
                printf("%s\n", etu.nom);
                changerCouleur(MAGENTA);
                printf("\t\t\tPrénom              : ");
                changerCouleur(BLACK);
                printf("%s\n", etu.prenom);
                changerCouleur(MAGENTA);
                printf("\t\t\tDate de naissance   : ");
                changerCouleur(BLACK);
                printf("%02d/%02d/%04d\n", etu.date.jour, etu.date.mois, etu.date.annee);
                changerCouleur(MAGENTA);
                printf("\t\t\tVille               : ");
                changerCouleur(BLACK);
                printf("%s\n", etu.ville);
                changerCouleur(MAGENTA);
                printf("\t\t\tNuméro de téléphone : ");
                changerCouleur(BLACK);
                printf("%s\n", etu.num_tele);
                changerCouleur(MAGENTA);
                printf("\t\t\tMot de passe        : ");
                changerCouleur(BLACK);
                printf("%s\n", etu.mot_de_passe);
                changerCouleur(MAGENTA);
                printf("\t\t\tGmail               : ");
                changerCouleur(BLACK);
                printf("%s\n", etu.gmail);
                changerCouleur(MAGENTA);
                printf("\t\t\tCNE                 : ");
                changerCouleur(BLACK);
                printf("%s\n", etu.cne);
                changerCouleur(MAGENTA);
                printf("\t\t\tSexe                : ");
                changerCouleur(BLACK);
                printf("%s\n", etu.sex);

                // Ajouter une pause pour permettre à l'utilisateur de lire les informations
                changerCouleur(MAGENTA);
                printf("\n\t\t\tAppuyez sur Entrée pour continuer...");
                changerCouleur(BLACK);
                getchar(); // Attendre l'appui sur Entrée
                getchar(); // Consommer le '\n' laissé par scanf

                // Demander ce qu'il veut modifier
                effacerEcran();
                changerCouleur(BLUE);
                afficherTitreEncadre("MODIFIER UN CHAMP");
                changerCouleur(MAGENTA);
                printf("\n\t\t\tQue voulez-vous modifier ? \n");
                printf("\t\t\t[1] : Nom\n");
                printf("\t\t\t[2] : Prénom\n");
                printf("\t\t\t[3] : Date de naissance\n");
                printf("\t\t\t[4] : Ville\n");
                printf("\t\t\t[5] : Gmail\n");
                printf("\t\t\t[6] : CNE\n");
                printf("\t\t\t[7] : Niveau\n");
                printf("\t\t\t[8] : Numéro de téléphone\n");
                printf("\t\t\t[9] : Sexe\n");
                changerCouleur(BLACK);
                printf("\n\t\t\tVotre choix : ");
                scanf("%d", &opt);

                // Modification selon le choix
                effacerEcran();
                changerCouleur(BLUE);
                afficherTitreEncadre("MODIFICATION");
                switch (opt) {
                    case 1:
                        changerCouleur(MAGENTA);
                        printf("\n\t\t\tEntrez le nouveau nom : ");
                        changerCouleur(BLACK);
                        scanf(" %[^\n]s", etu.nom);
                        break;
                    case 2:
                        changerCouleur(MAGENTA);
                        printf("\n\t\t\tEntrez le nouveau prénom : ");
                        changerCouleur(BLACK);
                        scanf(" %[^\n]s", etu.prenom);
                        break;
                    case 3:
                        changerCouleur(MAGENTA);
                        printf("\n\t\t\tEntrez la nouvelle date de naissance (JJ MM AAAA) : ");
                        changerCouleur(BLACK);
                        scanf("%d %d %d", &etu.date.jour, &etu.date.mois, &etu.date.annee);
                        break;
                    case 4:
                        changerCouleur(MAGENTA);
                        printf("\n\t\t\tEntrez la nouvelle ville : ");
                        changerCouleur(BLACK);
                        scanf(" %[^\n]s", etu.ville);
                        break;
                    case 5:
                        do {
                            changerCouleur(MAGENTA);
                            printf("\n\t\t\tEntrez le nouveau Gmail : ");
                            changerCouleur(BLACK);
                            scanf(" %[^\n]s", etu.gmail);
                            v = verifierEmail(etu.gmail) ? 0 : 1;
                            if (v) {
                                changerCouleur(RED);
                                printf("\n\t\t\tAdresse email invalide. Veuillez réessayer.\n");
                                changerCouleur(BLACK);
                            }
                        } while (v == 1);
                        break;
                    case 6:
                        changerCouleur(MAGENTA);
                        printf("\n\t\t\tEntrez le nouveau CNE : ");
                        changerCouleur(BLACK);
                        scanf(" %[^\n]s", etu.cne);
                        break;
                    case 7:
                        changerCouleur(MAGENTA);
                        printf("\n\t\t\tEntrez le nouveau niveau : ");
                        changerCouleur(BLACK);
                        scanf(" %[^\n]s", etu.nv);
                        break;
                    case 8:
                        changerCouleur(MAGENTA);
                        printf("\n\t\t\tEntrez le nouveau numéro de téléphone : ");
                        changerCouleur(BLACK);
                        scanf(" %[^\n]s", etu.num_tele);
                        break;
                    case 9:
                        do {
                            changerCouleur(MAGENTA);
                            printf("\n\t\t\tEntrez le nouveau sexe (M/F) : ");
                            changerCouleur(BLACK);
                            scanf(" %s", etu.sex);
                            if (strcmp(etu.sex, "M") != 0 && strcmp(etu.sex, "F") != 0) {
                                changerCouleur(RED);
                                printf("\n\t\t\tSexe invalide. Veuillez entrer 'M' ou 'F'.\n");
                                changerCouleur(BLACK);
                            }
                        } while (strcmp(etu.sex, "M") != 0 && strcmp(etu.sex, "F") != 0);
                        break;
                    default:
                        changerCouleur(RED);
                        printf("\n\t\t\tChoix invalide. Veuillez réessayer.\n");
                        changerCouleur(BLACK);
                        break;
                }

                // Écrire les modifications dans le fichier temporaire
                fprintf(c, "%s %s %s %d %d %d %s %s %s %s %s %s\n", etu.nv, etu.nom, etu.prenom,
                        etu.date.jour, etu.date.mois, etu.date.annee, etu.ville,
                        etu.num_tele, etu.mot_de_passe, etu.gmail, etu.cne, etu.sex);

                // Appliquer les modifications dans le fichier de niveau
                char fichier_niveau[20];
                sprintf(fichier_niveau, "%s.txt", etu.nv);
                FILE *niveau_file = fopen(fichier_niveau, "r");
                FILE *temp_niveau = fopen("temp_niveau.txt", "w");

                if (niveau_file != NULL && temp_niveau != NULL) {
                    char niveau_ligne[300];
                    etudiant niveau_etu;

                    while (fgets(niveau_ligne, sizeof(niveau_ligne), niveau_file) != NULL) {
                        sscanf(niveau_ligne, "%s %s %s %d %d %d %s %s %s %s %s %s", niveau_etu.nv, niveau_etu.nom, niveau_etu.prenom,
                               &niveau_etu.date.jour, &niveau_etu.date.mois, &niveau_etu.date.annee, niveau_etu.ville,
                               niveau_etu.num_tele, niveau_etu.mot_de_passe, niveau_etu.gmail, niveau_etu.cne, niveau_etu.sex);

                        if (strcmp(niveau_etu.cne, cne_cherche) == 0) {
                            fprintf(temp_niveau, "%s %s %s %d %d %d %s %s %s %s %s %s\n", etu.nv, etu.nom, etu.prenom,
                                    etu.date.jour, etu.date.mois, etu.date.annee, etu.ville,
                                    etu.num_tele, etu.mot_de_passe, etu.gmail, etu.cne, etu.sex);
                        } else {
                            fputs(niveau_ligne, temp_niveau);
                        }
                    }

                    fclose(niveau_file);
                    fclose(temp_niveau);

                    remove(fichier_niveau);
                    rename("temp_niveau.txt", fichier_niveau);
                }
            } else {
                fprintf(c, "%s %s %s %d %d %d %s %s %s %s %s %s\n", etu.nv, etu.nom, etu.prenom,
                        etu.date.jour, etu.date.mois, etu.date.annee, etu.ville,
                        etu.num_tele, etu.mot_de_passe, etu.gmail, etu.cne, etu.sex);
            }
        }

        fclose(c);
        fclose(f);

        if (trouve == 1) {
            remove("eleve_ensah.txt");
            rename("temp.txt", "eleve_ensah.txt");
            changerCouleur(GREEN);
            afficherTitreEncadre("SUCCES");
            printf("\n\t\t\tL'étudiant a été modifié avec succès.\n");
            changerCouleur(BLACK);
        } else {
            remove("temp.txt");
            changerCouleur(RED);
            afficherTitreEncadre("ERREUR");
            printf("\n\t\t\tAucun étudiant trouvé avec ce CNE.\n");
            changerCouleur(BLACK);
        }

        // Demander si l'utilisateur veut modifier un autre étudiant
        changerCouleur(MAGENTA);
        printf("\n\t\t\tVoulez-vous modifier un autre étudiant ? (o/n) : ");
        changerCouleur(BLACK);
        scanf(" %c", &choix);
    } while (choix == 'o' || choix == 'O');

    changerCouleur(BLUE);
    afficherTitreEncadre("FIN DE LA MODIFICATION");
    changerCouleur(BLACK);
    printf("\n\t\t\tRetour au menu principal.\n");
}
void infosurensah(){
    changerCouleur(BLUE);
printf("L'Ecole Nationale des Sciences Appliquees Al-Hoceima dispense des formations de deux annees preparatoires et trois annees de specialites dans les domaines suivants :\n");
changerCouleur(BLACK);
printf("Genie Informatique ;\nGenie Civil ;\nGenie de l'eau et de l'Environnement ;\nGenie energetique et energies renouvelables.\nEtalee sur une superficie de 5.700 m2, l'ENSA d'Al Hoceima est de nature a doter cette zone geographique d'un pole scientifique a travers la creation d'un noyau universitaire, appuyer le secteur de l'enseignement superieur technique et promouvoir la formation professionnelle.\n\n");
changerCouleur(BLUE);
printf("D'une capacite d'accueil de plus de 500 etudiants, l'ENSA comprend :\n");
changerCouleur(BLACK);
printf("Deux amphitheatres ;\n des salles de cours et des travaux pratiques ;\n des laboratoires ;\n une bibliotheque ;\ndes terrains de sports et des vestiaires ;\nune cafeteria ;\nune residence universitaire.\nL'Ecole Nationale des Sciences Appliquees d'Al Hoceima comprend une residence universitaire d'une capacite d'accueil de 500 lits pour le logement des etudiants et etudiantes.\n");
effacerEcranAvecAttenteEntree();
}
void lesetudeaensah(){

changerCouleur(BLUE);
afficherDansCadre("Les etudes a ENSAH:");
changerCouleur(BLACK);
printf("Les etudes a l'ENSA d'Al-Hoceima durent cinq ans, reparties entre un cycle preparatoire de deux ans et un cycle ingenieur d'etat d'une duree de trois ans.\nLa formation est dispensee sous forme d'enseignements theoriques et activites pratiques organises en modules et en semestres.\nUn module d'enseignement est constitue des enseignements theoriques et/ou pratiques portant sur une ou plusieurs matieres ayant des objectifs, des contenus et une didactique qui leur sont propres.\nLe controle des connaissances est de type continu. Il a lieu sous forme de tests, de travaux pratiques ou diriges, de devoirs, de stages et d'un ou de plusieurs examens ou de tout autre moyen d'evaluation pedagogique.\nLe redoublement n'est autorise qu'une seule annee dans chaque cycle.\n\n");
changerCouleur(MAGENTA);
printf("L'eleve-ingenieur de l'ENSAH recoit une formation lui permettant de :\n");
changerCouleur(BLACK);
printf("acquerir des competences scientifiques, techniques et professionnelles ;\netre qualifie pour s'adapter aux exigences du developpement socio-economique regional et national ;\nrenforcer le savoir-faire methodologique ;\ns'engager et etre capable d'assurer des responsabilites ;\nconnaitre le metier de l'ingenieur et s'adapter a un milieu professionnel evolutif ;\netre apte au travail en groupe et a la communication ;\naiguiser le sens de la creativite et de l'innovation.\nPour plus de details, veuillez se referer aux Cahier des Normes Pedagogiques Nationale\n");

effacerEcranAvecAttenteEntree();
}

#include <stdio.h>
#include <string.h>

// Définition des couleurs
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"
#define BLACK   "\033[30m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"




// Fonction pour attendre une touche (compatible Windows et Linux/macOS)
void attendreTouche() {
#ifdef _WIN32
    _getch(); // Pour Windows
#else
    // Pour Linux/macOS
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}



#include <stdio.h>
#include <string.h>

// Définition des couleurs pour un fond blanc
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"
#define BLACK   "\033[30m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"


// Fonction pour afficher un cadre
void afficherCadre(const char *message) {
    int longueur = strlen(message) + 4; // +4 pour les bordures
    printf("\n\t+");
    for (int i = 0; i < longueur; i++) printf("-");
    printf("+\n");
    printf("\t|  %s  |\n", message);
    printf("\t+");
    for (int i = 0; i < longueur; i++) printf("-");
    printf("+\n");
}


// Définition des couleurs pour le texte
#define RESET   "\033[0m"  // Réinitialiser les couleurs
#define BLUE    "\033[34m" // Texte bleu
#define GREEN   "\033[32m" // Texte vert
#define RED     "\033[31m" // Texte rouge
#define MAGENTA "\033[35m" // Texte magenta
#define CYAN    "\033[36m" // Texte cyan
#define YELLOW  "\033[33m" // Texte jaune




void Etudiantselectioner() {
    FILE *fichier = fopen("eleveselectionne.txt", "r"); // Ouvrir le fichier en mode lecture
    if (fichier == NULL) { // Vérifier si le fichier existe
        printf("%sErreur : impossible d'ouvrir le fichier \"eleveselectionne.txt\".%s\n", RED, RESET);
        return;
    }

    effacerEcran(); // Effacer l'écran
    printf("%s", BLUE);
    afficherCadre("ELEVES SELECTIONNES");
    printf("%s", RESET);

    // Afficher l'en-tête du tableau
    printf("%s", MAGENTA);
    printf("\n\t%-10s %-15s %-15s %-15s %-15s %-15s %-15s %-15s %-15s\n",
           "Niveau", "Nom", "Prénom", "Date de Naiss.", "Ville", "Téléphone", "Mot de Passe", "Email", "CNE");
    printf("\t-----------------------------------------------------------------------------------------------------------------\n");
    printf("%s", RESET);

    char ligne[256]; // Buffer pour stocker une ligne du fichier

    // Lire le fichier ligne par ligne et afficher chaque ligne dans le tableau
    while (fgets(ligne, sizeof(ligne), fichier)) {
        char niveau[10], nom[20], prenom[20], ville[20], mot_de_passe[20], gmail[50], cne[20];
        int jour, mois, annee;
        long num_tele;

        // Extraire les informations de la ligne
        sscanf(ligne, "%s %s %s %d %d %d %s %ld %s %s %s",
               niveau, nom, prenom, &jour, &mois, &annee, ville, &num_tele, mot_de_passe, gmail, cne);

        // Afficher les informations dans le tableau
        printf("\t%-10s %-15s %-15s %02d/%02d/%04d   %-15s %-15ld %-15s %-15s %-15s\n",
               niveau, nom, prenom, jour, mois, annee, ville, num_tele, mot_de_passe, gmail, cne);
    }

    fclose(fichier); // Fermer le fichier

    // Ajouter une pause avant de retourner au menu principal
    printf("\n%s\tAppuyez sur Entrée pour retourner au menu principal...%s", MAGENTA, RESET);
    getchar(); // Attendre l'appui sur Entrée
}


void envoyerNotification(Etudiant etu) {
    FILE *fichier = fopen("notifications.txt", "a");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier notifications.txt.\n");
        return;
    }

    char message[200];
    sprintf(message, "Votre nombre d'absences est de %d. Merci de justifier ou d'eviter les absences futures.", etu.absences);

    fprintf(fichier, "%s %s %s %s\n", etu.cne, etu.nom, etu.prenom, message);
    fclose(fichier);
changerCouleur(GREEN);
    printf("\n\n\n\t\t\t\tNotification envoyee à %s %s (%s).\n", etu.nom, etu.prenom, etu.cne);
    changerCouleur(BLACK);
    effacerEcranAvecAttenteEntree();
}
void Menuinfo_sur_ensah(){
while (1) {
        effacerEcran();
        printf("\n\n");


        char *options[] = {
            "\t\t\t\t  staf administration              ",
            "\t\t\t\t  des informations sur ensah       ",
             "\t\t\t\t  Les etudes a L ENSAH              ",
            "\t\t\t\t  retour"



        }; int choix = afficherMenuAvecNavigation(options, 4);

        switch (choix) {
            case 0:
                effacerEcran();
              staffadministration();
                printf("\nAppuyez sur une touche pour continuer...");
                _getch();
                break;
                case 1:
                effacerEcran();
               infosurensah();
                _getch();
                break;
            case 2:
                effacerEcranAvecAttenteEntree();
               lesetudeaensah();
              _getch();
                 case 3:
                return; // Quitter le menu étudiant

            default:
                break;

        }

        }
}
void afficherEmploi() {
    char niveau[50];
    char file[50];
    char c;
    changerCouleur(MAGENTA);
    printf("Vous voulez voir l'emploi du temps de quel niveau ?\n");
    changerCouleur(BLACK);
    scanf(" %[^\n]s", niveau);

    sprintf(file, "emploi %s.txt", niveau);

    FILE *m = fopen(file, "r");
    if (m == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }
changerCouleur(BLUE);
    afficherDansCadre("Affichage de l'emploi du temps pour le niveau");
    changerCouleur(BLACK);

    while ((c = fgetc(m)) != EOF) {
        printf("%c", c);
    }fclose(m);}




void menuproramme(){
while (1) {
        effacerEcran();
        printf("\n\n");


        char *options[] = {
            "\t\t\t\t reinscription",
            "\t\t\t\t  filiere ",
            "\t\t\t\t   Emploi",
            "\t\t\t\t   consultation ma moyenne  ",
            "\t\t\t\t   afficher annonce",
            "\t\t\t\t   cours",
            "\t\t\t\t   retour"



        }; int choix = afficherMenuAvecNavigation(options, 7);
char cneRecherche[20];
        switch (choix) {
            case 0:

                effacerEcranAvecAttenteEntree();
                changerCouleur(MAGENTA);
                printf("\n\n Entrez votre CNE  : ");
                scanf(" %[^\n]", cneRecherche);

    // Appel de la fonction qui gère l'enregistrement et la réinscription
                gererEtudiant(cneRecherche);
                break;
                case 1:
                effacerEcran();
               affichefiliere();
                _getch();
                break;
                case 2:
                effacerEcran();
                afficherEmploi();
                printf("\nAppuyez sur une touche pour continuer...");
                _getch();
                break;
                            case 3:
                effacerEcran();
                afficher_notes_et_moyenne();
                _getch();
                break;
                            case 4:
                effacerEcran();
                afficherAnnonces();
                printf("\nAppuyez sur une touche pour continuer...");
                _getch();
                break;
                            case 5:
                effacerEcran();
                affichercours();
                printf("\nAppuyez sur une touche pour continuer...");
                _getch();
                break;

            case 6:
                return; // Quitter le menu étudiant

            default:
                break;

        }

        }
}

void afficherAnnonces() {
    char ligne[256];  // Tampon pour lire chaque ligne du fichier
    FILE *f = fopen("annonces.txt", "r");  // Ouvre le fichier en mode lecture

    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        exit(1);
    }

    // Titre avec des étoiles et couleur
    printf("\n");
changerCouleur(MAGENTA);
printf("\n\n \n\n");

printf("\t\t\t\t  ***    *     *   *     *   *****     *     *     *****    *****             \n");
printf("\t\t\t\t *   *   **    *   **    *  *     *    **    *    *         *                 \n");
printf("\t\t\t\t*     *  * *   *   * *   * *       *   * *   *    *         *****             \n");
printf("\t\t\t\t*******  *  *  *   *  *  * *       *   *  *  *    *         *                 \n");
printf("\t\t\t\t*     *  *   * *   *   * *  *     *    *   * *    *         *                 \n");
printf("\t\t\t\t*     *  *    **   *    **   *****     *    **     *****    *****             \n");
getchar();
changerCouleur(WHITE);

   changerCouleur(BLACK);
    // Trouver le nombre d'annonces pour déterminer la largeur du tableau
    int annonceCount = 0;
    changerCouleur(BLUE);

changerCouleur(BLACK);
// Lire les annonces une première fois pour compter le nombre de lignes
while (fgets(ligne, sizeof(ligne), f) != NULL) {
    annonceCount++;
}

// Remettre le curseur au début du fichier pour relire les annonces
rewind(f);

// Afficher la bordure supérieure du tableau

printf("\n\n\n\n\n");
changerCouleur(MAGENTA);
printf("+---------------------------------------------------------------+\n");
changerCouleur(BLACK);

// Lire et afficher les annonces une par une
while (fgets(ligne, sizeof(ligne), f) != NULL) {
    // Supprimer le saut de ligne (\n) si présent
    ligne[strcspn(ligne, "\n")] = '\0';

    // Afficher chaque annonce centrée dans la largeur du tableau

    printf("| %-61s |\n", ligne); // %61s pour centrer dans la largeur
    changerCouleur(BLACK);
}

// Afficher la bordure inférieure du tableau
changerCouleur(MAGENTA);
printf("+---------------------------------------------------------------+\n");
changerCouleur(BLACK); // Réinitialiser la couleur
effacerEcranAvecAttenteEntree();

fclose(f);  // Fermer le fichier
}
// Fonction pour ajouter un étudiant
#define WIDTH 80
#define LARGEUR_CONSOLE 80  // Ajustez selon la largeur de votre console
 // Fonction pour centrer le texte dans la console

void afficherCentre(const char* texte) {
    int longueurTexte = strlen(texte);
    int espacement = (LARGEUR_CONSOLE - longueurTexte) / 2;
    for (int i = 0; i < espacement; i++) printf(" ");
    printf("%s\n", texte);
}
void afficherTitreEncadre(const char *titre) {
    int longueur = strlen(titre);
    int largeurCadre = longueur + 4; // Ajouter des espaces pour le cadre
    int espacesGauche = (LARGEUR_CONSOLE - largeurCadre) / 2; // Centrer le cadre

    // Bordure supérieure
    for (int i = 0; i < espacesGauche; i++) printf(" ");
    printf("+");
    for (int i = 0; i < largeurCadre; i++) printf("-");
    printf("+\n");

    // Titre centré
    for (int i = 0; i < espacesGauche; i++) printf(" ");
    printf("|  %s  |\n", titre);

    // Bordure inférieure
    for (int i = 0; i < espacesGauche; i++) printf(" ");
    printf("+");
    for (int i = 0; i < largeurCadre; i++) printf("-");
    printf("+\n");
}
void ajouterEtudiant() {
    Etudiant etu;
    FILE *fichierFiliere = NULL;
    FILE *fichierGeneral = NULL;
    char nomFichier[20];
    int continuer = 1; // Variable pour contrôler la boucle

    while (continuer) {
        // Effacer l'écran et afficher le titre encadré
        effacerEcran();
        changerCouleur(BLUE);
        afficherTitreEncadre("AJOUTER UN ETUDIANT");
        changerCouleur(BLACK);

        // Demande du niveau de l'étudiant
        changerCouleur(MAGENTA);
        printf("\n\t\t\tEntrez le niveau (ex : cp1, GEER1, GMEC3, etc.) : ");
        changerCouleur(BLACK);
        fgets(etu.nv, sizeof(etu.nv), stdin);
        etu.nv[strcspn(etu.nv, "\n")] = 0; // Supprimer le '\n'

        // Demande du nom de l'étudiant
        changerCouleur(MAGENTA);
        printf("\t\t\tEntrez le nom de l'etudiant : ");
        changerCouleur(BLACK);
        fgets(etu.nom, sizeof(etu.nom), stdin);
        etu.nom[strcspn(etu.nom, "\n")] = 0;

        // Demande du prénom de l'étudiant
        changerCouleur(MAGENTA);
        printf("\t\t\tEntrez le prenom de l'etudiant : ");
        changerCouleur(BLACK);
        fgets(etu.prenom, sizeof(etu.prenom), stdin);
        etu.prenom[strcspn(etu.prenom, "\n")] = 0;

        // Demande de la date de naissance de l'étudiant
        changerCouleur(MAGENTA);
        printf("\t\t\tEntrez la date de naissance (jour mois annee) : ");
        changerCouleur(BLACK);
        scanf("%d %d %d", &etu.date.jour, &etu.date.mois, &etu.date.annee);
        getchar(); // Consommer le '\n'

        // Demande de la ville de l'étudiant
        changerCouleur(MAGENTA);
        printf("\t\t\tEntrez la ville : ");
        changerCouleur(BLACK);
        fgets(etu.ville, sizeof(etu.ville), stdin);
        etu.ville[strcspn(etu.ville, "\n")] = 0;

        // Demande du numéro de téléphone de l'étudiant
        changerCouleur(MAGENTA);
        printf("\t\t\tEntrez le numero de telephone : ");
        changerCouleur(BLACK);
        fgets(etu.num_tele, sizeof(etu.num_tele), stdin);
        etu.num_tele[strcspn(etu.num_tele, "\n")] = 0;

        // Demande du mot de passe de l'étudiant
        changerCouleur(MAGENTA);
        printf("\t\t\tEntrez le mot de passe : ");
        changerCouleur(BLACK);
        fgets(etu.mot_de_passe, sizeof(etu.mot_de_passe), stdin);
        etu.mot_de_passe[strcspn(etu.mot_de_passe, "\n")] = 0;

        // Demande de l'adresse Gmail de l'étudiant
        changerCouleur(MAGENTA);
        printf("\t\t\tEntrez l'adresse Gmail : ");
        changerCouleur(BLACK);
        fgets(etu.gmail, sizeof(etu.gmail), stdin);
        etu.gmail[strcspn(etu.gmail, "\n")] = 0;

        // Demande du CNE de l'étudiant
        changerCouleur(MAGENTA);
        printf("\t\t\tEntrez le CNE : ");
        changerCouleur(BLACK);
        fgets(etu.cne, sizeof(etu.cne), stdin);
        etu.cne[strcspn(etu.cne, "\n")] = 0;

        // Demande du sexe de l'étudiant
        changerCouleur(MAGENTA);
        printf("\t\t\tEntrez le sexe (M pour masculin, F pour feminin) : ");
        changerCouleur(BLACK);
        scanf(" %c", &etu.sexe);
        getchar(); // Consommer le '\n'

        // Effacer l'écran avec une attente avant de sauvegarder
        effacerEcranAvecAttenteEntree();

        // Définir le nom du fichier spécifique à la filière
        sprintf(nomFichier, "%s.txt", etu.nv);

        // Ouvrir le fichier correspondant à la filière en mode ajout
        fichierFiliere = fopen(nomFichier, "a");
        if (fichierFiliere == NULL) {
            perror("Erreur lors de l'ouverture du fichier de filiere");
            return;
        }

        // Ouvrir le fichier général en mode ajout
        fichierGeneral = fopen("eleve_ensah.txt", "a");
        if (fichierGeneral == NULL) {
            perror("Erreur lors de l'ouverture du fichier general");
            fclose(fichierFiliere); // Ne pas oublier de fermer le fichier ouvert
            return;
        }

        // Format des informations de l'étudiant
        const char *format = "%s %s %s %02d %02d %04d %s %s %s %s %s %c\n";

        // Écrire les informations de l'étudiant dans le fichier spécifique à la filière
        fprintf(fichierFiliere, format,
                etu.nv, etu.nom, etu.prenom,
                etu.date.jour, etu.date.mois, etu.date.annee,
                etu.ville, etu.num_tele,
                etu.mot_de_passe, etu.gmail, etu.cne, etu.sexe);

        // Écrire les mêmes informations dans le fichier général
        fprintf(fichierGeneral, format,
                etu.nv, etu.nom, etu.prenom,
                etu.date.jour, etu.date.mois, etu.date.annee,
                etu.ville, etu.num_tele,
                etu.mot_de_passe, etu.gmail, etu.cne, etu.sexe);

        effacerEcranAvecAttenteEntree();

        // Message de confirmation
        changerCouleur(GREEN);
        afficherTitreEncadre("ETUDIANT AJOUTE AVEC SUCCES");
        changerCouleur(BLACK);
        effacerEcranAvecAttenteEntree();

        // Fermer les fichiers
        fclose(fichierFiliere);
        fclose(fichierGeneral);

        // Demander si l'utilisateur veut ajouter un autre étudiant
        changerCouleur(MAGENTA);
        printf("\n\t\t\tVoulez-vous ajouter un autre etudiant ? (1 pour oui, 0 pour non) : ");
        changerCouleur(BLACK);
        scanf("%d", &continuer);

        getchar();  // Consommer le '\n' laissé par scanf
        effacerEcranAvecAttenteEntree();
    }
}
// Structure pour représenter un étudiant
// Fonction pour réinscrire un étudiant
void reinscrireEtudiant(const char *cneRecherche) {
    const char *fichierReinscrits = "elvreinsc.txt";

    FILE *fichierReinscription = fopen(fichierReinscrits, "a");
    if (fichierReinscription == NULL) {
        perror("Erreur lors de l'ouverture du fichier de reinscription");
        return;
    }

    fprintf(fichierReinscription, "CNE: %s\n", cneRecherche);
    fclose(fichierReinscription);
       changerCouleur(WHITE);
    effacerEcranAvecAttenteEntree();
changerCouleur(GREEN);
    printf("\n\n\n\n\n\n\t\t\t\t vous avez bien reinscris.\n");
    changerCouleur(WHITE);
    effacerEcranAvecAttenteEntree();
    changerCouleur(BLACK);
}
// Fonction pour demander les informations complètes d'un étudiant
Etudiant saisirInformationsEtudiant() {
    Etudiant etudiant;
changerCouleur(MAGENTA);
    printf("Nom                                 : ");
    changerCouleur(BLACK);
    scanf(" %[^\n]", etudiant.nom);
changerCouleur(MAGENTA);
    printf("Prenom                              : ");
     changerCouleur(BLACK);
    scanf(" %[^\n]", etudiant.prenom);
changerCouleur(MAGENTA);
    printf("Date de naissance (jour mois annee) : ");
     changerCouleur(BLACK);
    scanf("%d %d %d", &etudiant.date.jour, &etudiant.date.mois, &etudiant.date.annee);
changerCouleur(MAGENTA);
    printf("Ville                               : ");
     changerCouleur(BLACK);
    scanf(" %[^\n]", etudiant.ville);
changerCouleur(MAGENTA);
    printf("Numéro de telephone                 : ");
     changerCouleur(BLACK);
    scanf("%d", &etudiant.num_tele);
changerCouleur(MAGENTA);
    printf("Mot de passe                        : ");
     changerCouleur(BLACK);
    scanf(" %[^\n]", etudiant.mot_de_passe);
changerCouleur(MAGENTA);
    printf("Gmail                               : ");
     changerCouleur(BLACK);
    scanf(" %[^\n]", etudiant.gmail);
changerCouleur(MAGENTA);
    printf("CNE                                 : ");
     changerCouleur(BLACK);
    scanf(" %[^\n]", etudiant.cne);
changerCouleur(MAGENTA);
    printf("Niveau (ex : cp1, GC1, GEER1, ...)  : ");
     changerCouleur(BLACK);
    scanf(" %[^\n]", etudiant.nv);

    return etudiant;
}
// Fonction pour écrire les informations dans les fichiers
void enregistrerEtudiant(const Etudiant etudiant) {
    char nomFichier[20];
    sprintf(nomFichier, "%s.txt", etudiant.nv);

    // Ouvrir le fichier spécifique à la filière
    FILE *fichierFiliere = fopen(nomFichier, "a");
    if (fichierFiliere == NULL) {
        perror("Erreur lors de l'ouverture du fichier specifique");
        return;
    }

    // Ouvrir le fichier général
    FILE *fichierGeneral = fopen("eleve_ensah.txt", "a");
    if (fichierGeneral == NULL) {
        perror("Erreur lors de l'ouverture du fichier general");
        fclose(fichierFiliere);
        return;
    }

    // Format pour écrire les informations
    const char *format = "%s %s %s %02d %02d %04d %s %d %s %s %s\n";

    // Écrire dans le fichier spécifique
    fprintf(fichierFiliere, format,
            etudiant.nv, etudiant.nom, etudiant.prenom,
            etudiant.date.jour, etudiant.date.mois, etudiant.date.annee,
            etudiant.ville, etudiant.num_tele,
            etudiant.mot_de_passe, etudiant.gmail, etudiant.cne);

    // Écrire dans le fichier général
    fprintf(fichierGeneral, format,
            etudiant.nv, etudiant.nom, etudiant.prenom,
            etudiant.date.jour, etudiant.date.mois, etudiant.date.annee,
            etudiant.ville, etudiant.num_tele,
            etudiant.mot_de_passe, etudiant.gmail, etudiant.cne);

    printf("etudiant enregistre avec succes dans les fichiers.\n");

    // Fermer les fichiers
    fclose(fichierFiliere);
    fclose(fichierGeneral);
}
// Fonction pour gérer l'enregistrement et la réinscription
void gererEtudiant(const char *cneRecherche) {
    const char *fichierENSAH = "eleve_ensah.txt";
    const char *fichierSelectionnes = "eleveselectionne.txt";

    if (rechercherCNE(fichierENSAH, cneRecherche)) {
        reinscrireEtudiant(cneRecherche);
    } else if (rechercherCNE(fichierSelectionnes, cneRecherche)) {
        changerCouleur(WHITE);
        effacerEcranAvecAttenteEntree();
        changerCouleur(GREEN);
        printf("\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\tvous avez deja selectionnes.\n");
        changerCouleur(WHITE);
        effacerEcranAvecAttenteEntree();
                changerCouleur(BLACK);


        // Saisir les informations complètes de l'étudiant
        Etudiant etudiant = saisirInformationsEtudiant();

        // Enregistrer les informations dans les fichiers
        enregistrerEtudiant(etudiant);
    } else {
         changerCouleur(WHITE);
        effacerEcranAvecAttenteEntree();
        changerCouleur(RED);;
        printf("\t\t\t\t\taucun eleve est trouve pour ce CNE.\n");
        changerCouleur(BLACK);
    }
}
// Fonction pour afficher les informations d'un étudiant trouvé
void afficherUnEtudiant() {
    Etudiant etu;
    char cne_cherche[50];
    char niveau_cherche[50];
    int trouve = 0;
effacerEcranAvecAttenteEntree();
    // Ouverture des fichiers
    FILE *f = fopen("eleve_ensah.txt", "r");

    if (f == NULL) {
        printf("Erreur d'ouverture du fichier !\n");
        exit(1);
    }

    // Demande du niveau et du nom de l'étudiant à rechercher
    printf("\n\n");
changerCouleur(BLUE);
    printf("\t\t\t\t** VOTRE PROFIL **\n");
    changerCouleur(MAGENTA);

    printf("\n\n\nVeuillez entrer votre niveau  : ");
    changerCouleur(BLACK);
    scanf(" %s", niveau_cherche);
    changerCouleur(MAGENTA);
    printf("\n\nVeuillez entrer votre cne       : ");
    changerCouleur(BLACK);
    scanf(" %[^\n]s", cne_cherche);
    effacerEcranAvecAttenteEntree();

    char ligne[300];

    // Lecture du fichier pour chercher l'étudiant
    while (fgets(ligne, sizeof(ligne), f) != NULL) {  // Lire une ligne entière
        sscanf(ligne, "%s %s %s %d %d %d %s %s %s %s %s ", etu.nv, etu.nom, etu.prenom,
               &etu.date.jour, &etu.date.mois, &etu.date.annee, etu.ville,
               etu.num_tele, etu.mot_de_passe, etu.gmail, etu.cne);

        // Comparer le niveau et le nom avec ceux recherchés
        if (strcmp(etu.nv, niveau_cherche) == 0 && strcmp(etu.cne, cne_cherche) == 0) {
            trouve = 1;
            changerCouleur(MAGENTA);
            printf("\n\n\n\n\n\n\n");

    printf("\t\t\t  *****   *****   ******    *****   *    *         *****       \n");
    printf("\t\t\t  *   *   *   *   *    *    *       *    *         *           \n");
    printf("\t\t\t  *   *   *   *   *    *    *       *    *         *           \n");
    printf("\t\t\t  *****   *****   *    *    *****   *    *         *****       \n");
    printf("\t\t\t  *       *  *    *    *    *       *    *         *           \n");
    printf("\t\t\t  *       *   *   *    *    *       *    *         *           \n");
    printf("\t\t\t  *       *    *  ******    *       *    ******    *****       \n");

    changerCouleur(WHITE);
        effacerEcranAvecAttenteEntree();
         changerCouleur(BLACK);
           // Affichage des informations de l'étudiant avec couleurs
changerCouleur(BLUE);  // Couleur pour les titres
printf("\n\t\t\t\tvotre information :\n\n\n");
changerCouleur(MAGENTA);  // Titre "Niveau"
printf("\tNiveau             : ");
changerCouleur(BLACK);    // Couleur pour le résultat
printf("%s\n", etu.nv);

changerCouleur(MAGENTA);  // Titre "Nom"
printf("\tNom                : ");
changerCouleur(BLACK);    // Couleur pour le résultat
printf("%s\n", etu.nom);

changerCouleur(MAGENTA);  // Titre "Prénom"
printf("\tPrenom             : ");
changerCouleur(BLACK);    // Couleur pour le résultat
printf("%s\n", etu.prenom);

changerCouleur(MAGENTA);  // Titre "Date de naissance"
printf("\tDate de naissance  : ");
changerCouleur(BLACK);    // Couleur pour le résultat
printf("%d/%d/%d\n", etu.date.jour, etu.date.mois, etu.date.annee);

changerCouleur(MAGENTA);  // Titre "Ville"
printf("\tVille              : ");
changerCouleur(BLACK);    // Couleur pour le résultat
printf("%s\n", etu.ville);

changerCouleur(MAGENTA);  // Titre "Numéro de téléphone"
printf("\tNumero de telephone: ");
changerCouleur(BLACK);    // Couleur pour le résultat
printf("%s\n", etu.num_tele);

changerCouleur(MAGENTA);  // Titre "Mot de passe"
printf("\tMot de passe       : ");
changerCouleur(BLACK);    // Couleur pour le résultat
printf("%s\n", etu.mot_de_passe);

changerCouleur(MAGENTA);  // Titre "Gmail"
printf("\tGmail              : ");
changerCouleur(BLACK);    // Couleur pour le résultat
printf("%s\n", etu.gmail);

changerCouleur(MAGENTA);  // Titre "CNE"
printf("\tCNE                : ");
changerCouleur(BLACK);    // Couleur pour le résultat
printf("%s\n", etu.cne);

            break;  // Sortir de la boucle après avoir trouvé l'étudiant
        }
    }

    // Si l'étudiant n'est pas trouvé
    if (!trouve) {
        printf("\n\t\t\t\t\t * L'etudiant n'a pas ete trouve. *\n");
    }

    // Fermeture du fichier
    fclose(f);
}




// Fonctions de génération des documents (à inclure)

// Fonction pour afficher les absences
void afficherAbsences() {
    FILE *fichier = fopen("absences.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier absences.txt.\n");
        return;
    }
effacerEcranAvecAttenteEntree();
    Etudiant etu;
     changerCouleur(MAGENTA);
    printf("\n\n\n\n\n\n");
    printf("\n\t\t\t\t\t*******************************************\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**     L I S T E  A B S C E N C E S      **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t**                                       **\n");
    printf("\t\t\t\t\t*******************************************\n");
        changerCouleur(WHITE);
        effacerEcranAvecAttenteEntree();
        changerCouleur(BLACK);
    while (fscanf(fichier, "%s %s %s %d\n", etu.cne, etu.nom, etu.prenom, &etu.absences) != EOF) {
printf("\n\n\n");
  changerCouleur(MAGENTA);
printf("\t\t\t\tcne                                :");
        changerCouleur(BLACK);

printf(" %s \n",etu.cne);
changerCouleur(MAGENTA);
printf("\t\t\t\tnom                                :");
        changerCouleur(BLACK);

printf(" %s \n",etu.nom);
changerCouleur(MAGENTA);
printf("\t\t\t\tprenom                             :");
        changerCouleur(BLACK);

printf(" %s \n",etu.prenom);
changerCouleur(MAGENTA);
printf("\t\t\t\tnobre d abscences totales          :");
        changerCouleur(BLACK);

printf(" %d \n",etu.absences);




    }
changerCouleur(WHITE);
        effacerEcranAvecAttenteEntree();
         changerCouleur(BLACK);
    fclose(fichier);
}

// Fonction pour mettre à jour les absences
void mettreAJourAbsences() {
    effacerEcranAvecAttenteEntree();
    FILE *fichierEtudiants = fopen("absences.txt", "r");
    FILE *fichierTemp = fopen("temp.txt", "w");
    if (fichierEtudiants == NULL || fichierTemp == NULL) {
        printf("Erreur : Impossible d'ouvrir les fichiers.\n");
        return;
    }

    Etudiant etu;
    char cneRecherche[50];
    int nouvellesAbsences;
    int trouve = 0;
changerCouleur(MAGENTA);
    printf("Entrez le CNE de l'etudiant : ");
    changerCouleur(BLACK);
    scanf("%s", cneRecherche);
    changerCouleur(MAGENTA);
    printf("Entrez le nombre d'absences a mettre à jour : ");
     changerCouleur(BLACK);
    scanf("%d", &nouvellesAbsences);
    effacerEcranAvecAttenteEntree();

    // Parcourir le fichier pour mettre à jour l'étudiant
    while (fscanf(fichierEtudiants, "%s %s %s %d\n", etu.cne, etu.nom, etu.prenom, &etu.absences) != EOF) {
        if (strcmp(etu.cne, cneRecherche) == 0) {
            trouve = 1;
            etu.absences = nouvellesAbsences;

            // Vérifier si une notification doit être envoyée
            if (etu.absences >= 3) {
                envoyerNotification(etu);
            }
        }
        fprintf(fichierTemp, "%s %s %s %d\n", etu.cne, etu.nom, etu.prenom,etu.absences);}
                      changerCouleur(GREEN);
    printf("\t\t\t\t*********************************************\n");
    printf("\t\t\t\t*                                           *\n");
    printf("\t\t\t\t*        le nombre d abscence est           *\n");
    printf("\t\t\t\t*                                           *\n");
    printf("\t\t\t\t*            bien met  a jour               *\n");
    printf("\t\t\t\t*                                           *\n");
    printf("\t\t\t\t*                                           *\n");
    printf("\t\t\t\t*********************************************\n");
    printf("\n");
changerCouleur(BLACK);
effacerEcranAvecAttenteEntree();




    if (!trouve) {
        printf("etudiant avec le CNE %s non trouve.\n", cneRecherche);
    }


    fclose(fichierEtudiants);
    fclose(fichierTemp);

    // Remplacer l'ancien fichier par le fichier temporaire
    remove("absences.txt");
    rename("temp.txt", "absences.txt");
}

// Fonction pour afficher le menu principal



// Fonction pour vérifier si un CNE existe dans un fichier donné (ligne par ligne)
int rechercherCNE(const char *nomFichier, const char *cneRecherche) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    char ligne[500];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char cneLigne[20];
        sscanf(ligne, "%*s %*s %*s %*d %*d %*d %*s %*d %*s %*s %s", cneLigne);
        if (strcmp(cneLigne, cneRecherche) == 0) {
            fclose(fichier);
            return 1; // CNE trouvé
        }
    }

    fclose(fichier);
    return 0; // CNE non trouvé
}
void afficherReinscrits() {
    const char *nomFichier = "elvreinsc.txt";
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char cne[20];
    changerCouleur(BLUE);
    afficherDansCadre("Liste des etudiants reinscrits");
    changerCouleur(BLACK);

    // Lire chaque ligne du fichier
    while (fgets(cne, sizeof(cne), fichier) != NULL) {
        // Afficher le CNE de l'étudiant
        printf("%s", cne);
    }

    fclose(fichier);
}
void afficherMenuConsultation() {
    while (1) {
        effacerEcran();
        printf("\n\n");

        char *options[] = {
            "\t\t\t\t programme",
            "\t\t\t\t  infos etudiant ",
            "\t\t\t\t infos ensah",
            "\t\t\t\t   retour  ",



        }; int choix = afficherMenuAvecNavigation(options, 4);

        switch (choix) {
            case 0:
                effacerEcran();
                menuproramme();
                printf("\nAppuyez sur une touche pour continuer...");
                _getch();
                break;

            case 1:
                effacerEcran();
                Menuinfo_sur_etudiant();
                // Ajoutez ici le code pour afficher les détails du profil
                printf("\nAppuyez sur une touche pour continuer...");
                _getch();
                break;
            case 2:
            effacerEcran();
             Menuinfo_sur_ensah();
            case 4:
                return; // Retour au menu étudiant

            default:
                break;
        }
    }
}
void afficherMenuEtudiant() {
    char cneRecherche[20];
    while (1) {
        effacerEcran();
        printf("\n\n");


        char *options[] = {
            "\t\t\t\t\tInscription",
            "\t\t\t\t\tConsultation",
            "\t\t\t\t\tQuitter"
        };

        int choix = afficherMenuAvecNavigation(options, 3);

        switch (choix) {
            case 0:
                effacerEcranAvecAttenteEntree();
                  changerCouleur(MAGENTA);
                printf("\n\n Entrez votre CNE  : ");
                scanf(" %[^\n]s", cneRecherche);

    // Appel de la fonction qui gère l'enregistrement et la réinscription
                gererEtudiant(cneRecherche);
                _getch();
                break;

         case 1:
    // Déclarer la variable avant l'appel de la fonction
    {
        int result = verifiermdp();

        if (result == 1) {
            afficherMenuConsultation();
        } else {
            printf(RED "Mot de passe ou CNE incorrect.\n" RESET);
            _getch();
            return; // Retour au menu principal en cas d'échec
        }
    }
    break;


            case 2:
                return; // Quitter le menu étudiant

            default:
                break;
        }
    }
}
void affichage_par_admin() {
    while (1) {
        effacerEcran();
        printf("\n\n");


    char *options[] = {

        "\t\t\t\t  afficher les eleves selectionner ",
        "\t\t\t\t  afficher les eleves reinscris ",

        "\t\t\t    Retour"
    };

    while (1) {
        int choix = afficherMenuAvecNavigation(options, 3);

        switch (choix) {

            case 0:
                effacerEcran();
              Etudiantselectioner();
              _getch();
                break;
            case 1:
                 effacerEcran();
             afficherReinscrits();
             _getch();
                break;

            case 2:
                return;
            default:
                break;
        }
    }
}
}
void ajouterAnnonce() {
    char message[256];
    FILE *f = fopen("annonces.txt", "a");  // Ouvre le fichier en mode ajout

    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        exit(1);
    }

    // Titre avec des étoiles et couleur
    printf("\n");
    changerCouleur(BLUE);  // Couleur jaune pour le titre
    afficherDansCadre("Ajouter une Annonce");


    // Demander le message de l'annonce
    changerCouleur(MAGENTA); // Couleur verte pour le message
    printf("Message de l'annonce : ");
    changerCouleur(BLACK);  // Réinitialiser la couleur

    scanf(" %[^\n]s", message);  // Le message de l'annonce (avec espaces autorisés)

    // Enregistrer l'annonce dans le fichier
    fprintf(f, "%s\n", message);

    // Confirmation du succès avec un message centré
    int len = strlen(message);
    int spaces = (80 - len) / 2;  // Calculer le nombre d'espaces pour centrer

    // Affichage centré pour la confirmation
    printf("\n");
    for (int i = 0; i < spaces; i++) {
        printf(" ");  // Espaces avant le texte
    }

    printf(GREEN);  // Couleur bleue pour la confirmation
    printf("Annonce ajoutee avec succes !\n");
    printf(BLACK);  // Réinitialiser la couleur

    fclose(f);  // Fermer le fichier
}
typedef struct {
    char titre[50];
    char entreprise[50];
    char duree[20];
    char description[200];
} Stage;


void ajouterStage() {
    Stage stage;

    effacerEcran();
    changerCouleur(BLUE);
    afficherDansCadre("Ajouter un Stage");


    // Récupération des informations du stage
    changerCouleur(MAGENTA);
    printf("\tTitre du stage : ");
    changerCouleur(BLACK);
    fflush(stdin);
    fgets(stage.titre, sizeof(stage.titre), stdin);
changerCouleur(MAGENTA);
    printf("\tNom de l'entreprise : ");
    changerCouleur(BLACK);
    fflush(stdin);
    fgets(stage.entreprise, sizeof(stage.entreprise), stdin);
changerCouleur(MAGENTA);
    printf("\tDuree (exemple : 2 mois) : ");
    changerCouleur(BLACK);
    fflush(stdin);
    fgets(stage.duree, sizeof(stage.duree), stdin);
changerCouleur(MAGENTA);
    printf("\tDescription du stage : ");
    changerCouleur(BLACK);
    fflush(stdin);
    fgets(stage.description, sizeof(stage.description), stdin);

    // Sauvegarder dans un fichier
    FILE *fichier = fopen("stages.txt", "a"); // Ouvre le fichier en mode ajout
    if (fichier == NULL) {
        printf("\n\tErreur : Impossible d'ouvrir le fichier pour sauvegarder.\n");
        return;
    }

    fprintf(fichier, "Titre: %sEntreprise: %sDuree: %sDescription: %s\n",
            stage.titre, stage.entreprise, stage.duree, stage.description);

    fclose(fichier);
    effacerEcranAvecAttenteEntree();
changerCouleur(GREEN);
    printf("\n\tStage ajoute avec succes ! ");
    _getch();
}
void afficherBordure() {
    for (int i = 0; i < LARGEUR_CONSOLE; i++) printf("=");
    printf("\n");
}


void calculerStatistiquesSexe() {
    FILE *f = fopen("eleve_ensah.txt", "r");

    if (f == NULL) {
        printf("Erreur d'ouverture du fichier !\n");
        exit(1);
    }

    etudiant etu;
    int nbHommes = 0, nbFemmes = 0;
    char ligne[500];

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        ligne[strcspn(ligne, "\n")] = 0;

        sscanf(ligne, "%s %s %s %d %d %d %s %s %s %s %s %s", etu.nv, etu.nom, etu.prenom,
               &etu.date.jour, &etu.date.mois, &etu.date.annee, etu.ville,
               etu.num_tele, etu.mot_de_passe, etu.gmail, etu.cne, etu.sex);

        if (strcmp(etu.sex, "M") == 0) {
            nbHommes++;
        } else if (strcmp(etu.sex, "F") == 0) {
            nbFemmes++;
        }
    }

    fclose(f);

    afficherBordure();

    afficherDansCadre("Statistiques des etudiants par sexe");

    afficheerCentre("|   Sexe   | Nombre |");

    char buffer[50];
    changerCouleur(BLUE);
    snprintf(buffer, sizeof(buffer), "                                  |  Hommes  |   %d    | ", nbHommes);
    afficherCentre(buffer);
    changerCouleur(MAGENTA);
    snprintf(buffer, sizeof(buffer), "|  Femmes  |   %d    |", nbFemmes);

    afficheerCentre(buffer);
    changerCouleur(GREEN);

    changerCouleur(GREEN);
    snprintf(buffer, sizeof(buffer), "Total d'etudiants : %d", nbHommes + nbFemmes);
    afficheerCentre(buffer);

}
void calculerStatistiquesReussite() {
    FILE *p = fopen("deliberation.txt", "r"); // Ouvrir le fichier en mode lecture
    if (p == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        exit(1);
    }

    etudiant etu;
    char ligne[MAX_LIGNE]; // Tampon pour lire chaque ligne du fichier
    int totalEtudiants = 0;
    int totalReussites = 0;
    int totalEchecs = 0;

    // Pour stocker le nombre de réussites et d'échecs par niveau
    int reussitesParNiveau[MAX_NIVEAU] = {0};
    int echecsParNiveau[MAX_NIVEAU] = {0};
    int etudiantsParNiveau[MAX_NIVEAU] = {0}; // Compteur pour le nombre d'étudiants par niveau

    // Demander le niveau à l'utilisateur
    char niveauRecherche[10]; // Stocker le niveau recherché sous forme de chaîne de caractères
    changerCouleur(MAGENTA);
    printf("Entrez le niveau pour lequel vous voulez connaitre les statistiques (ex : cp1, cp2, GI1, GI2, etc.) : ");
    changerCouleur(BLACK);
    scanf("%s", niveauRecherche);
    effacerEcranAvecAttenteEntree();

    // Lire chaque ligne du fichier
    while (fgets(ligne, sizeof(ligne), p) != NULL) {
        // Lire et analyser chaque ligne avec sscanf
        // Format de lecture : niveau, nom, prénom, cne, note1, note2, note3
        sscanf(ligne, "%s %s %s %s %d %d %d", etu.nv, etu.nom, etu.prenom, etu.cne,
                                             &etu.note1, &etu.note2, &etu.note3);

        etu.moyenne = (etu.note1 + etu.note2 + etu.note3) / 3.0;

        // Si l'étudiant appartient au niveau recherché
        if (strcmp(etu.nv, niveauRecherche) == 0) {  // Comparaison des chaînes de caractères
            // Vérifier si l'étudiant a réussi ou échoué
            if (etu.moyenne >= 10) {
                totalReussites++;
                reussitesParNiveau[atoi(etu.nv)]++;
                changerCouleur(MAGENTA); // Incrémenter le nombre de réussites pour le niveau
                printf("Etudiant:");
                changerCouleur(BLACK);
                printf(" %s %s \n", etu.nom, etu.prenom);
                changerCouleur(MAGENTA);
                printf("CNE: ");
                changerCouleur(BLACK);
                printf(" %s\n", etu.cne);
                changerCouleur(GREEN);
                printf(" - Reussite -\n");
                changerCouleur(MAGENTA);
                printf(" Moyenne: ");
                changerCouleur(BLACK);
                printf(" %.2f\n", etu.moyenne);
            } else {
                totalEchecs++;
                echecsParNiveau[atoi(etu.nv)]++; // Incrémenter le nombre d'échecs pour le niveau
                 printf("Etudiant:");
                changerCouleur(BLACK);
                printf(" %s %s \n", etu.nom, etu.prenom);
                changerCouleur(MAGENTA);
                printf("CNE: ");
                changerCouleur(BLACK);
                printf(" %s\n", etu.cne);
                changerCouleur(RED);
                printf(" - ECHEC -\n");
                changerCouleur(MAGENTA);
                printf(" Moyenne: ");
                changerCouleur(BLACK);
                printf(" %.2f\n", etu.moyenne);
            }

            etudiantsParNiveau[atoi(etu.nv)]++; // Incrémenter le nombre d'étudiants pour le niveau
            totalEtudiants++; // Incrémenter le total d'étudiants
        }
    }

    // Afficher les statistiques pour le niveau recherché
    if (etudiantsParNiveau[atoi(niveauRecherche)] > 0) {
        // Calcul du pourcentage de réussite
        float pourcentageReussite = (reussitesParNiveau[atoi(niveauRecherche)] / (float) etudiantsParNiveau[atoi(niveauRecherche)]) * 100;
        float pourcentageEchec = (echecsParNiveau[atoi(niveauRecherche)] / (float) etudiantsParNiveau[atoi(niveauRecherche)]) * 100;

        // Affichage centré des statistiques
        changerCouleur(BLUE);
       afficherDansCadre("Statistiques du Niveau");
 changerCouleur(MAGENTA);
        printf("Niveau: ");
        changerCouleur(BLACK);
         printf(" %s\n", niveauRecherche);
         changerCouleur(BLACK);
        printf("----------------------------------------------------\n");
        changerCouleur(MAGENTA);
        printf("Total des etudiants dans ce niveau: ");
        changerCouleur(BLACK);
         printf(" %d\n", etudiantsParNiveau[atoi(niveauRecherche)]);
         changerCouleur(GREEN);
        printf("Reussites: ");
        printf(" %d (%.2f%%)\n", reussitesParNiveau[atoi(niveauRecherche)], pourcentageReussite);
        changerCouleur(RED);
        printf("Echecs: ");
        printf(" %d (%.2f%%)\n", echecsParNiveau[atoi(niveauRecherche)], pourcentageEchec);
        changerCouleur(BLACK);
        printf("----------------------------------------------------\n");

    } else {
        afficherCadreCentree("Erreur");
changerCouleur(RED);
        printf("Aucun etudiant trouve pour le niveau %s.\n", niveauRecherche);
    }

    fclose(p); // Fermer le fichier après la lecture
}
void calculerStatistiquesTousLesNiveaux() {
    FILE *p = fopen("deliberation.txt", "r"); // Ouvrir le fichier en mode lecture
    if (p == NULL) {
        afficherCentre("Erreur d'ouverture du fichier.");
        exit(1);
    }

    etudiant etu;
    char ligne[MAX_LIGNE]; // Tampon pour lire chaque ligne du fichier
    int totalReussites = 0;
    int totalEchecs = 0;
    int totalEtudiants = 0;

    int reussitesParNiveau[MAX_NIVEAU] = {0};
    int echecsParNiveau[MAX_NIVEAU] = {0};
    int etudiantsParNiveau[MAX_NIVEAU] = {0};

    char niveaux[MAX_NIVEAU][MAX_NIVEAU_STR];
    int niveauIndex = 0;

    while (fgets(ligne, sizeof(ligne), p) != NULL) {
        sscanf(ligne, "%s %s %s %s %d %d %d", etu.nv, etu.nom, etu.prenom, etu.cne,
               &etu.note1, &etu.note2, &etu.note3);

        etu.moyenne = (etu.note1 + etu.note2 + etu.note3) / 3.0;

        int trouve = 0;
        for (int i = 0; i < niveauIndex; i++) {
            if (strcmp(niveaux[i], etu.nv) == 0) {
                trouve = 1;
                break;
            }
        }

        if (!trouve) {
            strcpy(niveaux[niveauIndex], etu.nv);
            niveauIndex++;
        }

        for (int i = 0; i < niveauIndex; i++) {
            if (strcmp(niveaux[i], etu.nv) == 0) {
                if (etu.moyenne >= 10) {
                    reussitesParNiveau[i]++;
                    totalReussites++;
                } else {
                    echecsParNiveau[i]++;
                    totalEchecs++;
                }
                etudiantsParNiveau[i]++;
                totalEtudiants++;
                break;
            }
        }
    }

    fclose(p);
changerCouleur(BLUE);
    aafficherCentre("----------------------------------------------------");
    aafficherCentre("STATISTIQUES DES ETUDIANTS PAR NIVEAU");
    aafficherCentre("----------------------------------------------------\n\n");

    for (int i = 0; i < niveauIndex; i++) {
        float pourcentageReussite = (reussitesParNiveau[i] / (float)etudiantsParNiveau[i]) * 100;
        float pourcentageEchec = (echecsParNiveau[i] / (float)etudiantsParNiveau[i]) * 100;

        char buffer[100];
        changerCouleur(MAGENTA);
        snprintf(buffer, sizeof(buffer), "Niveau : %s", niveaux[i]);
        aafficherCentre(buffer);
changerCouleur(BLACK);
        aafficherCentre("------------------------------------");

        snprintf(buffer, sizeof(buffer), "Total etudiants : %d", etudiantsParNiveau[i]);
        aafficherCentre(buffer);
changerCouleur(GREEN);
        snprintf(buffer, sizeof(buffer), "Reussites : %d (%.2f%%)", reussitesParNiveau[i], pourcentageReussite);
        aafficherCentre(buffer);
changerCouleur(RED);
        snprintf(buffer, sizeof(buffer), "Echecs : %d (%.2f%%)", echecsParNiveau[i], pourcentageEchec);
        aafficherCentre(buffer);
changerCouleur(BLACK);
        aafficherCentre("------------------------------------\n");
    }

    if (totalEtudiants > 0) {
        float pourcentageReussiteGlobale = (totalReussites / (float)totalEtudiants) * 100;
        float pourcentageEchecGlobale = (totalEchecs / (float)totalEtudiants) * 100;
changerCouleur(BLUE);
        aafficherCentre("----------------------------------------------------");
        aafficherCentre("STATISTIQUES GLOBALES");
        aafficherCentre("----------------------------------------------------\n\n");

        char buffer[100];
    changerCouleur(BLACK);
        snprintf(buffer, sizeof(buffer), "Total etudiants : %d", totalEtudiants);
        aafficherCentre(buffer);
changerCouleur(GREEN);
        snprintf(buffer, sizeof(buffer), "Reussites : %d (%.2f%%)", totalReussites, pourcentageReussiteGlobale);
        aafficherCentre(buffer);
changerCouleur(RED);
        snprintf(buffer, sizeof(buffer), "Echecs : %d (%.2f%%)", totalEchecs, pourcentageEchecGlobale);
        aafficherCentre(buffer);
changerCouleur(BLACK);
        aafficherCentre("----------------------------------------------------");
    }
}
void statistique_ensah() {
    while (1) {
        effacerEcran();
        printf("\n\n");

    char *options[] = {
        "\t\t\t\t   statistique par sexe ",
        "\t\t\t\t   statistique des reussites  ",
        "\t\t\t\t   statistiques tous les niveaux",
        "\t\t\t     Retour"
    };

    while (1) {
        int choix = afficherMenuAvecNavigation(options, 4);

        switch (choix) {
            case 0:
                effacerEcranAvecAttenteEntree();
               calculerStatistiquesSexe();
               _getch();
                break;
            case 1:
                effacerEcranAvecAttenteEntree();
               calculerStatistiquesReussite();
               _getch();
                break;
            case 2:
                effacerEcranAvecAttenteEntree();
               calculerStatistiquesTousLesNiveaux();
               _getch();
                break;
            case 3:
                return;
            default:
                break;
        }
    }
}
}



void afficherMenuAdmin() {
    while (1) {
effacerEcran();
    char *options[] = {
        "\t\t\t\t    des modifications_etudiants",
        "\t\t\t\t   affichage(inscrit,selectinne..)",
        "\t\t\t\t    gestion des stages ",
        "\t\t\t    historique",
        "\t\t\t    statistique",
        "\t\t\t afficher les absences ",
        "\t\t\t    Retour"
    };

    while (1) {
        int choix = afficherMenuAvecNavigation(options, 7);

        switch (choix) {
            case 0:
               modifications_etudiant();
                break;
            case 1:
                affichage_par_admin();
                break;
            case 2:
                effacerEcranAvecAttenteEntree();
              ajouterStage();
              _getch();
                break;
                 case 3:
              effacerEcran();
              afficherHistorique("historique.txt");
              _getch();
                break;
                case 4:
                effacerEcranAvecAttenteEntree();
                statistique_ensah();
                _getch();
                break;
                case 5:
               afficherAbsences();

break;
            case 6:
                return;
            default:
                break;
        }
    }
}
}
void supprimeretudiant() {
    char cne_s[200];
    char nv_s[200];
    int trouve = 0;

    // Effacer l'écran et afficher le titre encadré
    effacerEcran();
    changerCouleur(BLUE);
    afficherTitreEncadre("SUPPRIMER UN ETUDIANT");
    changerCouleur(BLACK);

    // Demander le niveau et le CNE de l'étudiant à supprimer
    changerCouleur(MAGENTA);
    printf("\n\t\t\tEntrez le niveau de l'étudiant : ");
    changerCouleur(BLACK);
    scanf("%199s", nv_s);
    changerCouleur(MAGENTA);
    printf("\t\t\tEntrez le CNE de l'étudiant : ");
    changerCouleur(BLACK);
    scanf(" %199s", cne_s);

    // Ouvrir le fichier principal en mode lecture
    FILE *f = fopen("eleve_ensah.txt", "r");
    if (f == NULL) {
        changerCouleur(RED);
        afficherTitreEncadre("ERREUR");
        printf("\n\t\t\tErreur lors de l'ouverture du fichier eleve_ensah.txt.\n");
        changerCouleur(BLACK);
        exit(1);
    }

    // Ouvrir un fichier temporaire en mode écriture
    FILE *s = fopen("temp.txt", "w");
    if (s == NULL) {
        changerCouleur(RED);
        afficherTitreEncadre("ERREUR");
        printf("\n\t\t\tErreur lors de l'ouverture du fichier temp.txt.\n");
        fclose(f);
        changerCouleur(BLACK);
        exit(1);
    }

    char ligne[1024];
    etudiant etu;

    // Parcourir le fichier pour trouver l'étudiant
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        sscanf(ligne, "%s %s %s %d %d %d %s %d %s %s %s %s",
               etu.nv, etu.nom, etu.prenom, &etu.date.jour, &etu.date.mois, &etu.date.annee,
               etu.ville, &etu.num_tele, etu.mot_de_passe, etu.gmail, etu.cne, etu.sex);

        if (strcmp(etu.nv, nv_s) == 0 && strcmp(etu.cne, cne_s) == 0) {
            trouve = 1;

            // Afficher les informations de l'étudiant dans un cadre
            effacerEcran();
            changerCouleur(BLUE);
            afficherTitreEncadre("INFORMATIONS DE L'ETUDIANT SUPPRIME");
            changerCouleur(MAGENTA);
            printf("\n\t\t\tNiveau              : ");
            changerCouleur(BLACK);
            printf("%s\n", etu.nv);
            changerCouleur(MAGENTA);
            printf("\t\t\tNom                 : ");
            changerCouleur(BLACK);
            printf("%s\n", etu.nom);
            changerCouleur(MAGENTA);
            printf("\t\t\tPrénom              : ");
            changerCouleur(BLACK);
            printf("%s\n", etu.prenom);
            changerCouleur(MAGENTA);
            printf("\t\t\tDate de naissance   : ");
            changerCouleur(BLACK);
            printf("%02d/%02d/%04d\n", etu.date.jour, etu.date.mois, etu.date.annee);
            changerCouleur(MAGENTA);
            printf("\t\t\tVille               : ");
            changerCouleur(BLACK);
            printf("%s\n", etu.ville);
            changerCouleur(MAGENTA);
            printf("\t\t\tNuméro de téléphone : ");
            changerCouleur(BLACK);
            printf("%s\n", etu.num_tele);
            changerCouleur(MAGENTA);
            printf("\t\t\tGmail               : ");
            changerCouleur(BLACK);
            printf("%s\n", etu.gmail);
            changerCouleur(MAGENTA);
            printf("\t\t\tCNE                 : ");
            changerCouleur(BLACK);
            printf("%s\n", etu.cne);
            changerCouleur(MAGENTA);
            printf("\t\t\tSexe                : ");
            changerCouleur(BLACK);
            printf("%s\n", etu.sex);

            // Ajouter une pause pour permettre à l'utilisateur de lire les informations
            changerCouleur(MAGENTA);
            printf("\n\t\t\tAppuyez sur Entrée pour confirmer la suppression...");
            changerCouleur(BLACK);
            getchar(); // Attendre l'appui sur Entrée
            getchar(); // Consommer le '\n' laissé par scanf
        } else {
            // Écrire les autres étudiants dans le fichier temporaire
            fprintf(s, "%s %s %s %d %d %d %s %d %s %s %s %s\n",
                    etu.nv, etu.nom, etu.prenom, etu.date.jour, etu.date.mois, etu.date.annee,
                    etu.ville, etu.num_tele, etu.mot_de_passe, etu.gmail, etu.cne, etu.sex);
        }
    }

    fclose(f);
    fclose(s);

    if (trouve) {
        // Supprimer le fichier original et renommer le fichier temporaire
        remove("eleve_ensah.txt");
        rename("temp.txt", "eleve_ensah.txt");

        // Afficher un message de succès
        changerCouleur(GREEN);
        afficherTitreEncadre("SUCCES");
        printf("\n\t\t\tL'étudiant a été supprimé avec succès.\n");
        changerCouleur(BLACK);
    } else {
        // Supprimer le fichier temporaire si l'étudiant n'a pas été trouvé
        remove("temp.txt");

        // Afficher un message d'erreur
        changerCouleur(RED);
        afficherTitreEncadre("ERREUR");
        printf("\n\t\t\tAucun étudiant trouvé avec ce niveau et ce CNE.\n");
        changerCouleur(BLACK);
    }

    // Ajouter une pause avant de retourner au menu principal
    changerCouleur(MAGENTA);
    printf("\n\t\t\tAppuyez sur Entrée pour retourner au menu principal...");
    changerCouleur(BLACK);
    getchar(); // Attendre l'appui sur Entrée
}
#include <stdio.h>
#include <string.h>

// Fonction pour afficher un titre encadré
/*void afficherTitreEncadre(const char *titre) {
    int longueur = strlen(titre) + 4; // +4 pour les bordures
    printf("\n\t\t\t+");
    for (int i = 0; i < longueur; i++) printf("-");
    printf("+\n");
    printf("\t\t\t|  %s  |\n", titre);
    printf("\t\t\t+");
    for (int i = 0; i < longueur; i++) printf("-");
    printf("+\n");
}*/





int chercherEtudiant(const char *cneRecherche) {
    const char *nomFichier = "eleve_ensah.txt";
    char ligne[256];
    int etudiantTrouve = 0;

    // Ouvrir le fichier en mode lecture
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("%sErreur lors de l'ouverture du fichier eleve_ensah.txt.%s\n", RED, RESET);
        return 0;
    }

    // Parcourir chaque ligne du fichier
    while (fgets(ligne, sizeof(ligne), fichier)) {
        char niveau[20], nom[20], prenom[20], ville[20], num_tele[20];
        char mot_de_passe[100], gmail[200], cne[20];
        int jour, mois, annee;

        // Extraire les informations de la ligne
        int nb_champs = sscanf(ligne, "%s %s %s %d %d %d %s %s %s %s %s",
                               niveau, nom, prenom,
                               &jour, &mois, &annee,
                               ville, num_tele, mot_de_passe, gmail, cne);

        // Vérifier si toutes les informations sont extraites et si le CNE correspond
        if (nb_champs == 11 && strcmp(cne, cneRecherche) == 0) {
            // Afficher un titre encadré pour les informations de l'étudiant
            printf("%s", GREEN);
            afficherTitreEncadre("INFORMATIONS DE L'ETUDIANT");

            // Afficher les informations de l'étudiant
            printf("%s\t\t\tNiveau              : %s%s\n", MAGENTA, RESET, niveau);
            printf("%s\t\t\tNom                 : %s%s\n", MAGENTA, RESET, nom);
            printf("%s\t\t\tPrénom              : %s%s\n", MAGENTA, RESET, prenom);
            printf("%s\t\t\tDate de naissance   : %s%02d/%02d/%04d\n", MAGENTA, RESET, jour, mois, annee);
            printf("%s\t\t\tVille               : %s%s\n", MAGENTA, RESET, ville);
            printf("%s\t\t\tNuméro de téléphone : %s%s\n", MAGENTA, RESET, num_tele);
            printf("%s\t\t\tMot de passe        : %s%s\n", MAGENTA, RESET, mot_de_passe);
            printf("%s\t\t\tEmail               : %s%s\n", MAGENTA, RESET, gmail);
            printf("%s\t\t\tCNE                 : %s%s\n", MAGENTA, RESET, cne);

            // Encadrer la fin des informations
            printf("%s", GREEN);
            afficherTitreEncadre("FIN DES INFORMATIONS");

            etudiantTrouve = 1;
            break; // Étudiant trouvé, arrêter la recherche
        }
    }

    // Fermer le fichier
    fclose(fichier);

    if (!etudiantTrouve) {
        printf("%s", RED);
        afficherTitreEncadre("ERREUR");
        printf("%s\t\t\tAucun étudiant trouvé avec le CNE : %s%s\n", MAGENTA, RESET, cneRecherche);
    }

    return etudiantTrouve;
}
void modifications_etudiant() {
    char cneRecherche[20];
    while (1) {
        effacerEcran();
        printf("\n\n");


    char *options[] = {
        "\t\t\t\tajouter etudiant",
        "\t\t\t\tMOdifier etudiant",
        "\t\t\t\tsupprimer etudiant ",

        "\t\t\t\trecherche etudiant",
        "\t\t\t\tajouter notifications",
        "\t\t\t\tmettre a jour abscence",
        "\t\t\t\tajouter annonces",
        "\t\t\tRetour"
    };

    while (1) {
        int choix = afficherMenuAvecNavigation(options, 8);

        switch (choix) {
            case 0:
                effacerEcranAvecAttenteEntree();
                ajouterEtudiant();
                break;
            case 1:
                modifierUnEtudiant();
                break;
            case 2:
                effacerEcranAvecAttenteEntree();
               supprimeretudiant();
               _getch();
                break;

                 case 3:
                     effacerEcranAvecAttenteEntree();
    {
        int continuerRecherche = 1;  // Variable pour continuer ou arrêter la recherche

        while (continuerRecherche) {
             char cneRecherche[20];
        Etudiant etu;
            changerCouleur(BLUE);
            printf("\t\t\t=== Recherche d'un etudiant par CNE ===\n\n\n");
            changerCouleur(MAGENTA);
            printf("Entrez le CNE de l'etudiant a rechercher : ");
            changerCouleur(BLACK);
            fgets(cneRecherche, sizeof(cneRecherche), stdin);
            cneRecherche[strcspn(cneRecherche, "\n")] = 0;
effacerEcranAvecAttenteEntree();
            // Effectuer la recherche
            if (!chercherEtudiant(cneRecherche)) {
                changerCouleur(RED);
                printf("\n\n\t\t\t\tAucun etudiant trouve pour ce CNE.\n");
                changerCouleur(BLACK);
            }

            // Demander à l'utilisateur s'il souhaite rechercher un autre étudiant
            changerCouleur(MAGENTA);
            printf("\nSouhaitez-vous chercher un autre etudiant ? (o/n) : ");
            changerCouleur(BLACK);
            char reponse[2];
            fgets(reponse, sizeof(reponse), stdin);

            // Si l'utilisateur entre 'o' ou 'O', continuer la recherche
            if (reponse[0] != 'o' && reponse[0] != 'O') {
                continuerRecherche = 0;  // Arrêter la boucle si l'utilisateur ne veut pas continuer
            }

            effacerEcranAvecAttenteEntree();  // Effacer l'écran avant de recommencer la recherche si nécessaire
        }

        break;
    }

                case 4:
             ajouterNotification();
             _getch();
                break;
            case 5:
                mettreAJourAbsences();
                 _getch();
                break;
            case 6 :
                effacerEcranAvecAttenteEntree();
                ajouterAnnonce();
                _getch();


                 case 7:
                return;
            default:
                break;
        }
    }
}
}
void afficherMenuPrincipal() {
    char *options[] = {
        "\t\t\t\t\tEtudiant",
        "\t\t\t\t\tAdministrateur",
        "\t\t\t\t\tQuitter"
    };

    while (1) {
        int choix = afficherMenuAvecNavigation(options, 3);

        switch (choix) {
            case 0:
                effacerEcran();

                afficherMenuEtudiant();
                break;
            case 1:
                effacerEcran();
              const char *nomFichier = "admins.bin";

// Créer le fichier contenant les administrateurs (une seule fois)
creerFichierAdmins(nomFichier);

// Vérification de l'identité de l'administrateur
if (verifierAdmin(nomFichier)) {
    changerCouleur(GREEN);
    afficherCadreCentree("=== Acces au programme accorde ===");
    changerCouleur(WHITE);

    // Afficher le menu administrateur si la vérification réussit
    afficherMenuAdmin();
} else {
    changerCouleur(FOREGROUND_RED);
    afficherCadreCentree("=== Acces refuse ===");
    changerCouleur(WHITE);
}


                break;
            case 2:
                return;
            default:
                break;
        }
    }

}
void config_console() {
    // La commande 'color' permet de changer les couleurs de la console
    // 'F0' signifie fond blanc (F) et texte noir (0)
    system("color F0");

}

typedef struct {
    char nom[50];
    char cne[20];
    char message[200];
} Notification;


void ajouterNotification() {
    effacerEcranAvecAttenteEntree();
    Notification notif;
    FILE *f;
    char reponse;

    do {
        f = fopen("notifications.txt", "a");  // Ouvre le fichier en mode ajout

        if (f == NULL) {
            printf("Erreur d'ouverture du fichier.\n");
            exit(1);
        }

        changerCouleur(BLUE);
        printf("\t\t\t\tenvoyer le message a \n\n");
        changerCouleur(BLACK);

        // Demander les informations pour la notification
        changerCouleur(MAGENTA);
        printf("Nom de l'etudiant : ");
        changerCouleur(BLACK);
        scanf(" %[^\n]s", notif.nom);   // Utiliser %[^\n] pour permettre des espaces dans le nom
        changerCouleur(MAGENTA);
        printf("CNE de l'etudiant : ");
        changerCouleur(BLACK);
        scanf(" %[^\n]s", notif.cne);
        effacerEcranAvecAttenteEntree();

        changerCouleur(BLUE);
        printf("Message de notification : ");
        changerCouleur(BLACK);
        scanf(" %[^\n]s", notif.message);  // Le message de notification

        // Enregistrer la notification dans le fichier
        fprintf(f, "%s %s %s\n", notif.nom, notif.cne, notif.message);

        changerCouleur(GREEN);
        printf("\n\n\n\t\t\t\t\tNotification envoyee avec succes !\n");
        changerCouleur(BLACK);
        fclose(f);  // Fermer le fichier

        // Demander à l'utilisateur s'il veut ajouter une autre notification
        effacerEcranAvecAttenteEntree();
        changerCouleur(MAGENTA);
        printf("\n\t\t\t\tVoulez-vous ajouter une notification pour un autre etudiant ? (o/n) : ");
        changerCouleur(BLACK);

        scanf(" %c", &reponse);
           effacerEcranAvecAttenteEntree();

    } while (reponse == 'o' || reponse == 'O');
}

void afficherNotification() {
    char cne[20];           // CNE de l'étudiant
    Notification notif;
    FILE *f = fopen("notifications.txt", "r");  // Ouvre le fichier en mode lecture

    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        exit(1);
    }

    // Demander à l'étudiant de saisir son CNE
    changerCouleur(MAGENTA); // Couleur rose
    printf("Entrez votre CNE : ");
    changerCouleur(BLACK); // Réinitialiser la couleur
    scanf(" %[^\n]s", cne);
    effacerEcranAvecAttenteEntree();

    // Chercher la notification pour cet étudiant
    int found = 0;  // Indicateur si une notification a été trouvée
    while (fscanf(f, "%s %s %[^\n]s", notif.nom, notif.cne, notif.message) != EOF) {
        // Comparer le CNE de l'étudiant avec celui du fichier
        if (strcmp(cne, notif.cne) == 0) {
            // Afficher "NOTIFICATION" centré en haut dans un cadre bleu
            changerCouleur(BLUE); // Couleur bleue pour le cadre
            afficherDansCadre("VOTRE BOITE DE NOTIFICATIONS :");

            // Afficher le message sous le cadre, en noir
            changerCouleur(MAGENTA); // Couleur noire pour le message
            printf("\nMESSAGES: \n");
            changerCouleur(BLACK);
            printf("\n %s\n", notif.message);
            effacerEcranAvecAttenteEntree();
            found = 1;
            break;
        }
    }

    if (!found) {
        changerCouleur(RED); // Couleur rouge pour l'erreur
        printf("Aucune notification trouvEe pour ce CNE.\n");
        changerCouleur(BLACK); // Réinitialiser la couleur
    }

    fclose(f);  // Fermer le fichier
}

void affichercours() {
    char module[200], niveau[50];
    char file[50];
    char c;
    FILE *m;

    while (1) {  // Boucle pour demander tant que le fichier n'existe pas
        changerCouleur(BLUE);
        printf("\n\n\n\t\t\t\tEntrer votre cours de niveau : ");
        changerCouleur(GREEN);
        printf("\n\t\t\t\t!! Exemple : cours_cp1 !!\n");
        changerCouleur(BLACK);
        scanf(" %[^\n]s", niveau); // Lecture de la saisie de l'utilisateur

        // Créer le nom du fichier en fonction du niveau
        sprintf(file, "%s.txt", niveau);
        changerCouleur(WHITE);
            effacerEcranAvecAttenteEntree();
           changerCouleur(BLACK);



        // Tenter d'ouvrir le fichier
        m = fopen(file, "r");

        if (m == NULL) {  // Si le fichier n'existe pas
            changerCouleur(RED);
            printf("\n\t\t\tLe format du cours n'est pas valide ou le fichier n'existe pas. Essayez a nouveau.\n");
            changerCouleur(WHITE);
            effacerEcranAvecAttenteEntree();
           changerCouleur(BLACK);
            continue;  // Demander à nouveau un niveau valide
        } else {
            break;  // Si le fichier existe, sortir de la boucle
        }
    }

    changerCouleur(WHITE);
    effacerEcranAvecAttenteEntree();
    changerCouleur(MAGENTA);

    // Affichage de l'encadré
    printf("\n\t\t\t\t\t***************************************\n");
    printf("\t\t\t\t\t**                                   **\n");
    printf("\t\t\t\t\t**                                   **\n");
    printf("\t\t\t\t\t**         === C O U R S ===         **\n");
    printf("\t\t\t\t\t**                                   **\n");
    printf("\t\t\t\t\t**                                   **\n");
    printf("\t\t\t\t\t**                                   **\n");
    printf("\t\t\t\t\t***************************************\n");

    changerCouleur(WHITE);
    effacerEcranAvecAttenteEntree();
    changerCouleur(BLACK);

    // Lecture et affichage du contenu du fichier
    while ((c = fgetc(m)) != EOF) {
        printf("%c", c);
    }

    fclose(m);  // Fermer le fichier après utilisation
}




void staffadministration(){

FILE *f=fopen("staff administratif.txt","r");
if(f==NULL){
    printf("error");
    exit(1);
}
char c;
while((c=fgetc(f))!=EOF){
    printf("%c",c);
}

fclose(f);
}







void print_ensah_line(int taille) {
    // Décalage vertical pour centrer
    for (int i = 0; i < 5; i++) {
        printf("\n");
    }

    // Affiche le mot ENSAH avec des espaces pour simuler un zoom
    for (int i = 0; i < 7; i++) {  // Nombre de lignes fixes
        for (int j = 0; j < taille; j++) {
            printf("\t");  // Décalage horizontal pour zoom
        }

        // Changer la couleur selon la ligne
        switch (i) {
            case 0:
                changerCouleur(MAGENTA);
                printf("******   **     **  *******    *********  **     **\n");
                break;
            case 1:
                changerCouleur(BLUE);
                printf("**       ***    **  **         **     **  **     **\n");
                break;
            case 2:
                changerCouleur(CYAN);
                printf("**       ****   **  **         **     **  **     **\n");
                break;
            case 3:
                changerCouleur(RED);
                 printf("******   ** **  **  ********   *********  *********\n");
                break;
            case 4:
                changerCouleur(GREEN);
                 printf("**       **  ** **        **   **     **  **     **\n");
                break;
            case 5:
                changerCouleur(YELLOW);
                 printf("**       **   ****        **   **     **  **     **\n");
                break;
            case 6:
                changerCouleur(BLACK);
                printf("******   **    ***  ********   **     **  **     **\n");
                break;
        }
    }

    // Réinitialiser la couleur
    changerCouleur(WHITE);
}


int main() {
    config_console();
    int taille = 1;         // Taille initiale
    int directionTaille = 1; // Direction du changement de taille (1 pour grandir, -1 pour rétrécir)
    int maxTaille = 10;      // Taille maximale
    int minTaille = 1;       // Taille minimale

    while (1) {
        effacerEcran();           // Efface l'écran pour un affichage propre
        print_ensah_line(taille); // Affiche ENSah avec effet de zoom
      Sleep(200);               // Pause pour ralentir l'animation

        // Modifie la taille
        taille += directionTaille;

        // Change la direction quand les limites sont atteintes
        if (taille >= maxTaille || taille <= minTaille) {
            directionTaille *= -1; // Inverser la direction de la taille (grandir ou rétrécir)
            break;
        }
    }

    // Après l'animation, afficher le menu principal
    afficherMenuPrincipal();
    return 0;
}

