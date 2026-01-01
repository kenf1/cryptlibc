use dotenvy::dotenv;
use std::{
    env::{self, VarError},
    ffi::{CStr, CString, c_char, c_int},
};

//copy from cryptlibc.h
#[repr(C)]
pub struct CryptConfig {
    version: *const c_char,  // "encrypt" or "decrypt"
    inputstr: *const c_char, // input string to process
    refstr: *const c_char,   // reference characters (alphabet, symbols, etc.)
    offset: c_int,           // shift amount
}

unsafe extern "C" {
    fn cryptlogic(config: *const CryptConfig) -> *mut c_char;
}

pub fn load_env(env_var: &str) -> Result<String, VarError> {
    dotenv().ok();
    env::var(env_var)
}

pub fn logic_wrapper(
    version: &CString,
    inputstr: &CString,
    refstr: &CString,
    offset: i32,
) {
    //build C-side config struct that matches cryptlibc.h
    let cfg = CryptConfig {
        version: version.as_ptr(),
        inputstr: inputstr.as_ptr(),
        refstr: refstr.as_ptr(),
        offset: offset as c_int,
    };

    unsafe {
        let result_ptr = cryptlogic(&cfg as *const CryptConfig);
        if !result_ptr.is_null() {
            let res = CStr::from_ptr(result_ptr).to_string_lossy().into_owned();
            println!("{version:?} result: {res}");

            // cryptlogic returned memory from malloc, free via CString::from_raw
            let _ = CString::from_raw(result_ptr);
        } else {
            eprintln!("Error: cryptlogic returned NULL");
        }
    }
}
