#!/usr/bin/env python3

import serial
import os

usb_dev = {'port': '/dev/ttyUSB1'}


# Print color
color_end = "\033[0m"
color_black = "\033[0;30m"
color_blackb = "\033[1;30m"
color_white = "\033[0;37m"
color_whiteb = "\033[1;37m"
color_red = "\033[0;31m"
color_redb = "\033[1;31m"
color_green = "\033[0;32m"
color_greenb = "\033[1;32m"
color_yellow = "\033[0;33m"
color_yellowb = "\033[1;33m"
color_blue = "\033[0;34m"
color_blueb = "\033[1;34m"
color_purple = "\033[0;35m"
color_purpleb = "\033[1;35m"
color_lightblue = "\033[0;36m"
color_lightblueb = "\033[1;36m"


def check_usb_port():
    ttyusb = False

    for i in range(30):
        if not os.system("ls /dev/ttyUSB%d > /dev/null" % i):
            usb_dev['port'] = '/dev/ttyUSB' + str(i)
            print(usb_dev['port'])
            ttyusb = True
            break

    if not ttyusb:
        print("%sFind USB failed.%s" % (color_redb, color_end))
        return False

    return True


if __name__ == '__main__':
    # Check USB Port
    if not check_usb_port():
        input("%s请按任意一个键退出!%s" % (color_redb, color_end))
        sys.exit()

    # Initial Serial
    ser_port = serial.Serial(port=usb_dev['port'], baudrate=115200, parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=5)
    print(ser_port)

    while True:
        key = input("\n%sPlease press any keys for test or q for quit: %s"
            % (color_yellow, color_end))
        if key == 'q':
            break

        while True:
            tmp = ser_port.readline().strip().decode()
            if tmp != '':
                print(tmp)
            else:
                break

    ser_port.close()
