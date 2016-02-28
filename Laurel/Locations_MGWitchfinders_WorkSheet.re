
Find each instance where <LOCATION> appears and put it on a new line.

FIND:
(<LOCATION>)
REPLACE:
\n\1

Find each instance where a line does not begin with <LOCATION> and delete it. 
Both of the expression below work, however, the first option will require a second step to remove all blank lines.

FIND:
^(?!<LOCATION>).+
REPLACE: 
#leave blank

FIND:
\n+^(?!.*LOCATION).*$
REPLACE:
#leave blank

Remove all blank lines.

FIND:
\n\s
REPLACE:
#leave blank

Find all text that follows </LOCATION> and remove the text, leaving </LOCATION>

FIND: 
(<\/LOCATION>).+
REPLACE:
\1