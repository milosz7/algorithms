#!/bin/bash
n_max=100000
n_to_generate=1000
reps=1000
touch sort_swaps.txt
for i in {1..1000..1}
do  
    ./Generator.x $n_to_generate $n_max > input.txt
    ./SelectionSort.x < input.txt >> sort_swaps.txt
    sleep 2
    rm input.txt
done