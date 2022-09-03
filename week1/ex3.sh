date
sleep 3
touch root.txt

date
sleep 3
touch home.txt

cd ..
ls -ltu -r -t > /home/zener/OS_course/week1/home.txt

cd ..
cd ..
ls -ltu -r -t > /home/zener/OS_course/week1/root.txt

# shellcheck disable=SC2164
cd /home/zener/OS_course/week1

cat < root.txt
cat < home.txt
ls
