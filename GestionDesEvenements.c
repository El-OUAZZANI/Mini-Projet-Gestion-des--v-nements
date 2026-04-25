#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_EVENTS 100
#define MAX_FACTURES 100
typedef struct{
char nom_plat[21]; 
}nom_plat ;
typedef struct {
char  nom_type[20] ; // nom de type du plat
nom_plat *plat ; // pointeur qui pointe dans un tableau qui contient les noms des plats           
int nombre_plat ; // nombre de plat(nombre de case de char *plat ) ----> nombre de plats
int *prix; // pointeur qui pointe sur un tableau de int dont chaque case contient le prix de chaque plat
}type_plat ;
typedef struct{
    type_plat *type; // pointeur de type : type_plat dont il pointe sur un tableau de de type : type_plat
    int nombre_type ; // nombre de type: type_plat
}plat;
   typedef struct{
      char nom_plat[21];
      int prix ;
    }plat_client ;
typedef struct{
    char nom_ressource[21] ;
    int prix ; // prix de chaque unite de ressource
    int quantite ;
    }ressource_client ;
typedef struct{
    char nom_evenement[21];
    ressource_client *ressource ;
    int nombre_ressource ; 

    int *type_plat ; // tableau qui contient les positions des types de plats reserve
    
    int nombre_type_plat ; // variable qui contient le nombre de type de plat reserver

    }reservation ;
    
typedef struct{
 reservation *res ;
 char id[21] ;
 char nom_complet[51] ;
}client ;
typedef struct{
    client *cl ;
    int nbr_client ;
    }ensemble_client ;
typedef struct{ //structure qui conserve le nom de chaque ressource et son prix
    char nom_outil[21];
    int prix ;
    }outil ;
typedef struct{       //structure qui contient un pointeur de type outil qui pointe vers un tableau pour stocker tous les ressources       
    outil *moyen ;
    int nbr_ressource ; 
    }ressource ;
typedef struct{
        char nom_type_eve[21] ; //tableau qui stocke le nom de type d'evenment
        char *id_client ; //tableau qui stocke les id des clients qui ont reserve le meme type d'evenement
        int prix_eve ; // une variable qui contient le prix du type d'evenement
    }evenement ; 
typedef struct {
    evenement *type_evenement ; //pointeur de type evenement
    int nbr_type_evenement ; // variable de type int qui stocke nombre de type d'evenement
}ensemble_eve ;

typedef struct {
    int id; 
    char titre[50]; 
    char type[30];
    char date[20]; 
    int personnel; 
    int equipment; 
    int fournitures; 
    int is_active; 
} Event;

 typedef struct { int id; char client[50];
  char evenement[50];
   float montant_total;
    int is_paid;
     }Facture;
void supression_saute(char tab[] , int taille){ // fonction qui afficher un caractere sans \n
    int a ;
    for(a=0 ; a < taille ; a++){
        if(   tab[a] != '\n'  &&  tab[a]  != '\0'    ){
           printf("%c",tab[a]) ;
        }
        else
        break ;
    }
    

 } int comparaison(char tab1[] , char tab2[] , int taille){ // cette fonction permet de comparer deux chaines de caracters a partir de rendre tous les caracters en miniscule, apres 
            int a ;
            for(a = 0 ; a < taille ; a++){ // boucle pour la comparaison
            tab1[a] = tolower(tab1[a]);
            tab2[a] = tolower(tab2[a]);}           
            if(strcmp(tab1,tab2) == 0)     // condition si les deux tableaux sont identiques
            return 1 ; // retourne 1 si oui
            else{
            return 0 ;  // retourn 0 si non
            }

             }
    int consultation_ressource(ressource *P){
        int a ;
        if(P == NULL){
        printf("\n    Aucun ressource trouve ! \n\n") ; 
        return 0 ; }
        printf("\n\n\tRessources disponible:\n\n");
        for (a = 0 ; a < P->nbr_ressource ; a++) {
            printf("%d-",a+1);
            supression_saute(P->moyen[a].nom_outil , 21) ;
            printf("  prix : %d DHS",P->moyen[a].prix);

            printf("\n");
        }
        printf("\n\n");

    }
    ressource * ajouter_ressource(ressource *P){ //fonction pour ajouter une ressource
    char tab[21] ;
    int i, a , prix  ;
    if(P == NULL){
        P = malloc(sizeof(ressource)) ;
        P->moyen = malloc(sizeof(outil)) ;
        P->nbr_ressource = 1 ;
    }else {
        P->nbr_ressource ++ ;
        P->moyen = realloc(P->moyen , P->nbr_ressource * sizeof(outil));
    }
    printf("Entrez le nom de ressource :\n");
    do{
        i = 0 ; 
    fflush(stdin) ;
    fgets(tab , 21 , stdin ) ;
    for(a = 0 ; a < P->nbr_ressource - 1 ; a++){
     i = comparaison(P->moyen[a].nom_outil , tab , 21) ;

    } if(i) printf("Nom de ressource existe deja !\n\n");
    }while(i) ;
    strcpy(P->moyen[P->nbr_ressource - 1].nom_outil , tab );
    printf("Entrez le prix de chaque unite:\n");
    do{
    scanf("%d",&prix);
    if(prix <=0) printf("Entrez le prix a nouveau:\n") ;
    }while(prix <=0);
    P->moyen[P->nbr_ressource-1].prix   =   prix ;

    return P ;
    }
     int consultation_type_evenement(ensemble_eve *P){
    int a ;
               if(P == NULL ){
                printf("\tAucun type evenement a ete trouve\n\n\n");
                return 0 ;
               }
               printf("\tTous les types d'evenements disponible :\n\n") ;
            for(a = 0 ; a < P->nbr_type_evenement ; a++){
                printf("  %d-",a+1);
               supression_saute(P->type_evenement[a].nom_type_eve , 21) ;
               printf("\n\n") ;
            }
            printf("\n");

               

}
 // Tableau pour stocker les evenements
