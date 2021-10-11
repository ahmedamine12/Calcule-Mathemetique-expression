#ifndef ARBRE_ARITH_H_INCLUDED
#define ARBRE_ARITH_H_INCLUDED

/***************************************************************************/

 typedef union
 {
     float nombre;     /** un operande **/
     char operation;  /** une operation (+,-,*,/) **/

 }Union;

 /**************************************************************************/

 typedef struct nd   /** structure d'un noeud **/
 {
     Union info;   /** l'information du noeud operande/operation **/
     struct nd *fgauche;  /** pointeur vers le sous-arbre gauche **/
     struct nd *fdroit;   /** pointeur vers le sous-arbre droit **/
 } Noeud;

 /**************************************************************************/

     char epurer_bl_tab();
     char lire_du_buffer();
     int est_operation(char c);
     int est_chiffre(char c);
     int char_equiv_int(char c);
     float evaluation_operat(float operd1, float operd2,char operat);

     Noeud *creer_noeud(Union elem);
     Noeud *inserer_dans_arbre(Noeud *arbre,Union val);
     float eval_resultat(Noeud *arbre);
     Noeud *raser_arbre(Noeud *arbre);
     void afficher_noeud(Noeud *arbre,int niv_actuel);
     void affichage_arbre(Noeud *arbre);

     Noeud *lire_expression_arith();

     void traitement();

#endif // ARBRE_ARITH_H_INCLUDED
