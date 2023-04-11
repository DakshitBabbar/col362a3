//#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

//this function takes the following inputs and creates the initial runs from the input file given
void sort_all(string fl_input, const long key_count, const int k = 2, const int num_merges = 0){

    ifstream myfile (fl_input);
 
    

    myfile.close();
}

//this function takes the following inputs and outputs the sorted file as the output file along with returning the number of merges performed
//input: input file name
//output: output file name
//key_count: the number of keys that need to be sorted from the input file
//k: the maximum number of runs that can be merged at one time
//num_merges: the number of merge steps to be taken, by default complete till we get the output
int external_merge_sort_withstop(const char* input, const char* output, const long key_count, const int k = 2, const int num_merges = 0){
    string fl_input = input;
    string fl_output = output;
	void sort_all(fl_input, key_count, k, num_merges);
	void merge_all(fl_output)
}