Event events[MAX_EVENTS];
// Compteur pour suivre le nombre d'evenements crees
int cont = 0;


void creation() {
    // Vérifier si le nombre maximum d'evenements est atteint
    if (cont >= MAX_EVENTS) {
        printf("\nErreur : Nombre maximum d'evenements atteint.\n");
        return;
    }

    Event new_event; // creer un nouvel evenement
    new_event.id = cont + 1; // Attribuer un ID unique

    printf("\nTitre de l'evenement : ");
    getchar(); // Nettoyer le buffer d'entrée
    fgets(new_event.titre, sizeof(new_event.titre), stdin); // Saisir le titre
    new_event.titre[strcspn(new_event.titre, "\n")] = 0; // Supprimer le retour à la ligne

    printf("Type (Soutenance/conference/Anniversaire/etc.) : ");
    fgets(new_event.type, sizeof(new_event.type), stdin); // Saisir le type
    new_event.type[strcspn(new_event.type, "\n")] = 0;

    printf("Date  : ");
    fgets(new_event.date, sizeof(new_event.date), stdin); // Saisir la date
    new_event.date[strcspn(new_event.date, "\n")] = 0;

    printf("Nombre de personnel : ");
    scanf("%d", &new_event.personnel); // Saisir le nombre de personnel

    printf("Nombre d'equipment : ");
    scanf("%d", &new_event.equipment); // Saisir la quantité d'equipment

    printf("Nombre de fournitures : ");
    scanf("%d", &new_event.fournitures); // Saisir la quantité de fournitures

    new_event.is_active = 1; // Par défaut, l'evenement est actif

    events[cont++] = new_event; // Ajouter l'evenement au tableau
    printf("\nEvenement cree avec succes !\n");
}


void modification() {
    int id;
    printf("\nEntrez l'ID de l'evenement à modifier : ");
    scanf("%d", &id); // Saisir l'ID de l'evenement

    // Vérifier si l'ID est valide
    if (id < 1 || id > cont || events[id - 1].is_active == 0) {
        printf("\nErreur : Evenement introuvable.\n");
        return;
    }

    Event *event = &events[id - 1]; // Obtenir une référence à l'evenement

    printf("\nModification de l'evenement #%d\n", id);
    getchar(); // Nettoyer le buffer d'entrée

    printf("Titre actuel : %s | Nouveau titre : ", event->titre);
    fgets(event->titre, sizeof(event->titre), stdin); // Saisir le nouveau titre
    event->titre[strcspn(event->titre, "\n")] = 0;

    printf("Type actuel : %s | Nouveau type : ", event->type);
    fgets(event->type, sizeof(event->type), stdin); // Saisir le nouveau type
    event->type[strcspn(event->type, "\n")] = 0;

    printf("Date actuelle : %s | Nouvelle date : ", event->date);
    fgets(event->date, sizeof(event->date), stdin); // Saisir la nouvelle date
    event->date[strcspn(event->date, "\n")] = 0;

    printf("Nombre actuel de personnel : %d | Nouveau nombre : ", event->personnel);
    scanf("%d", &event->personnel); // Saisir le nouveau nombre de personnel

    printf("Nombre actuel d'equipment : %d | Nouveau nombre : ", event->equipment);
    scanf("%d", &event->equipment); // Saisir la nouvelle quantité d'equipment

    printf("Nombre actuel de fournitures : %d | Nouveau nombre : ", event->fournitures);
    scanf("%d", &event->fournitures); // Saisir la nouvelle quantité de fournitures

    printf("\nEvenement modifie avec succes !\n");
}


