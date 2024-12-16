#include <iostream>
#include <thread>
#include <vector>
#include <numeric>

class scoped_thread{
    std::thread t;

public:
    explicit scoped_thread(std::thread t) : t(std::move(t)){
        if (!this->t.joinable())
            throw std::logic_error("No thread to join");
    }
    ~scoped_thread(){
        t.join();
    }
    scoped_thread(const scoped_thread&) = delete;
    scoped_thread& operator=(const scoped_thread&) = delete;
};

void calculate_factorial(int start, int end){
    for (int i = start; i <= end; ++i){
        long long factorial = 1;
        for (int j = 1; j <= i; ++j)
            factorial *= j;
        std::cout << "Factorial of " << i << " is " << factorial << "\n";
    }
}

int main(){
    scoped_thread t1(std::thread(calculate_factorial, 1, 5));
    scoped_thread t2(std::thread(calculate_factorial, 6, 10));

    std::cout << "Main thread finished.\n";
    return 0;
}