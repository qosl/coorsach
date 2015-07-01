#include "coppersmith_winograd.h"
int** coppersmith_winograd(int** A, int** B, int sz) {
	/* create square matrix C of size sz */
	int** C = new int*[sz];
	for (int i = 0; i < sz; i++) {
		/* create i-th row and fill it with 0 */
		C[i] = new int[sz];
		for (int j = 0; j < sz; j++) {
			C[i][j] = 0;
		}
	}
	/* base case  of recursion */
	if (sz == 2) {
		int e0 = A[1][0] + A[1][1];
		int e1 = e0 - A[0][0];
		int e2 = A[0][0] - A[1][0];
		int e3 = A[0][1] - e1;

		int n0 = B[0][1] - B[0][0];
		int n1 = B[1][1] - n0;
		int n2 = B[1][1] - B[0][1];
		int n3 = n1 - B[1][0];
		/* calculate matrices using only 7 multiplies */
		int p1 = e1 * n1;
		int p2 = A[0][0] * B[0][0];
		int p3 = A[0][1] * B[1][0];

		int p4 = e2 * n2;
		int p5 = e0 * n0;
		int p6 = e3 * B[1][1];
		int p7 = A[1][1] * n3;

		C[0][0] = p3 + p2;

		int z1 = p1 + p2;
		int z2 = z1 + p4;
		int z3 = z1 + p5;

		C[0][1] = z3 + p6;
		C[1][0] = z2 - p7;
		C[1][1] = z2 + p5;
	}
	else {
		/* partition matrix A */
		int** A_11 = new int*[sz / 2];
		int** A_12 = new int*[sz / 2];
		int** A_21 = new int*[sz / 2];
		int** A_22 = new int*[sz / 2];
		/* partition matrix B */
		int** B_11 = new int*[sz / 2];
		int** B_12 = new int*[sz / 2];
		int** B_21 = new int*[sz / 2];
		int** B_22 = new int*[sz / 2];
		/* partitiosz matrix C */
		int** C_11 = new int*[sz / 2];
		int** C_12 = new int*[sz / 2];
		int** C_21 = new int*[sz / 2];
		int** C_22 = new int*[sz / 2];
		/* fill A11, A12, ..., B11, ... C22 */
		for (int i = 0; i < sz; i++) {
			if (i < sz / 2) {
				A_11[i] = new int[sz / 2];
				A_12[i] = new int[sz / 2];
				A_21[i] = new int[sz / 2];
				A_22[i] = new int[sz / 2];

				B_11[i] = new int[sz / 2];
				B_12[i] = new int[sz / 2];
				B_21[i] = new int[sz / 2];
				B_22[i] = new int[sz / 2];

				C_11[i] = new int[sz / 2];
				C_12[i] = new int[sz / 2];
				C_21[i] = new int[sz / 2];
				C_22[i] = new int[sz / 2];
			}
			for (int j = 0; j < sz; j++) {
				if (i < sz / 2 && j < sz / 2) {
					A_11[i][j] = A[i][j];
					B_11[i][j] = B[i][j];
					C_11[i][j] = C[i][j];
				}
				if (i < sz / 2 && j >= sz / 2) {
					A_12[i][j - sz / 2] = A[i][j];
					B_12[i][j - sz / 2] = B[i][j];
					C_12[i][j - sz / 2] = C[i][j];
				}
				if (i >= sz / 2 && j < sz / 2) {
					A_21[i - sz / 2][j] = A[i][j];
					B_21[i - sz / 2][j] = B[i][j];
					C_21[i - sz / 2][j] = C[i][j];
				}
				if (i >= sz / 2 && j >= sz / 2) {
					A_22[i - sz / 2][j - sz / 2] = A[i][j];
					B_22[i - sz / 2][j - sz / 2] = B[i][j];
					C_22[i - sz / 2][j - sz / 2] = C[i][j];
				}
			}
		}
		/* create 7 P's */
		int** P1 = coppersmith_winograd(A_11, substract(B_12, B_22, sz / 2), sz / 2);
		int** P2 = coppersmith_winograd(add(A_11, A_12, sz / 2), B_22, sz / 2);
		int** P3 = coppersmith_winograd(add(A_21, A_22, sz / 2), B_11, sz / 2);
		int** P4 = coppersmith_winograd(A_22, substract(B_21, B_11, sz / 2), sz / 2);
		int** P5 = coppersmith_winograd(add(A_11, A_22, sz / 2),
										add(B_11, B_22, sz / 2), sz / 2);
		int** P6 = coppersmith_winograd(substract(A_12, A_22, sz / 2),
										add(B_21, B_22, sz / 2), sz / 2);
		int** P7 = coppersmith_winograd(substract(A_11, A_21, sz / 2),
										add(B_11, B_12, sz / 2), sz / 2);
		/* get matrices C11, C12, C21, C22 */
		C_11 = add(add(P5, P6, sz / 2), substract(P4, P2, sz / 2), sz / 2);
		C_12 = add(P1, P2, sz / 2);
		C_21 = add(P3, P4, sz / 2);
		C_22 = add(substract(P5, P3, sz / 2), substract(P1, P7, sz / 2), sz / 2);
		/* free memory: */
		delete P1;
		delete P2;
		delete P3;
		delete P4;
		delete P5;
		delete P6;
		delete P7;
		for (int i = 0; i < sz / 2; i++) {
			delete[] A_11[i]; 
			delete[] A_12[i]; 
			delete[] A_21[i]; 
			delete[] A_22[i];

			delete[] B_11[i]; 
			delete[] B_12[i]; 
			delete[] B_21[i]; 
			delete[] B_22[i];
		}
		delete[] A_11;
		delete[] A_12;
		delete[] A_21;
		delete[] A_22;

		delete[] B_11;
		delete[] B_12;
		delete[] B_21;
		delete[] B_22;
		/* assemble C11, C12, C21, C22 into C*/
		for (int i = 0; i < sz; i++) {
			for (int j = 0; j < sz; j++) {
				if (i < sz / 2 && j < sz / 2) {
					C[i][j] = C_11[i][j];
				}
				if (i < sz / 2 && j >= sz / 2) {
					C[i][j] = C_12[i][j - sz / 2];
				}
				if (i >= sz / 2 && j < sz / 2) {
					C[i][j] = C_21[i - sz / 2][j];
				}
				if (i >= sz / 2 && j >= sz / 2) {
					C[i][j] = C_22[i - sz / 2][j - sz / 2];
				}
			}
		}
		/* free memory: */
		for (int i = 0; i < sz / 2; i++) {
			delete[] C_11[i]; 
			delete[] C_12[i]; 
			delete[] C_21[i]; 
			delete[] C_22[i];
		}
	}
	return C;
}
