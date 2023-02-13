from argparse import ArgumentParser
from typing import Callable

__ROOT_PARSER = ArgumentParser()
__ROOT_FUNCTION = None


class ParserWrapper():
    def __init__(self, func: Callable, parser: ArgumentParser, parent):
        self.__func = func
        self.__parser = parser
        self.__subparsers = parser.add_subparsers()
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
        return self.__subparsers

    def getParser(self):
        return self.__parser


class Arg:
    def __init__(self, *args, **kwargs):
        self.__args = args
        self.__kwargs = kwargs

    def __call__(self, wrapper: ParserWrapper):
        wrapper.getParser().add_argument(*self.__args, **self.__kwargs)


def command(*args, **kwargs):
    parent: ParserWrapper = None
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
    kwargs = new_kwargs

    def __decorate(func):
        global __ROOT_FUNCTION
        nonlocal parent, cmd_name, kwargs
        wrapper: ParserWrapper = None
        if parent is None:
            assert __ROOT_FUNCTION == None, "Duplicate Root Command."
            wrapper = ParserWrapper(func, __ROOT_PARSER, None)
            wrapper.getSubparsers().required = True
            __ROOT_FUNCTION = wrapper
        else:
            name = cmd_name or func.__name__
            parent.getSubparsers().required = True
            subparser = parent.getSubparsers().add_parser(name, **kwargs)
            wrapper = ParserWrapper(func, subparser, parent)
            subparser.set_defaults(__subfunc=wrapper)

        for arg in args:
            if isinstance(arg, Arg):
                arg(wrapper)

        return wrapper
    return __decorate


if __name__ == "__main__":
    # Just test
    @command(Arg('-b', "--foo", help="foo help.", action="store", default="default"))
    def main(args):
        print("main", args)

    @command(Arg('-b', "--bar", help="foo help.", action="store", default="default"),
             parent=main, name="foo1")
    def subCmd1(args):
        print("subCmd1", args)

    @command(Arg('-b', "--bar", help="foo help.", action="store", default="default"),
             parent=subCmd1, name="bar1")
    def subSubCmd1(args):
        print("subSubCmd1", args)

    @command(Arg('-b', "--bar", help="foo help.", action="store", default="default"),
             parent=main, name="foo2")
    def subSubCmd1(args):
        print("subSubCmd1", args)

    main()
