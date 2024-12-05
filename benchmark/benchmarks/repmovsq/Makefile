run: obj/run.o ../driver.o
	$(CC) $(CFLAGS) $^ -o $@

obj/run.o: run.s
	mkdir -p obj
	nasm -f elf64 $^ -o $@

clean:
	rm -rf run obj/
