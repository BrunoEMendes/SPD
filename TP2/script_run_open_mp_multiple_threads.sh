#!/bin/bash

echo "Bash version ${BASH_VERSION}"
echo "Deleting old .txt files..."
echo "$(ls -l output/*.txt | wc -l)"
echo "Calculating times..."
echo "calculating with 4 threads"
export OMP_NUM_THREADS=4
for i in {11..18}
do
    #OPEN_MP
    echo "input $((10**$i))" &>> output/open_mp_4_threads.txt
   (time ./main -il7 $((10**$i))) &>> output/open_mp_4_threads.txt
    echo "" &>> output/open_mp_4_threads.txt
done
echo "DONE!"

echo "calculating with 8 threads"
export OMP_NUM_THREADS=8
for i in {11..18}
do
    #OPEN_MP
    echo "input $((10**$i))" &>> output/open_mp_8_threads.txt
   (time ./main -il7 $((10**$i))) &>> output/open_mp_8_threads.txt
    echo "" &>> output/open_mp_8_threads.txt
done
echo "DONE!"

echo "calculating with 16 threads"
export OMP_NUM_THREADS=16
for i in {11..18}
do
    #OPEN_MP
    echo "input $((10**$i))" &>> output/open_mp_16_threads.txt
   (time ./main -il7 $((10**$i))) &>> output/open_mp_16_threads.txt
    echo "" &>> output/open_mp_16_threads.txt
done
echo "DONE!"

echo "calculating with 32 threads"
export OMP_NUM_THREADS=32
for i in {11..18}
do
    #OPEN_MP
    echo "input $((10**$i))" &>> output/open_mp_32_threads.txt
   (time ./main -il7 $((10**$i))) &>> output/open_mp_32_threads.txt
    echo "" &>> output/open_mp_32_threads.txt
done
echo "DONE!"


echo "calculating with 64 threads"
export OMP_NUM_THREADS=64
for i in {11..18}
do
    #OPEN_MP
    echo "input $((10**$i))" &>> output/open_mp_64_threads.txt
   (time ./main -il7 $((10**$i))) &>> output/open_mp_64_threads.txt
    echo "" &>> output/open_mp_64_threads.txt
done
echo "DONE!"

echo "calculating with 128 threads"
export OMP_NUM_THREADS=128
for i in {11..18}
do
    #OPEN_MP
    echo "input $((10**$i))" &>> output/open_mp_128_threads.txt
   (time ./main -il7 $((10**$i))) &>> output/open_mp_128_threads.txt
    echo "" &>> output/open_mp_128_threads.txt
done
echo "DONE!"



# echo "$X"
# echo var
