
#ifndef MATRIX_H
#define MATRIX_H

#include<vector>
#include<stddef.h>
#include<iostream>
#include<cmath>
#include<armadillo>

namespace marfix_stt {

    /**
     * @brief ...
     *  This Class is dedicated for the matrix related operations...
     */
    class MatrixOperations {
    public:
        /**
         * @brief ...
         * This functions multiplies each element of first matrix to each element of second matrix, relative to the position.
         * @param matA p_matA:...The first input matrix
         * @param matB p_matB:...The second input matrix
         * @return std::vector< std::vector< double, std::allocator< double > >, std::allocator< std::vector< double, std::allocator< double > > > >  The resultant matrix
         */
        std::vector<std::vector<double>> Multiply(std::vector<std::vector<double>> matA, std::vector<std::vector<double>> matB);
        /**
         * @brief ...
         * This functions multiplies the given matrices and returns the resultant matrix
         * @param matA p_matA:...The first input matrix
         * @param matB p_matB:...The second input matrix
         * @return std::vector< std::vector< double, std::allocator< double > >, std::allocator< std::vector< double, std::allocator< double > > > >  The resultant matrix
         */
        std::vector<std::vector<double>> DotMultiply(std::vector<std::vector<double>> matA, std::vector<std::vector<double>> matB);
        /**
         * @brief ...
         * This functions return the tranpose of the given matrix
         * @param mat p_mat:... The input matrix
         * @return std::vector< std::vector< double, std::allocator< double > >, std::allocator< std::vector< double, std::allocator< double > > > > The tranpose of the given matrix
         */
        std::vector<std::vector<double>> Transpose(std::vector<std::vector<double>> mat);
        /**
         * @brief ...
         * This functions subtracts the given matrices and returns the resultant matrix
         * @param matA p_matA:...The first input matrix
         * @param matB p_matB:...The second input matrix
         * @return std::vector< std::vector< double, std::allocator< double > >, std::allocator< std::vector< double, std::allocator< double > > > >  The resultant matrix
         */
        std::vector<std::vector<double>> Subtract(std::vector<std::vector<double>> matA, std::vector<std::vector<double>> matB);
        /**
        * @brief ...
        * This functions adds the given matrices and returns the resultant matrix
        * @param matA p_matA:...The first input matrix
        * @param matB p_matB:...The second input matrix
        * @return std::vector< std::vector< double, std::allocator< double > >, std::allocator< std::vector< double, std::allocator< double > > > >  The resultant matrix
        */
        std::vector<std::vector<double>> Add(std::vector<std::vector<double>> matA, std::vector<std::vector<double>> matB);

        /**
         * @brief ...
         * This functions multiplies the given matrices and increments the result in the third matrix
         * @param matA p_matA:...The first input matrix
         * @param matB p_matB:...The second input matrix
         * @param matC p_matC:...The output matrix
         */
        void DotMultiplyAdd(std::vector<std::vector<double>> matA, std::vector<std::vector<double>> matB, std::vector<std::vector<double>>& matC);

        /**
         * @brief ...
         * This functions returns the absolute matrix of the given matrix
         * @param matA p_matA:...The input matrix
         * @return std::vector< std::vector< double, std::allocator< double > >, std::allocator< std::vector<      double, std::allocator< double > > > >  The resultant matrix after absolute
        */
        std::vector<std::vector<double>> Absolute(std::vector<std::vector<double>> mat);

        /**
         * @brief ...
         * This function returns the mean of the given matrix.
         * @param mat p_mat:... The input matrix
         * @return double The mean of the matrix
         */
        double Mean(std::vector<std::vector<double>> mat);
    };
}
#endif // MATRIX_H
