#ifndef MELFREQUENCYCEPSTRALCOEFFICIENTS__HPP
#define MELFREQUENCYCEPSTRALCOEFFICIENTS__HPP

#include "stt_common.hpp"
#include "filter_bank.hpp"
#include "feature_extractor.hpp"
#include "audiopreprocessor.hpp"

namespace marfix_stt {
    class MFCCFeatureExtractor : public IFeatureExtractor {
    public:
        MFCCFeatureExtractor(size_t number_of_cepstral_coefficients, bool use_energy_coefficient, bool add_deltas) :
            filter_bank_(number_of_cepstral_coefficients * 2),
            number_of_cepstral_coefficients_(number_of_cepstral_coefficients),
            use_energy_coefficient_(use_energy_coefficient),
            add_deltas_(add_deltas),
            audio_preprocessor_(400, 160)
        {
            filter_bank_.Create();
        }
    
        double NumberOfCepstralCoefficients()
        {
            return number_of_cepstral_coefficients_ + ((add_deltas_) ? (number_of_cepstral_coefficients_ * 2) : 0);
        }
        std::vector<std::vector<double>> ExtractFeatures(const std::vector<SampleType>& audio_buffer) override;
    private:
        std::vector<double> features_per_frame(const std::vector<double>& windowed_audio_buffer);
        FilterBank filter_bank_;
        double number_of_cepstral_coefficients_;
        std::vector<double> cepstral_coefficients_;
        bool use_energy_coefficient_;
        bool add_deltas_;
        AudioPreprocessor audio_preprocessor_;
    };
}

#endif // MELFREQUENCYCEPSTRALCOEFFICIENTS__HPP
