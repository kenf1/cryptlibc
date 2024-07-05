//import req c lib
const std = @import("std");
const c = @cImport({
    @cInclude("string.h");
    @cInclude("ctype.h");
    @cInclude("stdlib.h");
});

//c ffi
extern fn cryptlogic(inputstr: [*c]const u8, refstr: [*c]const u8, offset: c_int) [*c]u8;

pub fn main() !void {
    const refstr = "abcdefghijklmnopqrstuvwxyz";
    const offset: c_int = 1;
    const inputstr = "abc";

    //encrypt
    const res = cryptlogic(inputstr, refstr, offset);

    //handle error
    if (res == null) {
        std.debug.print("Error: Memory allocation failed\n", .{});
        return;
    }

    //free memory once cryptlogic completes
    defer c.free(res);

    std.debug.print("Result: {s}\n", .{res});
}
