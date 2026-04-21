#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_IMAGE.h>
#include <SDL2/SDL_ttf.h>
//#include "src/include/SDL2/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"


const int WIDTH = 800, HEIGHT = 800, GRID = 8;

float playerMarc = 2000;

int playerX =20;
int playerY =20;

float speed=8;

SDL_Window *window ;
SDL_Renderer *renderer; 
SDL_Texture *texture;
SDL_Texture *textu;
SDL_Texture* textFont;


SDL_Window* windowUI;
SDL_Renderer* rendererUI;

TTF_Font* gFont;


float spriteX=301;
float spriteY=0;
int const wtile = WIDTH/GRID;
int const htile= HEIGHT/GRID;

bool foot = false;
int playerTimer=0;

            // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void renderSprite(int x, int y, int h, int w, int xi, int yi, int grid);

void animatedSpritePlayer();
void renderText(int x, int y, int h, int w);

void draw(){
    //Color de fondo
    SDL_SetRenderDrawColor(renderer, 210, 250, 210,255);
    SDL_RenderClear(renderer);
    //SDL_SetRenderDrawColor(renderer,0,0,255,255);

    renderText(10, 10, 200, 200);


    renderSprite(spriteX,spriteY,32,32,0+(3*32),0+(3*32),32);

    for(int i=0;i < htile;i++){
        for(int t=0;t < wtile;t++){
                renderSprite(0,0,32,32,0+(i*32),0+(t*32),32);
        }
    }

   //renderSprite(0,301,32,32,0,0,32);
   animatedSpritePlayer();
}

void renderText(int x, int y, int h, int w){
        SDL_Rect rectText;
        rectText.h=h;
        rectText.w=w;
        rectText.x=x;
        rectText.y=y;
        SDL_RenderCopy(renderer, textFont, NULL,&rectText);
} 

void update(){

}

void imguiDraw(){
             // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();   
    
    if (show_demo_window){
            ImGui::ShowDemoWindow(&show_demo_window);
    
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("Velocidad", &speed, 1, 20); 

            
            
            ImGui::InputFloat("Sprite X", &spriteX, 32, 2, 0);
            ImGui::InputFloat("Sprite y", &spriteY, 32, 2,0); 


            ImGui::SliderFloat("Velocidad de pasos", &playerMarc, 1000, 4000); 
                           // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

           // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
    }
        // 3. Show another simple window.
        if (show_another_window)
        {
            printf("show_another_window");
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }


        ImGui::Render();
        SDL_SetRenderDrawColor(rendererUI, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(rendererUI);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(rendererUI);
}

void animatedSpritePlayer(){
    
    playerTimer++;
    if(playerTimer>playerMarc){
        if(foot){
            foot=false;
        }else{
            foot=true;
        }
        playerTimer=0;
    }

    if(foot){
        renderSprite(0,301,32,32,playerX,playerY,32);
    }else{
        renderSprite(0,330,32,32,playerX,playerY,32);
    }

}

void renderSprite(int x, int y, int h, int w, int xi, int yi, int grid){

        SDL_Rect rectanculo;
        rectanculo.h=h;
        rectanculo.w=w;
        rectanculo.x=x;
        rectanculo.y=y;


        SDL_Rect rectDest;
        rectDest.h=grid;
        rectDest.w=grid;
        rectDest.x=xi;
        rectDest.y=yi;
        SDL_RenderCopy(renderer, textu, &rectanculo,&rectDest);
}

int main(int argc, char ** arg){ 
    std::cout << "Hello world";
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        fprintf(stderr, "FALLA");
        printf("ERROR INICIAR %s\n",SDL_GetError() );
        return 1;
    }
 

     window = SDL_CreateWindow("windows",
                        SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                        WIDTH,HEIGHT, SDL_WINDOW_SHOWN);

    if(!window){
        printf("ERROR VENTANA %s\n",SDL_GetError() );
        return 1;
    }                    

     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer){
        printf("ERROR RENDER %s\n",SDL_GetError() );
        return 1;
    }
    

    #ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    #endif

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    windowUI = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    rendererUI = SDL_CreateRenderer(windowUI, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    
    if (rendererUI == nullptr)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return 0;
    }

    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return 0;
    }

    gFont = TTF_OpenFont( "ARCADECLASSIC.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        return 0;
    }
    
    SDL_Surface* surfFont = TTF_RenderText_Solid(gFont, "Hola",{ 0, 0, 0 }); 
    textFont = SDL_CreateTextureFromSurface(renderer, surfFont);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavNoCaptureKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(windowUI, rendererUI);
    ImGui_ImplSDLRenderer2_Init(rendererUI);


    //Cargar Sprite sheet
    SDL_Surface *surfRect = IMG_Load("items.png");
    SDL_Color colors = surfRect->format->palette->colors[0];
    SDL_SetColorKey(surfRect,1,SDL_MapRGB(surfRect->format, colors.r, colors.g, colors.b));
    textu = SDL_CreateTextureFromSurface(renderer, surfRect);
    SDL_FreeSurface(surfRect);
    SDL_FreeSurface(surfFont);

    bool run= true;
    while(run){
        SDL_Event event;
        if (SDL_PollEvent(&event)){
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                run = false;
                break;
            case SDL_KEYDOWN:
                    if (SDLK_UP == event.key.keysym.sym){
                        playerY-=speed;
                    }
                    if (SDLK_DOWN == event.key.keysym.sym){
                        playerY+=speed;
                    }
                    if (SDLK_LEFT == event.key.keysym.sym){
                        playerX-=speed;
                    }
                    if (SDLK_RIGHT == event.key.keysym.sym){
                        playerX+=speed;
                    }
                break;
            case SDL_WINDOWEVENT:                
                if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(windowUI))
                    run = false;
                if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                    run = false;    
                break;               
            default:
                break;
            }
        }


        update();
        draw();
        imguiDraw();

        SDL_RenderPresent(renderer);
    }

    // Cleanup

    TTF_CloseFont(gFont);

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();    
    ImGui::DestroyContext();

    SDL_DestroyRenderer(rendererUI);
    SDL_DestroyWindow(windowUI);    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();                    
    
    return 0;
}