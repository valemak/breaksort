# http://vk.com/alex.tovstoles?w=note161701071_11713788
#include <stdio.h>
#include <stdbool.h>

#define ZOOM 16// эта константа отвечает за то, на какие по размеру части будет разбит вспомогательный массив
// можно попробовать её менять

void breaksort(int massiv[], int n) {
	int a;
	int zoom = ZOOM; //Количество классов
	//Шаг 1. Пузырьковым методом перемещаем минимальный элемент в начало массива
	//Возможно, эффективнее будет сделать это выбором.
	for(int i = n - 1; i > 0; i--) {
		if(massiv[i] < massiv[i - 1]) {
			a = massiv[i];
			/* 1 x N */
			massiv[i] = massiv[i - 1];
			massiv[i - 1] = a;
		}
	}
	//Шаг 2. Пузырьковым методом перемещаем максимальный элемент в конец массива
	//Возможно, эффективнее будет сделать это выбором.
	for(int i = 2; i < n; i++)	{
		if(massiv[i] < massiv[i - 1]) {
			a = massiv[i];
			/* 1 x N */
			massiv[i] = massiv[i - 1];
			massiv[i - 1] = a;
		}
		massiv[i - 1] -= massiv[0];
	}
	//Шаг 3. Проверяем, не состоит ли массив из одинаковых элементов?
	//Зачем это?
	massiv[n - 1] -= massiv[0];//В последнем элементе - храним разницу между максимумом и минимумом
	if(massiv[n - 1] == 0) {//Если разница = 0, то максимум = минимум
		for(int i = 1; i < n; i++) {
			massiv[i] = massiv[0];//Восстанавливаем массив
		}
		return;//Если массив состоит из одинаковых элементов, то значит он отсортирован и завершаем процедуру
	}
	//Шаг 4. Из каких классов есть элементы в массиве?
	int b = massiv[n - 1] / zoom;//Из разницы между минимумом и максимумом выясняем диапазон каждого класса (он одинаков у всех)
	bool c[2 + b];//Массив из true/false, в котором отмечено для каких классов есть в массиве элементы соотвутствующего размера (количество элементов не подсчитывается)
//	for(int i = 0; i < 2 + b; i++){c[i] = 0;}
	c[0] = 1;
	c[1] = 1;	
	for(int i = 1; i < n; i++) {
		int d = 1 + massiv[i] / zoom;
		/* 1 x N */
		if(c[d] == 0) c[d] = 1;
	}
	//Шаг 5. Сколько раз встречается true+false для соседних классов 
	int e = 0;
	for(int i = 1; i <= b; i++) {
		/* 1 x (MAX - MIN) / zoom */
		if(c[i] == 0 && c[i - 1] == 1) e++;
	}
	e++;	
	int f[e + 1];
//	for(int i = 0; i < e; i++){f[i] = 0;}
	f[0] = zoom;
	f[e] = b;
	int g[e];
//	for(int i = 0; i < e; i++){g[i] = 0;}
	int h = 1;
	int m = 1 + b;
	for(int i = 1; i <= m; i {
		if(c[i] == 0 && c[i - 1] == 1) {
			f[h] = i - 2;
			/* 1 x (MAX - MIN) / zoom */
			h++;
		}
	}
	h = 1;
	for(int i = 1; i <= m; i++) {
		if(c[i] == 1 && c[i - 1] == 0) {
			g[h] = i;
			/* 1 x (MAX - MIN) / zoom */
			h++;
		}
	}
	for(int i = 1; i < e; i++) {
		f[i] = f[0] * f[i];
	}
	for(int i = 1; i < e; i++) {
		g[i] = f[0] * g[i] - 1;
	}
	f[e] = massiv[n - 1];
	int o[e + 1];
	for(int i = 1; i < n; i++) {
		for(int k = 1; k < e; k++) {
			if(massiv[i] > f[k] && massiv[i] < f[k] + f[0]) {
				f[k] = massiv[i];
				break;
			}
		}
		for(int k = 1; k < e; k++) {
			if(massiv[i] < g[k] && massiv[i] > g[k] - f[0]) {
				g[k] = massiv[i];
				break;
			}
		}
	}
	o[0] = 0;
	for(int i = 1; i <= e; i++) {
		o[i] = 1 + f[i] - g[i - 1];
		o[0] += o[i];
	}
	int q[o[0] + 1];
//	for (int i = 0, z = o[0] + 1; i < z; i++){q[i] = 0;}
	q[1] = 1;
	for(int i = 1; i < n; i++) {
		h = 0;
		for(int k = 1; k <= e; k++) {
			if(g[k - 1] <= massiv[i] && massiv[i] <= f[k]) {
				m = massiv[i] - g[k - 1] + h + 1;
				q[m]++;
				break;
			}
			h += o[k];
		}
	}
	a = 0;
	h = 0;
	m = - 1;
	for(int i = 1; i <= e; i++) {
		if(i > 1) a += o[i - 1];
		for(int j = 1; j <= o[i]; j++) {
			h++;
			for(int k = 1; k <= q[h]; k++) {
				m++;
				massiv[m] = massiv[0] + g[i - 1] + h - a - 1;
			}
		}
	}
}
