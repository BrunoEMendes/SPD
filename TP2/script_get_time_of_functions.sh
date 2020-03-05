#!/bin/bash

echo "Bash version ${BASH_VERSION}"
echo "Deleting old .txt files..."
echo "$(ls -l output/*.txt | wc -l)"
echo "Calculating times..."
for i in {1..10}
do

    ##POTENCIAS DE 10
    #sequential com otimização
    echo "input  $((10**$i))" &>> output/sequential_default_10.txt
    (time ./main -ql4 $((10**$i))) &>> output/sequential_default_10.txt
    echo "" &>> output/sequential_default_10.txt

    #sequential com otimização
    echo "input  $((10**$i))" &>> output/sequential_opti_10.txt
    (time ./main -ql4 $((10**$i))) &>> output/sequential_opti_10.txt
    echo "" &>> output/sequential_opti_10.txt

    #pthread 2
    echo "input $((10**$i))" &>> output/pthread_2_10.txt
    (time ./main -ql4 $((10**$i))) &>> output/pthread_2_10.txt
    echo "" &>> output/pthread_2_10.txt

    #pthread 3
    echo "input $((10**$i))" &>> output/pthread_3_10.txt
    (time ./main -ql4 $((10**$i))) &>> output/pthread_3_10.txt
    echo "" &>> output/pthread_3_10.txt

    #pthread 4 no mutex
    echo "input  $((10**$i))" &>> output/pthread_4_10.txt
    (time ./main -ql5 $((10**$i))) &>> output/pthread_4_10.txt
    echo "" &>> output/pthread_4_10.txt

    #mutex 4
    echo "input $((10**$i))" &>> output/pthread_mutex_4_10.txt
    (time ./main -ql6 $((10**$i))) &>> output/pthread_mutex_4_10.txt
    echo "" &>> output/pthread_mutex_4_10.txt

    #OPEN_MP
    echo "input $((10**$i))" &>> output/open_mp_10.txt
   (time ./main -ql7 $((10**$i))) &>> output/open_mp_10.txt
    echo "" &>> output/open_mp_10.txt

    #POTENCIAS DE 2
    #sequential sem otimização
    echo "input  $((2**$i))" &>> output/sequential_default_2.txt
    (time ./main -ql4 $((2**$i))) &>> output/sequential_default_2.txt
    echo "" &>> output/sequential_default_2.txt

    #sequential com otimização
    echo "input  $((2**$i))" &>> output/sequential_opti_2.txt
    (time ./main -ql4 $((2**$i))) &>> output/sequential_opti_2.txt
    echo "" &>> output/sequential_opti_2.txt

    #pthread 2
    echo "input $((2**$i))" &>> output/pthread_2_2.txt
    (time ./main -ql4 $((2**$i))) &>> output/pthread_2_2.txt
    echo "" &>> output/pthread_2_2.txt

    #pthread 3
    echo "input $((2**$i))" &>> output/pthread_3_2.txt
    (time ./main -ql4 $((2**$i))) &>> output/pthread_3_2.txt
    echo "" &>> output/pthread_3_2.txt

    #pthread 4 no mutex
    echo "input  $((2**$i))" &>> output/pthread_4_2.txt
    (time ./main -ql5 $((2**$i))) &>> output/pthread_4_2.txt
    echo "" &>> output/pthread_4_2.txt

    #mutex 4
    echo "input $((2**$i))" &>> output/pthread_mutex_4_2.txt
    (time ./main -ql6 $((2**$i))) &>> output/pthread_mutex_4_2.txt
    echo "" &>> output/pthread_mutex_4_2.txt

    #OPEN_MP
    echo "input $((2**$i))" &>> output/open_mp_2.txt
   (time ./main -ql7 $((2**$i))) &>> output/open_mp_2.txt
    echo "" &>> output/open_mp_2.txt
done
echo "DONE!"

# echo "$X"
# echo var
