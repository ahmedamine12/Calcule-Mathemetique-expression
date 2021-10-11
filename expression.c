#include <stdio.h>
#include <stdlib.h>
#include "expression.h"

 /*******************************************************************/
 /**  Nom de la fonction: est_operation
      Entree: un caractère
      Sortie: un entier
      Rôle de la fonction: elle fait le test sur un caractère et affirme
                           s'il est une opération ou non.
 **/

      int est_operation(char c)
      {
          if((c=='+')||(c=='-')||(c=='*')||(c=='/'))
            return ((int)1);
          return ((int)0);
      }


  /*******************************************************************/

 /**  Nom de la fonction: est_chiffre
      Entree: un caractère
      Sortie: un entier
      Rôle de la fonction: elle fait le test sur un caractère et affirme
                           s'il est un chiffre ou non.
 **/

    int est_chiffre(char c)
    {
        if((c>='0')&&(c<='9'))
            return ((int)1);
        return ((int)0);
    }

  /*******************************************************************/


  /**
      Nom de la fonction: char_equiv_int
      Entree: caractère
      Sortie: un entier
      Rôle de la fonction: cette fonction permet de faire la transformation
                           d'un chiffre de type char en un entier.
  **/

       int char_equiv_int(char c)
       {
        return ((int)(c-'0')); /** pas besoin de test sur la validité **/
       }

 /*******************************************************************/


 /**
     Nom de la fonction: evaluation_operat
     Entree: deux opérandes de type float
             operation de type char
     Sortie: le résultat de type float
     Rôle de la fonction: cette fonction permet l'évaluation d'une
                          opération arithmétique entre deux opérandes.
 **/

     float evaluation_operat(float operd1, float operd2,char operat)
     {
         switch(operat) /** selon le type de l'opération **/
         {
             case '+':return ((float)(operd1+operd2)); /** addition **/
             case '-':return ((float)(operd1-operd2)); /** soustraction **/
             case '*':return ((float)(operd1*operd2)); /** produit **/
             case '/':return ((float)(operd1/operd2)); /** division **/
         }
     }

 /******************************************************************/

 /**
      Nom de la fontion: creer_noeud
      Entree: variable de type Union (operation/nombre)
      Sortie: un pointeur sur le noeud créé
      Rôle de la fonction: cette fonction permet la creation
                           d'un noeud et de placer une operation
                           ou un nombre dans ce dernier
 **/
       Noeud *creer_noeud(Union elem)
       {
           Noeud *ne=(Noeud*)malloc(sizeof(Noeud));
           if(!ne) // si l'allocation n'a pas été faite
           {
               printf("erreur d'allocation"); // message d'erreur
               exit(0); // quitter le programme
           }
           if(est_operation(elem.operation)) // si elem est une operation
            ne->info.operation=elem.operation; // info du noeud sera une operation
           else                      // sinon
            ne->info.nombre=elem.nombre;    // info du noeud est un nombre

           ne->fdroit=ne->fgauche=NULL; // initialiser les fils par NULL
           return ((Noeud*)ne);  // retourner le noeud créé
       }

 /******************************************************************/

  /**
     Nom de la fonction: raser_arbre
     Entree: pointeur sur la racine de l'arbre
     Sortie: le pointeur NULL
     Rôle de la fonction: cette fonction permet de supprimer tous
                          les noeuds de l'arbre y compris la racine.
 **/
   Noeud *raser_arbre(Noeud *arbre)
   {
       if(arbre) /** si mon arbre existe **/
       {
           /** acceder au fils le plus à gauche **/
           arbre->fgauche=raser_arbre(arbre->fgauche);
           /** acceder au fils le plus à droite **/
           arbre->fdroit=raser_arbre(arbre->fdroit);
           /** liberer l'espace memoire occupé par le noeud **/
           free(arbre);
       }
       arbre=NULL;
       return ((Noeud*)arbre);
   }

 /*****************************************************************/


 /**  Nom de la fonction: afficher_noeud
      Entree: pointeur sur la racine de l'arbre
              un entier désignant le niveau du traitement
      sortie: les noeuds de l'arbre affichés horizontalement
      Rôle de la fonction: l'affichage graphique des
                           noeuds de l'arbre horizontalement. **/
    void afficher_noeud(Noeud *arbre,int niv_actuel)
    {
        int cmpt; // compteur
        if(arbre) // si mon arbre non NULL
        {
            /** j'accède au fils le plus à droite **/
            afficher_noeud(arbre->fdroit,niv_actuel+1);
            /** j'écris des tabulations autant que la différence entre
              niveau 0 et le niveau du noeud en cours de traitement **/
            for(cmpt=0;cmpt<niv_actuel;cmpt++)printf("\t");
            /** info du noeud peut être soit opération soit nombre **/
            if(!est_operation(arbre->info.operation))
                  printf("%.4f",arbre->info.nombre);
            else  printf("%c",arbre->info.operation);
            /** j'accède au fils le plus à gauche **/
            afficher_noeud(arbre->fgauche,niv_actuel+1);
        }
        printf("\n");
    }

