#!/bin/sh
njobs=10
for i in `seq 0 $(($njobs-1))`
do
p=$(($i *100))
o=$(($p+99))

sed "s/tmpnstart/$p/g" good_files_log.slurm > tmp.slurm
sed "s/runcc/runcc$i/g" tmp.slurm > tmp2.slurm
sed "s/tmpnend/$o/g" tmp2.slurm > good_files_log$i.slurm
rm tmp.slurm
rm tmp2.slurm

sbatch -J CC$i -o out_job$i.out good_files_log$i.slurm
echo "$i"
done




