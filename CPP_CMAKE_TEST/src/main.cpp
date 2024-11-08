#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

int main() {
    std::cout << "hello world" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::ofstream log("log.txt");
    log << "Hello World" << std::endl;
    log.close();
    return 0;
}