/************************************************************************/

/**
     Nom de la fonction: affichage_arbre
     Entree: pointeur sur la racine d'un arbre
     Sortie: l'arbre affiché graphiquement
     Rôle de la fonction: il est bien clair ..!
**/
    void affichage_arbre(Noeud *arbre)
    {
        if(arbre) // mon arbre contient des elements
        {
            afficher_noeud(arbre,0);
            printf("\n\n");
        }
    }

/************************************************************************/

/**
     Nom de la fonction: eval_resultat
     Entree: pointeur sur la racine d'un arbre
     Sortie: un réel
     Rôle de la fonction: evaluer l'expression arithmétique stockée dans
                          l'arbre.
**/
   float eval_resultat(Noeud *arbre)
  {
     if(arbre) /** l'arbre contient des elements **/
     {
        if(!est_operation(arbre->info.operation)) /** le noeud est un nombre **/
            return ((float)arbre->info.nombre);
          /** sinon, retourner l'evaluation des valeurs de ses fils gauche et droit **/
        return ((float)evaluation_operat(eval_resultat(arbre->fgauche),
                                         eval_resultat(arbre->fdroit),
                                         arbre->info.operation));
     }
   return((float)0); /** 0 pour un noeud Null **/
  }

/**************************************************************************/

    char epurer_bl_tab()
    {
        char c;
        c=getchar();
        while(c==' '||c=='\t')c=getchar();
        return ((char)c);
    }

/**************************************************************************/


/** Nom de la fonction:
     Entree: les valeurs dans le buffer
     sortie: un caractere valide
     Rôle de la fonction: lu du buffer un caractere et teste s'il est valide **/
    char lire_du_buffer()
    {
        char car_lu;
        /** epuration des blancs et des tabs jusqu'à un caractere **/
        car_lu=epurer_bl_tab();
        /** si le caractere lu n'est pas un chiffre,point(.),
            operation ou bien retour chariot on retourne
            un charactere qui designe erreur 'choix arbitraire' **/
            if((!est_chiffre(car_lu))&&(!est_operation(car_lu))
                      &&(car_lu!='.')&&(car_lu!='\n'))
                return ((char)'e'); // e : erreur
       return ((char)car_lu); // le caractere valide
    }

