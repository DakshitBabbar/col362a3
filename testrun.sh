make clean
make 
for i in 2
do
    for j in 25
    do
        echo "K: $i"
        echo "NUM_MERGES: $j"
        make remove
        # rm output.txt
        ./exec ../random.txt output.txt 1000000 $i $j
    done
done
