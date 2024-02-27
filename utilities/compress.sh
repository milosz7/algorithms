#!/bin/bash
folder=$1
out=$2
pattern="[hpp|cpp|h]"
files=$(find $folder -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \))
tar -cvzf $out $files