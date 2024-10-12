# Overview

* Check information about Intel `x86_64` CPU Core Numbering
* `Local APIC ID/SMT_ID/Core_ID/Pkg_ID`s

> [!WARNING]
> This code is experimental. Therefore, there may be errors in other generations of CPUs.

# TODO

* [ ] Support new specification
  * Intel update official document. [see reference](./Reference)
  * doc number 329176-002 rev 2.2 2023-04
  * [Link](https://cdrdv2-public.intel.com/775917/intel-64-architecture-processor-topology-enumeration.pdf)

# How to check

```bash
$ make
$ make run
```

# Examle result

* Intel(R) Pentium(R) G4560 2core 4thread
  * 7th gen Kaby Lake (2016-08-30 Launch)

```text
sudo ./get_local_apic_id_per_cores.sh
--- lscpu -e ---
CPU NODE SOCKET CORE L1d:L1i:L2:L3 ONLINE    MAXMHZ   MINMHZ      MHZ
  0    0      0    0 0:0:0:0          yes 3500.0000 800.0000 3199.986
  1    0      0    1 1:1:1:0          yes 3500.0000 800.0000 3199.990
  2    0      0    0 0:0:0:0          yes 3500.0000 800.0000 3200.013
  3    0      0    1 1:1:1:0          yes 3500.0000 800.0000 1528.036
--- 0x1 leaf version ---
cpuX	Local APIC ID	CORE ID
0	00100800	00
1	02100800	01
2	01100800	00
3	03100800	01
--- 0xB leaf version ---
cpuX	x2APIC ID	SMT_ID	Core_ID	Pkg_ID 
0	0		0	0	0
1	2		0	1	0
2	1		1	0	0
3	3		1	1	0
```

# Reference

* [TACC](https://www.researchgate.net/publication/348937616_Observations_on_Core_Numbering_and_Core_ID's_in_Intel_Processors)
  * See -> 5. About the "core id"
    * get core id from `CPUID.1:EBX[29:25]`
* [Intel 64 Architecture Processor Topology Enumeration](https://cdrdv2-public.intel.com/759067/intel-64-architecture-processor-topology-enumeration.pdf)
  * See -> 1.5.1 Sub ID Extraction Parameters for x2APIC ID
    * get `SMT_ID/Core_ID/Pkg_ID` from `CPUID.B[EBX=0,1]`
  * Document number 329176-001
  * Revision number 1.1
  * Date 2018-01

# LICENSE

[MIT](./LICENSE)

---

