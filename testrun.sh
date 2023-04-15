make clean
make 
for i in 2 8 16
do
    for j in 0
    do
        echo "K: $i"
        echo "NUM_MERGES: $j"
        make remove
        ./exec ../random.txt output.txt 1000000 $i $j
        diff output.txt ../randomexp.txt
    done
done
