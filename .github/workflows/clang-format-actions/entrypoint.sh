#!/bin/bash
function log() {
    echo -e "[ clang-format-action ] :: $1"
}
function split_csv() {
    IFS=','
    csv_data="$1"
    local -n global_list_array="$2"
    for i in $csv_data; do
        if [ -f "$i" ]; then
            global_list_array+=("$i")
        fi
    done
    unset IFS
}

SOURCES=()
PROBLEMETIC_FILES=()
EXIT_STATUS=0
STYLE="--style=file"

function resolve_inputs() {
    INPUT_STYLE=${INPUT_STYLE:-"file"}
    if [[ $INPUT_STYLE != "file" ]]; then
        STYLE="--style=$INPUT_STYLE"
    fi
    INPUT_SOURCES=${INPUT_SOURCES:-"**/*"}
}

function check_file() {
    local file="$1"
    log "Checking file: ${file}"
    message="$(clang-format -n -Werror $STYLE --fallback-style=Google "${file}")"
    local status="$?"
    if [ $status -ne 0 ]; then
        echo "$message" >&2
        EXIT_STATUS=1
        return 1
    fi
    return 0
}

function main() {
    log "Action started"
    resolve_inputs
    log "Sources to check: $INPUT_SOURCES with style: $INPUT_STYLE\n"
    split_csv "$INPUT_SOURCES" SOURCES

    for file in "${SOURCES[@]}"; do
        check_file "$file"
        if [ $? -ne 0 ]; then
            PROBLEMETIC_FILES+=("$file")
        fi
    done

    if [ $EXIT_STATUS -eq 0 ]; then
        log "Congrats! All the sources are clang formatted."
        exit 0
    else
        log "Some file is not formatted correctly."
        log "You might want to run: "
        for ((i = 0; i < ${#PROBLEMETIC_FILES[@]}; i++)); do
            if [ $i -ne 0 ]; then
                echo -n " && "
            fi
            log "clang-format ${STYLE} -i "${PROBLEMETIC_FILES[$i]}" \\"
        done
        exit 1
    fi
}

cd "$GITHUB_WORKSPACE" || exit 2
main