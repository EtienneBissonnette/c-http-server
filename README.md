# HTTP Server

This project implements a basic HTTP server in C. The server is designed to serve static files from the current directory where the executable is launched, providing index.html entry point is present. Can be extended to handle dynamic content and other HTTP methods if necessary.

## Features

- Serve static files (HTML, CSS, JavaScript, images, etc.)
- Basic MIME type detection
- Simple installation script for user scope execution using zsh
- Easily extendable to handle dynamic content and other features

## Requirements

- A C compiler (e.g., `clang` or `gcc`), may need to modify Makefile CC variable for `gcc`
- `make` utility

## Installation

### Compile the Project

To compile the project, simply run:

```sh
make
```

This will generate the http-server executable.

### Cleanup

To remove the compiled object files and executable, run:

```sh
make clean
```

### Install as global cmd (zsh)

To install executable and access anywhere in zsh session, simply run:

```sh
make install
```

You can now execute http-server anywhere without placing executable in target distribution folder.
[!NOTE]
Either close current shell session or run to access command:

```sh
source ~/zshrc
```

## Usage

You can place the compiled executable in the target distribution folder where you want to serve your static files.
[!NOTE]
Please ensure to have index.html entry point in the distribution folder.

```sh
./http-server
```

Otherwise, if you installed the command globally via zsh, you can simply run without placing executable in distribution folder:

```sh
http-server
```

By default, the server will run on port 8080 and serve files from the current directory.
