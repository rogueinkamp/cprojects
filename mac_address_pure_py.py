import timeit
import random


def convert_mac_address_to_standard_format(maybe_mac_address: str) -> str:
    """Take anything that appears to be a MAC address and converts it to standard format.

    (eg. 00:80:41:ae:fd:7e)
    """
    mac = str(maybe_mac_address)
    try:
        # remove delimiters and convert to lower case
        # mac = re.sub('[.:-]', '', mac).lower()

        # This is actually much faster:
        mac = mac.replace("[", "").replace(".", "").replace(":", "").replace("-", "").replace("]", "").lower()
        mac = ''.join(mac.split())  # remove whitespaces
        if len(mac) != 12:
            # length should be now exactly 12 (eg. 008041aefd7e)
            raise ValueError(f"MAC Address is not valid len of 12: {mac}")
        if not mac.isalnum():
            # should only contain letters and numbers
            raise ValueError(f"MAC Address is not all numbers and letters: {mac}")
        # convert mac in canonical form (eg. 00:80:41:ae:fd:7e)
        mac = ":".join(["%s" % (mac[i:i + 2]) for i in range(0, 12, 2)])
    except Exception as err:
        print(err)
        return maybe_mac_address
    return mac


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
    for mac_address_str in generate_mac_addresses():
        convert_mac_address_to_standard_format(
            mac_address_str
        )


if __name__ == "__main__":
    # mac_address_str = "00.80.41.ae.fd"
    main()
