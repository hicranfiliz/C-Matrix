

#ifndef CABOT_MATRIX_H_INCLUDED
#define CABOT_MATRIX_H_INCLUDED


typedef int** IntegerMatrix;

typedef enum
{
    matrix_return_success,
    matrix_return_allocation_error,
    matrix_return_file_io_error,
    matrix_return_invalid_size_error
}MatrixReturnType;

typedef unsigned int MatrixSizeType;


MatrixReturnType createIntegerMatrix(
        MatrixSizeType columns,
        MatrixSizeType rows,
        IntegerMatrix* matrix);

void destroyIntegerMatrix(IntegerMatrix matrix);


MatrixReturnType readIntegerMatrix(
        const char* filename,
        MatrixSizeType* columns,
        MatrixSizeType* rows,
        IntegerMatrix* matrix);

MatrixReturnType writeIntegerMatrix(
        const char* filename,
        MatrixSizeType columns,
        MatrixSizeType rows,
        IntegerMatrix matrix);



MatrixReturnType multiplyMatrix(
        IntegerMatrix matrix1,
        MatrixSizeType columns1,
        MatrixSizeType rows1,
        IntegerMatrix matrix2,
        MatrixSizeType columns2,
        MatrixSizeType rows2,
        IntegerMatrix* result);


#endif /* CABOT_MATRIX_H_INCLUDED */
