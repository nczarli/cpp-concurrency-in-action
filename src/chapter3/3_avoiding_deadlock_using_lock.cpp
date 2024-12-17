// Write two threads that swap data between two objects protected by two
// mutexes. Avoid deadlocks by using std::lock

#include <iostream>
#include <mutex>
#include <thread>

class Data {
public:
    int value;
    std::mutex mtx;
    
    Data(int val) : value(val){};
};

void swap_data(Data& d1, Data& d2){
    std::lock(d1.mtx, d2.mtx);
    std::lock_guard<std::mutex> lock1(d1.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(d2.mtx, std::adopt_lock);

    std::swap(d1.value, d2.value);
    std::cout << "Swapped : " << d1.value << " <-> " << d2.value << std::endl;
};

int main(){
    Data d1(10), d2(20);

    std::thread t1(swap_data, std::ref(d1), std::ref(d2)); 
    std::thread t2(swap_data, std::ref(d2), std::ref(d1));

    t1.join();
    t2.join();

    std::cout << "Final Vaues: d1=" << d1.value << ", d2=" << d2.value 
                << std::endl;
    return 0;

}