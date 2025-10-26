CC = clang
CFLAGS = -I D:/CNotes/src/include \
         -I D:/CNotes/src/include_image \
         -I D:/CNotes/src/include_ttf
LDFLAGS = -L D:/CNotes/src/lib \
          -L D:/CNotes/src/lib_image \
          -L D:/CNotes/src/lib_ttf \
          -lSDL3 -lSDL3_image -lSDL3_ttf

all:
	$(CC) $(CFLAGS) notebook.c $(LDFLAGS) -o notebook.exe

