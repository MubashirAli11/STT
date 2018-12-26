#include<vector>
#include<fstream>
#include<string>
#include<unordered_map>
#include<random>
#include<map>
#include<iostream>
#include <CppUTest/TestHarness.h>
TEST_GROUP(toy_example)
{

};
TEST(toy_example, calculate_viterbi_path)
{
    std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities_;
    std::unordered_map<std::string, std::unordered_map<std::string, double>>
            emission_probabilities_;
    std::unordered_map<std::string, double> final_probabilities_;
    std::unordered_map<std::string, double> initial_probabilities_;
    std::vector<std::string> observations_;
    std::vector<std::string> states_;
    std::unordered_map<std::string, double> temp;

    states_.push_back("H");
    states_.push_back("F");

    observations_.push_back("N");
    observations_.push_back("C");
    observations_.push_back("D");


    initial_probabilities_.insert(std::make_pair("H", 0.6));
    initial_probabilities_.insert(std::make_pair("F", 0.4));

    final_probabilities_.insert(std::make_pair("H", 0.5));
    final_probabilities_.insert(std::make_pair("F", 0.5));

    temp.insert(std::make_pair("H", 0.7));
    temp.insert(std::make_pair("F", 0.3));

    transition_probabilities_.insert(std::make_pair("H", temp));

    temp.clear();

    temp.insert(std::make_pair("H", 0.4));
    temp.insert(std::make_pair("F", 0.6));

    transition_probabilities_.insert(std::make_pair("F", temp));

    temp.clear();

    temp.insert(std::make_pair("N", 0.5));
    temp.insert(std::make_pair("C", 0.4));
    temp.insert(std::make_pair("D", 0.1));

    emission_probabilities_.insert(std::make_pair("H", temp));

    temp.clear();

    temp.insert(std::make_pair("N", 0.1));
    temp.insert(std::make_pair("C", 0.3));
    temp.insert(std::make_pair("D", 0.6));

    emission_probabilities_.insert(std::make_pair("F", temp));

    std::vector<std::string> path_;

    std::unordered_map<std::string, double> viterbi_probabilities_;

    int index;
    int probability_list_index;
    int difference;
    int states_index;
    int max_value_index;
    std::string temp_str;
    double probabilities;
    std::string last_state;
    std::unordered_map<std::string, std::string> b_ptr;
    std::vector<double> probabilities_list;
    std::multimap<double, int> sort_prob;
    std::multimap<double, int>::iterator itr;
    std::multimap<double, int>::iterator itr2;
    std::vector<double> hold_values;
    std::multimap<double, int> final_state_prob;


    for (size_t i = 0; i <  states_.size(); i++) {
        probabilities_list.push_back(initial_probabilities_[  states_[i]]* emission_probabilities_[  states_[i]][observations_[0]]);
    }

    for (size_t i = 0; i <  states_.size(); i++) {
        viterbi_probabilities_.insert(std::make_pair(states_[i] + "|" + observations_[0], probabilities_list[i]));
    }

    observations_.erase(observations_.cbegin());

    for (size_t i = 0; i < observations_.size(); i++) {
        states_index = 0;

        for (size_t j = 0; j <  states_.size(); j++) {
            probability_list_index = 0;
            difference = 0;

            for (size_t k = 0; k <  states_.size(); k++) {
                probabilities = transition_probabilities_[  states_[k]][  states_[j]] * emission_probabilities_[  states_[j]][observations_[i]];
                probabilities *= probabilities_list[probability_list_index];
                probabilities_list.push_back(probabilities);
                sort_prob.insert(std::make_pair(probabilities, probability_list_index++));
                last_state =  states_[j];
            }

            difference = probabilities_list.size() -   states_.size();
            itr = sort_prob.end();
            --itr;
            max_value_index = itr->second;
            max_value_index += difference;
            b_ptr.insert(std::make_pair(states_[states_index] + "|" + observations_[i],  states_[itr->second]));
            viterbi_probabilities_.insert(std::make_pair(states_[states_index++] + "|" + observations_[i], probabilities_list[max_value_index]));
            hold_values.push_back(probabilities_list[max_value_index]);
            sort_prob.clear();
        }

        probabilities_list.clear();
        difference = 0;

        for (size_t n = 0; n <  states_.size(); n++) {
            probabilities_list.push_back(hold_values[n]);
        }

        hold_values.clear();
    }

    sort_prob.clear();

    index = observations_.size() - 1;

    for (size_t i = 0; i <  states_.size(); i++) {
        final_state_prob.insert(std::make_pair(viterbi_probabilities_[  states_[i] + "|" + observations_[index]]*final_probabilities_[  states_[i]], i));
    }

    itr2 = final_state_prob.end();
    itr2--;

    viterbi_probabilities_.insert(std::make_pair("final state", itr2->first));


    path_.push_back(states_[itr2->second]);
    temp_str =  states_[itr2->second];

    for (int i = observations_.size() - 1; i >= 0; i--) {
        temp_str = b_ptr[temp_str + "|" + observations_[i]];
        path_.push_back(temp_str);
    }

    std::vector<std::string> c_path;
    std::copy(path_.rbegin(), path_.rend(), std::back_inserter(c_path));

    for (size_t i = 0; i < c_path.size(); i++) {
        std::cout << c_path[i] + "->";
    }

    std::cout << std::endl;
}
