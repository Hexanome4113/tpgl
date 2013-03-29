#!/usr/bin/env python
# -*- coding:utf-8 -*-

# le dossier où doivent être les sorties attendues :
DIR_SORTIE = "test/sortie/"

# ajouter ici les tests :
tests = [
#   ("nomFichierTest", "commande à taper"),
    ("testun", "./tpgl.py parsedtd test/rap1.dtd"),
    ("testdeux", "./tpgl.py parsedtd test/rap2.dtd"),
    ("testvalidaterap1", "./tpgl.py validate test/rap1.dtd"),
    ("testvalidateXML-noeudsOK", "./tpgl.py validate test/testValidOK.xml"),
    ("testvalidateXML-noeudsKO", "./tpgl.py validate test/testValidKOnoeud.xml"),
    ("testvalidateXML-attributsOK", "./tpgl.py validate test/testValidOKattribut.xml"),
    ("testvalidateXML-attributsKO", "./tpgl.py validate test/testValidKOattribut.xml"),
    ("testxslt", "./tpgl.py applyxslt test/xml_pour_test_xslt.xml test/xslt_pour_test_xslt.xslt"),
]

# ne pas modifier en dessous !

import subprocess

CSI = "\033["

colors = ["black", "red", "green", "yellow", "blue",
          "magenta", "cyan", "white", "", "standard"]

fgcode = CSI + "3%dm"


def ansi(name, code, ansi_list, cursor_dep=0):
    try:
        if cursor_dep:
            print code % (cursor_dep, chr(65 + ansi_list.index(name))),
        else:
            print code % (ansi_list.index(name),),
            print CSI + "1F"
    except ValueError:
        print "ANSI error : not found", name


def fgcolor(name):
    ansi(name, fgcode, colors)


def call(command):
    """ call a shell command and return its returncode
        and its stdout/err output """
    c = subprocess.Popen(command.split(' '), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    code = c.wait()
    out, err = c.communicate()
    return {'code': code, 'out': out.strip().split('\n'), 'err': err.strip().split('\n')}


def run_tests():
    tests_passed = 0
    for (nom_test, cmd) in tests:
        lines_obtenues = [l + '\n' for l in call(cmd)['out']]
        lines_obtenues[-1] = lines_obtenues[-1][:-1]

        fic_sortie = DIR_SORTIE + nom_test
        try:
            with open(fic_sortie, "r") as f:
                lines_attendues = f.readlines()
        except IOError:
            print "test manquant : rajout de la sortie (cheat)"
            with open(fic_sortie, "w") as f:
                f.write('\n'.join(lines_obtenues))
                lines_attendues = None
        if lines_attendues == lines_obtenues:
            tests_passed += 1
            fgcolor("green")
            print "PASSED :", nom_test
            fgcolor("standard")
        else:
            fgcolor("red")
            print ">> FAILED :", nom_test
            fgcolor("standard")
    print '---------------------------'
    print 'Passed : (%d/%d)' % (tests_passed, len(tests))


if __name__ == '__main__':
    run_tests()
