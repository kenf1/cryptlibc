.PHONY: rsbind zigcc dlib_linux dlib_mac dlib_win gobind gcctest zigtest guic clean

rsbind: #Compile Rust version
	cd rsver && cargo run

zigcc: #Compile C using Zig (GCC drop-in replacement)
	zig cc src/cryptlibc.c src/main.c -o src/main

dlib_linux: #Compile as dynamic lib (linux)
	cd src && gcc -shared -o libcryptlibc.so cryptlibc.c -fPIC

dlib_mac: #Compile as dynamic lib (mac)
	cd src && clang -dynamiclib -o libcryptlibc.dylib cryptlibc.c -arch arm64 -arch x86_64

dlib_win: #Compile as dynamic lib (windows)
	gcc -shared -o cryptlibc.dll cryptlibc.c -Wl,--out-implib,libcryptlibc.a

gobind: #Run Go version
	cp src/libcryptlibc.* gover/libcryptlibc.* && cd gover && go run .

rstidy: #Cleanup Rust target folder
	cd rsver && cargo clean

gcctest: #Run test with gcc
	cd src && \
	gcc -o test_cryptlibc test_cryptlibc.c cryptlibc.c && \
	./test_cryptlibc

guic: #Compile gui
	cd vendor/raylib/src && make PLATFORM=PLATFORM_DESKTOP

	gcc cryptlib_gui/clgui.c -Ivendor/raylib/src -Ivendor/raygui/src -I../src \
    -Lvendor/raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o main

clean: #Clean all
	rm -rf ./src/test_cryptlibc ./main
	cd rsver && cargo clean