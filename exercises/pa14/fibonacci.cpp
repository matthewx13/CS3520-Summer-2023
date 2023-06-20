#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>

unsigned long long fibonacci(unsigned int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

void parallelExecution(const std::vector<unsigned int>& numbers) {
    std::vector<std::future<std::pair<std::thread::id, unsigned long long>>> futures(numbers.size());

    auto startTime = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < numbers.size(); ++i) {
        futures[i] = std::async(std::launch::async, [](unsigned int n) {
            return std::make_pair(std::this_thread::get_id(), fibonacci(n));
        }, numbers[i]);
    }

    for (size_t i = 0; i < numbers.size(); ++i) {
        auto result = futures[i].get();
        std::cout << "Thread " << i + 1 << " ID: " << result.first << ", Fibonacci(" << numbers[i] << "): " << result.second << '\n';
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Parallel execution time: " << duration << " milliseconds\n";
}

void sequentialExecution(const std::vector<unsigned int>& numbers) {
    auto startTime = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << "Fibonacci(" << numbers[i] << "): " << fibonacci(numbers[i]) << '\n';
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Sequential execution time: " << duration << " milliseconds\n";
}

int main() {
    std::vector<unsigned int> numbers(3);
    std::cout << "Please provide 3 numbers greater than 30: ";
    for (unsigned int& number : numbers) {
        std::cin >> number;
    }

    std::cout << "\nPerforming parallel execution...\n";
    parallelExecution(numbers);

    std::cout << "\nPerforming sequential execution...\n";
    sequentialExecution(numbers);

    return 0;
}
