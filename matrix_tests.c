
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    true  = 1,
    false = 0
}Boolean;

char const passed_message[] = "PASS";
char const fail_message[] = "FAIL";

/**
 * @brief Macro to call a unit test and print its result
 */
#define TEST(x)                                                                         \
                do                                                                      \
                {                                                                       \
                    printf("%s(): %s\n", #x, x() ? passed_message : fail_message);      \
                }                                                                       \
                while(0)
                

Boolean testCreateIntegerMatrix()
{
    // Test case:
    MatrixSizeType columns = 3;
    MatrixSizeType rows = 2;
    IntegerMatrix matrix = NULL;
    MatrixReturnType result = createIntegerMatrix(columns, rows, &matrix);
    if (result != matrix_return_success || matrix == NULL)
        return false;

    // Test case: columns and rows are 0, expect an allocation error
    columns = 0;
    rows = 0;
    result = createIntegerMatrix(columns, rows, &matrix);
    if (result != matrix_return_allocation_error)
        return false;

    // Test case: columns is negative, expect an allocation error
    columns = -2;
    rows = 4;
    result = createIntegerMatrix(columns, rows, &matrix);
    if (result != matrix_return_allocation_error)
        return false;
        

    // If all test cases pass, return true:
    return true;
}

Boolean testDestroyIntegerMatrix(){
	
	MatrixSizeType columns = 5;
	MatrixSizeType rows = 16;
	
	IntegerMatrix matrix = NULL;
	
	MatrixReturnType result2 = createIntegerMatrix(columns,rows,&matrix);

	if(result2 == matrix_return_success){
		destroyIntegerMatrix(matrix);
		if(matrix[0] == NULL){
			return true;
		}
	}
	return false;
}


Boolean testReadIntegerMatrix(){
    const char* filename = "testfile.mtx";
    MatrixSizeType columns;
    MatrixSizeType rows;
    IntegerMatrix matrix = NULL;
    
    MatrixReturnType result = readIntegerMatrix(filename, &columns, &rows, &matrix);
    if (result == matrix_return_success) {
        // Matrisi ekrana yazdırma
        printf("Matris:\n");
        for (MatrixSizeType i = 0; i < rows; i++) {
            for (MatrixSizeType j = 0; j < columns; j++) {
                printf("%d\n", matrix[i][j]);
            }
            printf("\n");
        }

        return true;
    } else {
        // Hata durumunu ekrana yazdırma
        printf("Dosya okuma hatasi: ");
        if (result == matrix_return_file_io_error) {
            printf("Dosya islem hatasi\n");
        } else if (result == matrix_return_allocation_error) {
            printf("Bellek tahsisi hatasi\n");
        } 
        return false;
    }
    
}

Boolean testWriteIntegerMatrix(){
    const char* filename = "testfile.mtx";
    const char* writefilename = "writetestfile.mtx";
    MatrixSizeType columns;
    MatrixSizeType rows;
    IntegerMatrix matrix = (IntegerMatrix)malloc(sizeof(int**) * 6);
    for (int i = 0 ; i < 6; i++){
        matrix[i] = (int*)malloc(sizeof(int) * 5);
    }
    readIntegerMatrix(filename, &columns, &rows, &matrix);
    MatrixSizeType columns2;
    MatrixSizeType rows2;
    IntegerMatrix matrix2 = (IntegerMatrix)malloc(sizeof(int**) * 6);
    for (int i = 0 ; i < 6; i++){
        matrix2[i] = (int*)malloc(sizeof(int) * 5);
    }
    MatrixReturnType is_writed = writeIntegerMatrix(writefilename, columns, rows, matrix);
    if (is_writed != matrix_return_success){
        return false;
    }
    return true;
}

Boolean testMultiplyMatrix(){

    MatrixSizeType rows1 = 2;
    MatrixSizeType columns1 = 3;
    IntegerMatrix matrix1;
    MatrixReturnType createMatrix1Result = createIntegerMatrix(columns1, rows1, &matrix1);
    if (createMatrix1Result == matrix_return_success) {
        matrix1[0][0] = 1;
        matrix1[0][1] = 2;
        matrix1[0][2] = 3;
        matrix1[1][0] = 4;
        matrix1[1][1] = 5;
        matrix1[1][2] = 6;
    } else {
        printf("Hata: Matrix1 olusturulamadi.\n");
        return false;
    }

    MatrixSizeType rows2 = 3;
    MatrixSizeType columns2 = 2;
    IntegerMatrix matrix2;
    MatrixReturnType createMatrix2Result = createIntegerMatrix(columns2, rows2, &matrix2);
    if (createMatrix2Result == matrix_return_success) {
        matrix2[0][0] = 7;
        matrix2[0][1] = 8;
        matrix2[1][0] = 9;
        matrix2[1][1] = 10;
        matrix2[2][0] = 11;
        matrix2[2][1] = 12;
    } else {
        printf("Hata: Matrix2 olusturulamadi.\n");
        return false;
    }

    IntegerMatrix result;
    MatrixReturnType multiplyResult = multiplyMatrix(matrix1, columns1, rows1, matrix2, columns2, rows2, &result);

    if (multiplyResult == matrix_return_success) {
        printf("Carpim sonucu matris:\n");
        for (MatrixSizeType i = 0; i < rows1; i++) {
            for (MatrixSizeType j = 0; j < columns2; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    } else if (multiplyResult == matrix_return_invalid_size_error) {
        printf("Matrisler carpilamaz.\n");
        return false;
    } else if (multiplyResult == matrix_return_allocation_error) {
        printf("Bellekte yer ayirmada hata.\n");
        return false;
    }


    return true;
    
   
}

int main()
{
//TODO: Add unit tests here.

	TEST(testCreateIntegerMatrix);
	TEST(testDestroyIntegerMatrix);
	TEST(testReadIntegerMatrix);
	TEST(testWriteIntegerMatrix);
	TEST(testMultiplyMatrix);
    return 0;
}
