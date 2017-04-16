#include "graphics.h"

int main() {
	int compteur, modulo;
	compteur = 12;
	modulo = compteur % 5;
	printf("%d\n", modulo);
	
	wait_escape();
	exit(0);
}
