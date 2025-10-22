all:
	clang -Isrc/include -Isrc/include_image -Icanvas/headers -Lsrc/lib -Lsrc/lib_image canvas/canvas.c canvas/pencil_tools.c canvas/line_tool.c -lSDL3 -o canvas.exe
