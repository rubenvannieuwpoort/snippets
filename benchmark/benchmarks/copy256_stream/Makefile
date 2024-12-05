run: obj/run.o ../driver.o
	$(CC) $(CFLAGS) -mavx2 $^ -o $@

obj/run.o: run.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -O3 -mavx2 -o $@

clean:
	rm -rf run obj/
