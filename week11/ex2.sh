# I created files by using CLion, so there is no commands, which helps to create or print something to the files
link ../week1/file.txt _ex2.txt
# shellcheck disable=SC2046
find .. -inum $(stat -c "%i" ../week1/file.txt) > ex2.txt
find .. -inum $(stat -c "%i" ../week1/file.txt) -exec rm {} \; >> ex2.txt
