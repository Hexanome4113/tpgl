Le fichier xml.l contient l'analyseur lexical d'un fichier XML. Ce fichier vous est
fourni, normalement, peu de modifications devront y être apportées (la personnalisation
du préfixe nécessitera tout de même sa modification). 

Le fichier xml.y contient l'analyseur syntaxique associé.

Le fichier makefile permet d'éxécuter les commandes flex, bison et de compiler l'analyseur
de base du fichier XML. Commencez par taper make puis exécutez ./analyseXML avec un fichier
XML en *entrée standard*. L'option de bison  --debug est activée par défaut générant ainsi un
fichier xml.output contenant le détail de l'analyseur LALR. Lorsque des conflits apparaîtront
dans votre grammaire, vous pourrez aller voir directement dans ce fichier. Deux exemples de 
fichier xml vous sont fournis, rap1.xml qui sera reconnu par l'analyseur et rap2.xml qui ne 
le sera pas car il contient des attributs.

Par défaut, l'exécution de l'analyseur syntaxique sera détaillée, avec la liste des jetons
envoyés par flex ainsi que les actions associées. Pour enlever cet affichage, il faut commenter
la ligne "yydebug = 1;" dans le fichier xml.y.

A terme, le code de la fonction principale (main) devra être sorti de xml.y afin de rendre
l'analyseur plus modulaire.


**Fichiers tests de l'analyseur syntaxique du xml :
rap1.xml :
	ligne encodage : aucune
	attributs : aucun
	namespace : aucun
	balise autofermante : aucune

rap2.xml :
	ligne encodage : oui
	attributs : 4 (titres)
	namespace : aucun
	balise autofermante : aucune

rap3.xml :
	ligne encodage : oui
	attributs : 6 dont 3 dans la meme balise
	namespace : aucun
	balise autofermante : 1

rap4.xml :
	ligne encodage : oui
	attributs : 6 dont 3 dans la meme balise
	namespace : aucun
	balise autofermante : 2

rap5.xml :
	ligne encodage : oui
	attributs : 6 dont 3 dans la meme balise
	namespace : oui
	balise autofermante : 1
