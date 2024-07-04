use std::{
    ffi::{c_char,c_int,CStr,CString},
    ptr,
};

extern "C"{
    fn cryptlogic(
        inputstr: *const c_char,
        refstr: *const c_char,
        offset: c_int
    ) -> *mut c_char;
}

fn main(){
    let inputstr = CString::new("Hello from C!").unwrap();
    let refstr = CString::new("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890").unwrap();
    let offset = 2;

    unsafe{
        //pass args into C function
        let result_ptr = cryptlogic(
            inputstr.as_ptr(),
            refstr.as_ptr(),
            offset
        );

        //convert pointer -> Rust string
        if result_ptr != ptr::null_mut(){
            let res = CStr::from_ptr(result_ptr)
                .to_string_lossy()
                .into_owned();
            println!("Encrypted result: {}",res);
        }else{
            println!("Error");
        }
    }
}