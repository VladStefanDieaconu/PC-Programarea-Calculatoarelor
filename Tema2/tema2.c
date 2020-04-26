/*
 * Vlad-Stefan Dieaconu, 311CA
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFLEN 40000

// Functie pentru alocarea unei matrici continue de caractere
char **alloc_matrix(int N, int M){
	char *vec = (char *) calloc(N * M, sizeof(int));

	memset(vec, ' ', N * M);

	char **mat = (char **) calloc(N, sizeof(char *));
	for (int i = 0; i < N; i++) {
		mat[i] = vec + i * M;
	}

	return mat;
}

// Functie pentru afisarea unei matrici
void print_image(char **a, int n, int m) {
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			printf("%c", a[i][j]);
		}
		printf("\n");
	}
}

// Functie pentru aflarea maximului dintr-un vector
int find_maximum(int a[], int n) {
	int max = a[0];

	for (int c = 1; c < n; c++) {
		if (a[c] >= max) {
			max = a[c];
		}
	}

	return max;
}

int main(int argc, char *argv[])
{
	char line[BUFLEN];

	// Citire linie cu linie a datelor de intrare
	while(fgets(line, BUFLEN, stdin)) {

		char row_type;

		int cell_per_col[100];
		int len_cell_per_col = 0;

		char **queens;
		
		char *p;  
		p = strtok(line, " \0");

		// Separa sirul in "tokeni" folosind spatiul si caracterul NULL
		// ca delimitatori
		while (p != NULL) {

			// Verific daca am citit o litera speciala (R sau C)
			if (strncmp(p, "R", 1) == 0 || strncmp(p, "C", 1) == 0) {
				row_type = p[0];

				int row_max = find_maximum(cell_per_col, len_cell_per_col);

				queens = alloc_matrix(row_max, len_cell_per_col);

				p = strtok(NULL, " \0");

				// Verific daca urmeaza dupa alte perechi de cifre care sa
				// reprezinte locul unde se afla matcile
				while (p != NULL) {

					// Prima cifra din pereche reprezentand coloana
					int p1 = atoi(p);
					p = strtok(NULL, " \0");

					// A doua cifra din pereche reprezentand linia
					int p2 = atoi(p);

					// Pun Q in locul unde se afla matca
					queens[p2 - 1][p1 - 1] = 'Q';

					// Trec la urmatoarea pereche
					p = strtok(NULL, " \0");
					
				}

				break;

			// Citesc numarul de celule care se afla pe coloane
			} else {
				cell_per_col[len_cell_per_col] = atoi(p);
				++len_cell_per_col;
			}

			p = strtok(NULL, " \0");
		}

		// Initializez matricea principala in care retin configuratia fagurelui
		int max1 = find_maximum(cell_per_col, len_cell_per_col) * 2 + 2;
		int max2 = 125;
		char **mat = alloc_matrix(max1, max2);
		
		// Coloana porneste mereu de la 1 si merge cu +2
		int col_index = 1;

		// Daca prima coloana este coborata sau ridicata. 
		bool impar;
		if (row_type == 'R'){
			impar = true;
		}else {
			impar = false;
		}

		// i si j sunt coordonate in fagure (coloana, respectiv linie)
		// row_index si col_index sunt coordonate in matricea principala
		for (int i = 0; i < len_cell_per_col; ++i) {

			int row_index;

			if (impar) {
				row_index = 1;
			} else {
				row_index = 2;		
			}

			// Desenez efectiv fagurele caracter cu caracter
			for (int j = 0; j < cell_per_col[i]; ++j) {
				
				mat[row_index][col_index] = queens[j][i];

				mat[row_index - 1][col_index] = '_';
				mat[row_index + 1][col_index] = '_';

				mat[row_index][col_index - 1] = '/';
				mat[row_index][col_index + 1] = '\\';

				mat[row_index + 1][col_index - 1] = '\\';
				mat[row_index + 1][col_index + 1] = '/';
				
				row_index += 2;
			}

			// Alternez paritatea (daca coloana curenta a fost coborata,
			// urmatoarea este ridicata si invers)
			impar = !impar;
			col_index += 2;	
		}
 
 		// Afisez fagurele
		print_image(mat, max1, max2);
	}
}