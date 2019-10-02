#!/bin/sh
njobs=500
for i in `seq 0 $(($njobs-1))`
do

echo $i
jbi=jb$i
mkdir $jbi
mkdir $jbi/ana


cp ampt $jbi
cp input.ampt $jbi
cp exec.sh $jbi
cp jobsub.slurm $jbi
sed "s/jb0/$jbi/g" $jbi/jobsub.slurm > $jbi/jobsub$i.slurm
rm $jbi/jobsub.slurm

cd $jbi
sbatch -J ppb01jb$i -o out_job$i.out jobsub$i.slurm
cd ..

done




