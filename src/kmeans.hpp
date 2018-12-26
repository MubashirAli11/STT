#ifndef KMEANS__HPP
#define KMEANS__HPP

#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<map>
#include<iostream>

#include <caffe/caffe.hpp>
#include "code_book.hpp"

namespace marfix_stt {


    class kmeans {
    public:
        /**
         * @brief contructor which will use to write id, name and cluster centroid to database...
         *
         * @param k p_k:...
         * @param features p_features:...
         * @param  p_:...
         */
        kmeans(long k, std::vector<std::vector<double>> features, std::vector<std::string> , bool);

        /**
         * @brief update centroid value...
         *
         * @param feature p_feature:...
         * @return std::string
         */
        std::string Update_Clusters(std::vector<double> feature);
        std::string Update_Clusters(size_t index, std::vector<double> feature);
        size_t GetIndex(std::vector<double> features);
    private:
        marfix_stt::code_book cb;
        /**
         * @brief calculate euclidean distance taking two vectors...
         *
         * @param feature_1 p_feature_1:...
         * @param feature_2 p_feature_2:...
         * @return double
         */
        double Calculate_Euclidean_Distance(std::vector<double> feature_1, std::vector<double> feature_2);
        /**
         * @brief calculate centroid taking two vectors ...
         *
         * @param feature_1 p_feature_1:...
         * @param feature_2 p_feature_2:...
         * @return std::vector< double, std::allocator< double > >
         */
        std::vector<double> Calculate_Centroid(std::vector<double> feature_1, std::vector<double> feature_2);
        /**
         * @brief ...
         *
         */
        long k;
        /**
         * @brief ...
         *
         */
    public:
        std::vector<std::vector<double>> features;
        /**
         * @brief ...
         *
         */
        std::vector<std::string> cluster_names;
    };


}

#endif // KMEANS__HPP
