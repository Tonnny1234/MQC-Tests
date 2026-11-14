# env.sh - settings loaded by setup.sh and by every Slurm job. Edit this file once; nothing else needs editing.

# 1) Your Slurm account and default partition (from your access email; confirm with: sinfo -s)
export MQC_ACCOUNT="cs-sariel"
export MQC_PARTITION="cs"

# 2) Software modules. Find the exact names with:  module avail gcc ; module avail java
#    then replace the two names below, e.g.  module load gcc/13.3.0  and  module load java/21
if ! type module >/dev/null 2>&1; then source /etc/profile >/dev/null 2>&1 || true; fi
if type module >/dev/null 2>&1; then
    module load gcc/12.4.0  >/dev/null 2>&1 || true
    module load java/23 >/dev/null 2>&1 || module load openjdk >/dev/null 2>&1 || true
fi

# 3) Optional overrides (defaults point into ext/, which setup.sh fills)
# export ASTRAL3_JAR=/path/to/astral.5.7.8.jar
# export ASTRAL4_BIN=/path/to/astral4
# export JAVA=/path/to/java

export OMP_NUM_THREADS="${SLURM_CPUS_PER_TASK:-1}"
