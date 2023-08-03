
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

MatrixReturnType createIntegerMatrix(
        MatrixSizeType columns,
        MatrixSizeType rows,
        IntegerMatrix* matrix)
{
	if(columns <= 0 || rows <= 0 || matrix == NULL){
		return matrix_return_allocation_error;
	}
	
	// matrix icin bellekten alan tahsis etme: 
	*matrix = (int**)malloc(rows * sizeof(int*));
	if(*matrix == NULL){
	
		return matrix_return_allocation_error;
	}
	
	// her bir satir icin bellekten alan tahsisi:
	for(MatrixSizeType i = 0; i<rows; i++){
		(*matrix)[i] = (int*)malloc(columns * sizeof(int));
		if((*matrix)[i] == NULL){
			// alan tahsisi sirasinda bir hata varsa ayrilan alani serbest birak ve hata don:
			/*for(MatrixSizeType j = 0; j<i; j++){
				free((*matrix)[j]);
			}
			*/free(*matrix);
			return matrix_return_allocation_error;
		}
	}
	
	return matrix_return_success;
    
}

void destroyIntegerMatrix(IntegerMatrix matrix)
{
	if(matrix != NULL){
		for(MatrixSizeType i = 0; matrix[i] != NULL; i++){
			free(matrix[i]);
		}
		free(matrix);
	}
}

MatrixReturnType readIntegerMatrix(
        const char* filename,
        MatrixSizeType* columns,
        MatrixSizeType* rows,
        IntegerMatrix* matrix)
{

    FILE* file;
    file = fopen(filename, "r");
    if (!file)
    {
        return matrix_return_file_io_error;
    }
    
    fread(columns, sizeof(MatrixSizeType), 1, file);
    fread(rows, sizeof(MatrixSizeType), 1, file);
    
    // Bellekten matris için alan tahsis etme
    *matrix = (IntegerMatrix)malloc(sizeof(int*) * (*rows));
    for (MatrixSizeType i = 0; i < *rows; i++)
    {
        (*matrix)[i] = (int*)malloc(sizeof(int) * (*columns));
    }

    // Matrisi dosyadan okuma ve matris elemanlarına atama
    for (MatrixSizeType row = 0; row < *rows; row++)
    {
        for (MatrixSizeType col = 0; col < *columns; col++)
        {
            if (fread(&((*matrix)[row][col]), sizeof(int), 1, file) != 1)
            {
                fclose(file);
                destroyIntegerMatrix(*matrix); // Bellek temizleme
                return matrix_return_file_io_error;
            }
        }
    }

    fclose(file);
    return matrix_return_success;
   
}
   

MatrixReturnType writeIntegerMatrix(
        const char* filename,
        MatrixSizeType columns,
        MatrixSizeType rows,
        IntegerMatrix matrix)
{
	FILE* file;
    file = fopen(filename, "w");
   if (!file)
    {
        return matrix_return_file_io_error;
    }
    if ( fwrite(&rows, sizeof(int), 1, file) != 1)
    {
        return matrix_return_file_io_error;
    }
    if ( fwrite(&columns, sizeof(int), 1, file) != 1 )
    {
        return matrix_return_file_io_error;
    }
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            if (fwrite( &(matrix[row*(rows-1)+col]), sizeof(int), 1, file) != 1)
            {
                fclose(file);
                return matrix_return_file_io_error;
            }
        }
    }
    fclose(file);
    return matrix_return_success;

    
}

MatrixReturnType multiplyMatrix(
        IntegerMatrix matrix1,
        MatrixSizeType columns1,
        MatrixSizeType rows1,
        IntegerMatrix matrix2,
        MatrixSizeType columns2,
        MatrixSizeType rows2,
        IntegerMatrix* result)
{
	  // Çarpma işleminin yapılabilirliğini kontrol et.
    if (columns1 != rows2) {
        return matrix_return_invalid_size_error;
    }

    // Sonuç matrisini olusturmak icin bellekte yer ayırma:
    MatrixReturnType createResult = createIntegerMatrix(columns2, rows1, result);
    if (createResult != matrix_return_success) {
        return createResult; // Bellek hatası veya geçersiz boyut hatası durumunda dönüş yapar
    }

    // Matris carpimi:
    for (MatrixSizeType i = 0; i < rows1; i++) {
        for (MatrixSizeType j = 0; j < columns2; j++) {
            (*result)[i][j] = 0;
            for (MatrixSizeType k = 0; k < columns1; k++) {
                (*result)[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return matrix_return_success;
}

