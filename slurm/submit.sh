#!/bin/bash
# submit.sh - submit a task file (one command per line) as a Slurm job array.
#
#   bash slurm/submit.sh tasks/smoke.phase1.txt                       # defaults from env.sh
#   bash slurm/submit.sh tasks/stageB.phase2.txt --partition secondary --time 03:30:00 --repeat 3
#
# Options
#   --partition P      queue (default: MQC_PARTITION in env.sh)
#   --account A        account (default: MQC_ACCOUNT in env.sh)
#   --time T           time limit per array task, HH:MM:SS or D-HH:MM:SS (default 01:00:00)
#   --concurrent N     at most N array tasks running at once (default 64)
#   --cpus C           cores per array task (default 1)
#   --mem-per-cpu M    memory per core (default 4G)
#   --chunk K          commands per array task (default 1; raised automatically to keep the array under 900)
#   --jobs J           commands of one chunk that run at the same time (default: same as --cpus)
#   --after JOBID      start only after that job has ended
#   --repeat R         submit R passes, each starting when the previous one ends; unfinished searches
#                      resume from their checkpoint, finished work is skipped (default 1)
#   --dry-run          print the sbatch command instead of running it
set -e
cd "$(dirname "$0")/.."
source env.sh
[ $# -ge 1 ] || { sed -n '2,20p' "$0"; exit 1; }
TASKFILE=$1; shift
PARTITION=$MQC_PARTITION; ACCOUNT=$MQC_ACCOUNT; TIME=01:00:00; CONC=64; CPUS=1; MEM=4G; CHUNK=1; JOBS=""; AFTER=""; REPEAT=1; DRY=0
while [ $# -gt 0 ]; do
    case $1 in
        --partition) PARTITION=$2; shift 2;; --account) ACCOUNT=$2; shift 2;; --time) TIME=$2; shift 2;;
        --concurrent) CONC=$2; shift 2;; --cpus) CPUS=$2; shift 2;; --mem-per-cpu) MEM=$2; shift 2;;
        --chunk) CHUNK=$2; shift 2;; --jobs) JOBS=$2; shift 2;; --after) AFTER=$2; shift 2;;
        --repeat) REPEAT=$2; shift 2;; --dry-run) DRY=1; shift;;
        *) echo "unknown option $1"; exit 1;;
    esac
done
[ -f "$TASKFILE" ] || { echo "task file not found: $TASKFILE"; exit 1; }
[ -x bin/mqc ] || { echo "bin/mqc is missing: run 'bash setup.sh' first"; exit 1; }
N=$(grep -c -v '^[[:space:]]*$' "$TASKFILE" || true)
[ "$N" -gt 0 ] || { echo "no tasks in $TASKFILE"; exit 1; }
[ -n "$JOBS" ] || JOBS=$CPUS
while [ $(( (N + CHUNK - 1) / CHUNK )) -gt 900 ]; do CHUNK=$(( CHUNK + 1 )); done     # stay under the 1,000-job limit
ARR=$(( (N + CHUNK - 1) / CHUNK ))
# time limit in seconds, from HH:MM:SS or D-HH:MM:SS
D=0; HMS=$TIME; case $TIME in *-*) D=${TIME%%-*}; HMS=${TIME#*-};; esac
IFS=: read -r H M S <<< "$HMS"
SEC=$(( 10#$D * 86400 + 10#$H * 3600 + 10#${M:-0} * 60 + 10#${S:-0} ))
NAME=$(basename "$TASKFILE" .txt)
mkdir -p "logs/$NAME"
for PASS in $(seq 1 "$REPEAT"); do
    CMD=(sbatch --parsable --account="$ACCOUNT" --partition="$PARTITION" --time="$TIME" --cpus-per-task="$CPUS"
         --mem-per-cpu="$MEM" --array="1-${ARR}%${CONC}" --job-name="$NAME" --output="logs/$NAME/%A_%a.out"
         --export="ALL,MQC_ROOT=$PWD,MQC_TASKFILE=$TASKFILE,MQC_CHUNK=$CHUNK,MQC_JOBS=$JOBS,MQC_TIME_LIMIT_SEC=$SEC")
    [ -n "$AFTER" ] && CMD+=(--dependency="afterany:$AFTER")
    CMD+=(slurm/array.sbatch)
    if [ "$DRY" = 1 ]; then echo "${CMD[*]}"; AFTER="<job id of pass $PASS>"; continue; fi
    JOB=$("${CMD[@]}"); JOB=${JOB%%;*}
    echo "pass $PASS: submitted job $JOB  ($N tasks in $ARR array tasks, partition $PARTITION, time $TIME)"
    AFTER=$JOB
done
[ "$DRY" = 1 ] || echo "watch with: squeue -u \$USER     progress: python3 tools/progress.py $TASKFILE     logs: logs/$NAME/"
