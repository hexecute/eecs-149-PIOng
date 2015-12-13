#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "stl_driver.h"

using namespace std;
using namespace CPSGrader;

// a trace element is a vector of double for which the first value is time. 
typedef vector<double> trace_elem;

// a trace is a vector of trace elements. 
typedef vector<trace_elem> trace_data;

// this function reads a file with a simple format: each line contains values for a trace element
bool read_trace_file(const string &trace_file_name, vector< vector<double> > &data)
{

    std::ifstream file;
	file.open(trace_file_name.c_str());

	if (!file.is_open()) {
		cout << "trace file " << trace_file_name << " not found" << endl;
		return false;
	}

	string line;
	while (!std::getline(file, line, '\n').eof()) {
		istringstream reader(line);
		vector<double> lineData;
		while (!reader.eof()) {
			double val;
			reader >> val;
			lineData.push_back(val);
		}
		data.push_back(lineData);
	}
	file.close();
	return true;
}


int main(int argc, char** argv) {

	// instantiates the STLDriver
	STLDriver stl_driver = STLDriver();

	// read test_plan file 
	std::fstream infile(argv[argc - 1]);
	if (!infile.good()) {
		cout << "Could not open file: " << argv[argc - 1] << endl;
		return 0;
	}
	bool result = stl_driver.parse_stream(infile, argv[argc - 1]);

	if (result) {

        // Displays the sequence of tests read 
		stl_driver.print();

        // Process all trace tests in the queue
        while (!stl_driver.trace_test_queue_empty()) {
            // gets filename for the next trace 
            string trace_file_name = stl_driver.get_next_trace_test_env();

            // clear stl_driver trace data 
            stl_driver.data.clear();

            // read trace file and write it into the data field of the stl_driver
            bool success = read_trace(trace_file_name, stl_driver.data);

            // run the next trace test 
            if (success)
				stl_driver.run_next_trace_test();
			else {
                stl_driver.report = stl_driver.report + "Skipped test " + stl_driver.get_next_trace_test()->id +"\n";
                stl_driver.pop_next_trace_test();
            }
		}

        // displays test results 
        cout << "Report:" << endl;
        cout << stl_driver.report << endl;
		cout << "Test log:" << endl;
		cout << stl_driver.test_log << endl;

        // writes test log, reporting quantitative satisfaction of each formula and number of
        // positive test  
        if (stl_driver.dump_test_log_file("test_log.txt"))  
            cout << "Test log written in test_log.txt" << endl;
        else
            cout << "Problem writing test_log.txt file." << endl;   
    }
    else
        cout << "Problem parsing test_plan file." << endl;

   
	return 0;

}

