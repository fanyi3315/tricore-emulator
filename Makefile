CC=clang
MAKE=make
CFLAGS=-Ideps/

all:
	$(MAKE) clean
	$(MAKE) lint
	$(MAKE) build

clean:
	rm -rf build

lint:
	clang-format -i *.c

build:
	mkdir build
	$(CC) $(CFLAGS) deps/parson/*.c *.c -o build/tricore-emulator
