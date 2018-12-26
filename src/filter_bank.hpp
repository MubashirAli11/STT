#ifndef FILTERBANK__HPP
#define FILTERBANK__HPP

#include "stt_common.hpp"

namespace marfix_stt {
    /**
     * @brief Represents Mel filter bank
     *
     */
    class FilterBank {

    public:
        FilterBank(size_t number_of_filters) : number_of_filters_(number_of_filters),
            filter_bank_(number_of_filters, std::vector<double> (AudioFormat::BufferSize / 2 + 1, 0.0))
        { }
        /**
         * @brief Creates Filter bank
         *
         * @return true if filter bank is successfully created
         */

        bool Create();
        size_t GetNumberOfFilter()
        {
            return number_of_filters_;
        }
        const std::vector<double>& operator[](size_t index)
        {
            return filter_bank_[index];
        }
    private:
        size_t number_of_filters_;
        std::vector<std::vector<double>> filter_bank_;


    };
}

#endif // FILTERBANK__HPP
