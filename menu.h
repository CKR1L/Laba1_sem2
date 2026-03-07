#ifndef MENU_H
#define MENU_H
#include "matrix.h"
void display_menu();
void menu_choice(int choice, Matrix**mat1, Matrix**mat2);
int line_combination(Matrix*mat, const char* matrix_name);
void run_prog();
void run_test();
#endif