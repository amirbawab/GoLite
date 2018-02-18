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

# Run program
./build/bin/golite "--$1" "$2"
EXIT_CODE="$?"

# Scan option
if [[ "$1" == "scan" || "$1" == "parse" || "$1" == "typecheck" ]]; then
    if [ "$EXIT_CODE" -eq 0 ]; then
        echo "OK"
    fi
fi
exit $EXIT_CODE
