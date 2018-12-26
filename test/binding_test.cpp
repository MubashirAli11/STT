#include <functional>
#include <iostream>
#include <vector>
#include "activation_functions.hpp"

#include <CppUTest/TestHarness.h>

TEST_GROUP(binding)
{

};

TEST(binding, function_binding)
{
    // store a free function
    /*  std::function<void(int)> f_display = print_num;
      f_display(-9);

      // store a lambda
      std::function<void()> f_display_42 = []() { print_num(42); };
      f_display_42();

      // store the result of a call to std::bind
      std::function<void()> f_display_31337 = std::bind(print_num, 31337);
      f_display_31337();

      // store a call to a member function
      std::function<std::vector<std::vector<double>>(const Foo&, std::vector<std::vector<double>>, bool)> f_add_display = &Foo::print_add;*/

    //std::function<std::vector<std::vector<double>>(marfix_stt::activation_functions&, /////std::vector<std::vector<double>>, bool)> f_add_displa = &marfix_stt::activation_functions::Sigmoid;
    //const Foo foo(314159);
    //f_add_display(foo, 1);

    // store a call to a data member accessor
    //std::function<int(Foo const&)> f_num = &Foo::num_;
    // std::cout << "num_: " << f_num(foo) << '\n';

    // store a call to a member function and object
    // using std::placeholders::_1;
    // std::function<void(int)> f_add_display2 = std::bind( &Foo::print_add, foo, _1 );
    //  f_add_display2(2);

    // store a call to a member function and object ptr
    // std::function<void(int)> f_add_display3 = std::bind( &Foo::print_add, &foo, _1 );
    //f_add_display3(3);

    // store a call to a function object
    //std::function<void(int)> f_display_obj = PrintNum();
    // f_display_obj(18);
}
