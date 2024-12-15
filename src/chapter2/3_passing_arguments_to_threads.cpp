#include <iostream>
#include <thread>
#include <vector>
#include <numeric>

void calculate_sum(const std::vector<int>& numbers, int& result){
    result = std::accumulate(numbers.begin(), numbers.end(), 0);
}

int main(){
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    int result = 0;

    std::thread thread(calculate_sum, std::ref(numbers), std::ref(result));
    thread.join();

    std::cout << "Sum of numbers: " << result << "\n";
    return 0;

}