void annulation() {
    int id;
    printf("\nEntrez l'ID de l'evenement à annuler : ");
    scanf("%d", &id); 

    // Vérifier si l'ID est valide
    if (id < 1 || id > cont || events[id - 1].is_active == 0) {
        printf("\nErreur : Evènement introuvable.\n");
        return;
    }

    events[id - 1].is_active = 0; // Marquer l'evenement comme annulé
    printf("\nEvènement #%d annulé avec succes.\n", id);
}


void affichage(int show_active) {
    printf("\nListe des %s evenements :\n", show_active ? "evenements actifs" : "evenements passes");

    // Parcourir tous les evenements
    for (int i = 0; i < cont; i++) {
        // Afficher les evenements actifs ou annulés en fonction de show_active
        if ((show_active && events[i].is_active) || (!show_active && !events[i].is_active)) {
            printf("ID: %d | Titre: %s | Type: %s | Date: %s | Personnel: %d | Equipements: %d | Fournitures: %d\n",
                   events[i].id, events[i].titre, events[i].type, events[i].date, events[i].personnel,
                   events[i].equipment, events[i].fournitures);
        }
    }
}
           
ensemble_client * ajouter_client(ensemble_client *P){ // fonction pour ajouter un nouveau client
    int i = 0 , a ;
    char champ[51] ;
    if(P == NULL){  // condition si le client soit reserve a la premiere fois
    
     P = malloc(sizeof(ensemble_client)) ;
     P->cl = malloc(sizeof(client));
     P->cl->res = NULL ; // historique de reservation = NULL 
     printf("Entrez le nom complet du client:\n");
     fflush(stdin);                               // fonction pour vider le buffer
     fgets(P->cl->nom_complet , 51 , stdin);
     printf("Entrez l'id du client:\n");
     fflush(stdin) ;
     fgets(P->cl->id , 21 , stdin);
        P->nbr_client = 1  ;
    } else {             // condition si le client va etre ajouter a la n ieme fois
        P->nbr_client ++ ;
        P->cl = realloc(P->cl, (P->nbr_client) * sizeof(client)) ;
         printf("Entrez le nom complet du client:\n");
         
         fflush(stdin);
         fgets(P->cl[(P->nbr_client) - 1].nom_complet , 51 , stdin);
         do{
         printf("Entrez l'id du client:\n");
         fflush(stdin) ;
         fgets(champ,21,stdin);
         // fgets(P->cl[(P->nbr_client) - 1].id , 21 , stdin);

         for(a = 0, i = 0 ; a < P->nbr_client - 1 ; a++  ){ // verification que l'id entre est unique, P->nbr_client - 1 car on a incremente nbr client
          if(strcmp(P->cl[a].id,champ ) == 0 ){
          i++ ;
          printf("Id existe deja, entrez a nouveau!\n") ;
          break ; }
         }
         }while(i) ; // si i=1 alors l'id existe
         strcpy( P->cl[(P->nbr_client) - 1].id , champ ) ;
         P->cl[(P->nbr_client) - 1].res = NULL ; // historique de reservation = NULL
         }
        return P ;

} int consulation_client(ensemble_client *P){
    int a ;
        if(P == NULL){
        printf("Aucun client a ete trouve\n");
        return 0 ; }
        printf("\tClients disponilbes:\n\n\n");
        for(a=0 ; a < P->nbr_client ; a++){
            fflush(stdin);
            printf("%d-",a+1) ;
            supression_saute(P->cl[a].nom_complet , 51) ;
            
            fflush(stdin) ;
            printf(" --> id :") ;
            supression_saute(P->cl[a].id , 21) ;
           
            printf("\n") ;
        } printf("\n\n") ;
}
 ensemble_client * modification_client(ensemble_client *P){
    int a,b,i,c ; 
    char champ[21] ;
      if(P == NULL){
        printf("\tAucun client a ete trouve!:\n");
        return (0) ;
      }
    consulation_client(P) ; 
    printf("Entrez la position de client que vous voulez modifier:\n");
    do{
    scanf("%d",&a);
    if(a <= 0 || a > P->nbr_client)
    printf("Position invalide, entrez a nouveau:\n");
    }while(a <= 0 || a > P->nbr_client);
    do{
        printf("\tEntrez un choix pour une opperation:\n");
     printf("1-Changer nom\n");
     printf("2-Changer id\n");
     printf("3-Changer nom et id \n");
     
     scanf("%d",&i);
    }while(i<=0 || i > 3) ;
    if(i == 1 || i == 3 ){
    for( b = 0 ; b < 21  ; b++){ // boucle pour remplir le tableau en'\0'
       P->cl[a-1].nom_complet[b] = '\0' ;
       
    } 
    printf("Entrez le nouveau nom:\n");
    fflush(stdin);
    fgets(P->cl[a-1].nom_complet, 21 , stdin) ; 
      } if( i == 2 || i == 3){
         for( b = 0 ; b < 21  ; b++){ // boucle pour remplir le tableau en'\0'
       P->cl[a-1].id[b] = '\0' ;
       
    } 
    do{
        printf("Entrez l'id:\n") ;
        i=0 ;
    fflush(stdin); // vider le buffer
    fgets(P->cl[a-1].id,21,stdin); // lecture de l'id
    strcpy(champ, P->cl[a-1].id) ; // conservation du id entre dans un tableau nomme champ
    for(c = 0 ; c < P->nbr_client ; c++){ // boucle pour chercher si l'id entree n'est pas identique  avec un existant
        if(c == (a-1)) // condition si l'indice du client a modifier est identique a l'itteration arrive dans la boucle
        continue ; // stope la boucle puis incrementation
     if(strcmp(P->cl[c].id , champ) == 0 ){ 
     i++ ;
     printf("Un client possede le meme id , entrez a nouveau :\n") ;
     break ;}
     } 
    
     
    }while(i);
      }

    return P ;
} ensemble_client * supression_client(ensemble_client *P){
    int a,b ;
              if(P == NULL){
              printf("\t\tAucun client est disponible pour supprimer !\n");
              return(0) ;
              }
               
              consulation_client(P) ;
               do{
                printf("Entrez la position de client a supprimer:\n") ;
                scanf("%d",&a);
                if(a<=0 || a > P->nbr_client)
                printf("\tPosition invalide\n");
              }while(a<=0 || a > P->nbr_client);
              if( P->nbr_client == 1){   // condition si un seul client unique existe
                free(P) ; 
                P = NULL ;
              }else{
              P->nbr_client -- ;
              for(b = a-1 ; b < P->nbr_client ; b++){
                P->cl[a-1] = P->cl[a] ;
                } P->cl = realloc(P->cl , P->nbr_client * sizeof(client));

              }
              printf("\n\n\tClient supprime avec succes\n\n") ;
return P;
} 
 
