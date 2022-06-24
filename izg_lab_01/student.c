/******************************************************************************
 * Laborator 01 - Zaklady pocitacove grafiky - IZG
 * ihulik@fit.vutbr.cz
 *
 * $Id: $
 *
 * Popis: Hlavicky funkci pro funkce studentu
 *
 * Opravy a modifikace:
 * - ibobak@fit.vutbr.cz, orderedDithering
 */

#include "student.h"
#include "globals.h"

#include <time.h>

const int M[] = {
	0, 204, 51, 255,
	68, 136, 187, 119,
	34, 238, 17, 221,
	170, 102, 153, 85
};

const int M_SIDE = 4;

/******************************************************************************
 ******************************************************************************
 Funkce vraci pixel z pozice x, y. Je nutne hlidat frame_bufferu, pokud
 je dana souradnice mimo hranice, funkce vraci barvu (0, 0, 0).
 Ukol za 0.25 bodu */
S_RGBA getPixel(int x, int y)
{
	if (x >= 0 && y >= 0 && x < width && y < height)
		return frame_buffer[y * width + x];

	return COLOR_BLACK; //vraci barvu (0, 0, 0)
}
/******************************************************************************
 ******************************************************************************
 Funkce vlozi pixel na pozici x, y. Je nutne hlidat frame_bufferu, pokud
 je dana souradnice mimo hranice, funkce neprovadi zadnou zmenu.
 Ukol za 0.25 bodu */
void putPixel(int x, int y, S_RGBA color)
{
	if (x >= 0 && y >= 0 && x < width && y < height)
		frame_buffer[y * width + x] = color;
}
/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na odstiny sedi. Vyuziva funkce GetPixel a PutPixel.
 Ukol za 0.5 bodu */
void grayScale()
{
	float intensity;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			S_RGBA color = getPixel(x, y);
			intensity = 0.299 * color.red + 0.587 * color.green + 0.114 * color.blue;
			color.red = color.green = color.blue = ROUND(intensity);
			putPixel(x, y, color);
		}

	}
}

/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci algoritmu maticoveho rozptyleni.
 Ukol za 1 bod */

void orderedDithering()
{

	int i, j;

	grayScale();

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			i = x % M_SIDE;
			j = y % M_SIDE;

			if (getPixel(x, y).red > M[j * M_SIDE + i]) {
				putPixel(x, y, COLOR_WHITE);
			}
			else {
				putPixel(x, y, COLOR_BLACK);
			}
		}
	}

}

/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci algoritmu distribuce chyby.
 Ukol za 1 bod */
void errorDistribution()
{
	double e;
	int threshhold = 122;
	int value;

	grayScale();

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			//original
			S_RGBA color = getPixel(x, y);

			if (color.red > threshhold) {
				putPixel(x, y, COLOR_WHITE);
				e = color.red - COLOR_WHITE.red;
			}
			else {
				putPixel(x, y, COLOR_BLACK);
				e = color.red;
			}

			//first
			color = getPixel(x + 1, y);
			value = color.red + ROUND(3.0 / 8.0 * e);
			if (value < 0) {
				value = 0;
			}
			else if (value > 255) {
				value = 255;
			}
			color.red = color.blue = color.green = value;

			putPixel(x + 1, y, color);

			//second
			color = getPixel(x, y + 1);
			value = color.red + ROUND(3.0 / 8.0 * e);
			if (value < 0) {
				value = 0;
			}
			else if (value > 255) {
				value = 255;
			}
			color.red = color.blue = color.green = value;

			putPixel(x, y+ 1, color);

			//third 
			color = getPixel(x + 1, y + 1);
			value = color.red + ROUND(2.0 / 8.0 * e);
			if (value < 0) {
				value = 0;
			}
			else if (value > 255) {
				value = 255;
			}
			color.red = color.blue = color.green = value;

			putPixel(x + 1, y + 1, color);
		}
	}
}

/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci metody prahovani.
 Demonstracni funkce */
void thresholding(int Threshold)
{
	/* Prevedeme obrazek na grayscale */
	grayScale();

	/* Projdeme vsechny pixely obrazku */
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			/* Nacteme soucasnou barvu */
			S_RGBA color = getPixel(x, y);

			/* Porovname hodnotu cervene barevne slozky s prahem.
			   Muzeme vyuzit jakoukoli slozku (R, G, B), protoze
			   obrazek je sedotonovy, takze R=G=B */
			if (color.red > Threshold)
				putPixel(x, y, COLOR_WHITE);
			else
				putPixel(x, y, COLOR_BLACK);
		}
}

/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci nahodneho rozptyleni.
 Vyuziva funkce GetPixel, PutPixel a GrayScale.
 Demonstracni funkce. */
void randomDithering()
{
	/* Prevedeme obrazek na grayscale */
	grayScale();

	/* Inicializace generatoru pseudonahodnych cisel */
	srand((unsigned int)time(NULL));

	/* Projdeme vsechny pixely obrazku */
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			/* Nacteme soucasnou barvu */
			S_RGBA color = getPixel(x, y);

			/* Porovname hodnotu cervene barevne slozky s nahodnym prahem.
			   Muzeme vyuzit jakoukoli slozku (R, G, B), protoze
			   obrazek je sedotonovy, takze R=G=B */
			if (color.red > rand() % 255)
			{
				putPixel(x, y, COLOR_WHITE);
			}
			else
				putPixel(x, y, COLOR_BLACK);
		}
}
/*****************************************************************************/
/*****************************************************************************/