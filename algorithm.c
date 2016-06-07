#include <stdio.h>
#include <stdbool.h>

#define ZOOM 8

void sort(int massiv[], int n)
{
	int a;
	int zoom = ZOOM;
	for (int i = n - 1; i > 0; i--)
	{
		if (massiv[i] < massiv[i - 1])
		{
			a = massiv[i];
			massiv[i] = massiv[i - 1];
			massiv[i - 1] = a;
		}
	}
	for (int i = 2; i < n; i++)
	{
		if (massiv[i] < massiv[i - 1])
		{
			a = massiv[i];
			massiv[i] = massiv[i - 1];
			massiv[i - 1] = a;
		}
		massiv[i - 1] -= massiv[0];
	}
	massiv[n - 1] -= massiv[0];
	int b = massiv[n - 1] / zoom;
	bool c[1 + b];
	for (int i = 0; i < b; i++){c[i] = 0;}
	c[0] = 1;
	c[1] = 1;
	for (int i = 1; i < n; i++)
	{
		int d = 1 + massiv[i] / zoom;
		if (c[d] == 0) c[d] = 1;
	}
	int e = 0;
	for (int i = 1, z = b + 1; i < z; i++)
	{
		if (c[i] == 0 && c[i - 1] == 1) e++;
	}
	e++;
	int f[e + 1];
	for (int i = 0; i < e; i++){f[i] = 0;}
	f[0] = zoom;
	f[e] = b;
	int g[e];
	for (int i = 0; i < e; i++){g[i] = 0;}
	int h = 1;
	int m = 1 + b;
	for (int i = 1; i <= m; i++)
	{
		if (c[i] == 0 && c[i - 1] == 1)
		{
			f[h] = i - 2;
			h++;
		}
	}
	h = 1;
	for (int i = 1; i <= m; i++)
	{
		if (c[i] == 1 && c[i - 1] == 0)
		{
			g[h] = i;
			h++;
		}
	}
	for(int i = 1; i < e; i++)
	{
		f[i] = f[0] * f[i];
	}
	for(int i = 1; i < e; i++)
	{
		g[i] = f[0] * g[i] - 1;
	}
	f[e] = massiv[n - 1];
	int o[e + 1];
	for(int i = 1; i < n; i++)
	{
		for(int k = 1; k < e; k++)
		{
			if (massiv[i] > f[k] && massiv[i] < f[k] + f[0])
			{
				f[k] = massiv[i];
				break;
			}
		}
		for(int k = 1; k < e; k++)
		{
			if (massiv[i] < g[k] && massiv[i] > g[k] - f[0])
			{
				g[k] = massiv[i];
				break;
			}
		}
	}
	o[0] = 0;
	for(int i = 1; i <= e; i++)
	{
		o[i] = 1 + f[i] - g[i - 1];
		o[0] += o[i];
	}
	int q[o[0] + 1];
	for (int i = 0, z = o[0] + 1; i < z; i++){q[i] = 0;}
	q[1] = 1;
	for(int i = 1; i < n; i++)
	{
		h = 0;
		for(int k = 1; k <= e; k++)
		{
			if (g[k - 1] <= massiv[i] && massiv[i] <= f[k])
			{
				m = massiv[i] - g[k - 1] + h + 1;
				q[m]++;
				break;
			}
			h += o[k];
		}
	}
	h = 0;
	m = - 1;
	a = 0;
	for(int i = 1; i <= e; i++)
	{
		if (i > 1) a += o[i - 1];
		for(int j = 1; j <= o[i]; j++)
		{
			h++;
			for(int k = 1; k <= q[h]; k++)
			{
				m++;
				massiv[m] = massiv[0] + g[i - 1] + h - a - 1;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		printf("%i ", massiv[i]);
	}
	printf("\nn = %i\n\n", n);
///*///
}
