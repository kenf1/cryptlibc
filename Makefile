rsbind:
	cd rsver && \
	cargo run

tidy:
	cd rsver && \
	cargo clean

zigcc:
	zig cc src/cryptlibc.c src/main.c -o main