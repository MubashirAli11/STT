#ifndef INTERVAL__HPP
#define INTERVAL__HPP

struct Interval {
    Interval() : start_(), end_() {}
    Interval(double start, double end) : start_(start), end_(end) {}
    double start_;
    double end_;
};

struct IntervalComparator {
    bool operator()(const Interval& lhs, const Interval& rhs)
    {
        if (lhs.end_ < rhs.start_) {
            return true;
        }

        else {
            return false;
        }
    }
};
#endif // INTERVAL__HPP
