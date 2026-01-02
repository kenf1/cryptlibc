package main //must have dynamic lib & header file in same dir

/*
#cgo linux LDFLAGS: -L. -lcryptlibc
#cgo darwin LDFLAGS: -L. -lcryptlibc
#cgo windows LDFLAGS: -L. libcryptlibc.a

// CGO generate C.CryptConfig
typedef struct {
  const char *version;
  const char *inputstr;
  const char *refstr;
  int offset;
} CryptConfig;

#include "cryptlibc.h"
#include <stdlib.h>
*/
import "C"
import (
	"fmt"
	"unsafe"
)

func main() {
	refstr := C.CString("abcdefghijklmnopqrstuvwxyz")
	defer C.free(unsafe.Pointer(refstr))

	// Encrypt
	encryptConfig := C.CryptConfig{
		version:  C.CString("encrypt"),
		inputstr: C.CString("Hello World!"),
		refstr:   refstr,
		offset:   13,
	}
	defer C.free(unsafe.Pointer(encryptConfig.version))
	defer C.free(unsafe.Pointer(encryptConfig.inputstr))

	encryptResult := C.cryptlogic(&encryptConfig)
	if encryptResult == nil {
		fmt.Println("Encrypt failed")
		return
	}
	defer C.free(unsafe.Pointer(encryptResult))
	fmt.Printf("Encrypt(13): %s\n", C.GoString(encryptResult))

	//rebuild
	decryptConfig := C.CryptConfig{
		version:  C.CString("decrypt"),
		inputstr: encryptResult, // Reuse encrypted result
		refstr:   refstr,
		offset:   13,
	}
	defer C.free(unsafe.Pointer(decryptConfig.version))

	decryptResult := C.cryptlogic(&decryptConfig)
	if decryptResult == nil {
		fmt.Println("Decrypt failed")
		return
	}
	defer C.free(unsafe.Pointer(decryptResult))

	fmt.Printf("Decrypt(13): %s\n", C.GoString(decryptResult))
}
