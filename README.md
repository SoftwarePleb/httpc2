#  Http2

A simple HTTP server written in c. Not production ready, just for fun.

## Description

This application allows you to serve http files from a given directory.

## Table of Contents

1. [Description](#description)
2. [Getting Started](#getting-started)
3. [Usage](#usage)
4. [Supported File Types](#supported-file-types)

### Prerequisites

Ensure you at least CMake version 3.27 installed. 

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

clone the git repo:
`git clone https://github.com/SoftwarePleb/httpc2.git`

navigate to the project directory:
`cd httpc2`

create the binary:
`cmake .`

run the project:
`./http 5001 ../DemoHTML/`

browse to index.html in your browser:
http://localhost:5001/index.html

### Usage

`http [port] [directory]`

where port is the port number you want to listen from and directory is the directory you wish to serve files from.

for example:

`http 5001 /source/SimonSays/`

Listens to http://localhost:5001 and servers files from the SimonSays directory.

### Supported File Types

A list of currently supported file types:

* html
* js
* css
* jpg
* mp3
