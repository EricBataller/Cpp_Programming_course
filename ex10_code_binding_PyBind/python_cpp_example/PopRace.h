// ex10_.h : Include file for standard system include files,
// or project specific include files.

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <list>
#include <random>
#include <mutex>
#include <tuple>

using namespace std;


template <typename T>
class PopRace {
private:
	T _element; // _element will be the element that we will push into the queue (we could use _iterations too but this way we use template)
	int _iterations;
	int _num_participants;
	queue<T> q;
	mutex _m;
	list<thread> threads; //one thread for the producer and one thread for every consumer (participant)
	list<int> counts; //list where all the results of the consumer go
	

public:
	int max_counts = 0; //greatest element in counts
	int winner = 0; //index of the greatest element in counts

	PopRace(int iter, int num_part, T first_element) : _iterations(iter), _num_participants(num_part), _element(first_element) {}
	~PopRace() { cout << "~Destructor" << endl; }

private:

	void producer(mutex& m) { //produces an element (_iterations--) and pushes it to the queue as fast as it can
		while (_iterations != 0) {
			std::lock_guard<std::mutex> lock(m);
			q.push(_element);
			_iterations--;
			_element++;
		}
	}

	void consumer(mutex& m) { //Consumer pops the elements from queue within a time between (0 - 500 msec)
		this_thread::sleep_for(chrono::milliseconds(50)); //Make the consumers sleep while the producer is activated
		int con_count = 0; //count of how many elements pop the consumer

		random_device d; //Adding randomness to the time it takes to pop the variables
		mt19937 mt(d()); //Mersenne Twister pseudo-random number generator
		int t_max = 500; //max time we assign for the consumer to pop an element
		uniform_int_distribution<int> distr(0, t_max);
		while (!q.empty()) {
			int t = distr(mt); //sample from time uniform distribution
			this_thread::sleep_for(chrono::milliseconds(t));
			std::lock_guard<std::mutex> lock(m);
			if (!q.empty()) {
				cout << "Popping element " << q.front() << " from Queue" << endl;
				con_count++;
				q.pop();
			}
		}
		std::lock_guard<std::mutex> lock(m);
		counts.push_back(con_count);
		cout << "Participant number " << counts.size() << " popped: " << con_count << " elements" << endl;
	}

public:

	void PoppingRace() {
		threads.push_back(thread(&PopRace::producer, this, ref(_m))); //First thread will be the producer
		for (int i = 0; i < _num_participants; i++) {
			threads.push_back(thread(&PopRace::consumer, this, ref(_m))); //The rest of the threads are the participants of the race
		}
		for (list<thread>::iterator it = threads.begin(); it != threads.end(); it++) {
			(*it).join();
		}
		threads.clear();

		int element = 0;
		int current;
		for (std::list<int>::iterator it = counts.begin(); it != counts.end(); it++)
		{
			current = *it;
			element++;
			if (current > max_counts) {
				max_counts = current;
				winner = element;
			}
		}
		cout << "The winner of this race is participant number " << winner << " with a total amount of " << max_counts << " elements popped from the queue." << endl;
	}

	const int GetWinner() const { return winner; }
	const int GetCounts() const { return max_counts; }
};

#endif 
