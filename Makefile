.PHONY: rsbind zigcc zigbind rstidy zigtidy zigtidydev allbind alltidy \
	gcctest zigtest guic clean

rsbind: #Compile Rust version
	cd rsver && cargo run

zigcc: #Compile C using Zig (GCC drop-in replacement)
	zig cc src/cryptlibc.c src/main.c -o src/main

zigbind: #Compile Zig version
	cd zigver && \
	zig build-exe main.zig ../src/cryptlibc.c -I../src -lc && \
	./main

rstidy: #Cleanup Rust target folder
	cd rsver && cargo clean

zigtidy: #Cleanup Zig files
	rm -rf .zig-cache && \
	cd zigver && \
	rm main main.o

zigtidydev: #Remove Zig cache (.zig-cache)
	cd Dev && rm -rf .zig-cache

allbind: rsbind zigbind #Compile both Rust & Zig versions

alltidy: rstidy zigtidy zigtidydev #Cleanup all

gcctest: #Run test with gcc
	cd src && \
	gcc -o test_cryptlibc test_cryptlibc.c cryptlibc.c && \
	./test_cryptlibc

zigtest: #Run test with zig
	cd src && \
	zig cc -o test_cryptlibc test_cryptlibc.c cryptlibc.c && \
	./test_cryptlibc

guic: #Compile gui
	cd vendor/raylib/src && make PLATFORM=PLATFORM_DESKTOP

	gcc cryptlib_gui/clgui.c -Ivendor/raylib/src \
	-Ivendor/raygui/src -Lvendor/raylib/src \
	-lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
	-o main

clean: #Clean all
	rm -rf ./src/test_cryptlibc ./main