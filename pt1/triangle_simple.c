#include <stdio.h>
#include <math.h>
#include <float.h>

int main()
{
	double t1_ax;
	double t1_ay;
	double t1_bx;
	double t1_by;
	double t1_cx;
	double t1_cy;
	double t2_ax;
	double t2_ay;
	double t2_bx;
	double t2_by;
	double t2_cx;
	double t2_cy;
	printf("Trojuhelnik #1:\n");
	printf("Bod A:\n");
	if (scanf("%lf %lf", &t1_ax, &t1_ay) != 2)
	{
		printf("Nespravny vstup.\n");
	}
	else 
	{
	printf("Bod B:\n");	
	if (scanf("%lf %lf", &t1_bx, &t1_by) != 2)
	{
		printf("Nespravny vstup.\n");
	}
	else
	{
	printf("Bod C:\n");
	if (scanf("%lf %lf", &t1_cx, &t1_cy) != 2)
	{
		printf("Nespravny vstup.\n");
	}
	else
	{
	if (fabs((t1_bx - t1_ax)*(t1_cy - t1_ay)-(t1_by - t1_ay)*(t1_cx - t1_ax)) <= 10 *DBL_EPSILON*(fabs((t1_bx - t1_ax)*(t1_cy - t1_ay)) + fabs((t1_by - t1_ay)*(t1_cx - t1_ax))))
	{
		printf("Body netvori trojuhelnik.\n");
	}
	else
	{
	printf("Trojuhelnik #2:\n");
	printf("Bod A:\n");
	if (scanf("%lf %lf", &t2_ax, &t2_ay) != 2)
	{
		printf("Nespravny vstup.\n");
	}
	else 
	{
	printf("Bod B:\n");
	if (scanf("%lf %lf", &t2_bx, &t2_by) != 2)
	{
		printf("Nespravny vstup.\n");		
	}
	else
	{
	printf("Bod C:\n");
	if (scanf("%lf %lf", &t2_cx, &t2_cy) != 2)
	{
		printf("Nespravny vstup.\n");
	}
	else
	{
	if (fabs((t2_bx - t2_ax)*(t2_cy - t2_ay)-(t2_by - t2_ay)*(t2_cx - t2_ax)) <= 10 *DBL_EPSILON*(fabs((t2_bx - t2_ax)*(t2_cy - t2_ay)) + fabs((t2_by - t2_ay)*(t2_cx - t2_ax))))
	{
		printf("Body netvori trojuhelnik.\n");
	}
	else 
	{
	double d1a_x = t1_bx - t1_cx;
	double d1b_x = t1_ax - t1_cx;
	double d1c_x = t1_ax - t1_bx;
	double d1a_y = t1_by - t1_cy;
	double d1b_y = t1_ay - t1_cy;
	double d1c_y = t1_ay - t1_by;
	
	double dist1a = sqrt(d1a_x*d1a_x + d1a_y*d1a_y);
	double dist1b = sqrt(d1b_x*d1b_x + d1b_y*d1b_y);
	double dist1c = sqrt(d1c_x*d1c_x + d1c_y*d1c_y);

	double d2a_x = t2_bx - t2_cx;
	double d2b_x = t2_ax - t2_cx;
	double d2c_x = t2_ax - t2_bx;
	double d2a_y = t2_by - t2_cy;
	double d2b_y = t2_ay - t2_cy;
	double d2c_y = t2_ay - t2_by;

	double dist2a = sqrt(d2a_x*d2a_x + d2a_y*d2a_y);
	double dist2b = sqrt(d2b_x*d2b_x + d2b_y*d2b_y);
	double dist2c = sqrt(d2c_x*d2c_x + d2c_y*d2c_y);

  	if ( dist1a > dist1c )
  	{
  	  double tmp = dist1a;
  	  dist1a = dist1c;
  	  dist1c = tmp;
  	}
  	if ( dist1b > dist1c )
  	{
  	  double tmp = dist1b;
  	  dist1b = dist1c;
  	  dist1c = tmp;
  	}

  	if ( dist2a > dist2c )
  	{
  	  double tmp = dist2a;
  	  dist2a = dist2c;
  	  dist2c = tmp;
  	}
  	if ( dist2b > dist2c )
  	{
  	  double tmp = dist2b;
  	  dist2b = dist2c;
  	  dist2c = tmp;
  	}

	if ( (dist1a / dist2a) == (dist1b / dist2b) && (dist1b / dist2b) == (dist1c / dist2c))
	{
		printf("Trojuhelniky jsou shodne.\n");
	}
	else
	{
		if ( fabs((dist1a + dist1b + dist1c) - (dist2a + dist2b + dist2c)) <= 10 *DBL_EPSILON*(fabs((dist1a + dist1b + dist1c)) + fabs((dist2a + dist2b + dist2c))) )
		{
			printf("Trojuhelniky nejsou shodne, ale maji stejny obvod.\n");
		}
		else
		{
			if ((dist1a + dist1b + dist1c) > (dist2a + dist2b + dist2c))
			{
			printf("Trojuhelnik #1 ma vetsi obvod.\n");
			}
			else 
			{
			printf("Trojuhelnik #2 ma vetsi obvod.\n");
			}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}

	
	return 0;
	
}
