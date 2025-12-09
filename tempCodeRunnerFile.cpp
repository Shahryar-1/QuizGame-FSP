#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    cout << "Wait 0.2 seconds...\n";
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "Done!\n";
    return 0;
}
