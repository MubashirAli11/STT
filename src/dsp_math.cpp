#include "dsp_math.hpp"
#include <complex>
#include <spdlog/spdlog.h>
#include <complex>

namespace marfix_stt {
    namespace DSPMath {
        namespace Transformations {

            namespace {


                bool IsPowOf2(size_t x)
                {
                    return x && !(x & (x - 1));
                }



                size_t ReverseBits(size_t x, unsigned int n)
                {
                    size_t result = 0;
                    unsigned int i;

                    for (i = 0; i < n; i++, x >>= 1) {
                        result = (result << 1) | (x & 1);
                    }

                    return result;
                }
                using namespace std::literals::complex_literals;

                auto console = spdlog::stdout_logger_mt("dsp_math");


            }

            std::vector<double> ComputeFFT(std::vector<std::complex<double>>& complex_data, bool pad_buffer)
            {

                size_t n = complex_data.size();

                if (!IsPowOf2(n)) {
                    if (!pad_buffer) {
                        throw "Length is not a power of 2";
                    }

                    else {
                        complex_data.insert(complex_data.end(), pow(2, ceil(log2(n))) - n, 0.0);
                        n = complex_data.size();
                    }
                }

                unsigned int levels = static_cast<unsigned int>(log2(n));

                // Bit-reversed addressing permutation
                for (size_t i = 0; i < n; i++) {
                    size_t j = ReverseBits(i, levels);

                    if (j > i) {
                        std::swap(complex_data[i], complex_data[j]);
                    }
                }

                // Cooley-Tukey decimation-in-time radix-2 DFT
                for (size_t size = 2; size <= n; size *= 2) {
                    size_t halfsize = size / 2;
                    size_t tablestep = n / size;

                    for (size_t i = 0; i < n; i += size) {
                        for (size_t j = i, k = 0; j < i + halfsize; j++, k += tablestep) {

                            double theta = 2 * std::acos(-1) * k / n;
                            std::complex<double> temp = complex_data[j + halfsize] * std::exp(-1i * theta);
                            complex_data[j + halfsize] = complex_data[j] - temp;
                            complex_data[j] += temp;
                        }
                    }

                    if (size == n) { // Prevent overflow in 'size *= 2'
                        break;
                    }
                }

                std::vector<double> complex_absolute;

                for (auto i : complex_data) {
                    complex_absolute.emplace_back(abs(i));
                }

                complex_absolute.resize(n / 2 + 1);
                return complex_absolute;
            }
            std::vector<double> ComputeDCT(std::vector<std::complex<double>>& complex_data)
            {
                size_t n = complex_data.size();

                std::vector<double> real_part;

                if (IsPowOf2(n)) {
                    complex_data.insert(complex_data.end(), n, std::complex<double> (0, 0));
                    ComputeFFT(complex_data, false);


                    for (size_t i = 0; i < n; i++) {
                        double scale_factor = (0 == i) ? sqrt(0.5) / sqrt(2 * n) : 1.0 / sqrt(2 * n);
                        complex_data[i] *= 2.0 * exp(-1i * (acos(-1) * (1.0 * i) / (2.0 * n))) * scale_factor;
                        real_part.emplace_back(complex_data[i].real());
                    }

                    real_part.resize(n);
                    console->info("Using fft for dct because {} is power of 2", n);
                }

                else {
                    for (size_t k = 0; k < n; k++) {
                        double s = (k == 0) ? sqrt(.5) : 1.;
                        real_part.emplace_back(0.0);

                        for (size_t i = 0; i < n; i++) {
                            real_part[k] += s * complex_data[i].real() * cos(acos(-1) / n * (i + 0.5) * k);
                        }

                        real_part[k] *= sqrt(2. / n);
                    }

                    console->info("Using normal dct because {} is not power of 2", n);

                }

                console->flush();

                return real_part;
            }
        }
        namespace {
            struct ConvertMicBufferToWindowedBuffer_ {

                ConvertMicBufferToWindowedBuffer_() {}

                double operator()(SampleType i)
                {
                    double amp = i;//Amplitude ( i );
                    double hpfs =
                        HighPassFilteredSignal(amp, previous, 0.95);
                    previous = amp;
                    return hpfs;//HammingWindowedSignal(hpfs, count++);
                }

            private:
                double previous = 0.0;
                int count = 0;
            };
        }
        std::vector<double> ConvertMicBufferToWindowedBuffer(const std::vector<SampleType>& audio_buffer)
        {

            std::vector<double> windowed_audio_buffer(audio_buffer.size(), 0.0);
            std::transform(audio_buffer.begin(), audio_buffer.end(), windowed_audio_buffer.begin(),
                           ConvertMicBufferToWindowedBuffer_());

            return windowed_audio_buffer;
        }
    }
}

