{
    "cflags": ["-lpthread", "-Wall", "-O2"],
    "targets": [
        {
            "target_name" : "yapcduino",
            "sources" : [
                "./src/yapcduino.cc",
                "./src/softpwm.c",
                "./src/arduino/wiring.c",
                "./src/arduino/wiring_digital.c",
                "./src/arduino/wiring_pulse.c"
            ]
        }
    ]
}