/*************************************************************************/
   /**
       Nom de la fonction: inserer_dans_arbre
       Entrée: pointeur sur la racine de l'arbre
               valeur à inserer de type Union
       Sortie: pointeur sur l'arbre modifié
       Rôle de la fonction: cette fonction permet l'insertion d'une information dans l'arbre
   **/
  Noeud *inserer_dans_arbre(Noeud *arbre,Union val)
  {
      Noeud *arb_aide=arbre; /** variable de parcours **/
      Noeud *ne=creer_noeud(val); /** creation du noeud à inserer **/
      /** si mon arbre est NULL **/
      if(!arbre)return ((Noeud*)ne);
      /**
          si val est un nombre alors on l'insere comme le fils le plus a droit
          de la racine
      **/
        if(!est_operation(val.operation)) // val n'est pas une opération
        {
            while(arb_aide->fdroit)arb_aide=arb_aide->fdroit; // dernier fils droit
            arb_aide->fdroit=ne; // lier le noeud avec le noueud courant comme fils droit
        }
        else /** une operation alooors! **/
        {
            /**  si l'operation est un {+,-} l'arbre devient le sous arbre gauche
                 du nouveau noeud
             **/
            if((val.operation=='+')||(val.operation=='-'))
            {
                ne->fgauche=arbre;
                arbre=ne;
            }
            else /** il ne reste que le cas d'une: {*,/} **/
            {
               /** si j'ai une racine qui contient un nombre ou {*} ou {/}
                    j'insere mon noeud comme nouvelle racine de l'arbre
                    et l'arbre devient S-A-G du nouveau noeud.
                **/
                if(!est_operation(arbre->info.operation)||(arbre->info.operation=='*')||(arbre->info.operation=='/'))
                {
                    ne->fgauche=arbre; // le SAG du nouveau noeud devient mon arbre
                    arbre=ne;    // la racine de l'arbre devient le nouveau noeud
                }
                /**
                    Quelque soit le cas maintenant alors l'insertion sera faite d'une manière simple
                    l'opération * ou / sera mise comme fils droit de la racine de l'arbre
                    et le SAD de la racine deviendra le SAG du nouveau noeud
                 **/
                else
                {
                   ne->fgauche=arbre->fdroit; // noeud prend le SAD comme son SAG
                   arbre->fdroit=ne; // le SAD de la racine devient le nouveau noeud
                }
            }
        }
      return ((Noeud*)arbre); /** Bingoo! arbre modifié **/
  }

