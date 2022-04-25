from __future__ import annotations
from arvigtools.utils.dbhelper import DatabaseHelper


def get_interface_ip_data_for_device(hostname: str):
    """Query to get all the IP addresses for each interface assigned to this device in Netbox.

    {'Address': '209.81.119.118', 'Age': '00:18:09', 'HardwareAddr':
    '0009.0f09.0022', 'State': 'Dynamic', 'Type': 'ARPA', 'Interface': 'PW-Ether1911'}
    """
    device_name = hostname
    query = (
        """
        select
            id,
            address,
            description,
            assigned_object_id
        from
            ipam_ipaddress
        where
            assigned_object_id in (
            select
                id
            from
                dcim_interface
            where
                device_id in (
                select
                    id
                from
                    dcim_device
                where
                    name = %s
        ))
        """
    )
    with DatabaseHelper("sandboxnetbox") as db_conn:
        query_data = db_conn.execute_query(
            query,
            params=(device_name,),
            colnames=True
        )

    return query_data


