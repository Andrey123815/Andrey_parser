#!/usr/bin/env bash

print_header() {
    echo "\n***** ${1} *****"
}

print_header "RUN cppcheck"
cppcheck --enable=all --language=c --error-exitcode=1 include src --suppress=missingInclude #--suppress=unusedFunction

print_header "RUN cpplint.py"
cpplint --extensions=c include/* src/*

print_header "SUCCESS"
