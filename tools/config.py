#!/usr/bin/env python3
import sys
import json
from pathlib import Path
# prevent generating __pycache__
sys.dont_write_bytecode = True


from utils import *


class _LDTConfigurationImpl:

    __DEFAULT_USER = "default_user"

    def __init__(self, path: Path) -> None:
        self.__path = path
        self.default_user: str = ""

        if self.__path.exists():
            content = json.loads(self.__path.read_text())

            if self.__DEFAULT_USER in content:
                self.default_user = content[self.__DEFAULT_USER]

    def save(self):
        content = {}

        if self.default_user != "":
            content[self.__DEFAULT_USER] = self.default_user

        self.__path.write_text(json.dumps(content))


class Configuration:
    __impl: _LDTConfigurationImpl = None

    @staticmethod
    def getInstance():
        if Configuration.__impl is None:
            Configuration.__impl = _LDTConfigurationImpl(LDTCONFIG_ABSOLUTE)
        return Configuration.__impl
