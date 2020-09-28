// ex9.2.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <random>
#include <mutex>

/*
This program generates a queue in which we'll inject elements using a producer() function while to
functions slow_consumer and fast_consumer compete to pop those elements. Fast consumer sleeps less and
therefore pops more elements and always wins.
*/

using namespace std;

static bool s_Finished = false; //This bool will finish the process when we want
int fcon_count = 0, scon_count = 0; //count of how many elements pop every consumer (fast_consumer and slow_consumer)

template<class T>
class SafeQueue {

	std::queue<T> q;
	std::mutex m;
	
public:
	T i;

	SafeQueue(T init) : i(init) {}
	
	void producer() { //produces an element (i++) and pushes it to the queue with a random time (0s - 0.5s) 
		random_device d; //Adding randomness to the time it takes to push the variables
		mt19937 mt(d()); //Mersenne Twister pseudo-random number generator
		int t_max = 500; //max time we assign for the sampler to generate the sample
		uniform_int_distribution<int> distr(0, t_max);
		while (!s_Finished) {
			int t = distr(mt); //sample from time uniform distribution
			this_thread::sleep_for(chrono::milliseconds(t));
			std::lock_guard<std::mutex> lock(m);
			q.push(i);
			i++;
		}
	}

	void slow_consumer() { //Consumer pops the elements from queue slowly (ready every 800 msec)
		while (!s_Finished) {
			this_thread::sleep_for(chrono::milliseconds(800));
			std::lock_guard<std::mutex> lock(m);
			if (q.empty()) {
				cout << "Producer too slow, give me more elements to pop out..." << endl;
			}
			else {
				cout << "Slow Consumer Popping element " << q.front() << " from Queue" << endl;
				scon_count++;
				q.pop();
			}
		}
	}

	void fast_consumer() { //Consumer pops the elements from queue fast (ready every 700msec)
		while (!s_Finished) {
			this_thread::sleep_for(chrono::milliseconds(700));
			std::lock_guard<std::mutex> lock(m);
			if (q.empty()) {
				cout << "Producer too slow, give me more elements to pop out..." << endl;
			}
			else {
				cout << "Fast Consumer Popping element " << q.front() << " from Queue" << endl;
				fcon_count++;
				q.pop();
			}
		}
	}
};


int main()
{
	SafeQueue<int> my_queue(0); //generate queue<int> and initialize i=0
	
	thread worker1{ &SafeQueue<int>::producer, &my_queue }; //Activate producer() and consumer() in different threads
	thread worker2{ &SafeQueue<int>::slow_consumer, &my_queue }; 
	thread worker3{ &SafeQueue<int>::fast_consumer, &my_queue };

	cin.get(); //Meanwhile, the main thread waits until you press something 
	s_Finished = true; //Stop the while loops in functions

	worker1.join(); //Block main thread until thread 1 and thread 2 are done --> Don't keep going with the main program
	worker2.join();
	worker3.join();

	cout << "\n Fast and slow consumers popped " << fcon_count << " and " << scon_count << " elements, respectively" <<  endl;
	cout << "\n Fast_consumer is the winner!!!" << endl;

	return 0;
}