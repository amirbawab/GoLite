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
        UGLIFY_PATH="$PWD/build/node_modules/uglify-js/bin/uglifyjs"

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
        TS_FILE="./build/codegen.ts"
        JS_FILE="${TS_FILE%.*}.js"
        JS_MIN_FILE="${TS_FILE%.*}.min.js"

        # Compile GoLite
        "$GOLITE_PATH" \
            codegen \
            "$GO_FILE" > /dev/null #OK

        # Check if GoLite compiled successfully
        EXIT_CODE="$?"
        if [[ $EXIT_CODE -ne 0 ]]
        then
            echo "!!! Error compiling GoLite"
            exit $EXIT_CODE
        fi

        # Compile TypeScript
        "$TSC_PATH" \
            --removeComments \
            --allowUnreachableCode \
            "$PWD/etc/typescript/stubs.ts" \
            "$TS_FILE"

        # Check if TypeScript compiled successfully
        EXIT_CODE="$?"
        if [[ $EXIT_CODE -ne 0 ]]
        then
            echo "!!! Error compiling TypeScript"
            exit $EXIT_CODE
        fi

        # Compress and minify JS
        "$UGLIFY_PATH" \
            --compress \
            --mangle \
            --output "$JS_MIN_FILE" \
            "$JS_FILE"
            

        # Run JavaScript code
        node --max-old-space-size=4096 "$JS_MIN_FILE"
    fi
}

main $1
