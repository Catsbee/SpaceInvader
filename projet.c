#include "graphics.h"

	typedef int MONSTRE;
	
	typedef struct {
		POINT coin;
		MONSTRE T[10][5];
	}	ESQUADE;
	
	typedef struct {
		POINT position_tir;
		int verification;
	}	TIR;
	
	typedef struct {
		TIR T;
		ESQUADE M;
		POINT joueur;
	}	JEU;

	#define MORT 0
	#define NIVEAU1 1
	#define NIVEAU2 2
	
	
// Définition 
JEU init_jeu(JEU J){
	int i, j;
	for(i=0; i<10; i++){
		for(j=0; j<5;j++){
			J.M.T[i][j] = 1;
			}
		}
	J.T.position_tir.x = 0;
	J.T.position_tir.y = 0;
	J.T.verification = 0;
	J.M.coin.y = 300 - 10;
	J.M.coin.x = 33;
	J.joueur.x = 150;
	return J;
	}

void affiche_joueur(JEU J){
	POINT pos_J;
	pos_J.x = J.joueur.x - 21;
	pos_J.y = 30;
	aff_pol("^", 40, pos_J, blue);	
	}

void affiche_tir(JEU J){
	J.T.position_tir.x = J.T.position_tir.x - 9;
	aff_pol("|", 20, J.T.position_tir, gold);
	}
	
void affiche_monstres(int i, int j, POINT P){
	POINT monstre;
	monstre.x = P.x + i*25;
	monstre.y = P.y + j*25;
	draw_circle(monstre, 10, red);
	}
	
void affiche_esquade(JEU J){
	int i, j;
	for (i = 0; i < 10; i++){
		for (j = 0; j < 5; j++){
			if (J.M.T[i][j] == 1){
				affiche_monstres(i, j, J.M.coin);
				}
			}
		}
	}

JEU tir_joueur(JEU J, int compteur){
	POINT fleche;
	fleche = get_arrow();
	if (J.T.verification == 0){
		if (fleche.y > 0){
			J.T.position_tir.x = J.joueur.x;
			J.T.position_tir.y = 48;
			J.T.verification = 1;
			}
		}
	return J;
	}

int deplacement_joueur(JEU J){
	int position_joueur;
	POINT fleche;
	position_joueur = 0;
	fleche = get_arrow();
	if (fleche.x < 0){
		position_joueur = -5;
		}
	if (fleche.x > 0){
		position_joueur = 5;
		}
	return position_joueur;
	}

int deplacement_tir(JEU J, int compteur){
	int modulo;
	modulo = compteur % 4;
	if (modulo == 0){
		if (J.T.verification == 1){
			J.T.position_tir.y = J.T.position_tir.y + 13;
			}
		if (J.T.verification == 0){
			J.T.position_tir.y = 0;
			}
		}
	return J.T.position_tir.y;
	}

int deplacement_esquade(JEU J, int compteur){
	int modulo;
	modulo = compteur % 70;
	if (modulo == 0){
		J.M.coin.y = J.M.coin.y - 5;
		}
	return J.M.coin.y;
	}

JEU tue_monstre(JEU J){
	int i, j;
	for (i = 0; i<10; i++){
		for (j = 0; j<5; j++){
			if (J.T.position_tir.x > J.M.coin.x - 11 + i*25 && J.T.position_tir.x < J.M.coin.x + 13 + i*25){
				if (J.T.position_tir.y > J.M.coin.y - 12 + j*25 && J.T.position_tir.y < J.M.coin.y + 12 + j*25){
					if (J.M.T[i][j] == 1){
						J.M.T[i][j] = 0;
						J.T.verification = 0;
						}
					}
				}
			}
		}
		return J;
	}

BOOL jeu_fini(JEU J){
	
	}


int main(){
	int height, weight;
	height = 300;
	weight = 300;
	init_graphics(weight,height);
	int compteur;
	JEU J;
	J = init_jeu(J);
	compteur = 0;
	affiche_auto_off();
	while (!jeu_fini(J)){									//vérifie si tous les monstres sont morts et si le joueur est mort
		fill_screen(black);
		
		J.joueur.x = J.joueur.x + deplacement_joueur(J);	//change la position du joueur sur l'axe x
		J = tir_joueur(J, compteur);						//crée un tir si le joueur appuie sur la fleche du haut
		J.T.position_tir.y = deplacement_tir(J, compteur);	//vérifie si il y a un tir et change la position du tir ou permet au joueur de tirer
		J.M.coin.y = deplacement_esquade(J, compteur);		//change la position de tous les monstres
		
		J = tue_monstre(J);									//vérifie si le tir a touché un des monstres et change le tableau si oui
		
		
		affiche_joueur(J);									//affiche le joueur à sa position
		affiche_tir(J);										//affiche le tir à sa position
		affiche_esquade(J);									//affiche les monstres
		affiche_all();
		
		attendre(30);
		compteur ++;
		if (J.T.position_tir.y > height){
			J.T.verification = 0;
			}
		}
	
	wait_escape();
	exit(0);
}
