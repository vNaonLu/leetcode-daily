import re

import regex
from requests.models import codes


class Description:
    _unordered_list_pat: re.Pattern = regex.compile(
        "[ \t]*<ul>(?P<content>(?:(?!<\/?ul>)[\w\W]|(?R))*)<\/ul>")
    _ordered_list_pat: re.Pattern = regex.compile(
        "[ \t]*<ol>(?P<content>(?:(?!<\/?ol>)[\w\W]|(?R))*)<\/ol>")
    _list_pat: re.Pattern = regex.compile(
        "[ \t]*<li>(?P<content>(?:(?!<\/?li>)[\w\W]|(?R))*)<\/li>")

    def _math(match: re.Match):
        repl = [
            ("[*]", "&times;"),
            ("==", "="),
            ("!=", "≠")
        ]
        content = match.group("content")
        for p, r in repl:
            content = re.sub(p, r, content)
        return " ‘{}’ ".format(content)

    def _sub(match: re.Match):
        content = "⎽({})".format(match.group("content"))
        replmap: dict[str, str] = {
            "0": "₀", "1": "₁", "2": "₂", "3": "₃", "4": "₄", "5": "₅",
            "6": "₆", "7": "₇", "8": "₈", "9": "₉", "+": "₊", "-": "₋",
            "=": "₌", "(": "₍", ")": "₎",
            "a": "ₐ", "d": "ᵈ", "e": "ₑ", "f": "ᶠ", "h": "ₕ",
            "i": "ᵢ", "j": "ⱼ", "k": "ₖ", "l": "ₗ", "m": "ₘ", "n": "ₙ",
            "o": "ₒ", "p": "ₚ", "r": "ᵣ", "s": "ₛ", "t": "ₜ", "u": "ᵤ",
            "v": "ᵥ", "x": "ₓ"
        }
        relp: str = ""
        for c in match.group("content"):
            if c in replmap:
                relp += replmap[c]
            else:
                relp = None
                break
        if relp != None:
            content = relp
        return content

    def _sup(match: re.Match):
        content = "^({})".format(match.group("content"))
        replmap: dict[str, str] = {
            "0": "⁰", "1": "¹", "2": "²", "3": "³", "4": "⁴", "5": "⁵",
            "6": "⁶", "7": "⁷", "8": "⁸", "9": "⁹", "+": "⁺", "-": "⁻",
            "=": "⁼", "(": "⁽", ")": "⁾",
            "a": "ᵃ", "b": "ᵇ", "c": "ᶜ", "d": "ᵈ", "e": "ᵉ",
            "f": "ᶠ", "g": "ᵍ", "h": "ʰ", "i": "ⁱ", "j": "ʲ", "l": "ˡ",
            "k": "ᵏ", "m": "ᵐ", "n": "ⁿ", "o": "ᵒ", "p": "ᵖ", "r": "ʳ",
            "s": "ˢ", "t": "ᵗ", "u": "ᵘ", "v": "ᵛ", "w": "ʷ", "x": "ˣ",
            "y": "ʸ", "z": "ᶻ",
        }
        relp: str = ""
        for c in match.group("content"):
            if c in replmap:
                relp += replmap[c]
            else:
                relp = None
                break
        if relp != None:
            content = relp
        return content

    def _unordered_list(match: re.Match):
        ul = Description._unordered_list_pat
        ol = Description._ordered_list_pat
        mat_cnt = match.group("content")
        lists = Description._list_pat.findall(mat_cnt)
        res: list[str] = []
        for line in lists:
            line = ul.sub(Description._unordered_list, line)
            line = ol.sub(Description._ordered_list, line)
            line = re.sub("\n", "\n    ", line)
            res.append("    - {}".format(line))
        return "\n".join(res)

    def _ordered_list(match: re.Match):
        ul = Description._unordered_list_pat
        ol = Description._ordered_list_pat
        mat_cnt = match.group("content")
        lists = Description._list_pat.findall(mat_cnt)
        res: list[str] = []
        number = 0
        ptn = "    {{:{}}}. {{}}".format(int(len(lists)/10))
        for line in lists:
            line = ul.sub(Description._unordered_list, line)
            line = ol.sub(Description._ordered_list, line)
            line = re.sub("\n", "\n    ", line)
            number += 1
            res.append(ptn.format(number, line))
        return "\n".join(res)

    _repl = [
        ("[ \t]*<b>(?P<content>[\w\W]*?)<\/b>[ \t]*",                       # “ ”
         lambda match: " “{}” ".format(match.group("content"))),
        ("[ \t]*<strong>(?P<content>[\w\W]*?)<\/strong>[ \t]*",             # “ ”
         lambda match: " “{}” ".format(match.group("content"))),
        ("[ \t]*<em>(?P<content>[\w\W]*?)<\/em>[ \t]*",                     # “ ”
         lambda match: " “{}” ".format(match.group("content"))),

        ("<img(?P<content>[\w\W]*?)\/>", ""),
        ("</?div.*?>", ""),
        ("\n\n", "\n"),

        ("[ \t]*<code>(?P<content>[\w\W]+?)<\/code>[ \t]*", _math),         # code
        ("<sup>(?P<content>[\w\W]+?)<\/sup>",
         _sup),                        # sup
        ("<sub>(?P<content>[\w\W]+?)<\/sub>",
         _sub),                        # sub
        ("&#39;", "'"),                                                     # '
        ("&quot;", "'"),                                                    # "
        # space
        ("&nbsp;", ""),
        ("&lt;(?!=)", "<"),                                                 # <
        ("&gt;(?!=)", ">"),                                                 # >
        ("&lt;=", "≤"),                                                     # ≤
        ("&gt;=", "≥"),                                                     # ≥
        ("&le;", "≤"),                                                      # ≤
        ("&ge;", "≥"),                                                      # ≥
        ("&times;", "×"),                                                   # ×
        ("&ldquo;", "“"),                                                   # “
        ("&rdquo;", "”"),                                                   # ”

        ("[ \t]*<blockquote>(?P<content>[\w\W]*?)<\/blockquote>",
         lambda match: match.group("content")),
        ("[ \t]*<p>(?P<content>[\w\W]*?)<\/p>",
         lambda match: match.group("content")),
        ("[ \t]*<pre>(?P<content>[\w\W]*?)<\/pre>",
         lambda match: match.group("content")),
        ("[ \t]*<span>(?P<content>[\w\W]*?)<\/span>",
         lambda match: match.group("content"))
    ]

    @staticmethod
    def prettify(content: str):
        ul = Description._unordered_list_pat
        ol = Description._ordered_list_pat
        for patt, repl in Description._repl:
            content = regex.sub(patt, repl, content)
        content = ul.sub(Description._unordered_list, content)
        content = ol.sub(Description._ordered_list, content)
        return content

    def bound(content: str, limit: int = None):
        if content == None:
            return None
        if not limit:
            return content.splitlines()
        else:
            pat = re.compile("([^\n]{{1,{}}})(?: |$| *\.$)".format(limit))
            content = pat.findall(content)
            return content

class CodeSnippet:
    @staticmethod
    def prettify(content: str):
        content = re.sub("\/\*[\w\W]*?\*\/", "", content)
        content = re.sub("\/\/[^\n]*\n?", "", content)
        content = re.sub("  ", " ", content)
        content = re.sub(" *public:", " public:", content)
        content = re.sub(" *private:", " private:", content)
        content = re.sub(" *protected:", " protected:", content)
        content = re.sub("\n\n", "\n", content)
        return content
