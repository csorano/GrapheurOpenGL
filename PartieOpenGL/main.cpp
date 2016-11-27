/**************************
* Includes
*
**************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include <math.h>
#include <ctype.h>

#define MAXINPUT 100

int bascule = 0;
//Bornes xMin et xMax d�finies par l'utilisateur (par d�faut � 0 et 1)
int xMin = 0;
int xMax = 1;
//Bornes yMin et yMax d�finies par l'utilisateur (par d�faut � -1 et 1)
int yMin = -1;
int yMax = 1;

//Le pas doit nous permettre de calculer et d'afficher le bon nombre de graduations sur l'axe des abscisses
double pasCalcule = 0.1;

//Plus precision se rapproche de 0, plus le trac� est pr�cis
float precision = 0.05;

//Testing structure
struct point
{
	float x, y;
};

point tab[2000];

//Testing method
void fillPointTab()
{
	//Pourquoi ce truc est �gal � 0 ? Teste avec 45 puis 46 et 47 ;-)
	float trucQuiDeplaceLaCourbeSurLAxeDesAbscisses = 0.0;
	point tmp = { 0.0, 0.0 };
	for (int i = 0; i < 2000; ++i)
	{
		//Pourquoi avions-nous mis 50 ?
		tmp.x = trucQuiDeplaceLaCourbeSurLAxeDesAbscisses - 50.0;
		tmp.y = sin((double)tmp.x);
		tab[i] = tmp;
		trucQuiDeplaceLaCourbeSurLAxeDesAbscisses = trucQuiDeplaceLaCourbeSurLAxeDesAbscisses + precision;
	}
}

//permet de placer un point dans l'intervalle [-1;1] en fonction de l'intervalle donn� par l'utilisateur
float inter_abscisse(float x, float x1, float x2){
	return(2 / (x2 - x1))*(x - ((x2 + x1) / 2));
}

//permet de placer un point dans l'intervalle [-1;1] en fonction de l'intervalle donn�e par l'utilisateur
float inter_ordonnee(float y, float y1, float y2){
	return(2 / (y2 - y1))*(y - ((y2 + y1) / 2));
}

//permet de convertir le tableau de points cr�� par fillPointTab() en tableau de points situ�s dans le bon intervalle d�fini par xMin et xMax
void convertTab(){
	int tabLength = sizeof(tab) / sizeof(point);
	point tmp = { 0.0, 0.0 };
	point res = { 0.0, 0.0 };
	for (int i = 0; i<tabLength; ++i)
	{
		tmp = tab[i];
		res.x = inter_abscisse(tmp.x, xMin, xMax);
		res.y = inter_ordonnee(tmp.y, yMin, yMax);
		tab[i] = res;
	}
}

/**
* myKey
*
* Gestion des touches du clavier
*
* @parma c code ascci d�finissant une touche du clavier
*
*/
void myKey(int c)
{
	switch (c)
	{
	case 'a':
		bascule ^= 1; /* La bascule passe alternativement de 0 a 1 */
		break;
	}
}

void drawCurve()
{
	int val1 = 0;
	int val2 = 0;
	int tabLength = sizeof(tab) / sizeof(point);
	point tmp1 = { 0.0, 0.0 };
	point tmp2 = { 0.0, 0.0 };
	setcolor(0.7F,0.8F,1.0F);
	for (int i = 0; i<tabLength - 1; ++i)
	{
		val1 = i;
		val2 = i + 1;
		tmp1 = tab[val1];
		tmp2 = tab[val2];
		line(tmp1.x, tmp1.y, tmp2.x, tmp2.y);
	}
}

/**
* myDraw
*
* Proc�dure
*
*/
void myDraw(void)
{
	drawGrid(pasCalcule);
	setcolor(0.3F,0.3F,0.3F);
	//line(0, -1, 0, 1); //Abscisse
	//line(-1, 0, 1, 0); //Ordonn�e
	drawCurve();
	if (bascule)
	{
		/* Trace un rectangle rouge � l'ecran si active
		* par appui de la touche 'a' */
		//setcolor(1.0F,0.0F,0.0F);
		//bar(-0.5F,-0.5F,0.5F,0.5F);  
	}
	setcolor(0.7F,0.8F,1.0F);
	//outtextxy((-(abs(xMin)*pasCalcule)+pasCalcule),pasCalcule,"Fonction sinus");  
}

// Restaure la valeur par d�faut des bornes si l'utilisateur rentre des valeurs incorrectes.
void resetBornes(void)
{
	xMin = 0;
	xMax = 1;
	yMin = -1;
	yMax = 1;
}

/**
* Fonction g�rant les tests des donn�es rentr�es par l'utilisateur concernant les bornes
*
* @param input : chaine saisie par l'utilisateur
* @return bool
*/
bool checkInput(char* input, int* borne)
{
	int length, i;
	length = strlen(input);
	for (i = 0; i < length; i++)
	{
		if (!isdigit(input[i])&& input[i] != '-')
		{
			printf("Veuillez saisir une valeur numerique.\n");
			resetBornes();
			return false;
		}
	}
	*borne = atoi(input);
	return true;
}

// Fonction permettant le scan des valeurs des bornes et la gestion des erreurs �ventuelles.
void scanBornes(void)
{
	char tmp[MAXINPUT] = "";

	printf("Entrez la borne X minimale : ");
	scanf("%s", &tmp);
	if (!checkInput(tmp, &xMin)) scanBornes();

	printf("Entrez la borne X maximale : ");
	scanf("%s", &tmp);
	if (!checkInput(tmp, &xMax)) scanBornes();

	printf("Entrez la borne Y minimale : ");
	scanf("%s", &tmp);
	if (!checkInput(tmp, &yMin)) scanBornes();

	printf("Entrez la borne Y maximale : ");
	scanf("%s", &tmp);
	if (!checkInput(tmp, &yMax)) scanBornes();

	if (xMin > xMax || yMin > yMax)
	{
		printf("Bornes incorrectes. Les bornes minimum doivent etre strictement superieures aux bornes maximum.\n");
		resetBornes();
		scanBornes();
	}
	else if (xMax == xMin || yMax == yMin)
	{
		printf("Bornes incorrectes. Les bornes minimum et maximum ne peuvent etre egales.\n");
		resetBornes();
		scanBornes();
	}
}

/**
* main
*
* La fonction principale avec deux arguments permettant de r�cup�rer les �l�ments en ligne de comment.
*
* Dans  cet  exemple  les  fonctions  (dites  callback)  myDraw  et  myKey  sont  install�es  ici  par
* l'appel  InitGraph  en  tant  que fonctions  r�agissantes  aux  �v�nements  de  "re-dessinage"  (pour  myDraw)
* et  aux  �v�nements  d'appui  sur  une  touche  du clavier (myKey).
*
* @parma ac : nombre de param�tres
* @parma av : tableau contenant les param�tres
*
*/
int main(int ac, char *av[])
{
	// J'ai sorti le scan du main !
	scanBornes();

	pasCalcule = ((2.0)/(abs(xMax-xMin)));

	fillPointTab();
	convertTab();
	InitGraph(ac, av, "Essai Glut", 800, 700, xMin, xMax, myDraw, myKey);
	return 0;
}


