// ex9.1.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

static bool s_Finished = false; //This bool will finish the process when we want

vector<double> DoWork1(vector<double>& v) //This function prints "working" every  1 second. It also modifies the 1rst value of a vector passed by reference
{
	cout << " Started thread id-" << this_thread::get_id() << endl;

	while(!s_Finished) {
		cout << "Working thread 1...\n" << endl;
		this_thread::sleep_for(1s);
	}

	typename vector<double>::iterator ibeg;
	ibeg = v.begin();
	++(*ibeg);
	cout << "Vector passed by reference modified: " << *ibeg << "," << *(++ibeg) << endl;
	return v;
}

vector<double> DoWork2(vector<double> v) //This function prints every 0.5 second. Does the same as the other one but this time the vector is passed by value
{
	this_thread::sleep_for(0.0001s); //If i don't make it sleep for a short amount of time, id printing messages will get mixed 
	cout << " Started thread id-" << this_thread::get_id() << endl;

	while (!s_Finished) {
		cout << "Working thread 2...\n" << endl;
		this_thread::sleep_for(0.5s);
	}

	typename vector<double>::iterator ibeg;
	ibeg = v.begin();
	++(*ibeg);
	cout << "Vector passed by value modified: " << *ibeg << "," << *(++ibeg) << endl;
	return v;
}

int main()
{
	vector<double> v1{ 0., 1.};
	vector<double> v2{ 0., 1. };


	thread worker1{ DoWork1, v1 }; //Starting thread 1 and 2 --> we pass the function and the arguments
	thread worker2{ DoWork2, std::ref(v1) }; //since dowork2 works with a reference, indicate explicitly the use of a reference

	cin.get(); //Meanwhile, the main thread waits until you press something 
	s_Finished = true; //Stop the while loops in DoWork functions and print the vectors

	worker1.join(); //Block main thread until thread 1 and thread 2 are thone --> Don't keep going with the main program
	worker2.join();
	cout << "Finished." << endl; //Once we finish thread 1 and 2 --> finish function
	cout << "Started thread id-" << this_thread::get_id() <<  endl;
	return 0;
}
