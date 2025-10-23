all:
	clang -c canvas.c -o canvas.o -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/canvas/headers
	clang -c -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/canvas/headers D:/CNotes/canvas/Tools/pen_tool.c -o pen_tool.o
	clang -c -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/canvas/headers D:/CNotes/canvas/Tools/line_tool.c -o line_tool.o
	clang -c -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/canvas/headers D:/CNotes/canvas/UI/tools_panel.c -o tools_panel.o
	clang -c -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/canvas/headers D:/CNotes/canvas/UI/button.c -o button.o

	clang canvas.o pen_tool.o line_tool.o button.o tools_panel.o \
	      -LD:/CNotes/src/lib \
	      -LD:/CNotes/src/lib_image \
	      -lSDL3 \
	      -lSDL3_image \
	      -o canvas.exe
