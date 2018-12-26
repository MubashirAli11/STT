#include "stt_common.hpp"
#include "dsp_math.hpp"
#include <spdlog/spdlog.h>

#include <cmath>
#include <vector>
#include <iostream>
#include <complex>
#include <fstream>
#include "dsp_math.hpp"

#include <CppUTest/TestHarness.h>

TEST_GROUP(DiscreteCosineTransformation)
{
    void setup() {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    }
    void teardown() {

        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();

        spdlog::drop_all();

    }



};


TEST(DiscreteCosineTransformation, compare_dct_with_out_power_of_2_with_python_scipy_fftpack)
{


    std::vector<double>  fftresult;
    std::vector<std::complex<double>> complex_data;

    for (int i = 1; i <= 5; i++) {
        complex_data.emplace_back(i, 0.0);
    }

    std::vector<double> python_results = { 6.70820393e+00,  -3.14949989e+00,   3.51083347e-17,
                                           -2.83990228e-01,  -2.80866677e-16
                                         };
    fftresult = marfix_stt::DSPMath::Transformations::ComputeDCT(complex_data);


    for (int i = 0; i < 5; i++) {
        DOUBLES_EQUAL(python_results[i], fftresult[i], 0.0000001);
    }


}
TEST(DiscreteCosineTransformation, compare_dct_with_power_of_2_with_python_scipy_fftpack)
{
    std::vector<double>  fftresult;
    std::vector<std::complex<double>> complex_data;


    for (int i = 1; i <= 8; i++) {
        complex_data.emplace_back(i, 0.0);
    }

    std::vector<double> python_results = { 12.72792206,  -6.44232302,   0.        ,  -0.6734548 ,
                                           0.        ,  -0.2009029 ,   0.        ,  -0.05070232
                                         };

    fftresult = marfix_stt::DSPMath::Transformations::ComputeDCT(complex_data);


    for (int i = 0; i < 8; i++) {
        DOUBLES_EQUAL(python_results[i], fftresult[i], 0.0000001);
    }

}

