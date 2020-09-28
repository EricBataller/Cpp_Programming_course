// ex10_.cpp : Defines the entry point for the application.
//
#include "pybind11/pybind11.h"
#include "PopRace.h"


namespace py = pybind11;

PYBIND11_MODULE(pybind11_module_example, m) {
	// Make C++ functions accessible from Python
	py::class_<PopRace<int>> (m, "PopRace") //, py::dynamic_attr())
		.def(py::init<int, int, int>(), py::arg("iterations"), py::arg("participants"), py::arg("first_element_queue"))
		.def("PoppingRace", &PopRace<int>::PoppingRace)
		.def("GetWinner", &PopRace<int>::GetWinner)
		.def("GetCounts", &PopRace<int>::GetCounts)
	.def("__repr__", [](const PopRace<int>& a) { return "<There is no representation for PoppingRace>"; });

	m.doc() = "pybind11_module_example"; // optional module docstring
}


/*
//This is a test to check if PopRace class works properly

int main()
{
	const int iterations = 100;
	const int participants = 3;
	int first_element = 5;

	PopRace<int> The_Race(iterations, participants, first_element);
	The_Race.Popping_race();
	The_Race.GetWinner();

	return 0;
}
*/

