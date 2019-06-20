#!/bin/bash

for i in 1
do
    printf "plot 'speedplot.dat' using 1:2 with lines, '' using 1:3 with lines\n";
    while true
    do
        printf "set autoscale y\n"
        export lastMeasurementTime=$(cat speedplot.dat | tail -n 1 | awk '{print $1}')
        printf "set xrange[$(echo "$lastMeasurementTime - 30" | bc):$lastMeasurementTime]\n"
        printf "replot\n"
        sleep 1
    done
done | gnuplot
