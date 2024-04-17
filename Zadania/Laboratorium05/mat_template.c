#include <stdio.h>
#include <math.h>
#include<stdlib.h> 

#define SIZE 40

void read_vector(double x[], int n) {
	for (int i = 0; i < n; ++i) {
		scanf("%lf", x++);
	}
}

void print_vector(double x[], int n) {
	for (int i = 0; i < n; ++i) {
		printf("%.4f ", x[i]);
	}
	printf("\n");
}

void read_mat(double A[][SIZE], int m, int n) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%lf", &A[i][j]);
		}
	}
}

void print_mat(double A[][SIZE], int m, int n) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%.4f ", A[i][j]);
		}
		printf("\n");
	}
}

// 1. Calculate matrix product, AB = A X B
// A[m][p], B[p][n], AB[m][n]
void mat_product(double A[][SIZE], double B[][SIZE], double AB[][SIZE], int m, int p, int n) {
	for (int a = 0; a < m; ++a)
	{
		for (int b = 0; b < n; ++b)
		{
			AB[a][b] = 0;
		}
	}
	for (int a = 0; a < m; ++a)
	{
		for (int b = 0; b < n; ++b)
		{
			for (int i = 0; i < p; ++i)
			{
				AB[a][b] += A[a][i] * B[i][b];
			}
		}
	}

}


// 2. Matrix triangulation and determinant calculation - simplified version
// (no rows' swaps). If A[i][i] == 0, function returns NAN.
// Function may change A matrix elements.
double gauss_simplified(double A[][SIZE], int n) {
	int currentCol = 0;
	for (int x = 0; x < n; ++x)
	{
		if (A[x][x] == 0)
		{
			return NAN;
		}
		for (int a = x + 1; a < n; ++a)
		{
			double coeff = A[a][x] / A[x][x];
			for (int b = x; b < n; ++b)
			{
				A[a][b] += -1 * coeff * A[x][b];
				if (a == b && A[a][b] == 0)
				{
					return NAN;
				}
			}
		}
		currentCol += 1;
	}

	double coefficient = A[0][0];

	for (int i = 1; i < n; ++i)
	{
		coefficient *= A[i][i];
	}
	return coefficient;
}

void backward_substitution_index(double A[][SIZE], const int indices[], double x[], int n) {
	for (int i = n - 1; i >= 0; --i)
	{
		for (int j = n - 1; j > i; --j)
		{
			x[indices[i]] -= x[indices[j]] * A[indices[i]][j];
		}
		x[indices[i]] /= A[indices[i]][i];
	}

	double tmp[n];

	for(int i = 0; i < n; ++i)
	{
		tmp[i] = x[indices[i]];
	}
	for(int i = 0; i < n; ++i)
	{
		x[i] = tmp[i];
	}

}

// 3. Matrix triangulation, determinant calculation, and Ax = b solving - extended version
// (Swap the rows so that the row with the largest, leftmost nonzero entry is on top. While
// swapping the rows use index vector - do not copy entire rows.)
// If max A[i][i] < eps, function returns 0.
// If det != 0 && b != NULL && x != NULL then vector x should contain solution of Ax = b.

double gauss(double A[][SIZE], const double b[], double x[], const int n, const double eps) {
	int rowsIndexes[n];

	for (int i = 0; i < n; ++i)
	{
		rowsIndexes[i] = i;
	}

	if (b != NULL && x != NULL)
	{
		for (int i = 0; i < n; ++i)
		{
			x[i] = b[i];
		}
	}

	int swaps = 0;
	for (int p = 0; p < n - 1; ++p)
	{
		for (int i = p + 1; i < n; ++i)
		{
			if (abs(A[rowsIndexes[i]][p]) > abs(A[rowsIndexes[p]][p]))
			{
				int tmp = rowsIndexes[i];
				rowsIndexes[i] = rowsIndexes[p];
				rowsIndexes[p] = tmp;
				swaps += 1;
			}
		}

		if (abs(A[rowsIndexes[p]][p]) < eps)
		{
			return -0;
		}
		for (int a = p + 1; a < n; ++a)
		{
			double coeff = A[rowsIndexes[a]][p] / A[rowsIndexes[p]][p];
			for (int b = p; b < n; ++b)
			{
				A[rowsIndexes[a]][b] += -1 * coeff * A[rowsIndexes[p]][b];
			}
			if (x != NULL)
			{
				//
				x[rowsIndexes[a]] += -1 * coeff * x[rowsIndexes[p]];
			}
		}
	}

	if (b != NULL && x != NULL)
	{
		backward_substitution_index(A, rowsIndexes, x, n);
	}

	double coefficient = A[rowsIndexes[0]][0];

	for (int i = 1; i < n; ++i)
	{
		coefficient *= A[rowsIndexes[i]][i];
	}
	if (swaps % 2 == 1)
	{
		coefficient *= -1;
	}
	return coefficient;

}

