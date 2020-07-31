#!/bin/sh

for i in `seq 0 9`
do

sed "s/apple/runcc$i.sh/g" haddjob.slurm > haddjob$i.slurm

sbatch -J CC$i -o out_haddjob$i.out haddjob$i.slurm
echo "$i"
done




