#!/bin/sh
njobs=100
for i in `seq 0 $(($njobs-1))`
do

echo $i
jbi=jb$i
mkdir $jbi


cp ROOT_Tree.c $jbi
cp ROOT_Tree.h $jbi
cp jobsub.slurm $jbi
sed "s/jb0/$jbi/g" $jbi/jobsub.slurm > $jbi/jobsub$i.slurm
rm $jbi/jobsub.slurm

sed "s/jb0/$jbi/g" $jbi/ROOT_Tree.c > $jbi/ROOT_Tree$i.c
mv $jbi/ROOT_Tree$i.c $jbi/ROOT_Tree.c

cd $jbi
sbatch -J B01jb$i -o out_job$i.out jobsub$i.slurm
cd ..

done




