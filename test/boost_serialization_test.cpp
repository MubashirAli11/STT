#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>

#include <CppUTest/TestHarness.h>

class Point {
    friend class boost::serialization::access;
    int x;
    int y;
public:
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& x;
        ar& y;
    }
    Point(int x, int y): x(x), y(y)
    {}
    int get_x()
    {
        return x;
    }
    int get_y()
    {
        return y;
    }

};

TEST_GROUP(boost_serialization)
{

};

TEST(boost_serialization, example_test)
{

    std::ostringstream serialized;
    //Point a(10, 15);
    boost::archive::text_oarchive oa(serialized);
    // oa << a;
    //
    // Point b(0, 0);
    //
    //  ia >> b;
    // std::cout << b.get_x() << ", " << b.get_y() << std::endl;

    std::vector<double> vectors;

    for (size_t i = 0; i < 10; i++) {
        vectors.push_back(rand() / double(RAND_MAX));
    }

    oa << vectors;
    // boost::serialization::access::serialize(oa, vectors, 0);
    std::cout << serialized.str() << std::endl;

    std::istringstream deserialized(serialized.str());

    boost::archive::text_iarchive ia(deserialized);
    std::vector<double> vectors2;
    ia >> vectors2;

}
