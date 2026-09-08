- LPAREN            : (
- RPAREN            : )
- LBRACE            : {
- RBRACE            : }
- LBRACKET          : [
- RBRACKET          : ]
- COMMA             : ,
- SEMICOLON         : ;

- COLON             : :
- COLON_EQUAL       : :=


- PLUS              : +
- PLUS_EQUAL        : +=

- MINUS             : -
- MINUS_EQUAL       : -=
- ARROW             : ->

- STAR              : *
- STAR_EQUAL        : *=

- SLASH             : /
- SLASH_EQUAL       : /=

- PERCENT           : %
- PERCENT_EQUAL     : %=

- GREATER           : >
- GREATER_EQUAL     : >=

- LESSER            : <
- LESSER_EQUAL      : <=

- BANG              : !
- BANG_EQUAL        : !=

- AMPERSAND         : &
- AND               : &&

- OR                : ||

- EQUAL             : =
- EQUAL_EQUAL       : ==
- BOLD_ARROW        : =>

- FUNCTION          : fn
- RETURN            : return
- FOR               : for
- WHILE             : while
- LOOP              : loop
- SWITCH            : switch
- BREAK             : break
- CONTINUE          : continue
- IF                : if
- ELSE              : else
- BUILTIN_READ      : __read__
- BUILTIN_WRITE     : __write__

- INTEGER           : [0-9]+
- FLOAT             : ([0-9]+\.|[0-9]*\.[0-9]+)
- TRUE              : true
- FALSE             : false
- STRING            : ".*"
- CHAR              : '([^\\]|\\(n|t|b|r|a|f|v|0|\\|'))'
- IDENTIFIER        : [a-zA-Z_][a-zA-Z0-9_]*
