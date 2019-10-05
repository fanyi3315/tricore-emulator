CC=clang
CFLAGS=-Ideps/

all:
	mkdir build
	$(CC) $(CFLAGS) deps/parson/*.c *.c -o build/tricore-emulator

clean:
	rm -rf build

lint:
	clang-format -i *.c
