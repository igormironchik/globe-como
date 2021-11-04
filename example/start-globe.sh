#!/bin/sh

read -r build_directory < ./build_directory
$build_directory/src/App/Globe -c ./Globe/Globe.cfg

