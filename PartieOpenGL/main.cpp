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
//Bornes xMin et xMax définies par l'utilisateur (par défaut à -10 et 10)
int xMin = -10;
int xMax = 10;
//Bornes yMin et yMax définies par l'utilisateur (par défaut à -10 et 10)
int yMin = -10;
int yMax = 10;

//Le pas doit nous permettre de calculer et d'afficher le bon nombre de graduations sur l'axe des abscisses
double pasCalculeX = 0.1;
double pasCalculeY = 0.1;

//Plus precision se rapproche de 0, plus le tracé est précis
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
	//Pourquoi ce truc est égal à 0 ? Teste avec 45 puis 46 et 47 ;-)
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

//permet de placer un point dans l'intervalle [-1;1] en fonction de l'intervalle donné par l'utilisateur
float inter_abscisse(float x, float x1, float x2){
	return(2 / (x2 - x1))*(x - ((x2 + x1) / 2));
}

//permet de placer un point dans l'intervalle [-1;1] en fonction de l'intervalle donnée par l'utilisateur
float inter_ordonnee(float y, float y1, float y2){
	return(2 / (y2 - y1))*(y - ((y2 + y1) / 2));
}

//permet de convertir le tableau de points créé par fillPointTab() en tableau de points situés dans le bon intervalle défini par xMin et xMax
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
* @parma c code ascci définissant une touche du clavier
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
* Procédure
*
*/
void myDraw(void)
{
	char tmp[MAXINPUT] = "";
	drawGrid(pasCalculeX, pasCalculeY);
	setcolor(0.3F,0.3F,0.3F);
	line(inter_abscisse(0,xMin,xMax), inter_ordonnee(yMin, yMin, yMax), inter_abscisse(0, xMin, xMax), inter_ordonnee(yMax, yMin, yMax)); //Abscisse
	line(inter_abscisse(xMin, xMin, xMax), inter_ordonnee(0, yMin, yMax), inter_abscisse(xMax, xMin, xMax), inter_ordonnee(0, yMin, yMax)); //Ordonnée
	drawCurve();
	if (bascule)
	{
		/* Trace un rectangle rouge à l'ecran si active
		* par appui de la touche 'a' */
		//setcolor(1.0F,0.0F,0.0F);
		//bar(-0.5F,-0.5F,0.5F,0.5F);  
	}
	// Affichage des bornes à l'écran
	setcolor(0.0F,1.0F,0.0F);

	sprintf(tmp, "xMin: %d", xMin);
	outtextxy(-0.95,0.90,tmp); 

	sprintf(tmp, "xMax: %d", xMax);
	outtextxy(-0.95, 0.82, tmp);

	sprintf(tmp, "yMin: %d", yMin);
	outtextxy(-0.95, 0.74, tmp);

	sprintf(tmp, "yMax: %d", yMax);
	outtextxy(-0.95, 0.66, tmp);
}

// Restaure la valeur par défaut des bornes si l'utilisateur rentre des valeurs incorrectes.
void resetBornes(void)
{
	xMin = -10;
	xMax = 10;
	yMin = -10;
	yMax = 10;
}

/**
* Fonction gérant les tests des données rentrées par l'utilisateur concernant les bornes
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
		if (i != 0 && input[i] == '-')
		{
			printf("Veuillez saisir une valeur numerique.\n");
			resetBornes();
			return false;
		}
		if (!isdigit(input[i]) && input[i] != '-')
		{
			printf("Veuillez saisir une valeur numerique.\n");
			resetBornes();
			return false;
		}
	}
	*borne = atoi(input);
	return true;
}

/**
* Fonction permettant le scan des valeurs des bornes et la gestion des erreurs éventuelles.
*
* @return bool
*/
bool scanBornes(void)
{
	char tmp[MAXINPUT] = "";

	printf("Entrez la borne X minimale : ");
	scanf("%s", &tmp);
	if (!checkInput(tmp, &xMin)) return false;

	printf("Entrez la borne X maximale : ");
	scanf("%s", &tmp);
	if (!checkInput(tmp, &xMax)) return false;

	printf("Entrez la borne Y minimale : ");
	scanf("%s", &tmp);
	if (!checkInput(tmp, &yMin)) return false;

	printf("Entrez la borne Y maximale : ");
	scanf("%s", &tmp);
	if (!checkInput(tmp, &yMax)) return false;

	if (xMin > xMax || yMin > yMax)
	{
		printf("Bornes incorrectes. Les bornes minimum doivent etre strictement superieures aux bornes maximum.\n");
		resetBornes();
		return false;
	}
	else if (xMax == xMin || yMax == yMin)
	{
		printf("Bornes incorrectes. Les bornes minimum et maximum ne peuvent etre egales.\n");
		resetBornes();
		return false;
	}
	return true;
}

/**
* main
*
* La fonction principale avec deux arguments permettant de récupérer les éléments en ligne de comment.
*
* Dans  cet  exemple  les  fonctions  (dites  callback)  myDraw  et  myKey  sont  installées  ici  par
* l'appel  InitGraph  en  tant  que fonctions  réagissantes  aux  évènements  de  "re-dessinage"  (pour  myDraw)
* et  aux  évènements  d'appui  sur  une  touche  du clavier (myKey).
*
* @parma ac : nombre de paramètres
* @parma av : tableau contenant les paramètres
*
*/
int main(int ac, char *av[])
{
	// J'ai sorti le scan du main !
	bool scanOK = false;
	while (!scanOK)
	{
		scanOK = scanBornes();
	}

	pasCalculeX = ((2.0)/(abs(xMax-xMin)));
	pasCalculeY = ((2.0) / (abs(yMax - yMin)));

	fillPointTab();
	convertTab();
	InitGraph(ac, av, "Essai Glut", 800, 700, xMin, xMax, myDraw, myKey);
	return 0;
}


