from argparse import ArgumentParser
from typing import Callable


class ParserWrapper():
    def __init__(self, func: Callable, parser: ArgumentParser, parent, need_subcmd: bool, skip_if_has_subcmd: bool):
        self.__func = func
        self.__parser = parser
        self.__subparsers = None
        self.__required_sub = need_subcmd
        self.__parent: ParserWrapper = parent
        self.__skip_if_has_subcmd = skip_if_has_subcmd

    def __call__(self):
        args = self.__parser.parse_args()
        if hasattr(args, "__subfunc"):
            getattr(args, "__subfunc").__commandMain(args)
        else:
            self.__commandMain(args)

    def __commandMain(self, args):
        if self.__parent is not None:
            self.__parent.__commandMain(args)

        if not (self.__skip_if_has_subcmd and hasattr(args, "__subfunc") and getattr(args, "__subfunc") != self):
            self.__func(args)

    def addSubParser(self, name, **kwargs):
        if self.__subparsers is None:
            self.__subparsers = self.getParser().add_subparsers()
        self.__subparsers.required = self.__required_sub
        return self.__subparsers.add_parser(name, **kwargs)

    def getParser(self):
        return self.__parser


class ArgWrapper:
    def __init__(self, *args, **kwargs):
        self.__args = args
        self.__kwargs = kwargs

    def __call__(self, wrapper: ParserWrapper):
        wrapper.getParser().add_argument(*self.__args, **self.__kwargs)


__ROOT_PARSER: ArgumentParser = None
__ROOT_WRAPPER: ParserWrapper = None


def arg(*args, **kwargs):
    return ArgWrapper(*args, **kwargs)


def command(*args, parent: ParserWrapper = None, name: str = None, required_subcmd: bool = True, skip_if_has_subcmd: bool = False, **kwargs):
    # when |parent| not set, the node will automatically bind parent if the root exists.
    assert isinstance(name, str) or name == None, 'Invalid Command Name.'
    assert isinstance(
        parent, ParserWrapper) or parent == None, 'Invalid Parent Command.'
    assert isinstance(required_subcmd, bool), 'Invalid required_subcmd.'
    assert isinstance(skip_if_has_subcmd, bool), 'Invalid skip_if_has_subcmd.'
    cmd_name: str = name

    if parent == None:
        parent = __ROOT_WRAPPER

    if parent == __ROOT_WRAPPER and __ROOT_WRAPPER == None:
        if "help" in kwargs:
            del kwargs["help"]

    def __decorate(func):
        global __ROOT_PARSER, __ROOT_WRAPPER
        nonlocal parent, cmd_name, kwargs
        wrapper: ParserWrapper = None

        if parent is None:
            assert __ROOT_PARSER == None, "Duplicate Root Command."
            __ROOT_PARSER = ArgumentParser(**kwargs)
            wrapper = ParserWrapper(
                func, __ROOT_PARSER, None, required_subcmd, skip_if_has_subcmd)
            __ROOT_WRAPPER = wrapper
        else:
            name = cmd_name or func.__name__
            subparser = parent.addSubParser(name, **kwargs)
            wrapper = ParserWrapper(
                func, subparser, parent, required_subcmd, skip_if_has_subcmd)
            subparser.set_defaults(__subfunc=wrapper)

        for arg in args:
            if isinstance(arg, ArgWrapper):
                arg(wrapper)

        return wrapper
    return __decorate
