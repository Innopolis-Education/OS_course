# Execute from the working directory
touch file1
touch file2
echo Timofey >> file1
echo Didenko >> file2
gcc ex2.c -o ex2.out
chroot . ./ex2.out > ex2.txt
./ex2.out >> ex2.txt