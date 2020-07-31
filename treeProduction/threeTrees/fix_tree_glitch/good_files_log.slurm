#!/bin/bash
#SBATCH --nodes=1
#SBATCH --mem-per-cpu=1G
#SBATCH --time=0-01:30:00

echo $SLURM_JOB_ID
echo $SLURM_JOB_NAME
echo $SLURM_JOB_NODELIST


for i in `seq tmpnstart tmpnend`
do

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd /scratch/prichaew/ROOT/CMSSW_10_3_0/src
#cmsenv
eval `scramv1 runtime -sh`

cd /scratch/prichaew/models/rootoutputcc/ 

for p in `seq 0 9`
do 
inputFileName="/store/user/prichaew/slurmcc2/jb$i"
inputFileName+="/trees_hadrons_participants_partons_jb$i"
inputFileName+="_$p.root"

root -l -b >> runcc.sh <<EOF
  .L get_diff.C
  get_diff("$inputFileName")
  .q
EOF
echo $inputFileName
done

done


echo "Done!"

exit 0


