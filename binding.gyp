{
    "libraries": ["-lpthread"],
    "targets": [
        {
            "target_name" : "yapcduino",
            "include_dirs" : [
                "<!(node -e \"require('nan')\" 2> /dev/null)",
                "<!(node -e \"require('cbind')('src/yapcduino.nid')\" 2> /dev/null)"
            ],
            "sources" : [
                "./src/yapcduino.cpp",
                "./src/softpwm.c",
                "./src/arduino/wiring.c",
                "./src/arduino/wiring_digital.c",
                "./src/arduino/wiring_pulse.c",
                "./src/arduino/platform.c"
            ],
            "cflags": ["-w", "-O2", "-std=c++11"],
            "cflags_cc!": [ "-fno-exceptions" ],
        }
    ]
}
