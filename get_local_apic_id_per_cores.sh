#!/usr/bin/bash

if [ $(id -u) -ne 0 ]; then
  echo "This script must be run with root privileges"
  exit 1
fi

echo "--- lscpu -e ---"
lscpu -e

echo "--- (TACC) 0x1 leaf version ---"
echo -e "cpuX\tLocal APIC ID\tCORE ID"
CPUMAX=$(nproc)
for i in `seq 0 1 $((CPUMAX-1))` ; do taskset -c $i ./cpuid_by_tacc ; done
echo "--- (Intel Spec) 0xB leaf version ---"
echo -e "cpuX\tx2APIC ID\tSMT_ID\tCore_ID\tPkg_ID "
for i in `seq 0 1 $((CPUMAX-1))` ; do taskset -c $i ./cpuid_by_specification ; done

exit 0

