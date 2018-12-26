#include "dsp_math.hpp"
#include "stt_common.hpp"
#include <spdlog/spdlog.h>
#include <CppUTest/TestHarness.h>




TEST_GROUP(fft_test_group)
{

};

TEST(fft_test_group, FFTTest)
{
    using namespace std;

    vector<double>  fftresult;
    vector<complex<double>> complex_data;

    for (int i = 0; i < 16; i++) {
        complex_data.emplace_back(i / 16.0, 0);
    }

    for (int i = 0; i < 16; i++) {
        complex_data.emplace_back(0, 0);
    }

    ofstream output("fft_output1.txt", std::ios::trunc);
    fftresult = marfix_stt::DSPMath::Transformations::ComputeFFT(complex_data, false);


    /* cout << fftresult.size();
     copy(fftresult.begin(), fftresult.end(),
          ostream_iterator<double>(output, "\n"));*/
    copy(complex_data.begin(), complex_data.end(),
         ostream_iterator<std::complex<double>>(output, "\n"));



    output.flush();
    output.close();
}
