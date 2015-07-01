#include "strassen.h"

int** strassen(int** A, int** B, int sz) {
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
	if (sz == 128) {
		for (int i = 0; i < sz; i++) {
			for (int k = 0; k < sz; k++) {
				for (int j = 0; j < sz; j++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		//C[0][0] = A[0][0] * B[0][0];
	}
	else {
		/* partition matrix A into 4 submatrices */
		int** A_11 = new int*[sz / 2];
		int** A_12 = new int*[sz / 2];
		int** A_21 = new int*[sz / 2];
		int** A_22 = new int*[sz / 2];
		/* partition matrix B into 4 submatrices */
		int** B_11 = new int*[sz / 2];
		int** B_12 = new int*[sz / 2];
		int** B_21 = new int*[sz / 2];
		int** B_22 = new int*[sz / 2];
		/* partition matrix C into 4 submatrices */
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
		int** P1 = strassen(A_11, substract(B_12, B_22, sz / 2), sz / 2);
		int** P2 = strassen(add(A_11, A_12, sz / 2), B_22, sz / 2);
		int** P3 = strassen(add(A_21, A_22, sz / 2), B_11, sz / 2);
		int** P4 = strassen(A_22, substract(B_21, B_11, sz / 2), sz / 2);
		int** P5 = strassen(add(A_11, A_22, sz / 2), 
							add(B_11, B_22, sz / 2), sz / 2);
		int** P6 = strassen(substract(A_12, A_22, sz / 2), 
							add(B_21, B_22, sz / 2), sz / 2);
		int** P7 = strassen(substract(A_11, A_21, sz / 2), 
							add(B_11, B_12, sz / 2), sz / 2);
		/* get matrices C11, C12, C21, C22 */
		C_11 = add(add(P5, P6, sz / 2), substract(P4, P2, sz / 2), sz / 2);
		C_12 = add(P1, P2, sz / 2);
		C_21 = add(P3, P4, sz / 2);
		C_22 = add(substract(P5, P3, sz / 2), substract(P1, P7, sz / 2), sz / 2);
		/* free memory: */

		for (int i = 0; i < sz / 2; i++) {
			delete[] A_11[i]; 
			delete[] A_12[i]; 
			delete[] A_21[i]; 
			delete[] A_22[i];

			delete[] B_11[i]; 
			delete[] B_12[i]; 
			delete[] B_21[i]; 
			delete[] B_22[i];
			delete[] P1[i];
			delete[] P2[i];
			delete[] P3[i];
			delete[] P4[i];
			delete[] P5[i];
			delete[] P6[i];
			delete[] P7[i];
		}
		delete[] A_11;
		delete[] A_12;
		delete[] A_21;
		delete[] A_22;

		delete[] B_11;
		delete[] B_12;
		delete[] B_21;
		delete[] B_22;
		
		delete[] P1;
		delete[] P2;
		delete[] P3;
		delete[] P4;
		delete[] P5;
		delete[] P6;
		delete[] P7;

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
		for (int i = 0; i < sz / 2; i++) {
			delete[] C_11[i]; 
			delete[] C_12[i]; 
			delete[] C_21[i]; 
			delete[] C_22[i];
		}
	}
	return C;
}
