C:\Work\openocd-0.10.0\bin\openocd.exe -d2 -f C:\Work\openocd-0.10.0\share\openocd\scripts\interface\stlink.cfg -f C:\Work\openocd-0.10.0\share\openocd\scripts\target\nrf52.cfg

telnet 127.0.0.1  4444

reset halt

nrf5 mass_erase

program C:/Work/NordicSemiconductor/nRF5_SDK_15.2.0/components/softdevice/s132/hex/s132_nrf52_6.1.0_softdevice.hex verify

program C:/Work/MYDEV/nrf52/myblinky/_build\nrf52832_xxaa.hex/ verify

reset