// 4. Returns the determinant; B contains the inverse of A (if det(A) != 0)
// If max A[i][i] < eps, function returns 0.
double matrix_inv(double A[][SIZE], double B[][SIZE], int n, double eps) {
	int rowsIndexes[n];

		for (int i = 0; i < n; ++i)
	{
		rowsIndexes[i] = i;
	}


	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n;++j)
		{
			B[i][j] = 0.0;

			if(i == j)
			{
				B[i][j] = 1.0;
			}		
		}	
	}


	

	double swaps = 1;
	for (int p = 0; p < n; ++p)
	{
		for (int i = p+1; i < n; ++i)
		{
			if (abs(A[rowsIndexes[i]][p]) > abs(A[rowsIndexes[p]][p]))
			{
				int tmp = rowsIndexes[i];
				rowsIndexes[i] = rowsIndexes[p];
				rowsIndexes[p] = tmp;
				swaps *= -1;
			}
		}


		if (abs(A[rowsIndexes[p]][p]) < eps && p != n-1)
		{
			return 0.0;
		}
		for (int a = 0; a < n; ++a)
		{
			if(a == p)
			{
				continue;
			}
			double coeff = A[rowsIndexes[a]][p] / A[rowsIndexes[p]][p];
			for (int b = 0; b < n; ++b)
			{
				A[rowsIndexes[a]][b] -= coeff * A[rowsIndexes[p]][b];
				B[rowsIndexes[a]][b] -= coeff * B[rowsIndexes[p]][b];
			}
		}

	

	}
	for(int i = 0; i < n; ++i)
	{

	double coeff = A[rowsIndexes[i]][i];
		

	for (int b = 0; b < n; ++b)
	{
		if(b==0)
				swaps*=(coeff);
		A[rowsIndexes[i]][b] /= coeff;
		B[rowsIndexes[i]][b] /= coeff;
	}
	}
		

	double tmp[n][n];

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
	{
		tmp[i][j] = B[rowsIndexes[i]][j];
	}
	}
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
	{
		B[i][j] = tmp[i][j];
	}
	}


	double coefficient = A[rowsIndexes[0]][0];

	for (int i = 1; i < n; ++i)
	{
		coefficient *= A[rowsIndexes[i]][i];
	}
	coefficient*=swaps;
	return coefficient;



}

int main(void) {

	double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
	double b[SIZE], x[SIZE], det, eps = 1.e-13;

	int to_do;
	int m, n, p;

	scanf("%d", &to_do);

	switch (to_do) {
	case 1:
		scanf("%d %d %d", &m, &p, &n);
		read_mat(A, m, p);
		read_mat(B, p, n);
		mat_product(A, B, C, m, p, n);
		print_mat(C, m, n);
		break;
	case 2:
		scanf("%d", &n);
		read_mat(A, n, n);
		printf("%.4f\n", gauss_simplified(A, n));
		break;
	case 3:
		scanf("%d", &n);
		read_mat(A, n, n);
		read_vector(b, n);
		det = gauss(A, b, x, n, eps);
		printf("%.4f\n", det);
		if (det) print_vector(x, n);
		break;
	case 4:
		scanf("%d", &n);
		read_mat(A, n, n);
		det = matrix_inv(A, B, n, eps);
		printf("%.4f\n", det);
		if (det) print_mat(B, n, n);
		break;
	default:
		printf("NOTHING TO DO FOR %d\n", to_do);
		break;
	}
	return 0;
}

