typedef struct{
    void** data;
    int line;
    int column;
    int type;
}Matrix;
Matrix* create_matrix(int line, int column, int type);
void free_matrix(Matrix* mat);
int input_matrix(Matrix*mat);
int print_matrix(Matrix*mat);
int check_type_matrix(Matrix*a, Matrix*b);
Matrix*add_matrices(Matrix*a, Matrix*b);
Matrix*multiplication_matrices(Matrix*a, Matrix*b);
Matrix*transposition_matrix(Matrix*mat);
Matrix*AddLinearCombination(Matrix*mat, int target_line, int line1, int line2, void* coeff1, void* coeff2);