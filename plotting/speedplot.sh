#!/bin/bash

for i in 1
do
    printf "plot 'speedplot.dat' using 1:2 with lines, '' using 1:3 with lines\n";
    while true
    do
        printf "set autoscale xy\n"
        printf "replot\n"
        sleep 1
    done
done | gnuplot
