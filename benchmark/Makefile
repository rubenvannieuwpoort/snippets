BENCHMARKS := $(dir $(wildcard benchmarks/*/))

.PHONY: build clean benchmark.csv

benchmark.csv: build
	./benchmark copy128_stream copy256_4 memcpy repmovsb > benchmark.csv

build:
	$(MAKE) -C benchmarks;
	for dir in $(BENCHMARKS); do \
	  $(MAKE) -C $$dir; \
	done

clean:
	make clean -C benchmarks
	for dir in $(BENCHMARKS); do \
	  $(MAKE) clean -C $$dir; \
	done
	rm -rf benchmark.csv

