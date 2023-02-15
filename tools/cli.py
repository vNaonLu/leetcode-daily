from argparse import ArgumentParser
from typing import Callable


class ParserWrapper():
    def __init__(self, func: Callable, parser: ArgumentParser, parent):
        self.__func = func
        self.__parser = parser
        self.__subparsers = None
        self.__parent: ParserWrapper = parent

    def __call__(self):
        args = self.__parser.parse_args()
        if hasattr(args, "__subfunc"):
            getattr(args, "__subfunc").__commandMain(args)
        else:
            self.__commandMain(args)

    def __commandMain(self, args):
        if self.__parent is not None:
            self.__parent.__commandMain(args)
        self.__func(args)

    def getSubparsers(self):
        if self.__subparsers is None:
            self.__subparsers = self.getParser().add_subparsers()
        return self.__subparsers

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


def command(*args, **kwargs):
    # when |parent| not set, the node will automatically bind parent if the root exists.
    parent: ParserWrapper = __ROOT_WRAPPER
    cmd_name: str = None
    new_kwargs = {}

    for key, val in kwargs.items():
        if key == 'parent':
            assert isinstance(val, ParserWrapper), 'Invalid Parent Command.'
            parent = val
        elif key == 'name':
            assert isinstance(val, str), 'Invalid Command Name.'
            cmd_name = val
        else:
            new_kwargs[key] = val
    if parent == __ROOT_WRAPPER and __ROOT_WRAPPER == None:
        if "help" in new_kwargs:
            del new_kwargs["help"]
    kwargs = new_kwargs

    def __decorate(func):
        global __ROOT_PARSER, __ROOT_WRAPPER
        nonlocal parent, cmd_name, kwargs
        wrapper: ParserWrapper = None

        if parent is None:
            assert __ROOT_PARSER == None, "Duplicate Root Command."
            __ROOT_PARSER = ArgumentParser(**kwargs)
            wrapper = ParserWrapper(func, __ROOT_PARSER, None)
            __ROOT_WRAPPER = wrapper
        else:
            name = cmd_name or func.__name__
            parent.getSubparsers().required = True
            subparser = parent.getSubparsers().add_parser(name, **kwargs)
            wrapper = ParserWrapper(func, subparser, parent)
            subparser.set_defaults(__subfunc=wrapper)

        for arg in args:
            if isinstance(arg, ArgWrapper):
                arg(wrapper)

        return wrapper
    return __decorate


if __name__ == "__main__":
    # Just test
    @command(
        arg('-b', "--foo", help="foo help.", action="store", default="default"),
        arg('-z', "--foo1", help="foo help.", action="store", default="default"),
    )
    def main(args):
        print("main", args)

    @command(
        arg('-b', "--bar", help="foo help.", action="store", default="default"),
        parent=main, name="foo1"
    )
    def subCmd1(args):
        print("subCmd1", args)

    @command(
        arg('-b', "--bar", help="foo help.", action="store", default="default"),
        parent=subCmd1, name="bar1"
    )
    def subSubCmd1(args):
        print("subSubCmd1", args)

    @command(
        arg('-b', "--bar", help="foo help.", action="store", default="default"),
        parent=main, name="foo2"
    )
    def subSubCmd1(args):
        print("subSubCmd1", args)

    @command(
        arg('-b', "--foo", help="foo help.", action="store", default="default")
    )
    def main2(args):
        print("main2", args)

    main()
