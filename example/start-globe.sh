#!/bin/sh

read -r build_directory < ./build_directory
$build_directory/Globe -c ./Globe/Globe.cfg

