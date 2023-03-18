#!/usr/bin/env python3
import regex
from html.parser import HTMLParser as _NativeHTMLParser

__SUPERSCRIPTS = {
    "0": "⁰", "1": "¹", "2": "²", "3": "³", "4": "⁴", "5": "⁵",
    "6": "⁶", "7": "⁷", "8": "⁸", "9": "⁹", "+": "⁺", "-": "⁻",
    "=": "⁼", "(": "⁽", ")": "⁾",
    "a": "ᵃ", "b": "ᵇ", "c": "ᶜ", "d": "ᵈ", "e": "ᵉ",
    "f": "ᶠ", "g": "ᵍ", "h": "ʰ", "i": "ⁱ", "j": "ʲ", "l": "ˡ",
    "k": "ᵏ", "m": "ᵐ", "n": "ⁿ", "o": "ᵒ", "p": "ᵖ", "r": "ʳ",
    "s": "ˢ", "t": "ᵗ", "u": "ᵘ", "v": "ᵛ", "w": "ʷ", "x": "ˣ",
    "y": "ʸ", "z": "ᶻ"
}

__SUBSCRIPTS = {
    "0": "₀", "1": "₁", "2": "₂", "3": "₃", "4": "₄", "5": "₅",
    "6": "₆", "7": "₇", "8": "₈", "9": "₉", "+": "₊", "-": "₋",
    "=": "₌", "(": "₍", ")": "₎",
    "a": "ₐ", "d": "ᵈ", "e": "ₑ", "f": "ᶠ", "h": "ₕ",
    "i": "ᵢ", "j": "ⱼ", "k": "ₖ", "l": "ₗ", "m": "ₘ", "n": "ₙ",
    "o": "ₒ", "p": "ₚ", "r": "ᵣ", "s": "ₛ", "t": "ₜ", "u": "ᵤ",
    "v": "ᵥ", "x": "ₓ"
}


def __replaceImpl(content: str, *, table: dict[str, str]):
    replaced = ""
    for c in content:
        if c not in table:
            return content
        replaced += table[c]
    return replaced


def superscript(content: str):
    return __replaceImpl(content, table=__SUPERSCRIPTS)


def subscript(content: str):
    return __replaceImpl(content, table=__SUBSCRIPTS)


class __HTMLParser(_NativeHTMLParser):
    _INDENT = "  "

    def __init__(self, *, convert_charrefs: bool = True, show_raw_data: bool = False) -> None:
        super().__init__(convert_charrefs=convert_charrefs)
        self.show_raw_data = show_raw_data
        self.buffer = ""
        self.current_tag: list[tuple[str, object]] = []
        self.relative_tag: list[str] = []
        self.ordinated_idx: list[int] = []

    def handle_starttag(self, tag, attrs):
        self.current_tag.append((tag, attrs))

        if tag == 'ul' or tag == 'ol':
            self.relative_tag.append(tag)
            if tag == 'ol':
                self.ordinated_idx.append(1)

        elif tag == 'li':
            if self.relative_tag[-1] == 'ol':
                self.buffer += f'\n{self._INDENT * (len(self.relative_tag) - 1)} {self.ordinated_idx[-1]}. '
                self.ordinated_idx[-1] += 1
            else:
                self.buffer += f'\n{self._INDENT * (len(self.relative_tag) - 1)} • '

        elif tag == 'code':
            if len(self.buffer) > 0 and not regex.match("[ \t\n]", self.buffer[-1]):
                self.buffer += " "
            if not self.show_raw_data:
                self.buffer += "|"

    def handle_endtag(self, ctag):
        tag, attrs = self.current_tag.pop()
        assert tag == ctag

        if tag == 'ul' or tag == 'ol':
            self.relative_tag.pop()
            if tag == 'ol':
                self.ordinated_idx.pop()

        if tag == 'li' or tag == 'ul' or tag == 'ol':
            pass

        elif tag == 'a' and 'href' in attrs:
            self.buffer += '({})'.format(attrs['href'])

        elif tag == 'img':
            for attr, val in attrs:
                if attr == 'src':
                    self.buffer += '![img]({})'.format(val)
                    break

        elif tag == 'code' and not self.show_raw_data:
            self.buffer += "|"

    def handle_data(self, data):
        tag, attrs = "", {}
        if len(self.current_tag):
            tag, attrs = self.current_tag[-1]

        elif tag != 'pre':
            data = regex.sub(r"[ \t]+", r" ", data)

        if tag == 'a':
            data = f'[{data}]'

        elif tag == "sub":
            repl = subscript(data)
            if repl == data:
                data = f'_{{{repl}}}'
            else:
                data = repl

        elif tag == "sup":
            repl = superscript(data)
            if repl == data:
                data = f'^{{{repl}}}'
            else:
                data = repl

        self.buffer += data.replace('\xa0', ' ')


def parseHtml(content: str, *, show_raw_data = False):
    parser = __HTMLParser(show_raw_data=show_raw_data)
    parser.feed(content)
    return regex.sub('\n+', '\n', parser.buffer)


if __name__ == "__main__":
    a = parseHtml('''
    <p>You are given an integer array <code>height</code> of length <code>n</code>. There are <code>n</code> vertical lines drawn such that the two endpoints of the <code>i<sup>th</sup></code> line are <code>(i, 0)</code> and <code>(i, height[i])</code>.</p>

<p>Find two lines that together with the x-axis form a container, such that the container contains the most water.</p>

<p>Return <em>the maximum amount of water a container can store</em>.</p>

<p><strong>Notice</strong> that you may not slant the container.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/17/question_11.jpg" style="width: 600px; height: 287px;" />
<pre>
<strong>Input:</strong> height = [1,8,6,2,5,4,8,3,7]
<strong>Output:</strong> 49
<strong>Explanation:</strong> The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> height = [1,1]
<strong>Output:</strong> 1
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
        <li><code>n == height.length</code></li>
        <li><code>2 &lt;= n &lt;= 10<sup>5</sup></code></li>
        <li><code>0 &lt;= height[i] &lt;= 10<sup>4</sup></code></li>
</ul>

''')
    print(a)