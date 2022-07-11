"""This is using the helper.c from python to do fast ip in network checking."""

from __future__ import annotations
import os
from ctypes import CDLL
import ctypes


so_file = f"{os.getcwd()}/helper.so"
c_functions = CDLL(so_file)


def fast_ip_in_network(ip_address_to_check: str, network_address: str, mask_bits: int) -> bool:
    try:
        for mac_address_str in generate_mac_addresses():
            c_char_mac_address_str = ctypes.c_char_p(bytes(mac_address_str, encoding="utf-8"))
            # print(c_char_mac_address_str)
            c_functions.convert_mac_addr_str_std_fmt.restype = ctypes.c_char_p
            ret = c_functions.fast_ip_in_network()
            # print("ORIGINAL: ", mac_address_str, "CONVERTED: ", ctypes.c_char_p(ret).value.decode("utf-8"))
    except Exception as err:
        print(err)

