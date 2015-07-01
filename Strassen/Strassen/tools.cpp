#include "tools.h"
#include "classic.h"
#include "coppersmith_winograd.h"
#include "strassen.h"

/* create matrix of size sz */
int** create_matrix(int n) {
	int new_n = n;
	if (!is_pow_of_2(n)) {
		new_n = change_matrix_size(n);
	}
	int** lol = new int*[new_n];
	for (int i = 0; i < new_n; i++) {
		lol[i] = new int[new_n];
		for (int j = 0; j < new_n; j++) {
			if (j >= n || i >= n) {
				lol[i][j] = 0;
				continue;
			}
			lol[i][j] = rand() % 10;
		}
	}
	return lol;
}
/* add matrices of size sz */
int** add(int** matr1, int** matr2, int sz) {
	int** lol = new int*[sz];
	for (int i = 0; i < sz; i++) {
		lol[i] = new int[sz];
		for (int j = 0; j < sz; j++) {
			lol[i][j] = matr1[i][j] + matr2[i][j];
		}
	}
	return lol;
}
/* substract matrices of size sz */
int** substract(int** matr1, int** matr2, int sz) {
	int** lol = new int*[sz];
	for (int i = 0; i < sz; i++) {
		lol[i] = new int[sz];
		for (int j = 0; j < sz; j++) {
			lol[i][j] = matr1[i][j] - matr2[i][j];
		}
	}
	return lol;
}
/* print matrix of size sz on screen */
void print_matrix(int** matr, int sz) {
	cout << endl;
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			cout << setw(4) << matr[i][j];
		}
		cout << endl;
	}
}
int change_matrix_size(int chislo) {
	int ret = 0;
	for (int i = 0; i < 100000; i++) {
		if (is_pow_of_2(i) && i > chislo) {
			ret = i;
			break;
		}
	}
	return ret;
}
bool is_pow_of_2(int a) {
	if (a == 1) return 0;
	return !(a&(a - 1));
}
void salutation() {
	cout << "This program multiplies matrices of size n using 3 different methods:\n"
		<< "1. Classic method.\n"
		<< "2. Strassen method.\n"
		<< "3. Coppersmith-Winograd method.\n";
	cout << "Enter n:";

}
int is_correct_input(string &n) {
	if (n.size() > 4) return 0;
	for (unsigned int i = 0; i < n.size(); i++) {
		if (!(int(n[i]) >= 48 && int(n[i]) <= 57)) {
			return 0;
		}
	}
	int ret = atoi(n.c_str());
	return ret;
}
void save_to_file(int** matr, char * name, int sz) {
	FILE *f = fopen(name, "w+");
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			char lol[8];
			itoa(matr[i][j], lol, 10);
			fprintf(f, "%7s", lol);
		}
		fputc('\n', f);
	}
}
void menu() {
	cout << "-----------------------------------------------------\n"
		<< "1. Compute matrix C by classic method.              |\n"
		<< "-----------------------------------------------------\n"
		<< "2. Compute matrix C by Strassen method.             |\n"
		<< "-----------------------------------------------------\n"
		<< "3. Compute matrix C by Coppersmith-Winograd method. |\n"
		<< "-----------------------------------------------------\n"
		<< "4. Save matrices A, B, C to files.                  |\n"
		<< "-----------------------------------------------------\n"
		<< "5. Exit                                             |\n"
		<< "-----------------------------------------------------\n";
}
int main_activity(string& lol) {
	int n = is_correct_input(lol);
	if (n == 0) {
		cout << "\nWrong input!\n";
		return -1;
	}
	system("cls");
	int** matrixC = NULL;

	int** matrixA = create_matrix(n);

	cout << "Matrix A: ";
	if (n > 19) cout << "too big for console output!" << endl;
	else print_matrix(matrixA, n);

	int** matrixB = create_matrix(n);

	cout << "Matrix B: ";
	if (n > 19) cout << "too big for console output!" << endl;
	else print_matrix(matrixB, n);

	int n_n = n;
	if (!is_pow_of_2(n)) {
		n_n = change_matrix_size(n);
	}
	menu();
	char key;
	do {
		fflush(stdin);
		cin >> key;
		if (!(int(key) >= 49 && int(key) <= 53)) {
			return -1;
		}
		switch (key) {
		case '1': {
			system("cls");
			clock_t begin = clock();
			matrixC = classic(matrixA, matrixB, n_n);
			clock_t end = clock();
			cout << "Matrix A: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixA, n);

			cout << "Matrix B: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixB, n);

			cout << "Matrix C: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixC, n);

			cout << "Matrix C of size " << n << " was computed by classic method." << endl;
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			cout << "Time taken by this method:" << elapsed_secs << endl;
			menu();
			break;
		}
		case '2': {
			system("cls");
			clock_t begin = clock();
			matrixC = strassen(matrixA, matrixB, n_n);
			clock_t end = clock();
			cout << "Matrix A: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixA, n);

			cout << "Matrix B: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixB, n);

			cout << "Matrix C: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixC, n);

			cout << "Matrix C of size " << n << " was computed by Strassen method." << endl;

			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			cout << "Time taken by this method:" << elapsed_secs << endl;
			menu();
			break;

		}
		case '3': {
			system("cls");
			clock_t begin = clock();
			matrixC = coppersmith_winograd(matrixA, matrixB, n_n);
			clock_t end = clock();
			cout << "Matrix A: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixA, n);

			cout << "Matrix B: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixB, n);

			cout << "Matrix C: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixC, n);

			cout << "Matrix C of size " << n << " was computed by Coppersmith-Winograd method." << endl;

			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			cout << "Time taken by this method:" << elapsed_secs << endl;
			menu();
			break;			
		}
		case '4': {
			system("cls");
			cout << "Matrix A: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixA, n);

			cout << "Matrix B: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixB, n);

			if (matrixC == NULL) {
				cout << "Compute matrix C first" << endl;
				menu();
				break;
			}
			cout << "Matrix C: ";
			if (n > 19) cout << "too big for console output!" << endl;
			else print_matrix(matrixC, n);

			cout << "Saving matrix A to file... ";
			save_to_file(matrixA, "A.txt", n);
			cout << "Done!" << endl;

			cout << "Saving matrix B to file... ";
			save_to_file(matrixB, "B.txt", n);
			cout << "Done!" << endl;

			cout << "Saving matrix C to file... ";
			save_to_file(matrixC, "C.txt", n);
			cout << "Done!" << endl;
			menu();
			break;
		}
		case '5': return 0;
		}
	} while (1);
}
