#include "fps.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include<vector>
#include<cmath>
#include "sentence_breaker.hpp"
#include "searchncount.hpp"
#include "spdlog/spdlog.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(ngrams_test)
{
    void setup() {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    }
    void teardown() {

        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};

double max(double x, double y)
{
    if (x > y) {
        return x;
    }

    return y;
}

TEST(ngrams_test, ngrams_complete_test)
{

    std::vector<std::string> sentences;
    std::ofstream sefile, outfile, confile;
    confile.open("config");
    sefile.open("se_sentences");
    outfile.open("probs");
    std::vector<std::string> words;
    std::ifstream infile("sentences");
    std::string s;

    while (std::getline(infile, s)) {
        if (s.empty()) {
            continue;
        }

        s = "جیر جیر " + s + " جیرا جیرا";
        sentences.push_back(s);
        sefile << s << std::endl;
    }

    marfix_stt::SentenceBreaker sb("se_sentences");
    words = sb.GetWords();
    marfix_stt::SearchNCount snc(sentences);
    double D = 0.9;
    auto console  = spdlog::stdout_logger_mt("Generating Probabilities");
    auto console1 = spdlog::stdout_logger_mt("Generating Senetences");
    /*
    for ( unsigned long i=0; i<words.size(); i++ )
    {double sum=0.0;
        for ( unsigned long j=0; j<words.size(); j++ )
            {
               double count01=snc.GetNonUniqueCounts(words[i],words[j]);
               double count02=snc.GetNonUniqueCounts(words[i]);
               double c;
             if(count02==0.0)
                 c=0.0;
             else
               c=max((count01-D),0.0)/count02;

             double d;
             if(count02==0.0)
                 d=0.0;
                 else
                  d=(D/count02)*snc.GetUniqueCounts(words[i],"dot");

             double e=snc.GetUniqueCounts("dot",words[j])/(double)(16.0);

             double
                 result=c+d*e;

             sum+=result;
               //  trigram_counts[i][j][k]=result;

                 outfile<< words[i]+" "+words[j]<<" = "<< std::setprecision(300) << result<<std::endl;
            }

        std::cout<<sum<<std::endl;
    }
    */
    long total_bigrams = 0;

    for (unsigned long tb = 0; tb < words.size(); tb++) {
        total_bigrams += snc.GetUniqueCounts("dot", words[tb]);
    }

    std::vector<std::vector<std::vector<double>>> trigram_counts(words.size(), std::vector<std::vector<double>>(words.size(), std::vector <double>(words.size(), 0.0)));
    console->info("Started Generating Probabilities...");

    for (unsigned long i = 0; i < words.size(); i++) {
        for (unsigned long j = 0; j < words.size(); j++) {
            for (unsigned long k = 0; k < words.size(); k++) {
                int count01 = snc.GetNonUniqueCounts(words[i], words[j], words[k]);
                int count02 = snc.GetNonUniqueCounts(words[i], words[j]);
                double a;

                if (count02 == 0) {
                    a = 0.0;
                }

                else {
                    a = max((count01 - D), 0.0) / count02;
                }

                double b;

                if (count02 != 0.0) {
                    b = (D / count02) * snc.GetUniqueCounts(words[i], words[j], "dot");
                }

                else {
                    b = 0.0;
                }

                count01 = snc.GetUniqueCounts("dot", words[j], words[k]);
                count02 = 0.0;

                for (unsigned long cu = 0; cu < words.size(); cu++) {
                    count02 += snc.GetUniqueCounts("dot", words[j], words[cu]);
                }

                double c;

                if (count02 == 0.0) {
                    c = 0.0;
                }

                else {
                    c = max((count01 - D), 0.0) / count02;
                }

                double d;

                if (count02 == 0.0) {
                    d = 0.0;
                }

                else {
                    d = (D / count02) * snc.GetUniqueCounts(words[j], "dot");
                }

                double e = snc.GetUniqueCounts("dot", words[k]) / (double)(total_bigrams);
                double result;

                if (b == 0.0) {
                    result = c + d * e;
                }

                else {
                    result = a + b * (c + d * e);
                }

                trigram_counts[i][j][k] = result;
                console->info("{}%", (i / (double)(words.size() - 1)) * 100.0);
                outfile << words[i] + " " + words[j] + " " + words[k] << " = " << result << std::endl;
            }
        }
    }

    //Generation code
    console->info("Started Generating Sentences...");
    int ns = 3;

    for (auto i = 0; i < ns; i++) {
        std::string sent = "";
        std::string nword = "جیر";

        while (1) {
            unsigned int it = 0, last;
            last = it;

            for (it = 0; it < words.size(); it++) {
                if (words[it].compare(nword) == 0) {
                    break;
                }
            }

            if (sent.compare("") == 0) {
                last = it;
            }

            marfix_stt::FitnessProportionateSelection fpss(trigram_counts[last][it]);
            int w = fpss.Select();
            nword = words[w];

            if (0 == nword.compare("جیرا")) {
                break;
            }

            sent = sent + nword + " ";
        }

        outfile << sent << std::endl;
        console1->info("{}%", (i / (double)(ns - 1)) * 100.0);
    }

    std::cout << "done";
    confile.close();
    sefile.close();
    infile.close();
    outfile.close();
    console->flush();
    console1->flush();
    spdlog::drop_all();
}
