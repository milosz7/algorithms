#!/bin/bash
n_max=1000000
n_to_generate=10000
generate_limit=250000
jump=10000
sorts=("InsertionSort" "BubbleSort" "SelectionSort")
rm *.txt
while [ $n_to_generate -le $generate_limit ]
do 
    filename=input_$n_to_generate.txt
    touch $filename
    ./Generator.x $n_to_generate $n_max > $filename
    for sort in ${sorts[@]}; do
        touch ${sort}_results.txt
        ./${sort}.x < $filename >> ${sort}_results.txt
    done
    n_to_generate=$(($n_to_generate+$jump))
done
rm input_*.txt