plat * cree_type_plat(plat *P){ // fonction pour cree des nouveaux types de plats par exemple dessert
char tab[21]; int c, i = 0;
printf("Entrez le nouveau type de plat a ajouter, max 20 carcteres:\n");
if(P == NULL){
P = malloc(sizeof(plat)) ;
P->type = malloc(sizeof(type_plat)); // utilisation de malloc pour allouer dynamiquement a la premiere fois
P->type[0].nombre_plat = 0;
P->nombre_type = 1 ;

}else{ // condition si le type soit allouer a la n ieme fois
  P->nombre_type ++ ;
  P->type = realloc(P->type , (P->nombre_type) * sizeof(type_plat)); // reallocation de type plat
  P->type[(P->nombre_type) - 1 ].nombre_plat = 0; // initialisation de nombre plat a 0
  }
  fflush(stdin); // fonction pour vider le buffer
   do{
    i = 0;
    fgets(tab,21,stdin);
  for(int a = 0 ; a < P->nombre_type - 1 ; a++){
    i = comparaison(P->type[a].nom_type, tab , 20) ;
    if(i){
        printf("Type existe deja. Entrez a nouveau:\n");
        break;
    }  }  
  }while(i) ;
  strcpy(P->type[P->nombre_type - 1].nom_type, tab) ;
  
  return P;
}
int consultation_plat(plat *P){
   int a,b;
   if( P == NULL){
    printf("\tAucun type de plat a ete trouve !\n\n\n"); 
    return(0) ;                                       // arrete de fonction au cas si aucun plat a ete trouve
   } for(a=0 ; a < P->nombre_type ; a++){

    printf("  %d-",a+1);
    supression_saute(P->type[a].nom_type , 21 ) ; 
    printf("\n");
    if(P->type[a].nombre_plat == 0)
    printf("\t(vide)\n\n\n");
    else{
    for(b=0 ; b < P->type[a].nombre_plat ; b++){ // boucle pour afficher les plats
        printf("\t%d-",b+1);
        supression_saute(P->type[a].plat[b].nom_plat , 21 ) ; // appel fonction d'anffichage
        
        printf(": %d DHS\n\n\n",P->type[a].prix[b]);
    } } 
   }

}
plat * ajouter_plat(plat *P){
    if(P == NULL){
        printf("Aucun type a ete trouve pour ajouter un plat\n"); // condition si les types des plats sont vides
        return 0;
    }
    char tab[21];
    int a , c , i = 0 ;
      consultation_plat(P); 
    printf ("Choisir un type de plat :");
    fflush(stdin); // fonction pour vider le buffer

    do{
    scanf("%d",&c);
     if(c < P->nombre_type || c > P->nombre_type) printf("Numero invalide. Entrez a nouveau: ");
    }while(c < P->nombre_type || c > P->nombre_type);
    c -- ;
    do{
    ( P->type[c].nombre_plat ) ++ ; // incrementation de nombre de plat
    if((P->type[c].nombre_plat ) == 1){ // condition si le plat va etre allouer a la premiere fois
    P->type[c].plat = malloc(sizeof(nom_plat)); // allocation d'une structure qui se compose de nom de plat
    P->type[c].prix = malloc(sizeof(int)) ; // allocation de tableau de type int  qui se compose de prix de chaque plat
    }
    else { // condition si le plat va etre allouer a la n ieme fois
    P->type[c].plat = realloc(P->type[c].plat , (P->type[c].nombre_plat) * sizeof(nom_plat) ) ; // reallouer dynamiquement le tableu de plats , P->type[c].nombre_plat indique le nombre des plat, par exemple si (P->type[c].nombre_plat) = 2, le stockage va etre 2 ---> enfin 2 * sizeof(nom_plat) ---> 2 structures vont etre alloue
    P->type[c].prix = realloc(P->type[c].prix,(P->type[c].nombre_plat) * sizeof(int) ); // meme cas , mais pour prix
    }
    printf ("Entrez le nom de plat pour ajouter :\n");
    fflush(stdin); //fonction pour vider le buffer 
    scanf("%s",P->type[c].plat[ (P->type[c].nombre_plat) - 1 ].nom_plat) ;
    //fgets( P->type[c].plat[ (P->type[c].nombre_plat) - 1 ].nom_plat  , 21 , stdin ) ; // l'utilisateur entre le nom du plat en indice (P->type[c]->nombre_plat) - 1)  cela signifie l'indice du tableau  "plat" qui pointe vers des tructures, par exemple si le nombre de plat = 1, cel implique -> plat[(1 - 1) ] -> indice 0
    printf("Entrez le prix du plat:\n");
    do{
    scanf("%d",&(P->type[c].prix[ ((P->type[c].nombre_plat) - 1) ]) );
    if((P->type[c].prix[ ((P->type[c].nombre_plat) - 1) ]) <= 0 )
    printf("Entrez un prix raisonable!  \n") ;
    }while( (P->type[c].prix[ ((P->type[c].nombre_plat) - 1) ]) <= 0) ;
    printf("Entrez 1 pour ajouter un autre plat sinon quelqonque :\n");
    scanf("%d",&a);
    }while(a == 1) ;
     // printf ("\tLa mise ajour apres l'ajout du plat :\n"); //fflush(stdin); printf("\t%s\n", &( P->type[c].nom_type) ); // pour afficher le nom du type for(a = 0 ; a < (P->type[c].nombre_plat) ; a++ ) { // boucle pour afficher tous les plats du meme type fflush(stdin); printf("%d-%s\n",a+1,&(P->type[c].plat[ (a) * 21 ] )); }

    return P ;
} 

