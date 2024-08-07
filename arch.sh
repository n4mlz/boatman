#!/bin/bash

cd $(dirname $0)

mkdir -p ./image/arch
rm -rf ./image/arch/*
cd ./image/arch
wget https://archive.archlinux.org/iso/2024.07.01/archlinux-bootstrap-x86_64.tar.zst
tar -I zstd -xvf archlinux-bootstrap-x86_64.tar.zst
rm archlinux-bootstrap-x86_64.tar.zst
