#!/bin/bash

function printUsage() {
    cat<<EOF
Execute TypeScript files

Usage: 
    execute.sh [FILE]
EOF
    
}

function main() {

    if [[ ${#@} -ne 1 ]]
    then
        printUsage
    else
    
        # Compier
        GOLITE_PATH="$PWD/run.sh"
        TSC_PATH="$PWD/build/node_modules/typescript/bin/tsc"

        # Check if TypeScript compiler was installed
        if [ ! -f "$GOLITE_PATH" ]; then
            echo "GoLite compiler was not found"
            exit 1
        fi

        # Check if TypeScript compiler was installed
        if [ ! -f "$TSC_PATH" ]; then
            echo "TypeScript compiler was not found"
            exit 1
        fi

        # Input and output files
        GO_FILE="$1"
        TS_FILE="${GO_FILE%.*}.ts"
        JS_FILE="${TS_FILE%.*}.js"

        # Compile GoLite
        "$GOLITE_PATH" \
            codegen \
            "$GO_FILE" > "$TS_FILE"

        # Check if GoLite compiled successfully
        EXIT_CODE="$?"
        if [[ $EXIT_CODE -ne 0 ]]
        then
            echo "!!! Error compiling GoLite"
            exit $EXIT_CODE
        fi

        # Compile TypeScript
        "$TSC_PATH" \
            "$PWD/etc/typescript/stubs.ts" \
            "$TS_FILE"

        # Check if TypeScript compiled successfully
        EXIT_CODE="$?"
        if [[ $EXIT_CODE -ne 0 ]]
        then
            echo "!!! Error compiling TypeScript"
            exit $EXIT_CODE
        fi

        # Run JavaScript code
        node "$JS_FILE"
    fi
}

main $1