plat* modification_plat(plat *P){
    int a,b,i,j;

      if( P == NULL){ // condition pour verifier si le nombre de type n'est pas vide
        printf("Aucun type trouve\n");
        return 0 ;}
        consultation_plat(P); // appel de la fonction consultation plat pour afficher tous les types de plats avec les plats
        printf("\tchoisir le numero de type qui contient le plat que vous voulez modifier  :\n");
        do{
            scanf("%d",&a); // ici l'utilisateur entre la position de type
        }while(a<=0 || a > (P->nombre_type));
        if((P->type[a-1].nombre_plat) == 0 ){ // condition pour verifier si le nombre de plat de meme type est vide, a-1 pour l'indice care a contient la position de type
            printf("Les plats de ce type est vide \n");
            return(0);
        }
        printf("\t\t%s\n",P-> type[a-1].nom_type); // Pour afficher un grand titre de type insere par l'utilisateur
        if(P->type[a-1].nombre_plat == 0) // condition si le nombre de plat est vide
        printf("(vide) \n");
        else{
        for(b = 0 ; b < P->type[a-1].nombre_plat ; b++){   // Boucle pour afficher tous les plats du type insere 
        printf("\t%d-",b+1);
         supression_saute(P->type[a-1].plat[b].nom_plat , 21 ) ;
        //affichage_sans_saute( P->type[a-1].plat[b].nom_plat ) ;
        printf(" : %d DHS\n", P->type[a-1].prix[b] ) ;
        printf("\n");
    } 
     }

        do{
            printf("Entrez la position de plat a modifier :\n");
           scanf("%d",&i);
        }while(i <= 0 || i > (P->type[a-1].nombre_plat) );

        for( j = 0 ; j <= 20 ; j++ ){ // cette boucle sert pour vider le nom du plat a partir de la remplir avec \0
            P->type[a-1].plat[i-1].nom_plat[j] = '\0';
        }
        printf("Entrez le nouveau nom de plat:\n");
        scanf("%s",P->type[a-1].plat[i-1].nom_plat);
         // fgets( P->type[a-1].plat[i-1].nom_plat , 21 , stdin ); // (i-1)  est l'indice de plat choisit
        printf("Entrez le nouveau prix: \n");
        do{
        scanf("%d",&(P->type[a-1].prix[i-1]));
        if ( (P->type[a-1].prix[i-1]) <= 0)
        printf("Entrez un prix raisonable !\n") ;
        }while((P->type[a-1].prix[i-1]) <= 0 ) ;

        return P ;

} plat* supression_plat(plat *P){
    int a,b,i,j;
    if(P->nombre_type == 0){
        printf("Aucun type de plat a ete trouve:\n");
        return(0); }
        printf("Entrez la position de type du plat dont ou se situe le plat pour supprimer:\n");
        consultation_plat(P);
        do{
        scanf("%d",&a);
        if(a<=0 || a>(P->nombre_type) )
        printf("Numero de type invalide, entrez a nouveau:\n");
        }while(a<=0 || a > (P->nombre_type) );
        if(P->type[a-1].nombre_plat == 0){
        printf("liste des plats de cet type est vide\n");
        return(0);}
        if(P->type[a-1].nombre_plat == 1){ // condition si il existe 1 seul plat, cela vas permet d'utiliser la fonction free pour liber
        free(P->type[a-1].plat->nom_plat) ;
        free(P->type[a-1].plat);
        free(P->type[a-1].prix);
        P->type[a-1].nombre_plat -- ;
        printf("Le seul plat a ete suprimme en succes \n");
        return(0);
        }
        do{
            printf("Entrez la position de plat pour supprimer:\n");
            scanf("%d",&i);
        }while(i<=0 || i > P->type[a-1].nombre_plat);
        
        if( i == P->type[a-1].nombre_plat){ // condition si la position de plat se situe dans la fin de tableau *Plat
            P->type[a-1].nombre_plat -- ;
            P->type[a-1].plat = realloc(P->type[a-1].plat, (P->type[a-1].nombre_plat )*sizeof(nom_plat)) ; // utilisation de realloc pour diminuer la taille
            P->type[a-1].prix = realloc( P->type[a-1].prix , (P->type[a-1].nombre_plat) * sizeof(int) ) ;
        } else { // condition si la position de plat se situe au premier ou en milieu de *Plat

            for( j = i - 1 ; j < P->type[a-1].nombre_plat ; j++){ //
                P->type[a-1].plat[j] = P->type[a-1].plat[j + 1];
                P->type[a-1].prix[j] = P->type[a-1].prix[j + 1];
                            }
            P->type[a-1].nombre_plat -- ;
            P->type[a-1].plat = realloc( P->type[a-1].plat , ( P->type[a-1].nombre_plat ) * sizeof(nom_plat)  ) ;
            P->type[a-1].prix = realloc( P->type[a-1].prix , (P->type[a-1].nombre_plat) * sizeof(int) ) ;
        } 

            printf("Les plats apres la mise a jour:\n");
        return P ; 
        }

