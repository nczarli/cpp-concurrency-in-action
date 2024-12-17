// Delibretaly introduce a race condition by sharing a counter between two
// threads without using a mutex.

#include <iostream>
#include <thread>

int counter = 0;
// std::mutex counter_mutex

void increment_counter(){
    for (int i = 0; i < 1000000; ++i){
        // std::lock_guard<std::mutex> lock(counter_mutex)
        ++counter;
    }
}

int main(){
    std::thread t1(increment_counter);
    std::thread t2(increment_counter);

    t1.join();
    t2.join();

    std::cout << "Final Counter Value: " << counter << std::endl;
    return 0;
}