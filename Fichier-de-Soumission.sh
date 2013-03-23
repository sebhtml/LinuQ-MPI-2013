#PBS -S /bin/bash
#PBS -N test
#PBS -o test.stdout
#PBS -e test.stderr
#PBS -q qwork@mp2
#PBS -l nodes=2:ppn=1
#PBS -l walltime=00:00:01:00

cd $PBS_O_WORKDIR

module load openmpi_gcc64/1.6.4

mpiexec -n 48 ./Programme1-Iprobe
