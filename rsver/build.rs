use cc::Build;

fn main() {
    Build::new().file("../src/cryptlibc.c").compile("cryptlibc");
}
