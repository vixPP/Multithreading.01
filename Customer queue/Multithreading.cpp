#include <iostream>
#include <thread>
#include<mutex>
#include<chrono>
#include<atomic>

using namespace std;

mutex m{};
int MAX_CLIENTS = 10; 
atomic<int> AtomicClientCount = 0; 

void Add1() 
{
    while (AtomicClientCount < MAX_CLIENTS)
    {
        this_thread::sleep_for(chrono::seconds(1)); 
        if (AtomicClientCount < MAX_CLIENTS)
        {
            AtomicClientCount++;
            cout << AtomicClientCount << endl;
        }
    }
}

void sub1() 
{
    while (AtomicClientCount < MAX_CLIENTS)
    {
        this_thread::sleep_for(chrono::seconds(2));
        if (AtomicClientCount < MAX_CLIENTS)
        {
            AtomicClientCount--;
            cout << AtomicClientCount << endl;
        }
    }
}

int main() 
{
    thread addThread(Add1);
    thread subThread(sub1);

    addThread.join();
    subThread.join();

    return EXIT_SUCCESS;
}
