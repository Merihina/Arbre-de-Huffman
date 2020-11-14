#include <stdio.h>
#include <stdlib.h>
typedef struct cou
{
    int freq;
    char val;
}couple;

typedef struct tree
{
    couple cc;
    struct tree *fg;
    struct tree *fd;
    } arbre;

typedef struct noeud
{
    char x;
    struct noeud *suivant;
    } liste;

void cree_couple(char lettre , couple *c)
{
    c->freq=0;
    c->val=lettre;
}

void saisie_couple(int f ,char lettre, couple *c)
{
    c->freq=f;
    c->val=lettre;
}

void creer_feuille (couple c, arbre **bebe)
{
    if (((*bebe)= (arbre *) malloc (sizeof(arbre)))== NULL)
        printf ("erreur allocation");
    else
    {
        (*bebe)->cc =c;
        (*bebe)->fg= NULL;
        (*bebe)->fd=NULL;
    }
}

void creer_liste(liste **l)
{
    *l=NULL;
}

void cons (couple c, arbre *ag, arbre *ad, arbre **pepe)
{
    if (((*pepe)=(arbre *)malloc (sizeof(arbre)))==NULL)
        printf ("erreur allocation");
    else
    {
        (*pepe)->cc=c;
        (*pepe)->fg=ag;
        (*pepe)->fd=ad;
    }
}
liste *adjqz(int el,liste *p)
{
    liste *y,*courant;
    y=(liste*)malloc(sizeof(liste));
    y->x=el;
    y->suivant=NULL;
    if(p==NULL)
        p=y;
    else
    {
        courant=p;
        while(courant->suivant)
            courant=courant->suivant;
        courant->suivant=y;
    }
    return(p);
}

void adjq(char el, liste **ancienne )
{
    liste *y, *courant;
    y= (liste *) malloc (sizeof (liste));
    y->x= el ;
    y->suivant= NULL;
    if (!*ancienne)
        *ancienne=y;
    else {
            courant= *ancienne;
            while (courant->suivant)
                courant=courant->suivant;
            courant->suivant=y;
         }
}

int nbr_element (char ch,  liste *l)
{
    liste *courant;
    int a=0;
    char valeur;
    if(l==NULL)
        return a;
    else
    {
        courant=l;
        while(courant)
        {
            valeur=courant->x;
            if(valeur==ch)
            {
                a++;
                courant=courant->suivant;
            }
            else
                courant=courant->suivant;
        }
    }
    return a;
}

void saisie_liste( liste **l)
{
    char a;
    printf("donnez l'element : ");
    scanf(" %c",&a);
    adjq(a,l);
    while (a!='#')
    {
        printf("saisie # si vous voulez arretez la saisie \n");
        printf("donnez l'element : ");
        scanf(" %c",&a);
        if(a!='#')
            adjq(a,l);
    }
}

void affiche_liste (liste *l )
{
    while(l)
    {
        printf("%c ",l->x);
        l=l->suivant;
    }
    printf("\n");
}

void affiche_couple (couple c)
{
    printf("%d",c.freq);
    printf("%c",c.val);
}

int appartient (char el, liste *tete)
{
    liste *courant;
    int trouve=0;
    if (tete)
    {
        courant=tete;
        while (courant && !trouve)
        {
            if (courant->x == el)
                trouve=1;
            courant=courant->suivant;
        }
    }
    return trouve;
}

liste *sans_rep (liste *l)
{
    liste *resultat;
    creer_liste(&resultat);
    liste *courant;
    courant =l;
    int a;
    adjq(courant->x,&resultat);
    courant=courant->suivant;
    while(courant)
    {
        a=appartient(courant->x,resultat);
        if(a==0)
        {
            adjq(courant->x,&resultat);
            courant=courant->suivant;
        }
        else
            courant=courant->suivant;
    }
    return(resultat);
}

int longueur (liste *tete)
{
    liste *courant;
    int i=0;
    if (tete!=NULL)
    {
        courant=tete;
        while (courant)
        {
            i++;
            courant=courant->suivant;
        }
    }
    return i;
}

void ini_tab (couple *c ,liste *l)
{
    int a,i=0;
    a=longueur(l);
    liste *courant;
    courant =l;
    while(courant)
    {
        cree_couple(courant->x,&c[i]);
        courant=courant->suivant;
        i++;
    }
    /*for(i=0;i<a;i++)
    {
        cree_couple(l->x,&c[i]);
        courant=courant->suivant;
    }*/
}

void affiche_tab(couple *c,liste *l)
{
    int a,i;
    a=longueur(l);
    for(i=0;i<a;i++)
    {
        printf("( %c ,  %d)",(c[i]).val,(c[i]).freq);
        printf("||");
    }

}

void remplire(couple *c,liste *l,liste *ll)
{
    int a,i;
    a=longueur(ll);
    liste *courant;
    courant =ll;
    for(i=0;i<a;i++)
    {
        int x;
        x=nbr_element(courant->x,l);
        (c[i]).freq=x;
        courant=courant->suivant;
    }
}

