#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd /scratch/tuos/models/reu2020/ROOT/CMSSW_10_3_0/src
#cmsenv
eval `scramv1 runtime -sh`

cd /scratch/tuos/models/reu2020/txt2root/threeTrees

filenames="pcFileList0.txt"

rm run.log

while read line;
do

  echo $line
  #root -l extractEntries.C
  root -l -b >> run.log <<EOF
  .L extractEntries.C
  extractEntries("$line")
  .q
EOF

done<$filenames


