import os
import random
from ctypes import CDLL
import ctypes


so_file = f"{os.getcwd()}/macAddressConvert.so"
c_functions = CDLL(so_file)

# mac_address_str = "00.80.41.ae.fd"
def generate_mac_addresses():
    mac_addresses = []
    for _ in range(1, 1000000):
        mac_addresses.append(
            "52.54.00.%02x.%02x.%02x" % (
                random.randint(0, 255),
                random.randint(0, 255),
                random.randint(0, 255),
                )
        )
    print(len(mac_addresses))
    return mac_addresses


def main():
    try:
        for mac_address_str in generate_mac_addresses():
            c_char_mac_address_str = ctypes.c_char_p(bytes(mac_address_str, encoding="utf-8"))
            # print(c_char_mac_address_str)
            c_functions.convert_mac_addr_str_std_fmt.restype = ctypes.c_char_p
            ret = c_functions.convert_mac_addr_str_std_fmt(
                c_char_mac_address_str
            )
            # print("ORIGINAL: ", mac_address_str, "CONVERTED: ", ctypes.c_char_p(ret).value.decode("utf-8"))
    except Exception as err:
        print(err)


if __name__ == "__main__":
    main()
