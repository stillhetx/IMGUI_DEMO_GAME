cflag= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
cc=g++ -I src/include -L src/lib
imguiFile=imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp imgui_impl_sdl2.cpp imgui_impl_sdlrenderer2.cpp

all:
	$(cc) *.o -o main main.cpp $(cflag)

imgui:
	$(cc) -c $(imguiFile) $(cflag)
