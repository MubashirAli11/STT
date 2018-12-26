#include<stddef.h>
#include "matrix.hpp"
#include <CppUTest/TestHarness.h>

using namespace marfix_stt;

TEST_GROUP(matrix)
{

};

TEST(matrix, multiplication_test)
{
    MatrixOperations m1;
    std::vector<std::vector<double>> trans(2, std::vector<double>(3, 0));
    trans[0][0] = 1;
    trans[0][1] = 2;
    trans[0][2] = 3;
    trans[1][0] = 4;
    trans[1][1] = 5;
    trans[1][2] = 6;
    std::vector<std::vector<double>> trans1(3, std::vector<double>(2, 0));
    trans1[0][0] = 7;
    trans1[0][1] = 8;
    trans1[1][0] = 9;
    trans1[1][1] = 10;
    trans1[2][0] = 11;
    trans1[2][1] = 12;
    std::vector<std::vector<double>> expected_result(2, std::vector<double>(2, 0));
    expected_result[0][0] = 58;
    expected_result[0][1] = 64;
    expected_result[1][0] = 139;
    expected_result[1][1] = 154;
    std::vector<std::vector<double>> result;
    result = m1.DotMultiply(trans, trans1);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[0].size(); j++) {
            CHECK_EQUAL(expected_result[i][j], result[i][j]);
        }
    }
}

TEST(matrix, transpose_test)
{
    MatrixOperations m1;
    std::vector<std::vector<double>> trans(2, std::vector<double>(3, 0));
    trans[0][0] = 1;
    trans[0][1] = 2;
    trans[0][2] = 3;
    trans[1][0] = 4;
    trans[1][1] = 5;
    trans[1][2] = 6;
    std::vector<std::vector<double>> trans1 = m1.Transpose(trans);

    for (size_t i = 0; i < trans[0].size(); i++) {
        for (size_t j = 0; j < trans.size(); j++) {
            CHECK_EQUAL(trans[j][i], trans1[i][j]);
        }
    }
}

TEST(matrix, add_test)
{
    MatrixOperations m1;
    std::vector<std::vector<double>> trans(2, std::vector<double>(2, 0));
    trans[0][0] = 1;
    trans[0][1] = 2;
    trans[1][0] = 3;
    trans[1][1] = 4;
    std::vector<std::vector<double>> trans1(2, std::vector<double>(2, 0));
    trans1[0][0] = 7;
    trans1[0][1] = 8;
    trans1[1][0] = 9;
    trans1[1][1] = 10;

    std::vector<std::vector<double>> expected_result(2, std::vector<double>(2, 0));
    expected_result[0][0] = 8;
    expected_result[0][1] = 10;
    expected_result[1][0] = 12;
    expected_result[1][1] = 14;
    std::vector<std::vector<double>> result;
    result = m1.Add(trans, trans1);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[0].size(); j++) {
            CHECK_EQUAL(expected_result[i][j], result[i][j]);
        }
    }
}

TEST(matrix, sub_test)
{
    MatrixOperations m1;
    std::vector<std::vector<double>> trans(2, std::vector<double>(2, 0));
    trans[0][0] = 1;
    trans[0][1] = 2;
    trans[1][0] = 3;
    trans[1][1] = 4;
    std::vector<std::vector<double>> trans1(2, std::vector<double>(2, 0));
    trans1[0][0] = 7;
    trans1[0][1] = 8;
    trans1[1][0] = 9;
    trans1[1][1] = 10;

    std::vector<std::vector<double>> expected_result(2, std::vector<double>(2, 0));
    expected_result[0][0] = -6;
    expected_result[0][1] = -6;
    expected_result[1][0] = -6;
    expected_result[1][1] = -6;
    std::vector<std::vector<double>> result;
    result = m1.Subtract(trans, trans1);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[0].size(); j++) {
            CHECK_EQUAL(expected_result[i][j], result[i][j]);
        }
    }
}
