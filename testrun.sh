make
for i in 2 8 16 
do
    for j in 5 50 100
    do
        echo "K: $i"
        echo "NUM_MERGES: $j"
        make remove
        time ./exec ../random.txt output.txt 1000000 $i $j
        diff output.txt ../randomexp.txt
    done
done
