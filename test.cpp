#include <iostream>
#include <chrono>
#include "bitfield.hpp"

constexpr int p = 2147483647;

template<class T>
unsigned char bench(int i)
{
    T x;
    x.a1 = p ^ ((p ^ i) >> 5);
    x.a2 = p ^ ((p ^ i) >> 7);
    return (unsigned char)x;
}

struct MyBitField2
{
    unsigned char a1 : 1, a2 : 1;

    operator unsigned char() const
    {
        return this->a1 | (this->a2 << 2);
    }

    static unsigned char benchFunc(int i)
    {
        return bench<MyBitField2>(i);
    }
};


template<class F>
long long test_time(void)
{
	
	std::chrono::time_point<std::chrono::high_resolution_clock> start_point, end_point; // creating time points
	
	start_point = std::chrono::high_resolution_clock::now(); // storing the starting time point in start 
	
    unsigned char x = 0;
    for (int i = 0; i < 10000; i++) 
    {
        std::cout << (int) F::benchFunc(i);
    }
	 
	end_point = std::chrono::high_resolution_clock::now(); //storing the ending time in end 
	
	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_point).time_since_epoch().count(); 
	// casting the time point to microseconds and measuring the time since time epoch
	
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_point).time_since_epoch().count();
	
	std::cout<<"Time taken = "<<(end-start)<<" microseconds ("<<((int)x)<<")"<<std::endl;
	
	return end - start;
}

enum class Test {
    t=0, a=1, r=3
};

BitStruct<unsigned char, Test, 
    BitField<Test, Test::t>,
    BitField<Test, Test::a>,
    BitField<Test, Test::r>
> x;

int main(int argc, char const * const argv[])
{

    // std::cout << "Hello, World" << std::endl;
    // x.set(TestFields::R);
    // std::cout << (int)(unsigned char)x << std::endl;
    // std::cout << sizeof(x) << std::endl;
    // test_time<MyBitField>();
    // test_time<MyBitField2>();
    // C x;
    x.set<Test::a>();
    std::cout << (int)x.get() << std::endl;
    std::cout << sizeof(x) << std::endl;

    // TestTest2<Test> x;
    // std::cout << (int)x.get<Test::a>() << std::endl;
}