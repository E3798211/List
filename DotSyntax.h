#ifndef DOTSYNTAX_H_INCLUDED
#define DOTSYNTAX_H_INCLUDED

const char OPEN[] = "xdg-open ";

const char DOT1[] = "dot -Tps ";
const char DOT2[] = " -o ";


const char             BEGIN[]  = "digraph G {\n";
const char               END[]  = "}\n";

const char  SET_RECORD_SHAPE[]  = "node[shape = record];\n";

const char BEGIN_DECLARATION[]  = " [label = \"";
const char   END_DECLARATION[]  = "\"];\n";
const char        NEXT_FIELD[]  = " | ";

const char FORWARD_DIRECTION[]  = " [color = green];\n";
const char    BACK_DIRECTION[]  = " [color = yellow];\n";

const char                TO[]  = " -> ";

#endif // DOTSYNTAX_H_INCLUDED