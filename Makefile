# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Executable name
TARGET = http-server

# Installation directory
PREFIX = $(HOME)/bin

# Source files
SRCS = server.c utils/error.c utils/mime.c http-server.c

# Header files (for dependencies)
HDRS = http-server.h server.h utils/error.h utils/mime.h

# Object files
OBJS = $(SRCS:.c=.o)

# Rule to compile source files into object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to set http-server command for zsh for current user
set_global_zsh: $(TARGET)
	mkdir -p $(PREFIX)
	mv $(TARGET) $(PREFIX)
	chmod +x $(PREFIX)/$(TARGET)
	touch ~/.zshrc 
	grep -qxF 'export PATH=$(PREFIX):$$PATH' ~/.zshrc || echo 'export PATH=$(PREFIX):$$PATH' >> ~/.zshrc
	source ~/.zshrc 
	echo "Installed $(TARGET) to $(PREFIX) and added to PATH. Please run 'source ~/.zshrc' to update your PATH in the current shell session."

# Rule for full install in zsh
install: $(TARGET) set_global_zsh clean

# Declare 'clean' as a phony target to prevent conflicts with files of the same name
.PHONY: clean install
