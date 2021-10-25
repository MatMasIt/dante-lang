#define stampa printf
#include <stdio.h>
#include <stdlib.h>
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
#include <math.h>



typedef struct

{	double x
;
	double y
;
	double z
;
}punto
;


   int
 distanza(punto a, punto b)
{	double x_inferiore, y_inferiore, z_inferiore
;
	double x_superiore, y_superiore, z_superiore
;
	double d_x, d_y, d_z
;
	x_inferiore = min(a.x,b.x)
;
	y_inferiore = min(a.y,b.y)
;
	z_inferiore = min(a.z,b.z)
;
	x_superiore = max(a.x,b.y)
;
	y_superiore = max(a.y,b.y)
;
	z_superiore = max(a.z,b.z)
;
	d_x = x_superiore - x_inferiore
;
	d_y = y_superiore - y_inferiore
;
	d_z = z_superiore - y_inferiore
;
	return sqrt(pow(d_x, 2)+pow(d_y, 2)+pow(d_z, 2))
;
}

int main()

{	punto a,b
;
	a.x = 2
;
	a.y = 1
;
	a.z = 3
;
	b.x = 5
;
	b.y = 10
;
	b.z = 7
;
	double dist = distanza(a,b)
;
	stampa("A=(%f,%f,%f)\n",a.x,a.y,a.z)
;
	stampa("B=(%f,%f,%f)\n",b.x,b.y,b.z)
;
	stampa("Distanza : %f\n",dist)
;
}
