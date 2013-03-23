#PBS -S /bin/bash
#PBS -N test3
#PBS -o test3.stdout
#PBS -e test3.stderr
#PBS -q qwork@mp2
#PBS -l nodes=2:ppn=1
#PBS -l walltime=00:00:01:00

cd $PBS_O_WORKDIR

module load openmpi_gcc64/1.6.4

mpiexec -n $((2*24)) ./Programme1-Iprobe
