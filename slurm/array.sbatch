#!/bin/bash
#SBATCH --job-name=mqc
#SBATCH --nodes=1
#SBATCH --ntasks=1
# Generic array job. Do not submit this file directly: use slurm/submit.sh, which passes the account,
# partition, time limit, array range and the variables below.
#   MQC_ROOT            project folder          MQC_TASKFILE  file with one command per line
#   MQC_CHUNK           commands per array task MQC_JOBS      how many of them run at the same time
#   MQC_TIME_LIMIT_SEC  the job's time limit in seconds
cd "$MQC_ROOT" || exit 1
source env.sh
# Searches stop and save a checkpoint 3 minutes before Slurm would kill the job.
export MQC_DEADLINE_EPOCH=$(( $(date +%s) + MQC_TIME_LIMIT_SEC - 180 ))
START=$(( (SLURM_ARRAY_TASK_ID - 1) * MQC_CHUNK + 1 ))
END=$(( SLURM_ARRAY_TASK_ID * MQC_CHUNK ))
echo "host $(hostname)  array task $SLURM_ARRAY_TASK_ID  lines $START-$END of $MQC_TASKFILE  started $(date)"
run_one() { echo ">>> $1"; bash -c "$1" || echo "!!! FAILED (exit $?): $1"; }
export -f run_one
sed -n "${START},${END}p" "$MQC_TASKFILE" | grep -v '^[[:space:]]*$' | xargs -d '\n' -P "${MQC_JOBS:-1}" -I{} bash -c 'run_one "$1"' _ {}
echo "finished $(date)"
