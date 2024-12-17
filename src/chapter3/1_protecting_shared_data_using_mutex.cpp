// Write a program that allows two threads to concurrently modify a shared
// list. Use a std::mutex to protect access to the list.

#include <iostream>
#include <list>
#include <mutex>
#include <thread>

std::list<int> shared_list;
std::mutex list_mutex;

void add_elements(int start, int end){
    for (int i = start; i <= end; ++i){
        std::lock_guard<std::mutex> lock(list_mutex);
        shared_list.push_back(i);
        std::cout << "Added: " << i << std::endl;
    }
}

void print_list(){
    std::lock_guard<std::mutex> lock(list_mutex);
    std::cout << "Shared List: ";
    for (const auto& val : shared_list){
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::thread t1(add_elements, 1, 5);
    std::thread t2(add_elements, 6, 10);

    t1.join();
    t2.join();

    print_list();
    return 0;
}

//
// Question
//
// What happens if you remove the std::lock_guard<std::mutex> in the
// add_elements function?
//

//
// Answer
// 
// Without lock_guard, race conditions will occur, and the program may
// print inconsistent or corrupted results when accessing shared_list