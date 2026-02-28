typedef struct{
    void** data;
    int line;
    int column;
    int type;
}Matrix;
Matrix* create_matrix(int line, int column, int type);
void free_matrix(Matrix* mat);
void input_matrix(Matrix*mat);
void print_matrix(Matrix*mat);
int check_type_matrix(Matrix*a, Matrix*b);
Matrix*add_matrices(Matrix*a, Matrix*b);
Matrix*multiplication_matrices(Matrix*a, Matrix*b);
Matrix*transposition_matrix(Matrix*mat);
