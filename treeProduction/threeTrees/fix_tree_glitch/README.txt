Code developed by Everett and Shengquan in Summer 2020

Running the submit.sh will create 10 "good_files_log.slurm" and submit their slurm jobs.
Each of the jobs will create a "run.sh" which consists of a single-lined list of the non-defective root output trees.
You will need to manually enter "hadd <outputfiledestination> " into the beginning of each run.sh.
You then need to run haddsub.sh which will create 10 "haddjob.slurm" files and submit their jobs to slurm. 
These jobs will create a total of 10 root output files.
Then submit "finaljob.slurm" which will combine these 10 large root output file into one final root file.
