help:
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make \033[36m<target>\033[0m\n"} \
	/^[a-zA-Z0-9_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } \
	/^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) }' $(MAKEFILE_LIST)

rsbind: ##Compile Rust version
	cd rsver && \
	cargo run

zigcc: ##Compile C using Zig (GCC drop-in replacement)
	zig cc src/cryptlibc.c src/main.c -o main


zigbind: ##Compile Zig version
	cd zigver && \
	zig build-exe main.zig ../src/cryptlibc.c -I../src -lc && \
	./main

rstidy: ##Cleanup Rust target folder
	cd rsver && \
	cargo clean

zigtidy: ##Cleanup Zig files
	rm -rf .zig-cache && \
	cd zigver && \
	rm main main.o

zigtidydev: ##Remove Zig cache (.zig-cache)
	cd Dev && \
	rm -rf .zig-cache