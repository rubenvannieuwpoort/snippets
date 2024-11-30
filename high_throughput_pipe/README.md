# High-throughput pipe

I saw https://codegolf.stackexchange.com/a/236630 about a week ago, and was very interested. The author of that answer gave an assembly program that uses some black magic to solve the famous "fizzbuzz" problem with an amazing throughput (someone reported 56GiB/s, I "only" get around 24GiB on my Ryzen 5 1600).

I read the assembly code in that answer. Most of the complexity is specific to the fizzbuzz problem, the part that sets up the high-throughput pipe is actually quite simple. So, I decided to extract that part to a C program for demonstration purposes.

Note that the performance is somewhat more variable. I think this is due to the exact instructions that the compiler generates. If you know a way to get more consistent performance, I'd love to know.

Word of caution: Storing the output of this program to a file might get you into trouble. I haven't tried it, but I suspect it might crash your machine.


## Compilation

```
git clone https://github.com/rubenvannieuwpoort/high_throughput_pipe
cd high_throughput_pipe
make
```

To run, use
```
./high_throughput_pipe | pv > /dev/null
```

or
```
taskset 1 high_throughput_pipe | taskset 2 pv > /dev/null
```

On my machine, the first one is slightly faster, but it is expected that the latter will run slightly faster on many performant modern machines.


## Contents of the program

The program works as follows:
  1. Set up a buffer
  2. Write half of the buffer
  3. Output the finished half of the buffer to stdout with the vmsplice system call
  4. Repeat from step 2, using the other half of the buffer

The idea now is to let the reading and writing process use the same memory *in the L2 cache*. (L2 cache is the fastest memory that can be shared between cores, on most architectures; L1 is faster but core-specific). This requires querying the L2 cache size using the `cpuid` instruction, and pinning the processes writing and reading from the pipe to a specific core (using `taskset`).

All in all, all the tricks used are:
  1. Use the vmsplice system call which lets programs use shared memory as a stream
  2. Use buffers of half the L2 cache size so that the shared memory fits in L2 cache
  3. Set the pipe size to half the L2 cache size
  4. Use huge pages to simplify physical address lookup


## Notes

On my machine, I get a consistent speed of 24GiB/s when I compile with `-O3` on `clang`. For some reason I get only 20GiB when I compile with `gcc`.

On your machine, it might help to add (some subset of) `-march=native -o test -fno-pie -no-pie -fno-plt`. This did not seem to increase throughput on my machine.
