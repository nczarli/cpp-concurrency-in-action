#include <iostream>
#include <vector>
#include <numeric>
#include <thread>
#include <future>
#include <chrono>

// Notes on iterators
// An iterator is an object that allows you to traverse the 
// elements of a container (like a vector, list, or array) 
// without exposing its underlying implementation. Iterators
// act as pointers to elements in the container, providing 
// access to elements and operations like incrementing or
// dereferencing.


template<typename Iterator, typename T>
T parallel_accumulate(Iterator begin, Iterator end, T init){

    const auto length = std::distance(begin, end);
    const size_t num_threads = std::thread::hardware_concurrency();
    const size_t block_size = length / num_threads;

    std::vector<std::future<T>> futures;
    Iterator block_start = begin;
    for (size_t i = 0; i < num_threads; ++i){
        Iterator block_end = (i == num_threads - 1) ? end : block_start + block_size;
        futures.emplace_back(std::async(std::launch::async, [block_start, block_end](){
            return std::accumulate(block_start, block_end, T{});
        }));
        block_start = block_end;
    }

    T result = init;
    for (auto& f : futures){
        result += f.get();
    }

    return result;
}

int main(){
    std::vector<double> data(1'000'000, 1); // Vector with 1,000,000 elements of value 1


    // Measure single-threaded execution time
    auto start_single = std::chrono::high_resolution_clock::now();
    auto single_threaded_result = std::accumulate(data.begin(), data.end(), 0);
    auto end_single = std::chrono::high_resolution_clock::now();
    auto single_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_single - start_single).count();

    // Measure multi-threaded execution time
    auto start_parallel = std::chrono::high_resolution_clock::now();
    auto parallel_result = parallel_accumulate(data.begin(), data.end(), 0);
    auto end_parallel = std::chrono::high_resolution_clock::now();
    auto parallel_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_parallel - start_parallel).count();

    // Print results
    std::cout << "Single-threaded result : " << single_threaded_result << "\n";
    std::cout << "Parallel result : " << parallel_result << "\n";
    std::cout << "Time taken (single-threaded): " << single_duration << " ms\n";
    std::cout << "Time taken (multi-threaded): " << parallel_duration << " ms\n";

    return 0;
}