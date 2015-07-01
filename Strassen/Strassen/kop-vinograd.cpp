#include "tools.h"
vector<vector<int> > kopVinogradMultiply(vector<vector<int> >& A, 
											vector<vector<int> >& B) {
	unsigned short int n = A.size();
	/* create square matrix C of size n */
	vector<vector<int> > C(n);
	for (unsigned short int i = 0; i < n; i++) {
		C[i].resize(n);
	}	
	/* base case  of recursion */
    if (n == 2) {

		int e0 = A[1][0] + A[1][1];
		int e1 = e0 - A[0][0];
		int e2 = A[0][0] - A[1][0];
		int e3 = A[0][1] - e1;
		
		int n0 = B[0][1] - B[0][0];
		int n1 = B[1][1] - n0;
		int n2 = B[1][1] - B[0][1];
		int n3 = n1 - B[1][0];

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
		// always 2
		//for (unsigned short int i = 0; i < n; i++) {
		//	for (unsigned short int k = 0; k < n; k++) {
		//		for (unsigned short int j = 0; j < n; j++) {
		//			C[i][j] += A[i][k] * B[k][j];
		//		}
		//	}
		//}
		// int E1 = A[0][0] + B[0][1]; // AND SO ON...
	}
	else {
	/* partition matrix A */
	vector<vector<int> > A_11(n/2);
	vector<vector<int> > A_12(n/2);
	vector<vector<int> > A_21(n/2);
	vector<vector<int> > A_22(n/2);
	/* partition matrix B */
	vector<vector<int> > B_11(n/2);
	vector<vector<int> > B_12(n/2);
	vector<vector<int> > B_21(n/2);
	vector<vector<int> > B_22(n/2);
	/* partition matrix C */
	vector<vector<int> > C_11(n/2);
	vector<vector<int> > C_12(n/2);
	vector<vector<int> > C_21(n/2);
	vector<vector<int> > C_22(n/2);
		/* fill A11, A12, ..., B11, ... C22 */
		for (unsigned short int i = 0; i < n; i++) {
			if (i < n/2) {
				A_11[i].resize(n/2);
				A_12[i].resize(n/2);
				A_21[i].resize(n/2);
				A_22[i].resize(n/2);

				B_11[i].resize(n/2);
				B_12[i].resize(n/2);
				B_21[i].resize(n/2);
				B_22[i].resize(n/2);

				C_11[i].resize(n/2);
				C_12[i].resize(n/2);
				C_21[i].resize(n/2);
				C_22[i].resize(n/2);
			}
			for (unsigned short int j = 0; j < n; j++) {
				if (i < n/2 && j < n/2) {
					A_11[i][j] = A[i][j];
					B_11[i][j] = B[i][j];
					C_11[i][j] = C[i][j];
				}
				if (i < n/2 && j >= n/2) {
					A_12[i][j - n/2] = A[i][j];
					B_12[i][j - n/2] = B[i][j];
					C_12[i][j - n/2] = C[i][j];
				}
				if (i >= n/2 && j < n/2) {
					A_21[i - n/2][j] = A[i][j];
					B_21[i - n/2][j] = B[i][j];
					C_21[i - n/2][j] = C[i][j];
				}
				if (i >= n/2 && j >= n/2) {
					A_22[i - n/2][j - n/2] = A[i][j];
					B_22[i - n/2][j - n/2] = B[i][j];
					C_22[i - n/2][j - n/2] = C[i][j];
				}	
			}
		}
		/* create 4 C's */
		C_11 = add(kopVinogradMultiply(A_11, B_11), kopVinogradMultiply(A_12, B_21));
		C_12 = add(kopVinogradMultiply(A_11, B_12), kopVinogradMultiply(A_12, B_22));
		C_21 = add(kopVinogradMultiply(A_21, B_11), kopVinogradMultiply(A_22, B_21));
		C_22 = add(kopVinogradMultiply(A_21, B_12), kopVinogradMultiply(A_22, B_22));
		/* assemble C11, C12, C21, C22 into C*/
		for (unsigned short int i = 0; i < n; i++) {
			for (unsigned short int j = 0; j < n; j++) {
				if (i < n / 2 && j < n / 2) {
					C[i][j] = C_11[i][j];
				}
				if (i < n / 2 && j >= n / 2) {
					C[i][j] = C_12[i][j - n / 2];
				}
				if (i >= n / 2 && j < n / 2) {
					C[i][j] = C_21[i - n / 2][j];
				}
				if (i >= n / 2 && j >= n / 2) {
					C[i][j] = C_22[i - n / 2][j - n / 2];
				}
			}
		}
	}
	return C;
}
