#!/usr/local/bin/node
"use strict";

var lstr = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"; // 100 b
var sstr = "."; // 1 b

var N = 100 * 1000; // number of loop
var M = 1000;       // number of concatination

function doit(p, name) {
    var t0 = Date.now();
    for(var i = 0; i < N; i++) {
        var s = "";
        for(var j = 0; j < M; j++) {
            s += p;
        }
    }
    process.stderr.write(s); // force join

    var t1 = Date.now();
    console.log(name + ": " + ((t1 - t0) / 1000));
}

var i;
for(i = 0; i < 2; i++) {
    doit(lstr, "long");
}

for(i = 0; i < 2; i++) {
    doit(sstr, "short");
}

