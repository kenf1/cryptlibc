use std::ffi::CString;

mod config;

fn main() {
    match config::load_env("KEY") {
        Ok(key) => {
            let key_c = CString::new(key).expect("KEY contains interior NUL");
            let offset = 13; //ROT13 :)

            // encrypt
            let version_enc = CString::new("encrypt").unwrap();
            let input_enc = CString::new("Hello from C!").unwrap();
            config::logic_wrapper(&version_enc, &input_enc, &key_c, offset);

            // decrypt
            let version_dec = CString::new("decrypt").unwrap();
            let input_dec = CString::new("Uryyb sebz P!").unwrap();
            config::logic_wrapper(&version_dec, &input_dec, &key_c, offset);
        }
        Err(_) => {
            eprintln!("Unable to import specified var from .env file (KEY)");
        }
    }
}
