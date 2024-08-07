#!/bin/bash

cd $(dirname $0)

mkdir -p ./image/alpine
rm -rf ./image/alpine/*
cd ./image/alpine
wget http://dl-cdn.alpinelinux.org/alpine/v3.12/releases/x86_64/alpine-minirootfs-3.12.1-x86_64.tar.gz
tar xzf alpine-minirootfs-3.12.1-x86_64.tar.gz
rm alpine-minirootfs-3.12.1-x86_64.tar.gz
