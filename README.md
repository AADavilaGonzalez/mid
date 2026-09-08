# Mid Lang

Language procesor frontend for the made up mid lang. Further language
documentation can be found inside the `doc` directory.

## Build
1. `cmake -S . -B build`
2. `cd build`
3. `make`

## Basic Usage
`mid [flags] <input> [-o output]`
By default will process the input file through all available stages
outputting the result a file named 'output' or 'a.out' if not specified.

It is recommended to execute the example programs under 'examples'
to test out the language processor once compiled i.e
`./build/mid -l ./examples/small.mid -o lexer_output.lex`

### Lexing (Lexical Analysis)
`mid -l <input> [-o output]`\
Stops processor after lexing phase, outputs Token Stream as JSON

### Parsing (Syntactic Analysis)
`mid -p <input> [-o output]`\
Stops processor after parsing phase, outputs AST as JSON.

### Analysis (Semantic Analysis)
`mid -a <input> [-o output]`\
Stops processor after analysis phase, outputs Annotated AST as JSON.
Currently equivalent to not passing any flags in
