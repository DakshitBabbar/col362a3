#include <bits/stdc++.h>

using namespace std;

extern int external_merge_sort_withstop(const char* input, const char* output, const long key_count, const int k = 2, const int num_merges = 0);

int main(int argc, char *argv[]){

    char* inputf = argv[1];
	char* outputf = argv[2];
    const int key_count = atoi(argv[3]);
    const int k = atoi(argv[4]);
    const int num_merges = atoi(argv[5]);
    int retval = external_merge_sort_withstop(inputf, outputf, key_count, k, num_merges);

    cout << "Return value : " << retval << endl;
    return 0;
}
