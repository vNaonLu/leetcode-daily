import re

snippet_regex = re.compile("(?P<snippet>class[\w\W]*{[\w\W]*};)")

def code_snippet(content: str):
    _snpt: list[str] = []
    match = snippet_regex.findall(content)
    for _snippet in match:
        _snpt.append("\n".join(_snippet.split("\n")))
    return "\n".join(_snpt)
