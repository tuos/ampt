#!/bin/bash
#SBATCH --nodes=1
#SBATCH --mem-per-cpu=2G
#SBATCH --time=0-20:00:00

echo $SLURM_JOB_ID
echo $SLURM_JOB_NAME
echo $SLURM_JOB_NODELIST

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd /home/panomis/CMSSW_10_3_0/src
#cmsenv
eval `scramv1 runtime -sh`


cd /scratch/sofiapanomitros/ampt/Ampt-v1.26t9b-v2.26t9b/slurmJobsBatch04/produceTrees/jb0


root -l ROOT_Tree.c

echo "Done!"

exit 0


