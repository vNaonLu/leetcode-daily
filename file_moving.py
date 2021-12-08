#!/usr/bin/python3
import sys
from tools.utils import code_snippet


def _main():
    if len(sys.argv) < 2:
        return
    
    with open(sys.argv[1], 'r') as f:
        content = f.read()
        code_snippet.code_snippet(content)



if __name__ == "__main__":
    _main()
