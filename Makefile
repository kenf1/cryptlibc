#compile rust
rsbind:
	cd rsver && \
	cargo run

#gcc drop-in replacement (compiles C -> executable)
zigcc:
	zig cc src/cryptlibc.c src/main.c -o main

#zig build system (compiles Zig -> executable)
zigbind:
	cd zigver && \
	zig build-exe main.zig ../src/cryptlibc.c -I../src -lc && \
	./main

#cleanup rust files
rstidy:
	cd rsver && \
	cargo clean

#cleanup zig files
zigtidy:
	rm -rf .zig-cache && \
	cd zigver && \
	rm main main.o

zigtidydev:
	cd Dev && rm -rf .zig-cache