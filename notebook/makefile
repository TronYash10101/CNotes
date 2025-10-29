CC = clang
CFLAGS = -I D:/CNotes/src/include \
         -I D:/CNotes/src/include_image \
         -I D:/CNotes/src/include_ttf \
	 -I D:/CNotes/src/gtk \
         -I D:/CNotes/notebook/headers
LDFLAGS = -L D:/CNotes/src/lib \
          -L D:/CNotes/src/lib_image \
          -L D:/CNotes/src/lib_ttf \
          -lSDL3 -lSDL3_image -lSDL3_ttf

all:
	$(CC) $(CFLAGS) typing.c notebook.c  $(LDFLAGS) -o notebook.exe

