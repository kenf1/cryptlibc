package main //must have dynamic lib & header file in same dir

/*
#cgo linux LDFLAGS: -L. -lcryptlibc
#cgo darwin LDFLAGS: -L. -lcryptlibc

#include "cryptlibc.h"
#include <stdlib.h>
*/
import "C"
import (
	"fmt"
	"unsafe"
)

func main() {
	config := C.CryptConfig{
		version:  C.CString("encrypt"),
		inputstr: C.CString("Hello World!"),
		refstr:   C.CString("abcdefghijklmnopqrstuvwxyz"),
		offset:   13,
	}

	result := C.cryptlogic(&config)
	if result == nil {
		fmt.Println("Error: cryptlogic failed")
		return
	}
	defer C.free(unsafe.Pointer(result))

	fmt.Printf("Result: %s\n", C.GoString(result))
}
