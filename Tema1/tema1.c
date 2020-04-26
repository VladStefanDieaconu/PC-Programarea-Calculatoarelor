#include <stdio.h>
#include <math.h>

/*
* Vlad-Stefan DIEACONU, 311CA
*/

/* Calculeaza maximul a trei numere */
#define MAX(a, b, c) (a > b && a > c) ? a : (b > c) ? b : c

/* Calculeaza minimul a trei numere */
#define MIN(a, b, c) (a < b && a < c) ? a : (b < c) ? b : c


/*
 * Calculeaza valoarea nuantei (HUE).
 * Primeste ca parametri valorile R, G, B normalizate la intervalul [0,1],
 * Cmax si delta.
 */
float computeHue(float r, float g, float b, float cmax, float delta) {
	float h;

	if (delta == 0) {
		h = 0;

	} else if (cmax == r) {
		h = 60 * fmod((g - b) / delta, 6);

	} else if (cmax == g) {
		h = 60 * ((b - r) / delta + 2);

	} else if (cmax == b) {
		h = 60 * ((r - g) / delta + 4);
	}

    /* daca H este negativ la valoarea lui se aduna 360 si apoi este normat*/
	while (h < 0) {
		h = h + 360;
	}
	h = h / 360;

	return h;
}

/*
 * Calculeaza valoarea saturatiei.
 * Primeste ca parametri valorile  Cmax si delta.
 */
float computeSaturation(float cmax, float delta) {
	float s;

	if (cmax == 0){
		s = 0;

	} else {
		s = delta / cmax;
	}

	/* daca S este mai mare decat 100 acesta este normat */
	if (s > 100) {
		s /= 100;
	}

	return s;
}

/*
 * Calculeaza valoarea luminozitatii.
 * Primeste ca parametri valoarea  Cmax.
 */
float computeValue(float cmax) {
	float v;

	v = cmax;

    /* daca valoarea luminozitatii este mai mare ca 100 aceasta este normata */
	if (v > 100) {
		v /= 100;
	}

	return v;
}

int main () {

	int n, m, i, j;
	float x, r, g, b, h, s, v, cmax, cmin, delta;
	char c;

    /* Citim in ordine latimea si inaltimea imaginii,
	litera prin care se face selectia operatiei aplicate
	si factorul de modificare a caracteristicii */
	scanf ("%d %d %c %f", &n, &m, &c, &x);

	for (i = 0; i < m; ++i) {
		for(j = 0; j < n; ++j) {

			/* Citirea valorilor R, G, B */
			scanf ("%f %f %f", &r, &g, &b);

			/* Modificare intervalului de partenenta la [0, 1] */
			r = r / 255;
			g = g / 255;
			b = b / 255;

			/* Transformarea din RGB in modelul HSV */
			cmax = MAX(r, g, b);
			cmin = MIN(r, g, b);
			delta = cmax - cmin;

			h = computeHue(r,g,b,cmax, delta);
			s = computeSaturation(cmax, delta);
			v = computeValue(cmax);

			/* Editarea pixelilor in functie de operatia specificata */
			if(c == 'h') {
				h = h + x;

				h = (h < 1) ? h : 1;
				h = (h < 0) ? 0 : h;

			} else if( c == 's') {
				s = s * x;

				s = (s < 1) ? s : 1;
				s = (s < 0) ? 0 : s;

			} else if ( c == 'v') {
				v = v * x;

				v = (v < 1) ? v : 1;
				v = (v < 0) ? 0 : v;
			}

			/* Afisarea valorilor H S V calculate */
			printf ("%.5f %.5f %.5f \n", h, s, v);
		}
	}

	return 0;
}
