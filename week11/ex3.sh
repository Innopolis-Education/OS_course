# I created files by using CLion, so there is no commands, which helps to create or print something to the files
# shellcheck disable=SC2129
chmod a=rw _ex3.txt > ex3.txt # no output
chmod uo=rwx _ex3.txt >> ex3.txt # still no output
chmod g=u _ex3.txt >> ex3.txt  # again no output
echo "Next 3 lines are taken from https://www.google.com/search?q=
660 permission means: I (owner) can write and read the file. Group members can write and read the file.
777 - all can read/write/execute (full access).
755 - owner can read/write/execute, group/others can read/execute." >> ex3.txt