/********************************************************************************/
    /**
         Nom de la fonction: lire_expression_arith
         Entrée: les caracteres stockés au niveau du buffer
         Sortie: un pointeur sur la racine de l'arbre construit
                 Ou message d'erreur
         Rôle de la fonction: cette fonction permet de créer un arbre
                              d'après les valeurs stockées dans le buffer
                              un message d'erreur est déclenché dès qu'on se retrouve
                              avec un caractère incorrect ou bien dans un mauvais ordre
                              ou emplacement,puis on vide l'arbre et on quitte le programme.
                              Sinon, le caractere sera inséré dans l'arbre et on passe au suivant
                              en répétant le meme processus tant qu'on n'a pas un retour chariot
    **/
   Noeud *lire_expression_arith()
   {
       Noeud *arbre=NULL; // pointeur sur l'arbre initialisé par NULL
       char car_lu; // caractere du traitement
       char operati;
       int signe=1,point=0,val_ent=0,dernie_opera=0,erreur=0;
       Union var;
       float val_flott=0.0,coef=1.0;

       car_lu=lire_du_buffer();
       /** la partie 1 du programme concerne le traitement des elements de rencontrer le
           premier chiffre  **/
        if(car_lu=='e')// une erreure de lecture;
        {
            printf("erreur\n");
            arbre=raser_arbre(arbre);
            return ((Noeud*)arbre);
        }
         /* si le caractere ou la suite des caractères lus sont des + ou -
            on les comptes comme des signes */
        if((car_lu=='+')||(car_lu=='-'))
        {
              erreur=1;
            if(car_lu=='-') signe=-1;
            while((car_lu=='+')||(car_lu=='-'))
           {
              car_lu=lire_du_buffer();
              if(car_lu=='!')
              {
                printf("erreur\n");
                arbre=raser_arbre(arbre);
                return((Noeud*)arbre);
              }
            if(car_lu=='-') signe*=-1;
           } //fin while((car=='+')||(car=='-'))
        }//if((car_lu=='+')||(car_lu=='-'))
        /* si on se retrouve avec une operation * ou / c'est une erreur */
        if((car_lu=='*')||(car_lu=='/'))
        {
           printf("erreur\n");
           arbre=raser_arbre(arbre);
           return ((Noeud*)arbre);
        }//fin if((car_lu=='*')||(car_lu=='/'))

        /** maintenant on passe à la 2eme partie , traitement de l'ensemble des
            caracteres dans le buffer en commencant par le premier chiffre ou point
            lu jusqu'a le retour chariot ou bien un declencher une erreure
            **/
         while(car_lu!='\n')
         {
            /** Partie 1 traitement des nombres **/
            if((est_chiffre(car_lu))||(car_lu=='.'))
            {
                  erreur=0; /* a l'instant l'expression est bonne */
                  val_ent=0; /* pour stocker la partie entiere du nombre */
                  val_flott=0.0; /* bien sure c'est la partie decimale */
                  coef=1.0; /* coefficient pour former la partie decimale */
                  point=0; /* la validité des virgules  */
                  do // formation de la parite entiere du nombre
                  {
                       if(car_lu=='.') // si on rencontre un point
                       {
                        point=1; // indicateur va affirmer qu'on a trouvé une virgule
                        break; //  traiter la partie decimale
                       }
                       val_ent=(val_ent*10)+char_equiv_int(car_lu); // naissance de notre nombre
                       car_lu=lire_du_buffer(); // lire un caractere
                      if(car_lu=='e')// caractere lu pas bon
                      {
                        printf("erreur\n");
                        arbre=raser_arbre(arbre); // dommage
                        return((Noeud*)arbre);
                       }
                  }while(est_chiffre(car_lu)||(car_lu=='.'));
                  /** la partie decimale maintenant ' si point est vrai' **/
                  if(point==1)
                  {
                      do
                      {
                          car_lu=lire_du_buffer();
                          coef*=0.1;
                          if((car_lu=='e')||(car_lu=='.')) // caractere pas bon
                            {
                             printf("erreur\n");
                             arbre=raser_arbre(arbre); // dommage
                             return((Noeud*)arbre); // rien
                            }
                          if(est_chiffre(car_lu)) // si le caractere est un chiffre
                          val_flott+=((float)char_equiv_int(car_lu)*coef); // naissance de la partie decimale
                      }while(est_chiffre(car_lu)); // tant qu'on lit des chiffres
                  }
                   /** notre nombre est prêt **/
                   var.nombre=(float)((val_ent+val_flott)*signe);
                   /** cas particulier si la derniere operation lu est une division et l'operande qui
                       la suit est un zero , bien sur c'est un crime envers les maths, erreeeeeeur **/
                   if((var.nombre==0)&&(operati=='/'))
                    {
                      printf("erreur\n");
                      arbre=raser_arbre(arbre);
                      return((Noeud*)arbre);
                    }
               arbre=inserer_dans_arbre(arbre,var);
            } // fin partie 1.

            /** partie 2 traitement de l'opération **/
            if(est_operation(car_lu))
            {
                erreur=1;  /* va nous servir a la fin si l'expression se temrine par operation */
                signe=1;  /* pour les signes s'il existe apres operation lu */
                operati=car_lu; /* stocker l'operation */
                  while(est_operation(car_lu))
                  {
                       car_lu=lire_du_buffer();
                      if((car_lu=='e')||(car_lu=='*')||(car_lu=='/'))
                       {
                         printf("erreur\n");
                         arbre=raser_arbre(arbre);
                         return((Noeud*)arbre);
                       }
                       if(car_lu=='-') signe*=-1;
                  }
                  var.operation=operati; // affectation de l'operation
                  arbre=inserer_dans_arbre(arbre,var); // insertion de l'operation
            } // fin if(est_operation(car_lu))

         } // fin while(car_lu!='\n')

         /** si l'indicateur d'etat "erreur" est 1 c'est a dire l'expression s'est terminée
             par un caractere qui n'est pas chiffre**/
          if(erreur)
          {
            printf("erreur\n");
            arbre=raser_arbre(arbre);
            return((Noeud*)arbre);
          }
       return ((Noeud*)arbre); /** bingoooo! tout est bien passé **/
   }

/****************************************************************************************/


    void traitement()
    {
      Noeud *arbre=NULL;
      printf("**************(Merci d'entrer votre expression arithmetique)*******************\n\n");
      arbre=lire_expression_arith();
      printf("*********** Affichage de votre expression sous forme d'arbre ************\n\n");
      affichage_arbre(arbre);
      printf("\n Le resultat de l'evaluation de l'expression = %f\n\n",eval_resultat(arbre));
    }






