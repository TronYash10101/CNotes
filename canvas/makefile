all:
	clang -c canvas.c -o canvas.o -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/src/include_ttf -ID:/CNotes/canvas/headers -ID:/CNotes/src/include_nuklear
	clang -c -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/canvas/headers D:/CNotes/canvas/Tools/pen_tool.c -I D:/CNotes/src/gtk -I D:/CNotes/src/gtk/css -o pen_tool.o
	clang -c -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/canvas/headers D:/CNotes/canvas/Tools/line_tool.c -I D:/CNotes/src/gtk -I D:/CNotes/src/gtk/css -o line_tool.o
	clang -c -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/canvas/headers D:/CNotes/canvas/UI/tools_panel.c -I D:/CNotes/src/gtk -I D:/CNotes/src/gtk/css -o tools_panel.o
	clang -c -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/canvas/headers D:/CNotes/canvas/UI/button.c -I D:/CNotes/src/gtk -I D:/CNotes/src/gtk/css -o button.o
	clang -c -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/canvas/headers D:/CNotes/canvas/Tools/eraser_tool.c -I D:/CNotes/src/gtk -I D:/CNotes/src/gtk/css -o eraser_tool.o
	clang -c -ID:/CNotes/src/include -ID:/CNotes/src/include_image -ID:/CNotes/canvas/headers D:/CNotes/canvas/Tools/rectangle_tool.c -I D:/CNotes/src/gtk -I D:/CNotes/src/gtk/css -o rectangle_tool.o

	clang canvas.o pen_tool.o line_tool.o button.o tools_panel.o eraser_tool.o rectangle_tool.o\
	      -LD:/CNotes/src/lib \
	      -LD:/CNotes/src/lib_image \
	      -LD:/CNotes/src/lib_ttf \
	      -lSDL3 \
	      -lSDL3_image \
	      -lSDL3_ttf \
	      -o canvas.exe
