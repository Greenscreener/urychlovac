while true;
do  
    tail -n 1 speedplot.dat | awk '{printf("time since start: %.0f s\ncurrent speed: %.3f m·s¯¹\naverage speed: %.3f m·s¯¹", $1, $2, $3)}'
    sleep 0.1;
    clear;
done