int reserver_evenement(ensemble_client *client , ressource *ressource , ensemble_eve *evenement, plat *plat){
    
    int a = 1, p_client, p_eve, p_ressource ;

    int taille_res, b , qu_ressource ;

    if(client == NULL || ressource == NULL || evenement == NULL || plat == NULL){
       if(client == NULL) 
       printf("Veuillez entrez au moins un client pour resrver\n\n");
       if(ressource == NULL)
       printf("Veuillez entrez au moins une ressource pour reserver\n\n");
       if(evenement == NULL)
       printf("Veuillez entrez au moins un type d'evenement\n\n");
       if(plat == NULL)
       printf("Veuillez entrez au moins un type de plat\n\n");
       return 0 ;
    }
consulation_client(client) ;
       printf("Veuillez saisir la position du client pour reserver: ");
       do{
        scanf("%d",&p_client);
        if(( client-> nbr_client ) < p_client || client -> nbr_client > p_client )
        printf("\n\tPosition invalide. Entrez a nouveau:\n\n");
       }while((client -> nbr_client) < p_client || (client -> nbr_client) > p_client);
consultation_type_evenement( evenement) ;
       printf("Entrez la position de type d'evenement: ");
       do{
        scanf("%d",&p_eve); // position d'evenement choisit
        if( p_eve < (evenement -> nbr_type_evenement)  || p_eve > (evenement->nbr_type_evenement)  )
       printf("Position invalide. Entrez a nouveau:\n");
       }while(p_eve < (evenement -> nbr_type_evenement) || p_eve > (evenement -> nbr_type_evenement)  ) ;
       
       client->cl[p_client - 1 ].res = malloc(sizeof(reservation));
       
       strcpy( client ->cl[p_client - 1].res->nom_evenement , evenement->type_evenement[p_eve - 1].nom_type_eve ) ;



       printf("Entrez la position de type de ressource puis la quantite: ");
       client->cl[p_client - 1 ].res = malloc( sizeof (reservation) );
       client->cl[p_client - 1 ].res-> ressource = malloc(sizeof(ressource_client)); // allocation donnes de ressource pour la premiere fois
       // a = 1
    do{  
        consultation_ressource( ressource ) ; // affichage des ressources disponible

        do{
        scanf("%d",&p_ressource);
        if(p_ressource < (ressource -> nbr_ressource) || p_ressource > (ressource->nbr_ressource) )
        printf("Position invalide. Entrez a nouveau:\n") ;

        }while(p_ressource < ( ressource -> nbr_ressource) || p_ressource > ( ressource -> nbr_ressource) );

        strcpy( client->cl[p_client - 1].res[a - 1].ressource->nom_ressource , ressource->moyen[p_ressource - 1].nom_outil ) ; // clonage de nom de ressource sur la structure de client
       


        do{
                printf("Entrez la quantite:\n") ;
                scanf("%d",&qu_ressource) ;
                if(qu_ressource <= 0)
                printf("     Nombre invalide, Entrez a nouveau !\n");
        }while(qu_ressource <= 0 );

            client->cl[p_client - 1].res->ressource[a - 1].quantite = qu_ressource ;
            client->cl[p_client - 1].res->ressource[a - 1].prix = ressource->moyen[p_ressource - 1].prix ;
             

        printf("Entrez 1 pour ajouter une autre ressource sinon quelquonque: ");
        scanf("%d",&b);

        if(b == 1){ 
            a++ ;
        client->cl[p_client - 1].res->ressource  = realloc(client->cl[p_client - 1].res->ressource, a * sizeof(ressource_client)  );  // reallocation de tableau qui contient la quantité de chaque ressource
        }

       }while(b == 1);  
       

       return 0 ;
    }
    Facture factures[MAX_FACTURES]; // Tableau pour stocker les factures
 int facture_count = 0; // Compteur pour les factures

