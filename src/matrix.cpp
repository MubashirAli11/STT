#include "matrix.hpp"


using namespace marfix_stt;
using namespace arma;

std::vector<std::vector<double>> marfix_stt::MatrixOperations::DotMultiply(std::vector<std::vector<double>> matA, std::vector<std::vector<double>> matB)
{
    std::vector<std::vector<double>> resultant;

    if (matA[0].size() != matB.size()) {
        std::cout << "Matrices cant be multiplied..." << std::endl;
        return resultant;
    }

    mat A(matA.size(), matA[0].size()), B(matB.size(), matB[0].size()), C(matA.size(), matB[0].size());

    for (size_t i = 0; i < matA.size(); i++) {
        for (size_t j = 0; j < matA[0].size(); j++) {
            A(i, j) = matA[i][j];
        }
    }

    for (size_t i = 0; i < matB.size(); i++) {
        for (size_t j = 0; j < matB[0].size(); j++) {
            B(i, j) = matB[i][j];
        }
    }

    C = A * B;

    for (size_t i = 0; i < C.n_rows; i++) {
        std::vector<double> mult;

        for (size_t j = 0; j < C.n_cols; j++) {
            mult.push_back(C(i, j));
        }

        resultant.push_back(mult);
    }

    return resultant;
}


std::vector<std::vector<double>> marfix_stt::MatrixOperations::Multiply(std::vector<std::vector<double>> matA, std::vector<std::vector<double>> matB)
{
    std::vector<std::vector<double>> resultant;

    if (matA[0].size() != matB[0].size() && matA.size() != matB.size()) {
        std::cout << "Matrices cant be multiplied..." << std::endl;
        return resultant;
    }

    for (size_t i = 0; i < matA.size(); i++) {
        std::vector<double> mult;

        for (size_t j = 0; j < matA[0].size(); j++) {
            mult.push_back(matA[i][j]*matB[i][j]);
        }

        resultant.push_back(mult);
    }

    return resultant;
}


std::vector<std::vector<double>> marfix_stt::MatrixOperations::Transpose(std::vector<std::vector<double>> mat)
{
    std::vector<std::vector<double>> trans(mat[0].size(), std::vector<double>(mat.size(), 0));

    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat[0].size(); j++) {
            trans[j][i] = mat[i][j];
        }
    }

    return trans;
}



std::vector<std::vector<double>> marfix_stt::MatrixOperations::Subtract(std::vector<std::vector<double>> matA, std::vector<std::vector<double>> matB)
{
    std::vector<std::vector<double>> resultant;

    if (matA.size() != matB.size() || matA[0].size() != matB[0].size()) {
        std::cout << "Matrices cant be subtracted..." << std::endl;
        return resultant;
    }

    for (size_t i = 0; i < matA.size(); i++) {
        std::vector<double> mult;

        for (size_t j = 0; j < matA[0].size(); j++) {
            mult.push_back(matA[i][j] - matB[i][j]);
        }

        resultant.push_back(mult);
    }

    return resultant;
}


std::vector<std::vector<double>> marfix_stt::MatrixOperations::Add(std::vector<std::vector<double>> matA, std::vector<std::vector<double>> matB)
{
    std::vector<std::vector<double>> resultant;

    if (matA.size() != matB.size() || matA[0].size() != matB[0].size()) {
        std::cout << "Matrices cant be added..." << std::endl;
        return resultant;
    }

    for (size_t i = 0; i < matA.size(); i++) {
        std::vector<double> mult;

        for (size_t j = 0; j < matA[0].size(); j++) {
            mult.push_back(matA[i][j] + matB[i][j]);
        }

        resultant.push_back(mult);
    }

    return resultant;
}


void marfix_stt::MatrixOperations::DotMultiplyAdd(std::vector<std::vector<double>> matA, std::vector<std::vector<double>> matB, std::vector<std::vector<double>>& matC)
{
    if (matA[0].size() != matB.size()) {
        std::cout << "Matrices cant be multiplied..." << std::endl;
        return;
    }

    mat A(matA.size(), matA[0].size()), B(matB.size(), matB[0].size()), C(matA.size(), matB[0].size());

    for (size_t i = 0; i < A.n_rows; i++) {
        for (size_t j = 0; j < A.n_cols; j++) {
            A(i, j) = matA[i][j];
        }
    }

    for (size_t i = 0; i < B.n_rows; i++) {
        for (size_t j = 0; j < B.n_cols; j++) {
            B(i, j) = matB[i][j];
        }
    }

    C = A * B;

    for (size_t i = 0; i < C.n_rows; i++) {
        for (size_t j = 0; j < C.n_cols; j++) {
            matC[i][j] += C(i, j);
        }
    }
}


std::vector<std::vector<double>> marfix_stt::MatrixOperations::Absolute(std::vector<std::vector<double>> mat)
{

    std::vector<std::vector<double>> absl(mat.size(), std::vector<double>(mat[0].size(), 0));

    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat[0].size(); j++) {
            absl[i][j] = std::abs(mat[i][j]);
        }
    }

    return absl;
}

double marfix_stt::MatrixOperations::Mean(std::vector<std::vector<double>> mat)
{
    double meanm = 0;

    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat[0].size(); j++) {
            meanm += mat[i][j];
        }
    }

    return meanm / (mat.size() * mat[0].size());
}
