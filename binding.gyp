{
    "cflags": ["-Wall", "-O2", "--no-undefined"],
    "libraries": ["-lpthread"],
    "targets": [
        {
            "target_name" : "yapcduino",
            "sources" : [
                "./src/softpwm.c",
                "./src/yapcduino.cpp",
                "./src/arduino/wiring.c",
                "./src/arduino/wiring_digital.c",
                "./src/arduino/wiring_pulse.c"
            ]
        }
    ]
}
