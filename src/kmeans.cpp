#include "kmeans.hpp"

using namespace marfix_stt;

marfix_stt::kmeans::kmeans(long k, std::vector<std::vector<double>> features, std::vector<std::string> names, bool firstTime): cb(firstTime), k(k), cluster_names(names)
{

    if (firstTime) {
        this->features = features;

        // write to database
        // name and cluster centroids
        for (int i = 0; i < k; i++) {
            caffe::Datum d;
            d.set_channels(1);
            d.set_height(1);
            d.set_width(1);
            d.set_label(0);

            for (size_t j = 0; j < features[0].size(); j++) {
                d.add_float_data(features[i][j]);
            }

            const std::string& value = d.SerializeAsString();
            d.Clear();
            cb.insert(names[i], value);
        }
    }

    else {
        this->features = cb.readAll(13);
    }
}
std::string kmeans::Update_Clusters(size_t index, std::vector<double> feature)
{
    features[index] = Calculate_Centroid(feature, features[index]);
    //write updated centroids in database
    caffe::Datum d;
    d.set_channels(1);
    d.set_height(1);
    d.set_width(1);
    d.set_label(0);

    for (size_t j = 0; j < features[index].size(); j++) {
        d.add_float_data(features[index][j]);
    }

    const std::string& value = d.SerializeAsString();
    cb.insert(cluster_names[index], value);
    return cluster_names[index];
}

std::string marfix_stt::kmeans::Update_Clusters(std::vector<double> feature)
{
    std::map<double, long> distances;

    for (long i = 0; i < k; i++) {
        distances.insert(std::make_pair(Calculate_Euclidean_Distance(features[i], feature), i));
    }

    auto index = distances.begin()->second;
    /*   features[index]=Calculate_Centroid ( feature,features[index] );
       //write updated centroids in database
       caffe::Datum d;
       d.set_channels(1);
    d.set_height(1);
    d.set_width(1);
    d.set_label(0);
    for(size_t j=0;j<features[index].size();j++)
           d.add_float_data(features[index][j]);
       const std::string& value=d.SerializeAsString();
       cb.insert(cluster_names[index],value);*/
    return cluster_names[index];
}

size_t marfix_stt::kmeans::GetIndex(std::vector<double> feature)
{
    std::map<double, long> distances;

    for (long i = 0; i < k; i++) {
        distances.insert(std::make_pair(Calculate_Euclidean_Distance(features[i], feature), i));
    }

    auto index = distances.begin()->second;
    return index;
}
std::vector<double> marfix_stt::kmeans::Calculate_Centroid(std::vector<double> feature_1, std::vector<double> feature_2)
{
    std::vector<double> centroid;

    for (long i = 0; i < 13; i++) {
        centroid.push_back((feature_1[i] + feature_2[i]) / 2.0);
    }

    return centroid;
}


double marfix_stt::kmeans::Calculate_Euclidean_Distance(std::vector<double> feature_1, std::vector<double> feature_2)
{
    double sum = 0.0;

    for (long i = 0; i < 13; i++) {
        sum += pow(feature_1[i] - feature_2[i], 2.0);
    }

    return sqrt(sum);
}
