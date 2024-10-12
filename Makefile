CC = gcc

CFLAGS = -Wall -Wextra -pedantic

TACC = cpuid_by_tacc
SPEC = cpuid_by_specification
TARGETS = $(TACC) $(SPEC)

all: $(TARGETS)

$(TACC): $(TACC).c
	$(CC) $(CFLAGS) -o $@ $<

$(SPEC): $(SPEC).c
	$(CC) $(CFLAGS) -o $@ $<

run:
	sudo ./get_local_apic_id_per_cores.sh

clean:
	rm -f $(TARGETS)

.PHONY: all run clean

