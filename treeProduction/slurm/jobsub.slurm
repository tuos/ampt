#!/bin/bash
#SBATCH --nodes=1
#SBATCH --mem-per-cpu=1G
#SBATCH --time=0-20:00:00

echo $SLURM_JOB_ID
echo $SLURM_JOB_NAME
echo $SLURM_JOB_NODELIST

cd /scratch/tuos/models/ampt/slurm/v26/ppb01/jb0

module load PGI

bash exec.sh

echo "Done!"

exit 0


