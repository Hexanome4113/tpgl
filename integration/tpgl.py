from optparse import OptionParser

# options stuff
parser = OptionParser()
parser.add_option("-f", "--file", dest="filename",
                  help="write report to FILE", metavar="FILE")
parser.add_option("-q", "--quiet",
                  action="store_false", dest="verbose", default=True,
                  help="don't print status messages to stdout")

(options, args) = parser.parse_args()

# subcommands stuff
def parsexml(opt):
    print 'parsing xml'
    print opt

def parsedtd(opt):
    print 'parsing dtd'

def validate(opt):
    print 'validating xml'

def applyxsl(opt):
    print 'applying template'

subcommands = {
    'parsexml': parsexml,
    'parsedtd': parsedtd,
    'validate': validate,
    'applyxsl': applyxsl
}

if not args or args[0] not in subcommands:
    print 'missing or wrong subcommand'
else:
    subcommands[args[0]](options)