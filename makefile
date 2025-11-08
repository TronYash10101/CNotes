CC = clang

SOURCE_DIRS = D:/CNotes/notebook D:/CNotes/canvas D:/CNotes/canvas/Tools D:/CNotes/canvas/UI

SOURCE_FILES = CNotes.c \
               D:/CNotes/canvas/canvas.c \
               D:/CNotes/canvas/Tools/eraser_tool.c \
               D:/CNotes/canvas/Tools/line_tool.c \
               D:/CNotes/canvas/Tools/pen_tool.c \
               D:/CNotes/canvas/Tools/rectangle_tool.c \
               D:/CNotes/canvas/UI/button.c \
               D:/CNotes/canvas/UI/tools_panel.c \
               D:/CNotes/notebook/notebook.c \
               D:/CNotes/notebook/typing.c

INCLUDES = -I D:/CNotes/src/include \
           -I D:/CNotes/src/include_image \
           -I D:/CNotes/src/include_ttf \
           -I D:/CNotes/notebook/CNotes.h \
           -I D:/CNotes/canvas/headers \
           -I D:/CNotes/notebook/headers

LIBS = -L D:/CNotes/src/lib \
       -L D:/CNotes/src/lib_image \
       -L D:/CNotes/src/lib_ttf \
       -lSDL3 -lSDL3_image -lSDL3_ttf

all:
	$(CC) $(INCLUDES) $(SOURCE_FILES) $(LIBS) -o CNotes.exe
