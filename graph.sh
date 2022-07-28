#!/bin/bash
rm graphs/*.svg
rm graphs/cfg/*.svg

for f in graphs/*.gv; 
do 
    echo $f
    dot $f -T svg -o ${f%%.*}.svg
done

for f in graphs/cfg/*.gv; 
do 
    echo $f
    dot $f -T svg -o ${f%%.*}.svg
done

rm graphs/*.gv
rm graphs/cfg/*.gv
