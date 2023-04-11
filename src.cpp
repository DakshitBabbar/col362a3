#include <bits/stdc++.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <fstream>
// #include <string>
// #include <vector>
using namespace std;


//this function sorts the input run in ascending order 
//called by sort_all function
void sort_one(vector<string>& run){
    //use inbuilt sorting of a vector which uses introsort (hybrid algo which uses merge sort quick sort and heap sort, has O(n) space complexity and O(nlogn) time complexity)
    //sort(run.begin(), run.end());

    //or

    //use inbuilt sorting of a heap which uses heap sort (has O(1) space complexity and O(nlogn) time complexity)
    make_heap(run.begin(), run.end());
    sort_heap(run.begin(), run.end());
}


//this function takes creates the initial runs from the input file given and returns the number of runs made
//called by external_merge_sort_withstop
int sort_all(string fl_input, const long key_count){

    ifstream infile (fl_input); //the file is not loaded into menmory at this point
    
    vector<string> myrun;
    string element = "";
    int count = 0;
    int run_count = 0;
    string fl_scratch_output = "";
    while(count < key_count){
        //take the first few strings that consitute at most 800MB of space and put them in a vector
        for(int i=0; i<800000; i++){
            if (count = key_count) break;
            infile >> element;
            myrun.push_back(element);
            count++
        }

        //sort the vector
        sort_one(myrun);

        //output the sorted vector elements to the scratch output file
        fl_scratch_output = "temp.0."+ to_string(run_count+1)+ ".txt";
        ofstream outfile (fl_scratch_output);

        for(auto e: myrun){
            outfile << e << endl;
        }

        //close the output scratch files
        outfile.close();

        //increase the run count
        run_count++;

        //clear the vector
        myrun.clear();
    }

    //close the input file
    infile.close();

    return run_count;
}

//merges the runs from start to end (both inclusive) in the stage_num'th stage
void merge(int stage_num, int start, int end, int my_run_idx){
    int prev_stage = stage_num-1;
    

}


//this function takes the following inputs and merges all the runs to get the final output
//called by external_merge_sort_withstop
int merge_all(string fl_output, const int k = 2, const int num_merges = 0, int num_init_runs){
    int stage_count = 1;
    int in_run_count = num_init_runs;
    int merge_count = 0;
    while(in_run_count != 1){

        //check if the process needs to be stoped midway
        if(num_merges !=0){
            if(merge_count=num_merges){
                break;
            }
        }

        //if not then continue
        int out_run_count = 0;
        int run_idx = 1;
        while(run_idx <= in_run_count){

            //check if the process needs to be stoped midway
            if(num_merges !=0){
                if(merge_count=num_merges){
                    break;
                }
            }

            //if not then continue
            int start = run_idx;
            int end;
            if(run_idx+k-1 <= in_run_count){
                end = run_idx+k-1
            } else {
                end = in_run_count;
            }
            merge(stage_count, start, end, out_run_count+1)
            run_idx += k;
            merge_count++;
            out_run_count++;
        }
        stage_count++;
        in_run_count = out_run_count;
    }

    //##can be a bottle neck, try to optimise
    // Output the text from temp.last.1 to output file given
    string last_temp_file = "temp." + to_string(stage_count-1) ".1.txt";
    string temp = "";
    ifstream infile (last_temp_file);
    ofstream outfile (fl_output);
    while (getline (infile, temp)) {
      outfile << temp;
    }

    outfile.close();
    infile.close();

    //return the appropriate values
    if(num_merges!=0){
        return -1;
    } else {
        return merge_count;
    }

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
    int num_runs;
    int num_merges_out;

	num_runs = sort_all(fl_input, key_count);
	num_merges_out = merge_all(fl_output, k, num_merges, num_runs);

    return num_merges_out;
}
