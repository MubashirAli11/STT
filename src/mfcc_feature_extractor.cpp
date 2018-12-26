#include "mfcc_feature_extractor.hpp"
#include "dsp_math.hpp"
#include "filter_bank.hpp"
#include "feature_extractor.hpp"
#include <limits>
#include <fstream>

using namespace marfix_stt;

std::vector<std::vector<double>> MFCCFeatureExtractor::ExtractFeatures(const std::vector<SampleType>& audio_buffer)
{
    auto frames = audio_preprocessor_.Preprocess(audio_buffer);

    std::vector<std::vector<double>> total_cepstral_coefficients;

    for (auto frame : frames) {
        total_cepstral_coefficients.push_back(features_per_frame(frame));
    }

    if (add_deltas_) {
        for (size_t t = 0; t < total_cepstral_coefficients.size(); t++) {
            int p = t - 1;
            int n = t + 1;

            if (p < 0) {
                p = 0;
            }

            if ((size_t)n > total_cepstral_coefficients.size() - 1) {
                n = total_cepstral_coefficients.size() - 1;
            }

            if (p != n) {
                for (int i = 0; i < 13; i++) {
                    total_cepstral_coefficients[t].push_back((total_cepstral_coefficients[p][i] -
                            total_cepstral_coefficients[n][i]) / 2.0
                                                            );
                }

                for (int i = 13; i <= 26; i++) {
                    total_cepstral_coefficients[t].push_back((total_cepstral_coefficients[p][i] -
                            total_cepstral_coefficients[n][i]) / 2.0
                                                            );
                }
            }

            else {
                for (int x = 0; x < 2; x++) {
                    for (int i = 0; i < 13; i++) {
                        total_cepstral_coefficients[t].push_back(total_cepstral_coefficients[t][i]);
                    }
                }
            }
        }
    }

    return total_cepstral_coefficients;
}

std::vector<double> MFCCFeatureExtractor::features_per_frame(const std::vector<double>& windowed_audio_buffer)
{
    std::vector<double> power_spectrum_complex_absolute;
    std::vector<std::complex<double>> power_spectrum_complex;
    std::copy(windowed_audio_buffer.begin(), windowed_audio_buffer.end(), back_inserter(power_spectrum_complex));

    power_spectrum_complex_absolute = DSPMath::Transformations::ComputeFFT(power_spectrum_complex, true);

    for (auto& psca : power_spectrum_complex_absolute) {
        psca = (1.0 / AudioFormat::BufferSize) * pow(psca, 2);
    }

    std::vector<double> mel_energy(filter_bank_.GetNumberOfFilter(), 0.0);
    std::vector<std::complex<double>> log_mel_energy(filter_bank_.GetNumberOfFilter(), std::complex<double> (0.0, 0.0));

    for (size_t i = 0; i < filter_bank_.GetNumberOfFilter(); i++) {
        for (size_t j = 0; j < filter_bank_[i].size(); j++) {
            mel_energy[i] += filter_bank_[i][j] * power_spectrum_complex_absolute[j];
        }

        if (mel_energy[i] == 0) {
            mel_energy[i] = fabs(std::numeric_limits<double>::min());
        }

        log_mel_energy[i].real(log(mel_energy[i]));
    }

    cepstral_coefficients_ = DSPMath::Transformations::ComputeDCT(log_mel_energy);

    if (use_energy_coefficient_) {
        double energy = std::accumulate(power_spectrum_complex_absolute.begin(), power_spectrum_complex_absolute.end(), 0.0);

        if (energy == 0) {
            energy = fabs(std::numeric_limits<double>::min());
        }

        cepstral_coefficients_[0] = log(energy);

    }

    cepstral_coefficients_.resize(number_of_cepstral_coefficients_);

    return cepstral_coefficients_;
}

