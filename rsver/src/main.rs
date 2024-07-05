use std::{
    ffi::{c_char,c_int,CStr,CString},
    ptr,
    env,
};
use dotenv::dotenv;

extern "C"{
    fn cryptlogic(
        inputstr: *const c_char,
        refstr: *const c_char,
        offset: c_int
    ) -> *mut c_char;
}

fn main(){
    //import KEY from .env
    dotenv().ok();
    let key = env::var("KEY")
        .unwrap();

    let inputstr = CString::new("Hello from C!").unwrap();
    let refstr = CString::new(& *key).unwrap(); //dereference
    let offset = 2;

    unsafe{
        //pass args into C function (encrypt only)
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

            //drop pointer safely (after use)
            let _ = CString::from_raw(result_ptr);
        }else{
            println!("Error");
        }
    }
}