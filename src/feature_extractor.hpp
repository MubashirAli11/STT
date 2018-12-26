#ifndef FEATUREEXTRACTOR__HPP
#define FEATUREEXTRACTOR__HPP

#include "stt_common.hpp"
namespace marfix_stt {
    class IFeatureExtractor {
    public:
        virtual std::vector<std::vector<double>> ExtractFeatures(const std::vector<SampleType>& audio_buffer) = 0;
        virtual ~IFeatureExtractor() = default;
    };
}

#endif // FEATUREEXTRACTOR__HPP
