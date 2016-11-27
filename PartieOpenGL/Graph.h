/**
* @file Graph.h
*
* @brief présente quelques outils d'affichage nécessaires dans le cadre de ce
* projet.
* Il contient la déclaration des procédures disponibles pour ouvrir une fenêtre
* et y dessiner des figures. Les coordonnées des points dans la fenêtre sont
* définies sur l'intervalle [-1;1], (-1,-1) etant le coin inferieur gauche de
* la fenetre et (1,1) le coin superieur droit.
* 
* Pour une démonstration de l'utilisation de ces procédures, voir le fichier
* main.cpp.
*
*/

/**
* InitGraph
*
* Procédure d'initialisation de la fenêtre et de l'environnement OpenGL 
*
* @param ac nombre de paramètres
* @param av tableau contenant les paramètres 
* @param WinName le nom (titre) de la fenêtre d'affichage
* @param w la largeur de la fenêtre
* @param h la hauteur de la fenêtre
* @param Draw fonction qui affiche le graphique dans la fenêtre
* @param Key fonction appelée lors de l'appui sur une touche c du clavier,
*	 c désignant le code ascii de la touche
*
*/
void InitGraph(int ac,char *av[], const char *WinName,
               const int w, const int h, int min, int max, void (*Draw)(void),
               void (*Key)(int c));
/**
* line
*
* Cette procédure permet de tracer une ligne entre deux points (x0, y0) et
* (x1,y1) 
*
* @param x0 abscisse du 1er point
* @param y0 ordonnée du 1er point
* @param x0 abscisse du 2eme point
* @param y0 ordonnée du 2eme point
*
*/
void line(const float x0, const float y0, const float x1, const float y1);


/**
* setcolor
*
* Cette procédure permet de définir la couleur utilisée pour tracer les lignes.
* La couleur est définie par les valeurs des composantes rouge, vert et bleue.
*
* @param r composante rouge
* @param v composante verte
* @param b composante bleue
*
*/
void setcolor(const float r, const float v, const float b);

/**
* beginlines
*
* Cette procédure permet de commencer le tracé d'une ligne brisée composée
* de n segments de droite définis par (n+1) points.
*
* @param x0 l'abscisse du premier point de la ligne brisée
* @param y0 l'ordonnée du premier point de la ligne brisée
*
*/
void beginlines(const float x0, const float y0);

/**
* lineto
*
* Cette procédure permet d'ajouter un point à la ligne brisée en cours. Le
* dernier point défini et le nouveau point délimitent un nouveau segment de
* droite dans la ligne brisée.
*
* @param x l'abscisse du nouveau point de la ligne brisée
* @param y l'ordonnee du nouveau point de la ligne brisée
*
*/
void lineto(const float x, const float y);

/**
* finishlines
*
* Cette procédure permet de terminer le tracé de la ligne brisée en cours.
*
*/
void finishlines(void);

void drawGrid(double pasX, double pasY);

/**
* bar
*
* Cette procédure permet de tracer un rectangle défini par son coin supérieur
* gauche et son coin inférieur droit.
*
* @param x0 abscisse du coin supérieur gauche du rectangle
* @param y0 ordonnee du coin supérieur gauche du rectangle
* @param x1 abscisse du coin inférieur droit du rectangle
* @param y1 ordonnee du coin inférieur droit du rectangle
*
*/
void bar(const float x0, const float y0, const float x1, const float y1);

/**
* outtextxy
*
* Cette procédure permet d'écrire une chaîne de caractères dans une zone de
* texte définie par les coordonnées x et y
*
* @param x abscisse de l'origine (coin supérieur gauche) de la zone de texte
* @param y ordonnee de l'origine (coin supérieur gauche) de la zone de texte
* @param s chaîne de caractères contenant le texte à afficher
*
*/
void outtextxy(const float x, const float y, const char *s);



