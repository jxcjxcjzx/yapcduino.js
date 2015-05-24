{
    "cflags": ["-Wall", "-O2", "--no-undefined"],
    "libraries": ["-lpthread"],
    "targets": [
        {
            "target_name" : "yapcduino",
            "sources" : [
                "./src/yapcduino.cpp",
                "./src/softpwm.c",
                "./src/arduino/wiring.c",
                "./src/arduino/wiring_digital.c",
                "./src/arduino/wiring_pulse.c"
            ]
        }
    ]
}