// Fonction pour ajouter une facture 
void ajouter_facture() 
{ 
if (facture_count >= MAX_FACTURES) { printf("\nErreur : Limite de factures atteinte.\n");
 return; }
Facture *new_facture = &factures[facture_count++];
new_facture->id = facture_count;

printf("Nom du client : ");
scanf(" %[^]s", new_facture->client);
printf("Nom de l'événement : ");
scanf(" %[^]s", new_facture->evenement);
printf("Montant total : ");
scanf("%f", &new_facture->montant_total);

new_facture->is_paid = 0; // Par défaut, la facture n'est pas payée

printf("\nFacture ajoutée avec succès !\n");
}

// Fonction pour afficher les factures
 void afficher_factures() { 
    printf("\nListe des factures :\n"); 
    for (int i = 0; i < facture_count; i++) {
         printf("ID: %d | Client: %s | Événement: %s | Montant: %.2f DH | Status: %s\n", factures[i].id, factures[i].client, factures[i].evenement, factures[i].montant_total, factures[i].is_paid ? "Payée" : "Non payée");  
         } 
         }

// Fonction pour marquer une facture comme payée
 void payer_facture() { 
    int id; printf("\nEntrez l'ID de la facture à payer : "); 
    scanf("%d", &id);

if (id < 1 || id > facture_count) {
    printf("\nErreur : Facture introuvable.\n");
    return;
}

if (factures[id - 1].is_paid) {
    printf("\nCette facture est déjà payée.\n");
    return;
}

factures[id - 1].is_paid = 1;
printf("\nFacture ID %d marquée comme payée avec succès.\n", id);
}
    
