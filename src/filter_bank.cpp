#include "filter_bank.hpp"
#include "stt_common.hpp"
#include "dsp_math.hpp"
#include <cstddef>
#include <limits>
#include <fstream>
using namespace marfix_stt;
using std::vector;
using std::endl;
using std::ofstream;
bool FilterBank::Create()
{

    size_t number_of_filters = filter_bank_.size() + 2;
    vector<double> melFrequencies(number_of_filters, 0);
    vector<double> melFrequenciesInverse(number_of_filters, 0);
    vector<double> bin(number_of_filters, 0);

    melFrequencies[0] = DSPMath::MelFrequency(300);
    melFrequencies[number_of_filters - 1] = DSPMath::MelFrequency(8000);

    double mel_interval = (melFrequencies[number_of_filters - 1] - melFrequencies[0]) / (number_of_filters - 1);

    for (size_t i = 1; i < number_of_filters - 1; i++) {
        melFrequencies[i] = melFrequencies[i - 1] + mel_interval;
    }

    for (size_t i = 0; i < number_of_filters; i++) {

        double melFrequenciesInverse = DSPMath::MelFrequencyInverse(melFrequencies[i]);
        bin[i] = floor((AudioFormat::BufferSize + 1) * melFrequenciesInverse / static_cast<double>(AudioFormat::SelectedSampleRate));
    }

    for (size_t i = 0; i < filter_bank_.size(); i++) {
        for (size_t j = static_cast<size_t>(bin[i]); j <= static_cast<size_t>(bin[i + 1]); j++) {
            filter_bank_[i][j] = (j - bin[i]) / (bin[i + 1] - bin[i]);
        }

        for (size_t j = static_cast<size_t>(bin[i + 1]); j <= static_cast<size_t>(bin[i + 2]); j++) {
            filter_bank_[i][j] = (bin[i + 2] - j) / (bin[i + 2] - bin[i + 1]);
        }
    }

    ofstream file("filter_bank_new.txt", std::ios::trunc);

    // testing of filter bank start
    for (size_t i = 0; i < filter_bank_.size(); i++) {
        for (size_t j = 0; j < AudioFormat::BufferSize / 2 + 1; j++) {
            if (j == AudioFormat::BufferSize / 2) {
                file << filter_bank_[i][j];
            }

            else {
                file << filter_bank_[i][j] << ", ";
            }
        }

        file << endl;
    }

    // testing of filter bank end
    return true;
}
