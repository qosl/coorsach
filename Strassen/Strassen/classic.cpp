#include "classic.h"
int** classic(int** A, int** B, int sz){
	/* create square matrix C of size sz */
	int** C = new int*[sz];
	for(int i = 0; i < sz; i++) {
		C[i] = new int[sz];
		for (int j = 0; j < sz; j++) {
			C[i][j] = 0;
		}
	}
	for (int i = 0; i < sz; i++) {
		for (int k = 0; k < sz; k++) {
			for (int j = 0; j < sz; j++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}