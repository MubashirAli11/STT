#include <caffe/caffe.hpp>
#include "classifier.hpp"

using namespace caffe;
using namespace marfix_stt;

Classifier::Classifier(const std::string& model_file, const std::string& trained_file)
{
    Caffe::set_mode(Caffe::CPU);

    /* Load the network. */
    net_.reset(new Net<double>(model_file, TEST));
    net_->CopyTrainedLayersFrom(trained_file);

    CHECK_EQ(net_->num_inputs(), 1) << "Network should have exactly one input.";
    CHECK_EQ(net_->num_outputs(), 1) << "Network should have exactly one output.";

}



/* Return the top N predictions. */
/*
std::vector<Prediction> Classifier::Classify(const vector<int>& color, int N) {
 std::vector<double> output = Predict(color);

  N = std::min<int>(labels_.size(), N);
  std::vector<int> maxN = Argmax(output, N);
  std::vector<Prediction> predictions;
  for (int i = 0; i < N; ++i) {
    int idx = maxN[i];
    predictions.push_back(std::make_pair(labels_[idx], output[idx]));
  }

  return predictions;
}*/
std::vector<double> Classifier::Predict(const vector<double>& features)
{
    Blob<double>* input_layer = net_->input_blobs()[0];
    input_layer->Reshape(1, 1, 1, 13);
    /* Forward dimension change to all layers. */
    net_->Reshape();

    double* input_data = input_layer->mutable_cpu_data();

    for (size_t i = 0; i < features.size(); i++) {
        input_data[i] = features.at(i);
    }

    net_->Forward();

    /* Copy the output layer to a std::vector */
    Blob<double>* output_layer = net_->output_blobs()[0];
    const double* begin = output_layer->cpu_data();
    const double* end = begin + output_layer->channels();
    return std::vector<double>(begin, end);
}
