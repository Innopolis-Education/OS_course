date
sleep 3
touch root/root.txt

date
sleep 3
touch home/home.txt

cd ..
ls -ltu -r -t > /home/zener/OS_course/week1/home/home.txt

cd ..
cd ..
ls -ltu -r -t > /home/zener/OS_course/week1/root/root.txt

# shellcheck disable=SC2164
cd /home/zener/OS_course/week1

cat < root.txt
cat < home.txt
ls
