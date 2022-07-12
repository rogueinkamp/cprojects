"""This is using the helper.c from python to do fast ip in network checking."""

from __future__ import annotations
import os
from ctypes import CDLL
import ctypes


so_file = f"{os.getcwd()}/helper.so"
c_functions = CDLL(so_file)


def c_fast_ip_in_network(ip_address_to_check: str, network_address: str, mask_bits: int) -> bool:
    try:
        c_char_address_to_check = ctypes.c_char_p(bytes(ip_address_to_check, encoding="utf-8"))
        c_char_network_to_evaluate = ctypes.c_char_p(bytes(network_address, encoding="utf-8"))
        c_functions.ip_in_network.restype = ctypes.c_int
        # unsigned ip_in_network(const char* address_to_check, const char* network_address, int mask_len, int debug) {
        ret = c_functions.ip_in_network(c_char_address_to_check, c_char_network_to_evaluate, network_mask_bits, 1)
        print("ORIGINAL: ", ret, "CONVERTED: ", ctypes.c_int(ret).value)
    except Exception as err:
        print(err)

if __name__ == "__main__":
    address_to_check = "192.168.0.22"
    network_to_evaluate = "192.168.0.32"
    network_mask_bits = 27
    c_fast_ip_in_network(address_to_check, network_to_evaluate, network_mask_bits)
