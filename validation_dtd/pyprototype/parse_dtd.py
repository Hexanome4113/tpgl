#!/usr/bin/env python
# -*- coding:utf-8 -*-

import re
SUBELEM = r"([a-zA-Z-]+|\(.+\))(\+|\?|\*)?"
ALONE = re.compile(r"^ ?" + SUBELEM + r" ?$")
SEQUENCE = re.compile(r"^(" + SUBELEM + r" ?, ?)+" + SUBELEM + r" ?$")
CHOICE = re.compile(r"^(" + SUBELEM + r" ?\| ?)+" + SUBELEM + r" ?$")


def parse_content(s):
    quantifier = s[-1]
    if quantifier not in ('*', '+', '?'):
        quantifier = ''
    else:
        s = s[:-1]
    s = s[1:-1]  # strip parens
    if CHOICE.match(s):
        print "[{}] is a CHOICE".format(s)
    elif SEQUENCE.match(s) or ALONE.match(s):
        print "[{}] is a SEQUENCE".format(s)
    else:
        print "[{}] is NOTHING".format(s)


def main():
    dtd = "<!ELEMENT complex (front)*>"
    content = dtd.split(' ', 2)[2][:-1].strip()
    content = parse_content(content)

if __name__ == '__main__':
    main()
