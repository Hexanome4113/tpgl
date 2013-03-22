#!/usr/bin/python
# -*- coding:utf-8 -*-

import sys
from optparse import OptionParser
import subprocess
import os

EXE_NAME = "tpgl"

# codes d'erreurs
ERR_ANALYSE_LEXICALE = 101
ERR_ANALYSE_SYNTAXIQUE = 102
ECHEC_VALIDATION_DTD = 103
ERR_XSLT = 104

# subprocess wrapper :

def call(command):
    """ call a shell command and return its returncode
        and its stdout/err output """
    c = subprocess.Popen(command.split(' '), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    code = c.wait()
    out, err = c.communicate()
    return {'code': code, 'out': out.strip().split('\n'), 'err': err.strip().split('\n')}


# utility functions :

def printusage(subcommand, before=None, exit_after=True):
    if before is not None:
        print before + '\n'
    print subcommands[subcommand]['usage']
    if exit_after:
        sys.exit(-1)


def path_of_exe(exe_name):
    curdir = os.path.dirname(os.path.abspath(__file__))
    path = os.path.join(curdir, 'bin', exe_name)
    if not os.path.isfile(path):
        print 'Oops, erreur interne.\n  executable manquant: "%s"' % path
        sys.exit(-1)
    return path


def file_abspath_or_none(file):
    """ return the absolute path of the file if it exists
        Otherwise, return None """
    abspath = os.path.abspath(file)
    if os.path.isfile(abspath):
        return abspath
    return None


def option_or_nooption(name, presence, after_if_presence=""):
    if not after_if_presence:
        after_if_presence = ""
    else:
        after_if_presence = '=' + after_if_presence
    if presence:
        return name + after_if_presence
    else:
        return "no" + name


# subcommands :

def parsexml(opt, args):
    scname = 'parsexml'
    if len(args) < 1:
        printusage(scname, 'nom du fichier xml manquant')

    xmlfile = file_abspath_or_none(args[0])
    if xmlfile is None:
        printusage(scname, 'fichier "%s" inexistant' % args[0])

    xsltfile = None
    if opt.xsltfile is not None:
        xsltfile = file_abspath_or_none(opt.xsltfile)
        if xsltfile is None:
            printusage(scname, 'fichier "%s" inexistant' % opt.xsltfile)
    
    output = None
    if opt.output is not None:
        output = os.path.abspath(opt.output)
    
    restore = option_or_nooption("restore", opt.restore)
    validate = option_or_nooption("validate", opt.validate)
    applyxslt = option_or_nooption("applyxslt", xsltfile, xsltfile)

    command = path_of_exe(EXE_NAME) + ' ' + scname + ' ' + xmlfile + ' ' +\
        restore + ' ' + validate + ' ' + applyxslt
    cmd = call(command)

    if output is not None:
        sys.stdout = open(output, "w")

    if cmd['code'] in (ERR_ANALYSE_LEXICALE, ERR_ANALYSE_SYNTAXIQUE):
        lex_errs = [l.strip() for l in cmd['err'] if l.startswith('lexical')]
        syn_errs = [l.strip() for l in cmd['err'] if l.startswith('syntax')]

        if lex_errs:
            print "Erreur lors de l'analyse lexicale."
            print "Détail :"
            for line in lex_errs:
                _, ext, lineno, char = line.split(' ', 3)
            print "  - Fichier au format %s, ligne %s, caractère rencontré : %s" % (ext, lineno, char)

        if syn_errs:
            print "Erreur lors de l'analyse syntaxique."
            print "Détail : "
            for line in syn_errs:
                _, ext, msg = line.split(' ', 2)
            print "  - Fichier au format %s : %s" % (ext, msg)

    elif cmd['code'] == ECHEC_VALIDATION_DTD:
        print "Échec de la validation de conformité selon la DTD du fichier %s" % args[0]
        print "Détail :"
        print '  ', '\n  '.join((l.strip() for l in cmd['err']))
    elif cmd['code'] == ERR_XSLT:
        print "Erreur avec le fichier XSLT %s." % xsltfile
        print "Détail :"
        print '  ', '\n  '.join((l.strip() for l in cmd['err']))
    else:  # tout va bien
        if cmd['out'] not in ([], ['']):
            print '\n'.join(cmd['out'])
        if not opt.restore and not opt.validate and not xsltfile:
            print "Parsage réussi !"
    # print repr(cmd)
    

def parsedtd(opt, args):
    scname = 'parsedtd'
    if len(args) < 1:
        printusage(scname, 'nom du fichier dtd manquant')
    
    dtdfile = file_abspath_or_none(args[0])
    if dtdfile is None:
        printusage(scname, 'fichier "%s" inexistant' % args[0])
    
    output = None
    if opt.output is not None:
        output = os.path.abspath(opt.output)

    restore = option_or_nooption("restore", opt.restore)

    command = path_of_exe(EXE_NAME) + ' ' + scname + ' ' + dtdfile + ' ' + restore
    print command
    cmd = call(command)

    if output is not None:
        sys.stdout = open(output, "w")

    if cmd['code'] in (ERR_ANALYSE_LEXICALE, ERR_ANALYSE_SYNTAXIQUE):
        lex_errs = [l.strip() for l in cmd['err'] if l.startswith('lexical')]
        syn_errs = [l.strip() for l in cmd['err'] if l.startswith('syntax')]

        if lex_errs:
            print "Erreur lors de l'analyse lexicale."
            print "Détail :"
            for line in lex_errs:
                _, ext, lineno, char = line.split(' ', 3)
            print "  - Fichier %s (format %s), ligne %s, caractère rencontré : %s" % (args[0], ext, lineno, char)

        if syn_errs:
            print "Erreur lors de l'analyse syntaxique."
            print "Détail : "
            for line in syn_errs:
                _, ext, msg = line.split(' ', 2)
            print "  - Fichier %s (format %s) : %s" % (args[0], ext, msg)
    else:  # tout va bien
        if cmd['out'] not in ([], ['']):
            print '\n'.join(cmd['out'])
        if not opt.restore:
            print "Parsage réussi !"
    # print repr(cmd)


def validate(opt, args):
    scname = 'validate'
    if len(args) < 1:
        printusage(scname, 'nom du fichier xml manquant')
    
    xmlfile = file_abspath_or_none(args[0])
    if xmlfile is None:
        printusage(scname, 'fichier "%s" inexistant' % args[0])
    
    output = None
    if opt.output is not None:
        output = os.path.abspath(opt.output)

    command = path_of_exe(EXE_NAME) + ' ' + scname + ' ' + xmlfile
    cmd = call(command)

    if output is not None:
        sys.stdout = open(output, "w")

    if cmd['code'] in (ERR_ANALYSE_LEXICALE, ERR_ANALYSE_SYNTAXIQUE):
        lex_errs = [l.strip() for l in cmd['err'] if l.startswith('lexical')]
        syn_errs = [l.strip() for l in cmd['err'] if l.startswith('syntax')]

        if lex_errs:
            print "Erreur lors de l'analyse lexicale."
            print "Détail :"
            for line in lex_errs:
                _, ext, lineno, char = line.split(' ', 3)
            print "  - Fichier au format %s, ligne %s, caractère rencontré : %s" % (ext, lineno, char)

        if syn_errs:
            print "Erreur lors de l'analyse syntaxique."
            print "Détail : "
            for line in syn_errs:
                _, ext, msg = line.split(' ', 2)
            print "  - Fichier au format %s : %s" % (ext, msg)

    elif cmd['code'] == ECHEC_VALIDATION_DTD:
        print "Échec de la validation de conformité selon la DTD du fichier %s" % args[0]
        print "Détail :"
        print '  ', '\n  '.join((l.strip() for l in cmd['err']))
    else:  # tout va bien
        if cmd['out'] not in ([], ['']):
            #print '\n'.join(cmd['out'])
        else:
            print "Validation réussie !"
    # print repr(cmd)


def applyxslt(opt, args):
    scname = 'applyxslt'
    if len(args) < 2:
        printusage(scname, 'nom du fichier xml ou xslt manquant')
    print 'applying template'
    
    xmlfile = file_abspath_or_none(args[0])
    if xmlfile is None:
        printusage(scname, 'fichier "%s" inexistant' % args[0])
    
    xsltfile = file_abspath_or_none(args[1])
    if xsltfile is None:
        printusage(scname, 'fichier "%s" inexistant' % args[1])
    
    output = None
    if opt.output is not None:
        output = os.path.abspath(opt.output)
        
    command = path_of_exe(EXE_NAME) + ' ' + scname + ' ' + xmlfile + ' ' + xsltfile
    cmd = call(command)

    if output is not None:
        sys.stdout = open(output, "w")

    if cmd['code'] in (ERR_ANALYSE_LEXICALE, ERR_ANALYSE_SYNTAXIQUE):
        lex_errs = [l.strip() for l in cmd['err'] if l.startswith('lexical')]
        syn_errs = [l.strip() for l in cmd['err'] if l.startswith('syntax')]

        if lex_errs:
            print "Erreur lors de l'analyse lexicale."
            print "Détail :"
            for line in lex_errs:
                _, ext, lineno, char = line.split(' ', 3)
            print "  - Fichier au format %s, ligne %s, caractère rencontré : %s" % (ext, lineno, char)

        if syn_errs:
            print "Erreur lors de l'analyse syntaxique."
            print "Détail : "
            for line in syn_errs:
                _, ext, msg = line.split(' ', 2)
            print "  - Fichier au format %s : %s" % (ext, msg)

    elif cmd['code'] == ERR_XSLT:
        print "Erreur avec le fichier XSLT %s." % args[1]
        print "Détail :"
        print '  ', '\n  '.join((l.strip() for l in cmd['err']))
    else:  # tout va bien
        if cmd['out'] not in ([], ['']):
            print '\n'.join(cmd['out'])
    # print repr(cmd)


subcommands = {
    'parsexml': {
        'func': parsexml,
        'usage': 'usage: tpgl parsexml xmlfile [options]\n  ' +
                 'Parse le fichier XML "xmlfile".',
        'options': [
            {
                'args': ['-r', '--restore'],
                'kwargs': dict(action="store_true", dest="restore", default=False, help="Restitue le fichier parse sur la sortie")
            },
            {
                'args': ['-v', '--validate'],
                'kwargs': dict(action="store_true", dest="validate", default=False, help='Valide la conformite du fichier parse avec le fichier DTD qu il declare.')
            },
            {
                'args': ['-a', '--applyxslt'],
                'kwargs': dict(dest="xsltfile", default=None, help='Transforme le fichier parse a l\'aide du fichier XSLT XSLTFILE', metavar="XSLTFILE")
            },
            {
                'args': ['-o', '--output'],
                'kwargs': dict(dest="output", default=None, help='Redirige la sortie vers le fichier FILE', metavar="FILE")
            },
        ]
    },
    
    'parsedtd': {
        'func': parsedtd,
        'usage': 'usage: tpgl parsedtd dtdfile [options]\n  ' +
                 'Parse le fichier DTD "dtdfile".',
        'options': [
            {
                'args': ['-r', '--restore'],
                'kwargs': dict(action="store_true", dest="restore", default=False, help="Restitue le fichier parse sur la sortie")
            },
            {
                'args': ['-o', '--output'],
                'kwargs': dict(dest="output", default=None, help='Redirige la sortie vers le fichier FILE', metavar="FILE")
            },
        ]
    },
    
    'validate': {
        'func': validate,
        'usage': 'usage: tpgl validate xmlfile [options]\n  ' +
                 'Valide la conformite du fichier XML "xmlfile" avec le fichier DTD qu\'il declare.',
        'options': [
            {
                'args': ['-o', '--output'],
                'kwargs': dict(dest="output", default=None, help='Redirige la sortie vers le fichier FILE', metavar="FILE")
            },
        ]
    },
    
    'applyxslt': {
        'func': applyxslt,
        'usage': 'usage: tpgl applyxslt xmlfile xsltfile [options]\n  ' +
                 'Transforme le fichier XML "xmlfile" a l\'aide du fichier XSLT "xsltfile".',
        'options': [
            {
                'args': ['-o', '--output'],
                'kwargs': dict(dest="output", default=None, help='Redirige la sortie vers le fichier FILE', metavar="FILE")
            },
        ]
    },
}

# usage string, printed when subcommand error occurs
USAGE = """
  usage : tpgl subcommand [OPTIONS]
  help for a subcommand : tpgl subcommand -h
  subcommands available : """ + ', '.join(subcommands.keys())

# shortcuts
subcommands['x'] = subcommands['parsexml']
subcommands['d'] = subcommands['parsedtd']
subcommands['v'] = subcommands['validate']
subcommands['t'] = subcommands['applyxslt']

# options stuff
if len(sys.argv) > 1:
    if sys.argv[1] in subcommands: 
        subc = subcommands[sys.argv[1]]
        parser = OptionParser(usage=subc['usage'])
        for option in subc['options']:
            parser.add_option(*option['args'], **option['kwargs'])
        (options, args) = parser.parse_args()
        subc['func'](options, args[1:])  # on enleve l'arg 1 qui est la subcommand
    else:
        print 'wrong subcommand : "%s"' % sys.argv[1]
        print USAGE
else:
    print 'missing subcommand'
    print USAGE
