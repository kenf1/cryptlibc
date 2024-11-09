use std::env::VarError;
use std::{ptr,env};
use std::ffi::{c_char,c_int,CStr,CString};
use dotenv::dotenv;

extern "C"{
    fn cryptlogic(
        version: *const c_char,
        inputstr: *const c_char,
        refstr: *const c_char,
        offset: c_int,
    ) -> *mut c_char;
}

//import env var
fn load_env(env_var: String) -> Result<String,VarError>{
    dotenv().ok();
    env::var(env_var)
}

fn logic_wrapper(
    version: CString,
    inputstr: CString,
    refstr: CString,
    offset: i32,
){
    unsafe{
        //pass args into C function
        let result_ptr = cryptlogic(
            version.as_ptr(),
            inputstr.as_ptr(),
            refstr.as_ptr(),
            offset
        );

        //convert pointer -> Rust string
        if result_ptr != ptr::null_mut(){
            let res = CStr::from_ptr(result_ptr)
                .to_string_lossy()
                .into_owned();
            println!("{:?} result: {}",version,res);

            //drop pointer safely (after use)
            let _ = CString::from_raw(result_ptr);
        }else{
            println!("Error");
        }
    }
}

fn main(){
    match load_env("KEY".to_string()){
        Ok(key) => {
            //encrypt
            logic_wrapper(
                CString::new("encrypt").unwrap(),
                CString::new("Hello from C!").unwrap(),
                CString::new(& *key).unwrap(),
                2
            );

            //decrypt
            logic_wrapper(
                CString::new("decrypt").unwrap(),
                CString::new("Fcjjm dpmk A!").unwrap(),
                CString::new(& *key).unwrap(),
                2
            );
        },
        Err(_) => {
            println!("Unable to import specified var from .env file");
        }
    }
}