CXX = g++
ARCH = avx2

VTUNE_HOME = /opt/intel/oneapi/vtune/2021.5.0

INPUT_DIR = ~/input-datasets

.PHONY: clean

all: bm2 mm2

bm2: 
	cd tools/bwa-mem2; $(MAKE) CXX=$(CXX) arch=$(ARCH) VTUNE_HOME=$(VTUNE_HOME)
	cd kernels/fmi; $(MAKE) CXX=$(CXX) arch=$(ARCH) VTUNE_HOME=$(VTUNE_HOME)
	cd kernels/bsw; $(MAKE) CXX=$(CXX) arch=$(ARCH) VTUNE_HOME=$(VTUNE_HOME)

mm2:
	cd tools/minimap2; $(MAKE)
	cd kernels/chain; $(MAKE) CXX=$(CXX) arch=$(ARCH) VTUNE_HOME=$(VTUNE_HOME)

run_fmi:
	./kernels/fmi/fmi $(INPUT_DIR)/fmi/broad $(INPUT_DIR)/fmi/large/SRR7733443_10m_1.fastq 512 19 1

run_bsw:
	./kernels/bsw/bsw -pairs $(INPUT_DIR)/bsw/large/bandedSWA_SRR7733443_1m_input.txt -t 1 -b 512

run_chain:
	./kernels/chain/chain -i $(INPUT_DIR)/chain/large/c_elegans_40x.10k.in -o $(INPUT_DIR)/chain/large/c_elegans_40x.10k.out

clean:
	cd tools/bwa-mem2; $(MAKE) clean
	cd kernels/fmi; $(MAKE) clean
	cd kernels/bsw; $(MAKE) clean
	cd tools/minimap2; $(MAKE)
	cd kernels/chain; $(MAKE) clean
