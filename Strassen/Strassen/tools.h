#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
int** create_matrix(int);
int** add(int**, int**, int);
int** substract(int**, int**, int);
void print_matrix(int**, int);
bool is_pow_of_2(int);
int change_matrix_size(int);
int main_activity(string &);
void salutation();
int is_correct_input(string &);
void save_to_file(int**, char*, int);

