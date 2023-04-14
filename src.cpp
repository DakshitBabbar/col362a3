#include <bits/stdc++.h>
#include <chrono>
using namespace std;

//--globally defined system parameters--

//allowed size of the memory in Bytes to store the elemtns to be sorted
//int memorysize = 800000000;
int memorysize = 100000000;

//--globally defined system parameters--

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

//this function creates the initial runs from the input file given and returns the number of runs made
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
        int run_mem = 0;
        int run_lines = 0;
        while(run_mem<memorysize){
            if (count == key_count) break;

            if (getline (infile, element)) {
                myrun.push_back(element);
                count++;
                run_mem += element.length();
                run_lines++;
            } else {
                count == key_count;
                break;
            }
        }


        // for(int i=0; i<memorysize; i++){
        //     if (count == key_count) break;

        //     if (getline (infile, element)) {
        //       myrun.push_back(element);
        //       count++;
        //     } else {
        //         count == key_count;
        //         break;
        //     }
        // }

        //sort the vector
        sort_one(myrun);

        //output the sorted vector elements to the scratch output file
        fl_scratch_output = "temp.0."+ to_string(run_count+1)+ ".txt";
        ofstream outfile (fl_scratch_output);

        for(auto e: myrun){
            outfile << e << endl;
        }

        cout << "Number of lines in Run " << run_count+1 << ": " << run_lines << endl;

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

//this function defines the comaprison between two pairs based on the first elements
//called by the merge function for make_heap
struct greater_pair{
    bool operator()(const pair<string, int>& a,const pair<string, int>& b) const{
        if(a.first > b.first){
            return true;
        } else {
            return false;
        }
    }
};

//merges the runs from start to end (both inclusive) in the stage_num'th stage
//called by the merge_all function
void merge(int stage_num, int start, int end, int my_run_idx){
    int prev_stage = stage_num-1;

    //the number of lines per run that are supposed to be there in the buffer
    int mem_per_run = memorysize/(end-start+2);
    int output_buffer_size = memorysize - (end-start+1)*mem_per_run;

    //open all the files
    vector<ifstream> in_file_streams(end-start+1);
    string fl_input;
    for(int i=start; i<=end; i++){
        fl_input = "temp." + to_string(prev_stage) + "." + to_string(i) + ".txt";
        in_file_streams[i-start].open(fl_input);
    }  

    //make the buffer vector by taking input from files
    vector<pair<string,int>> sort_buffer;
    for(int i=start; i<=end; i++){
        pair<string, int> temp;
        int run_mem = 0;
        while(run_mem<mem_per_run){
            if (getline (in_file_streams[i-start], temp.first)) {
                temp.second = i;
                sort_buffer.push_back(temp);
                run_mem += temp.first.length();
            } else {
                break;
            }
        }

        // pair<string, int> temp;
        // for(int j=0; j<mem_per_run; j++){
        //     if(getline (in_file_streams[i-start], temp.first)){
        //         temp.second = i;
        //         sort_buffer.push_back(temp);
        //     } else {
        //         break;
        //     }
        // }
    }
    
    //make a heap of the buffer
    make_heap(sort_buffer.begin(), sort_buffer.end(), greater_pair());

    //make an output buffer
    vector<string> output_buffer; //maximum size of the output buffer is mem_per_run after which we will dump it to the drive

    int iter = 0;
    string fl_output = "temp." + to_string(stage_num) + "." + to_string(my_run_idx) + ".txt";
    ofstream outfile(fl_output, ios::app);
    while(sort_buffer.size() != 0){
        
        //fill the output buffer upto its limit
        int output_buffer_mem = 0;
        while(output_buffer_mem<output_buffer_size){
            //get the minimum element from the sort_buffer
            if(sort_buffer.size() != 0){
                pop_heap(sort_buffer.begin(), sort_buffer.end(), greater_pair());
                pair<string,int> temp_out = sort_buffer.back();
                sort_buffer.pop_back();

                //add it to the output_buffer
                output_buffer.push_back(temp_out.first);
                output_buffer_mem += temp_out.first.length();

                //replace the removed element with a new one from the same file that it was removed
                if(getline (in_file_streams[temp_out.second-start], temp_out.first)){
                    sort_buffer.push_back(temp_out);
                    push_heap(sort_buffer.begin(), sort_buffer.end(), greater_pair());
                }
            } else {
                break;
            }
        }

        // for(int i=0; i<output_buffer_size; i++){
        //     //get the minimum element from the sort_buffer
        //     if(sort_buffer.size() != 0){
        //         pop_heap(sort_buffer.begin(), sort_buffer.end(), greater_pair());
        //         pair<string,int> temp_out = sort_buffer.back();
        //         sort_buffer.pop_back();

        //         //add it to the output_buffer
        //         output_buffer.push_back(temp_out.first);

        //         //replace the removed element with a new one from the same file that it was removed
        //         if(getline (in_file_streams[temp_out.second-start], temp_out.first)){
        //             sort_buffer.push_back(temp_out);
        //             push_heap(sort_buffer.begin(), sort_buffer.end(), greater_pair());
        //         }
        //     }
        // }


        //cout << output_buffer.size() << endl;

        //dump the output buffer to the appropriate file
        //string fl_output = "temp." + to_string(stage_num) + "." + to_string(my_run_idx) + ".txt";
        // if(iter == 0){
        //     ofstream outfile(fl_output);
        //     for(auto e:output_buffer){
        //         outfile << e << endl;
        //     }
        //     outfile.close();

        // } else {    
        //     ofstream outfile(fl_output, ios::app);
        //     for(auto e:output_buffer){
        //         outfile << e << endl;
        //     }
        //     outfile.close();

        // }


        //dump the output buffer to the appropriate file
        for(auto e:output_buffer){
            outfile << e << endl;
        }
        

        output_buffer.clear();
        iter++;
    }

    //close all the files
    outfile.close();

    for(int i=start; i<=end; i++){
        in_file_streams[i-start].close();
    }

}

//this function takes the following inputs and merges all the runs to get the final output
//called by external_merge_sort_withstop
int merge_all(string fl_output, const int k, const int num_merges, int num_init_runs){
    int stage_count = 1;
    int in_run_count = num_init_runs;
    int merge_count = 0;
    while(in_run_count != 1){
        //check if the process needs to be stoped midway
        if(num_merges !=0){
            if(merge_count==num_merges){
                break;
            }
        }

        //if not then continue
        int out_run_count = 0;
        int run_idx = 1;
        while(run_idx <= in_run_count){
            //check if the process needs to be stoped midway
            if(num_merges !=0){
                if(merge_count==num_merges){
                    break;
                }
            }

            //if not then continue
            int start = run_idx;
            int end;
            if(run_idx+k-1 <= in_run_count){
                end = run_idx+k-1;
            } else {
                end = in_run_count;
            }
            merge(stage_count, start, end, out_run_count+1);
            run_idx += k;
            merge_count++;
            out_run_count++;
        }
        stage_count++;
        in_run_count = out_run_count;
    }

    //return the appropriate values
    if(in_run_count!=1){
        return -1;
    } else {
        //##can be a bottle neck, try to optimise
        // Output the text from temp.last.1 to output file given
        string last_temp_file = "temp." + to_string(stage_count-1) + ".1.txt";
        string temp = "";
        ifstream infile (last_temp_file);
        ofstream outfile (fl_output);
        while (getline (infile, temp)) {
          outfile << temp << endl;
        }

        outfile.close();
        infile.close();
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

