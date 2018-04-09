#/bin/bash
#
# Usage: ./run.sh <mode> <file>
# 	mode: scan|tokens|parse|pretty|symbol|typecheck|codegen
                                
# Check the command-line arguments are valid

if [ $# -lt 2 ]
then
	echo "Missing arguments"
	echo "Usage: $0 <mode> <file>"
	echo " + mode: scan|tokens|parse|pretty|symbol|typecheck|codegen"
	echo " + file: path to file (absolute or relative)"
	exit 1
fi

if [[ "|scan|tokens|parse|pretty|symbol|typecheck|codegen|" != *"|$1|"* ]]
then
	echo "Unknown mode \"$1\""
	echo "Usage: $0 <mode> <file>"
	echo " + mode: scan|tokens|parse|pretty|symbol|typecheck|codegen"
	echo " + file: path to file (absolute or relative)"
	exit 1

fi

# Output stream
OUT_STREAM=/dev/stdout

# Codegen updates output stream
if [[ "$1" == "codegen" ]]; then
    OUT_STREAM="./build/codegen.ts"
fi

# Run program
./build/bin/golite "--$1" "$2" > "$OUT_STREAM"
EXIT_CODE="$?"

# Scan option
if [[ "$1" == "scan" || "$1" == "parse" || "$1" == "typecheck" || "$1" == "codegen" ]]; then
    if [ "$EXIT_CODE" -eq 0 ]; then
        echo "OK"
    fi
fi
exit $EXIT_CODE
