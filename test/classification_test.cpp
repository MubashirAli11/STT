#include <caffe/caffe.hpp>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "classifier.hpp"
#include <CppUTest/TestHarness.h>

TEST_GROUP(classification)
{

};
TEST(classification, test_bug_model)
{


    using namespace caffe;
    using namespace marfix_stt;

    using std::string;
    /*
    string model_file   = "bug_model.prototxt";
    string trained_file = "bugnet_iter_1500.caffemodel";
    string label_file   = "labels.txt";
    Classifier classifier(model_file, trained_file, label_file);

    std::vector<int> color = {100, 20, 20};
    std::vector<Prediction> predictions = classifier.Classify(color, 1);

    /* Print the top N predictions. */
    /*for (size_t i = 0; i < predictions.size(); ++i) {
      Prediction p = predictions[i];
      std::cout << std::fixed << std::setprecision(4) << p.second << " - \""
                << p.first << "\"" << std::endl;
    }*/
}

