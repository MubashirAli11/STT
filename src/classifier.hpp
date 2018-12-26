#ifndef CLASSIFIER_HPP
#define CLASSIFIER_HPP

#include <string>
#include <vector>
#include <memory>
#include <caffe/caffe.hpp>
#include "stt_common.hpp"

namespace marfix_stt {

    using Prediction = std::pair<std::string, double>;

    class Classifier {

    public:
        Classifier(const std::string& model_file,
                   const std::string& trained_file);

        std::vector<double> Predict(const std::vector<double>& features);

        std::shared_ptr<caffe::Net<double>> net_;
    };
}
#endif // CLASSIFIER_HPP
