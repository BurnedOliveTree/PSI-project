import configparser
from argparse import ArgumentParser
from subprocess import check_output


class Host:
    def __init__(self, argv: list):
        parser = configparser.ConfigParser()
        parser.read(get_project_root() + "/serverModule/.config")
        host, port, ipv = self.__parse_args(argv)
        self.ip_version = ipv if ipv is not None and ipv in [4, 6] else int(parser.get("host", "ip_version"))
        self.host = host if host is not None else self.get_default_host_address(self.ip_version, parser)
        self.port = port if port is not None else int(parser.get("host", "port"))

    @staticmethod
    def __parse_args(argv):
        parser = ArgumentParser(description=f'Run a socket-using serverModule/client in python')
        parser.add_argument('-a', '--address', type=str, help='the ip address of serverModule')
        parser.add_argument('-p', '--port', type=int, help='the port of serverModule')
        parser.add_argument('-v', '--ipv', type=int, help='the ip version used in communication')
        args = parser.parse_args(argv[1:])
        return args.address, args.port, args.ipv

    @staticmethod
    def get_default_host_address(ip_version: int, parser) -> str:
        if ip_version == 4:
            return parser.get("host", "address_ipv4")
        elif ip_version == 6:
            return parser.get("host", "address_ipv6")


def get_project_root() -> str:
    return check_output(['git', 'rev-parse', '--show-toplevel']).decode('ascii').strip()