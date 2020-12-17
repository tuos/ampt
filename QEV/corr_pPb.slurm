#!/bin/bash
#SBATCH --nodes=1
#SBATCH --mem-per-cpu=1G
#SBATCH --time=0-4:30:00

echo $SLURM_JOB_ID
echo $SLURM_JOB_NAME
echo $SLURM_JOB_NODELIST



source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd /scratch/prichaew/ROOT/CMSSW_10_3_0/src
#cmsenv
eval `scramv1 runtime -sh`

cd /scratch/prichaew/fall2020/analysis/correlation_vs_nmult

root -l macro_correlation_vs_nmult.C


echo "Done!"

exit 0


