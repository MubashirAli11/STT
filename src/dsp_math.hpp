#ifndef DSP_MATH__HPP
#define DSP_MATH__HPP

#include "stt_common.hpp"
#include <complex>

namespace marfix_stt {

    namespace DSPMath {

        namespace Transformations {
            std::vector<double> ComputeFFT(std::vector<std::complex<double>>& complex_data, bool pad);
            std::vector<double> ComputeDCT(std::vector<std::complex<double>>& complex_data);
        }
        inline double MelFrequency(double frequency)
        {
            return 1125 * (log(1 + frequency / 700));
        }
        inline double MelFrequencyInverse(double MelFrequency)
        {
            return 700 * (exp(MelFrequency / 1125) - 1);
        }
        inline double HighPassFilteredSignal(double CurrentSignal,
                                             double PreviousSignal,
                                             double Alpha)
        {
            return CurrentSignal - (Alpha * PreviousSignal);
        }

        inline double Amplitude(SampleType Input)
        {
            return static_cast<double>(Input) / (std::numeric_limits<SampleType>::max() + 1);
        }

        inline double HammingWindowedSignal(double Input, int i)
        {

            double alpha = 0.54;
            double beta = 0.46;
            const double pi = 3.1415926535897;

            double outputSignalsY;
            double hammingWindow = (alpha - beta * (cos(2 * pi * i / 512.0)));

            outputSignalsY = (Input * hammingWindow);

            return outputSignalsY;
        }
        std::vector<double> ConvertMicBufferToWindowedBuffer(const std::vector<SampleType>& audio_buffer);

    }
}
#endif // DSP_MATH__HPP
