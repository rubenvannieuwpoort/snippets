#define _GNU_SOURCE // needed for vmsplice
#include <fcntl.h> // vmsplice
#include <cpuid.h> //__get_cpuid
#include <stdio.h> // printf, fprintf
#include <stdint.h> // uint64_t
#include <stdlib.h> // malloc
#include <stdbool.h> // true
#include <fcntl.h> // fcntl
#include <sys/mman.h> // madvise

#define OFFSET 131072
#define MIN_PAGE_SIZE 2097152

unsigned int get_l2_cache_size()
{
	uint32_t eax, ebx, ecx, edx;

    if (!__get_cpuid(0x80000006, &eax, &ebx, &ecx, &edx))
    	return 0;
	
	return ((ecx >> 16) & 0xffff) * 1024;
}

void initialize(uint64_t *buffer, unsigned int *bufsize)
{
	// Set buffer size to half the size of the L2 cache size

	unsigned int l2_cache_size = get_l2_cache_size();
	if (!l2_cache_size)
	{
		fprintf(stderr, "Failed to get L2 cache size.\n");
		exit(1);
	}
	*bufsize = l2_cache_size / sizeof(uint64_t) / 2;

	// Set pipe size to the buffer size
	int pipe_size = fcntl(1, F_SETPIPE_SZ, *bufsize * sizeof(uint64_t));
	if (pipe_size != *bufsize * sizeof(uint64_t))
	{
		fprintf(stderr, "Failed to set pipe size\n");
		exit(1);
	}

	// Advise kernel to use huge pages
	int err = madvise(buffer, MIN_PAGE_SIZE, MADV_HUGEPAGE);
	if (err)
	{
		fprintf(stderr, "Call to madvise failed\n");
		exit(1);
	}
}

int main(void)
{
	uint64_t buffer[MIN_PAGE_SIZE / sizeof(uint64_t)] __attribute__((aligned (MIN_PAGE_SIZE)));
	struct iovec iovec_base;

	unsigned int bufsize;

	initialize(buffer, &bufsize);

	uint64_t count = 0;
	uint64_t offset = 0;

	while (true)
	{
		for (int i = 0; i < bufsize; i++)
			buffer[offset + i] = count++;

		iovec_base.iov_base = &buffer[offset];
		iovec_base.iov_len = bufsize * sizeof(uint64_t);

		offset ^= OFFSET;

		do
		{
			ssize_t written = vmsplice(1, &iovec_base, 1, 0);
			iovec_base.iov_base += written;
			iovec_base.iov_len -= written;
		} while (iovec_base.iov_len);
	}

	return 0;
}