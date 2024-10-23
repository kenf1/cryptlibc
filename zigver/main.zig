//import req c lib
const std = @import("std");
const c = @cImport({
    @cInclude("string.h");
    @cInclude("ctype.h");
    @cInclude("stdlib.h");
});

//c ffi
extern fn cryptlogic(version: [*c]const u8, inputstr: [*c]const u8, refstr: [*c]const u8, offset: c_int) [*c]u8;

pub fn main() !void {
    const refstr = "abcdefghijklmnopqrstuvwxyz";
    const offset: c_int = 1;

    //encrypt (expect zab)
    const res0 = cryptlogic("encrypt", "abc", refstr, offset);

    //decrypt (expect abc)
    const res1 = cryptlogic("decrypt", "zab", refstr, offset);

    //handle error
    if (res0 == null or res1 == null) {
        std.debug.print("Error: Memory allocation failed\n", .{});
        return;
    }

    //free memory once cryptlogic completes
    //encrypt + decrypt
    defer {
        c.free(res0);
        c.free(res1);
    }

    std.debug.print("Result:\n{s}\n{s}\n", .{ res0, res1 });
}
