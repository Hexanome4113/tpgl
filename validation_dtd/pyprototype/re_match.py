#!/usr/bin/env python
# -*- coding:utf-8 -*-

import re


def stuff(x):
    if isinstance(x, basestring):
        if x[-1] in ('?', '*', '+'):
            quantifier = x[-1]
            x = x[:-1]
        else:
            quantifier = ''
        return "(?:" + x + " )" + quantifier
    elif isinstance(x, dict):
        strings = [stuff(e) for e in x['elems']]
        if x['type'] == 'sequence':
            s = ''.join(strings)
        elif x['type'] == 'choice':
            s = '|'.join(strings)
        quantifier = x.get('quantifier', '')
        return "(?:" + s + ")" + quantifier


def regex_from_dtd(dtd):
    # <!ELEMENT complex (front, (p | lite | note)*, author+, back?)*>
    # "((front )(p |lite |note )*(author )+(back )?)*"
    # 1) si ça finit pas par un ), on en rajoute autours
    regex = stuff(dtd)
    print 'REGEX is "{0}"'.format(regex)
    return "^" + regex + " ?$"


def str_from_xml(xml, separator=' '):
    s = separator.join(xml) + separator
    print 'XML is "{0}"'.format(s.strip())
    return s


def main():
    """ Teste si un élément XML respecte sa définition dans la DTD.
        Utilise pour cela les expressions régulières (PCRE).

        XML utilisé :
            <elem>
                <p>Lol</p>
                <q>Loul</q>
            </elem>

        DTD utilisée :
            <!ELEMENT elem (p, q)>
            # <!ELEMENT complex (front, (p | lite | note)*, author+, back?)*>
    """
    xml = ['front', 'note', 'note', 'lite', 'author', 'author', 'front', 'author', 'back']  # === xml à examiner
    # dtd = "(p, q)"  # === simili-regex utilisée pour cela
    # Non en fait on va partir d'une DTD déjà parsée :
    dtd = {
        'type': 'sequence',
        'elems': [
            'front',
            {
                'type': 'choice',
                'elems': ['p', 'lite', 'note'],
                'quantifier': '*'
            },
            'author+',
            'back?',
        ],
        'quantifier': '*'
    }

    chaine = str_from_xml(xml)
    regex = regex_from_dtd(dtd)

    if re.match(regex, chaine):
        print "Match ! :)"
    else:
        print "Match pas :'("

if __name__ == '__main__':
    main()