void tri (couple *c,liste *l )
{
    int i , j , ind ,taille;
    couple val;
    taille=longueur(l);
    for(i=0 ; i<taille ; i++)
    {
        ind=i;
        for(j=i+1 ; j<taille ; j++)
        {
            if((c[j]).freq>(c[ind]).freq)
            {
                ind=j;

            }
        }
        val=c[ind];
        c[ind]=c[i];
        c[i]=val;
    }
}

arbre **arb_tab(couple *c,liste *l)
{
    int taille,i;
    taille=longueur(l);
    arbre **ar;
    ar=malloc(taille*sizeof(arbre));
    for(i=0;i<taille;i++)
    {
        arbre *arb;
        creer_feuille(c[i],&arb);
        ar[i]=arb;
    }
    return(ar);
}

void postfixe (arbre *ar)
{
    if (ar!= NULL)
    {
        postfixe (ar->fg);
        postfixe (ar->fd);
        affiche_couple(ar->cc);
    }
}

void affiche_arbre_tab(arbre **ar,liste *l)
{
    int taille,i;
    taille=longueur(l);
    for(i=0;i<taille;i++)
    {
        postfixe(ar[i]);
        printf(" ");
    }
}

arbre *Huffman(arbre **ar,liste *l)
{
    int taille,i;
    i=0;
    taille=longueur(l);
    while(i!=taille-1)
    {
        couple a;
        arbre *ar2;
        saisie_couple(ar[taille-i-1]->cc.freq+(ar[taille-i-2])->cc.freq,'#',&a);
        cons(a,ar[taille-i-2],ar[taille-i-1],&ar2);
        //ar[i]=NULL;
        ar[taille-i-2]=ar2;
        tri_arbre(ar,l);
        i++;
    }
    return(ar[0]);
}

void affiche_arbre(arbre *ar,liste *l)
{
    int prof=0;
    int i=0;
    if(ar)
    {
        prof=longueur(l);
        for(i=0;i<prof;i++)
        {
            printf("|___ ");
        }
        printf("%d",ar->cc.freq);
        printf("\n");
        affiche_arbre(ar->fg,l);
        affiche_arbre(ar->fd,l);
    }
}

void tri_arbre (arbre **ar,liste *l )
{
    int i , j , ind ,taille;
    arbre *val;
    taille=longueur(l);
    for(i=0;i<taille;i++)
    {
        ind=i;
        //printf("mi");
        for(j=i+1;j<taille;j++)
        {
            if(ar[j]->cc.freq>(ar[ind]->cc.freq))
            {
                ind=j;
            }
        }
        val=ar[ind];
        ar[ind]=ar[i];
        ar[i]=val;
    }
}
void code(arbre *ar)
{
    if(ar)
    {
        if(ar->fg==NULL && ar->fd==NULL)
        {
            printf("%c",ar->cc.val);
        }
        else
        {
            code(ar->fg);
            printf("0");
        }
    }
}

liste *vider (liste *tete)
{
    liste *p,*q;
    if (tete==NULL) {}
    else if (tete->suivant ==NULL)
    {
        p=tete; tete=tete->suivant; free(p);}
        else
        {
            p=tete;
            while (p->suivant->suivant !=NULL)
                p=p->suivant;
            q=p->suivant; p->suivant=NULL; free(q);
        }
return(tete);
}

void principale (arbre *ar,liste *ll,liste *l)
{

    if(ar->fg==NULL & ar->fd==NULL)
        {
            adjq(ar->cc.val,&ll);
        }

    else
    {
        adjq('0',&ll);
        principale(ar->fd,ll,l);
        affiche_liste(ll);
        if(ll->x!='0' || ll->x!='1')
        {
            ll=vider(ll);
            ll=vider(ll);
        }
        adjq('1',&ll);
        principale(ar->fg,ll,l);
        /*while(ll)
        {
            ll=vider(ll);
        }*/
        affiche_liste(ll);
        if(ll->x!='0' || ll->x!='1')
        {
            ll=vider(ll);
            ll=vider(ll);
        }
    }
}



int main()
{
    liste *l,*res;
    int a;
    couple *c;
    arbre *ar;
    c=malloc(a*sizeof(couple));
    creer_liste(&l);
    saisie_liste(&l);
    affiche_liste(l);
    res=sans_rep(l);
    affiche_liste(res);
    a=longueur(res);
    ini_tab(c,res);
    affiche_tab(c,res);
    printf("\n");
    remplire(c,l,res);
    affiche_tab(c,res);
    printf("\n");
    tri(c,res);
    affiche_tab(c,res);
    ar=arb_tab(c,res);
    affiche_arbre_tab(ar,res);
    arbre *huff;
    huff=Huffman(ar,res);
    //printf("%d",huff);
    postfixe(huff);
    printf("\n");
    affiche_arbre(huff,l);
    //printf("%c",huff->fg->cc.val);
    //printf("%c",huff->fg->fd->cc.val);
    printf("\n");/*
    liste *test1;
    liste *test2;
    creer_liste(&test2);
    creer_liste(&test1);*/
    /*adjqz('z',test);
    affiche_liste(test);
    */
    ///printf("a");
    liste *test1;
    creer_liste(&test1);
    principale(huff,test1,l);
    return 0;


}