int main(){
     plat *Plat ;
     ensemble_client *Client  ;
     ensemble_eve *eve ;
     ressource *res ;
     res = NULL ;
     eve = NULL ;
     Client = NULL ;
     Plat = NULL;
     int a,b;
     int choice;
     int choix;
     do {
    printf("\n\t\t  Menu : \n\n");
    printf("\t0-Sortir\n");
    printf("\t1-Reserver un evenement\n");
    printf("\t2-Gestion plat\n");
    printf("\t3-Gestion d'evenement\n");
    printf("\t4-Gestion client\n");
    printf("\t5-Gestion ressources\n");
    printf("\t6-Factures\n");

    do {
        printf("\nVotre choix : ");
        scanf("%d", &a);
        if (a < 0 || a > 6)
            printf("Numero invalide, entrez a nouveau:\n");
    } while (a < 0 || a > 6);

    switch (a) {
        case 0:
            exit(0);
            break;

        case 1:
            printf("\tReservation d'evenement\n\n");
            do {
                printf("   0-Retour\n");
                printf("   1-Reserver un evenement\n");
                printf("   2-Consultation des evenements en cours\n");
                printf("   3-Annuller un evenement\n");

                do {
                    printf("\nVotre choix : ");
                    scanf("%d", &b);
                    if (b < 0 || b > 3)
                        printf("Numero invalide ! \n");
                } while (b < 0 || b > 3);

                switch (b) {
                    case 1:
                        reserver_evenement(Client, res, eve, Plat);
                        break;
                    case 2:
                        printf("Consultation des evenements en cours (fonctionnalite a implementer).\n");
                        break;
                    case 3:
                        printf("Annulation d'un evenement (fonctionnalite a implementer).\n");
                        break;
                }

            } while (b != 0);
            break;

        case 2:
            printf("\tGestion plats:\n\n");
            do {
                printf("   0-Retour\n");
                printf("   1-Cree type de plat\n");
                printf("   2-Ajouter un plat \n");
                printf("   3-Modification plat\n");
                printf("   4-Supression plat\n");
                printf("   5-Consultation des plats\n");

                do {
                    printf("\nVotre choix : ");
                    scanf("%d", &b);
                    if (b < 0 || b > 5)
                        printf("Numero invalide ! \n");
                } while (b < 0 || b > 5);

                switch (b) {
                    case 1:
                        Plat = cree_type_plat(Plat);
                        break;
                    case 2:
                        Plat = ajouter_plat(Plat);
                        break;
                    case 3:
                        Plat = modification_plat(Plat);
                        break;
                    case 4:
                        Plat = supression_plat(Plat);
                        break;
                    case 5:
                        consultation_plat(Plat);
                        break;
                }

            } while (b != 0);
            break;

        case 3:
           printf("Gestion des evenements :\n");
            do {
                printf("\n--- Gestion des Evenements ---\n");
                printf("1. creer un evenement\n");
                printf("2. Modifier un evenement\n");
                printf("3. Annuler un evenement\n");
                printf("4. Consulter les evenements actifs\n");
                printf("5. Consulter les evenements passes\n");
                printf("0. Quitter\n");

                printf("Votre choix : ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        creation();
                        break;
                    case 2:
                        modification();
                        break;
                    case 3:
                        annulation();
                        break;
                    case 4:
                        affichage(1);
                        break;
                    case 5:
                        affichage(0);
                        break;
                    case 0:
                        printf("\nRetour au menu principal.\n");
                        break;
                    default:
                        printf("\nChoix invalide, veuillez réessayer.\n");
                }

            } while (choice != 0);
            break; 

        case 4:
            printf("\tGestion client:\n\n");
            do {
                printf("   0-Retour\n");
                printf("   1-Ajouter un client\n");
                printf("   2-Consultation Clients\n");
                printf("   3-Modification Client\n");
                printf("   4-Supression Client\n");

                do {
                    printf("\nVotre choix : ");
                    scanf("%d", &b);
                    if (b < 0 || b > 4)
                        printf("Numero invalide ! \n");
                } while (b < 0 || b > 4);

                switch (b) {
                    case 1:
                        Client = ajouter_client(Client);
                        break;
                    case 2:
                        consulation_client(Client);
                        break;
                    case 3:
                        Client = modification_client(Client);
                        break;
                    case 4:
                        Client = supression_client(Client);
                        break;
                }

            } while (b != 0);
            break;

        case 5:
            printf("Gestion des ressources:\n");
            do {
                printf("0-Retour:\n");
                printf("1-Ajouter une ressource:\n");
                printf("2-Consultation des ressources:\n");

                do {
                    printf("\nVotre choix : ");
                    scanf("%d", &b);
                    if (b < 0 || b > 2)
                        printf("Numero invalide !, Entrez a nouveau:\n");
                } while (b < 0 || b > 2);

                switch (b) {
                    case 1:
                        res = ajouter_ressource(res);
                        break;
                    case 2:
                        consultation_ressource(res);
                        break;
                }

            } while (b != 0);
            break;
        case 6:
        do {
    printf("gestion des Facturation et Paiements:\n");
    printf("1. Ajouter une facture\n");
    printf("2. Afficher les factures\n");
    printf("3. Payer une facture\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            ajouter_facture();
            break;
        case 2:
            afficher_factures();
            break;
        case 3:
            payer_facture();
            break;
        case 0:
            printf("\nAu revoir !\n");
            break;
        default:
            printf("\nChoix invalide, veuillez réessayer.\n");
    }
} while (choix != 0);
        
    }

} while (1);

return 0;
     }
