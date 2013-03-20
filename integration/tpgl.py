#!/usr/bin/python
# -*- coding:utf-8 -*-

import sys
from optparse import OptionParser
import subprocess
import os

# subprocess wrapper
def call(command):
    """ call a shell command and return its returncode
        and its stdout/err output """
    c = subprocess.Popen(command.split(' '), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    code = c.wait()
    out, err = c.communicate()
    return {'code': code, 'out': out.strip().split('\n'), 'err': err.strip().split('\n')}


def printusage(subcommand, before=None, exit_after=True):
    if before is not None:
        print before + '\n'
    print subcommands[subcommand]['usage']
    if exit_after:
        sys.exit(-1)


def file_abspath_or_none(file):
    """ return the absolute path of the file if it exists
        Otherwise, return None """
    abspath = os.path.abspath(file)
    if os.path.isfile(abspath):
        return abspath
    return None


# subcommands :
def parsexml(opt, args):
    scname = 'parsexml'
    if len(args) < 1:
        printusage(scname, 'nom du fichier xml manquant')

    xmlfile = file_abspath_or_none(args[0])
    if xmlfile is None:
        printusage(scname, 'fichier "%s" inexistant' % args[0])

    dtdfile = None
    if opt.dtdfile is not None:
        dtdfile = file_abspath_or_none(opt.dtdfile)
        if dtdfile is None:
            printusage(scname, 'fichier "%s" inexistant' % opt.dtdfile)

    xsltfile = None
    if opt.xsltfile is not None:
        xsltfile = file_abspath_or_none(opt.xsltfile)
        if xsltfile is None:
            printusage(scname, 'fichier "%s" inexistant' % opt.xsltfile)
    
    output = None
    if opt.output is not None:
        output = os.path.abspath(opt.output)
    
    restore = opt.restore
    
    print "On va parser le fichier XML", xmlfile
    if restore:
        print "puis le regénérer à partir de l'objet en mémoire et l'envoyer sur la sortie"
    if dtdfile:
        print "puis on va vérifier qu'il respecte la DTD", dtdfile
    if xsltfile:
        print "puis on va le transformer selon le XSLT", xsltfile, "et afficher le résultat sur la sortie"
    if output:
        print "la sortie standard sera redirigée vers", output
    print "CMD"
    cmd = call("/home/fmatigot/coutcerr")
    print repr(cmd)
    


def parsedtd(opt, args):
    scname = 'parsedtd'
    if len(args) < 1:
        printusage(scname, 'nom du fichier dtd manquant')
    print 'parsing dtd'
    
    dtdfile = file_abspath_or_none(args[0])
    if dtdfile is None:
        printusage(scname, 'fichier "%s" inexistant' % args[0])
    
    output = None
    if opt.output is not None:
        output = os.path.abspath(opt.output)

    restore = opt.restore
    
    print opt, args


def validate(opt, args):
    scname = 'validate'
    if len(args) < 2:
        printusage(scname, 'nom du fichier xml ou dtd manquant')
    print 'validating xml'
    
    xmlfile = file_abspath_or_none(args[0])
    if xmlfile is None:
        printusage(scname, 'fichier "%s" inexistant' % args[0])
    
    dtdfile = file_abspath_or_none(args[1])
    if dtdfile is None:
        printusage(scname, 'fichier "%s" inexistant' % args[1])
    
    output = None
    if opt.output is not None:
        output = os.path.abspath(opt.output)
    
    print opt, args


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
        
    print opt, args


subcommands = {
    'parsexml': {
        'func': parsexml,
        'usage': 'usage: tpgl parsexml xmlfile [options]\n  ' +
                 'Parse le fichier XML "xmlfile".',
        'options': [
            {
                'args': ['-r', '--restore'],
                'kwargs': dict(action="store_true", dest="restore", default=False, help="Restitue le fichier parsé sur la sortie")
            },
            {
                'args': ['-v', '--validate'],
                'kwargs': dict(dest="dtdfile", default=None, help='Valide la conformité du fichier parsé avec le fichier DTD DTDFILE', metavar="DTDFILE")
            },
            {
                'args': ['-a', '--applyxslt'],
                'kwargs': dict(dest="xsltfile", default=None, help='Transforme le fichier parsé à l\'aide du fichier XSLT XSLTFILE', metavar="XSLTFILE")
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
                'kwargs': dict(action="store_true", dest="restore", default=False, help="Restitue le fichier parsé sur la sortie")
            },
            {
                'args': ['-o', '--output'],
                'kwargs': dict(dest="output", default=None, help='Redirige la sortie vers le fichier FILE', metavar="FILE")
            },
        ]
    },
    
    'validate': {
        'func': validate,
        'usage': 'usage: tpgl validate xmlfile dtdfile [options]\n  ' +
                 'Valide la conformité du fichier XML "xmlfile" avec le fichier DTD "dtdfile".',
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
                 'Transforme le fichier XML "xmlfile" à l\'aide du fichier XSLT "xsltfile".',
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
