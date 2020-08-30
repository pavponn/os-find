# 🔍 Find
[![MIT license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/pavponn/os-find/blob/master/LICENSE)

Find is an utility to search for specific files on your computer written in C++.
This is an educational project, aimed at understanding how to interact with POSIX API to retrieve file information.

## Main Features
* Filter by name, size ranges, inodes and link counts
* Print results
* Pass results to executable

## Usage 
`find <path> <args..>` - locate specifiс files in the provided path

### Supported arguments:
* `-name   <name>`      - filter by filename equals `<name>`
* `-inum   <number>`    - filter by inode number equals `<number>`
* `-size   <[-=+]size>` - filter by size (*less, equal* or *more*)
* `-nlinks <number>`    - hardlink count equals `<num>`
* `exec   <executable>` - pass located files to executable file `<executable>`

## Build
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
Requires C++14 compiler

## Test
Tested manually on macOS Mojave 10.14.3 and Linux 4.12.

## Copyright
Pavel Ponomarev, 2019 (pavponn@gmail.com)

MIT License.
