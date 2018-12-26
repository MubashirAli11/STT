#ifndef FPS__HPP
#define FPS__HPP

#include<vector>
#include <random>
#include<map>
#include<algorithm>


namespace marfix_stt {
    struct Interval {
        Interval() : start(), end() {}
        Interval(double start, double end) : start(start), end(end) {}
        double start;
        double end;
    };

    struct IntervalComparator {
        bool operator()(const Interval& lhs, const Interval& rhs)
        {
            if (lhs.end < rhs.start) {
                return true;
            }

            else {
                return false;
            }
        }
    };
    /**
     * @brief ...
     * This Class converts the probabilities into intervals.
     */
    class FitnessProportionateSelection {
    public:
        /**
         * @brief ...
         * Intializations
         * @param probabilities p_probabilities:...
         * The Probabilities Vector as input.
         */
        FitnessProportionateSelection(std::vector<double> probabilities);
        /**
         * @brief ...
         * This function randomly selects and returns the index of the word from intervals.
         * @return int
         */
        int Select();
        std::map<Interval, int, IntervalComparator> GetIntervals();

    private:
        std::vector<double> probabilities;
        std::map<Interval, int, IntervalComparator> probabilityIndex;
        /**
         * @brief ...
         * This Function converts the given probabilities into intevals the returns the intervals vector.
         */
        void ComputeIntervals();
    };
}
#endif // FPS__HPP
