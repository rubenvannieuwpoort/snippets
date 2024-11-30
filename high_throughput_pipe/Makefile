CC = clang
CFLAGS = -O3

high_throughput_pipe: high_throughput_pipe.c
	$(CC) $^ $(CFLAGS) -o $@

.PHONY: clean

clean:
	rm -rf high_throughput_pipe
