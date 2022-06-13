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
	double dist1a;
	double dist1b;
	double dist1c;
	double dist2a;
	double dist2b;
	double dist2c;

	printf("Trojuhelnik #1:\n");
	if (scanf(" { %lf , %lf , %lf }", &dist1a, &dist1b, &dist1c) == 3)
	{
		if ( ((fabs(dist1a) + fabs(dist1b)) > fabs(dist1c + 1E-6)) && ((fabs(dist1a) + fabs(dist1c)) > fabs(dist1b + 1E-6)) && ((fabs(dist1b) + fabs(dist1c)) > fabs(dist1a + 1E-6)) )
		{
		}
		else
		{
			printf("Neplatny trojuhelnik.\n");
			return 0;				
		}
	}
	else if (scanf(" [ %lf ; %lf ] , [ %lf ; %lf ] , [ %lf ; %lf ] }", &t1_ax, &t1_ay, &t1_bx, &t1_by, &t1_cx, &t1_cy) == 6)
	{
		if (fabs((t1_bx - t1_ax)*(t1_cy - t1_ay)-(t1_by - t1_ay)*(t1_cx - t1_ax)) <= 10 *DBL_EPSILON*(fabs((t1_bx - t1_ax)*(t1_cy - t1_ay)) + fabs((t1_by - t1_ay)*(t1_cx - t1_ax))))
		{
			printf("Neplatny trojuhelnik.\n");
			return 0;
		}
		else
		{
			double d1a_x = t1_bx - t1_cx;
			double d1b_x = t1_ax - t1_cx;
			double d1c_x = t1_ax - t1_bx;
			double d1a_y = t1_by - t1_cy;
			double d1b_y = t1_ay - t1_cy;
			double d1c_y = t1_ay - t1_by;
		
			dist1a = sqrt(d1a_x*d1a_x + d1a_y*d1a_y);
			dist1b = sqrt(d1b_x*d1b_x + d1b_y*d1b_y);
			dist1c = sqrt(d1c_x*d1c_x + d1c_y*d1c_y);
		}
	}
	else 
	{
		printf("Nespravny vstup.\n");
		return 0;
	}

	printf("Trojuhelnik #2:\n");
	if (scanf(" { %lf , %lf , %lf }", &dist2a, &dist2b, &dist2c) == 3)
	{
		if ( ((fabs(dist2a) + fabs(dist2b)) > fabs(dist2c + 1E-6)) && ((fabs(dist2a) + fabs(dist2c)) > fabs(dist2b + 1E-6)) && ((fabs(dist2b) + fabs(dist2c)) > fabs(dist2a + 1E-6)) )
		{
		}
		else
		{
			printf("Neplatny trojuhelnik.\n");
			return 0;			
		}
	}
	else if (scanf(" [ %lf ; %lf ] , [ %lf ; %lf ] , [ %lf ; %lf ] }", &t2_ax, &t2_ay, &t2_bx, &t2_by, &t2_cx, &t2_cy) == 6)
	{
		if (fabs((t2_bx - t2_ax)*(t2_cy - t2_ay)-(t2_by - t2_ay)*(t2_cx - t2_ax)) <= 10 *DBL_EPSILON*(fabs((t2_bx - t2_ax)*(t2_cy - t2_ay)) + fabs((t2_by - t2_ay)*(t2_cx - t2_ax))))
		{
			printf("Neplatny trojuhelnik.\n");
			return 0;
		}
		else
		{
			double d2a_x = t2_bx - t2_cx;
			double d2b_x = t2_ax - t2_cx;
			double d2c_x = t2_ax - t2_bx;
			double d2a_y = t2_by - t2_cy;
			double d2b_y = t2_ay - t2_cy;
			double d2c_y = t2_ay - t2_by;
	
			dist2a = sqrt(d2a_x*d2a_x + d2a_y*d2a_y);
			dist2b = sqrt(d2b_x*d2b_x + d2b_y*d2b_y);
			dist2c = sqrt(d2c_x*d2c_x + d2c_y*d2c_y);
		}
	}
	else 
	{
		printf("Nespravny vstup.\n");
		return 0;
	}




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
			else if ((dist1a + dist1b + dist1c) < (dist2a + dist2b + dist2c))
			{
			printf("Trojuhelnik #2 ma vetsi obvod.\n");
			}
		}
	}
	
	return 0;
	
}
