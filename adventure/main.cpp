// parts of this file have been copied from https://github.com/Twinklebear/TwinklebearDev-Lessons
// title is not determined yet, so "adventure" is used as substitute
#include <iostream> // load basic input/output
#include <SDL2/SDL.h> // load simple directmedia layer 2
#include <SDL2/SDL_image.h> // load sdl2 image library

const int SCREEN_WIDTH = 256; // 768
const int SCREEN_HEIGHT = 224; // 720

const int scr_dispos = 16*3; //screen disposition. describes space
                                 // reserved by item/menu screen bit



















/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
        os << msg << " error: " << SDL_GetError() << std::endl;
}





/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
        SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
        if (texture == nullptr)                
                logSDLError(std::cout, "LoadTexture");
        return texture;
}


/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
* width and height
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param w The width of the texture to draw
* @param h The height of the texture to draw
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
        //Setup the destination rectangle to be at the position we want
        SDL_Rect dst;
        dst.x = x;
        dst.y = y;
        dst.w = w;
        dst.h = h;
        SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
        int w, h;
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        renderTexture(tex, ren, x, y, w, h);
}













































































class Chart
{
    public:
        double x, xold, y, yold, w, h, vx, vy;
        Chart(int, int, int, int);
        //void set_values (int, int);
        //int get_x (); etc.
        int update ();
};


Chart::Chart(int a, int b, int c, int d)
{
    x = a;
    xold = a;
    y = b;
    yold = b;
    w = c;
    h = d;
    vx = 3;
    vy = 3;
}

int Chart::update () {
    return 0;
}











/*
TODO
class Block
{
    public:
        double x, y, w, h, coll;
        Block(int, int, int, int);
        //void set_values (int, int);
        //int get_x (); etc.
        int update ();
};


Block::Block(int a, int b, int c, int d, int coll, int sprite)
{
    x = a;
    y = b;
    w = c;
    h = d;
    c = coll;
    s = sprite;
    // 0 = no collision
    // 1 = collision (rock)
    // 2 = collision, can be destroyed by sword
}

int Block::update () {
    return 0;
}
*/








































































































int main(int argc, char** argv){
        //Start up SDL and make sure it went ok
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){logSDLError(std::cout, "SDL_Init");return 1;}

        //Setup our window and renderer
        SDL_Window *window = SDL_CreateWindow("Oss", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr){logSDLError(std::cout, "CreateWindow");return 2;}
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr){logSDLError(std::cout, "CreateRenderer");return 3;}

        //The textures we'll be using
        //SDL_Texture *background = loadTexture("sprites/background.png", renderer);
        SDL_Texture *cr = loadTexture("sprites/char_right.png", renderer);
        SDL_Texture *cl = loadTexture("sprites/char_left.png", renderer);
        SDL_Texture *cu = loadTexture("sprites/char_up.png", renderer);
        SDL_Texture *cd = loadTexture("sprites/char_down.png", renderer);
        SDL_Texture *tground = loadTexture("sprites/ground.png", renderer);
        SDL_Texture *trock = loadTexture("sprites/rock.png", renderer);
        //SDL_Texture *ttree = loadTexture("sprites/tree.png", renderer);
        SDL_Texture *cimg = cr; // start of facing the right side

        if (tground == nullptr || trock == nullptr || cl == nullptr || cr == nullptr
             || cu == nullptr || cd == nullptr)return 4;
            
        //Clear the window
        SDL_RenderClear(renderer);






        //create character
        //Chart c(100, 0, 16, 16); // extreme slowdown for utterly arbitrary reason (100%16!=0?)
        Chart c(16, 16*5, 16, 16);
        //create blocks
        int a001[][16] = {{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}, // 16x11
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                          {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
                          
        int a002[][16] = {{1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}, // 16x11
                          {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                          {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                          {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                          {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                          {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                          {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}};
        //Screen s(3, 3, a001); //x, y, mask
        
        
        
        
        
        
        
        SDL_Event e;
        
        bool quit = false;
        int i = 0;
        int jump = 1;
        int curr_screen = 5050; // 0 = start screen on top? TODO
        int on_a_block = -1;
        int on_a_wall = -1;
        int on_a_wall_side = 0;
        double dx = 0;
        bool up_held = false;
        bool right_held = false;
        bool left_held = false;
        bool down_held = false;
        // "fuckslide" value determines how much of the char
        // have to be over a ledge for him to fall / not hang on to
        // 1 = looks like char is hovering
        // 0.75 = you can fall through blocks
        // TODO: solution: have an extra check for if_inside_block
        double fuckslide = 1;
        
        
        while (!quit)        {
            /*std::cout << i << std::endl;
            std::cout << c.x << std::endl;
            std::cout << c.y << std::endl;
            std::cout << c.vx << std::endl;
            std::cout << c.vy << std::endl;*/
            
            //clear the screen, init some variables
            SDL_RenderClear(renderer);
            
            
            if (c.x > SCREEN_WIDTH)
            {
                curr_screen += 1; 
                c.x = 0;                            
            }
            else if (c.x < SCREEN_WIDTH)
            {
                curr_screen -= 1;  
                c.x = SCREEN_WIDTH - c.w;
            }
            else if (c.y > SCREEN_HEIGHT)
            {
                curr_screen += 100; 
                c.y = scr_dispos;                            
            }
            else if (c.y < scr_dispos)
            {
                curr_screen -= 100;  
                c.y = SCREEN_HEIGHT - c.h;
            }
            
            c.yold = c.y;
            c.xold = c.x;
            
            
            
            //CHECK INPUT
            //this while-loop checks for new events that
            //  happened in the last 20ms (see bottom)
            //read in an event, do something, then repeat
            while( SDL_PollEvent( &e ) ){
            
                switch( e.type ){
                
                    //If user closes the window
                    case SDL_QUIT:
                        quit = true;
                        break;
                           
                    /* Look for a keypress */
                    case SDL_KEYDOWN:
                        switch( e.key.keysym.sym ){
                            case SDLK_LEFT:
                                left_held = true;
                                break;
                            case SDLK_RIGHT:
                                right_held = true;
                                break;
                            case SDLK_UP:
                                up_held = true;
                                break;
                            case SDLK_DOWN:
                                down_held = true;
                                break;
                            case SDLK_r:
                                //TODO reset
                                //TODO save states
                                break;
                            case SDLK_x:
                                quit = true;
                                break;
                            default:
                                break;
                        };
                        break;
                    
                    
                    
                    
                    
                    case SDL_KEYUP:
                        switch( e.key.keysym.sym ){
                            case SDLK_LEFT:
                                left_held = false;
                                break;
                            case SDLK_RIGHT:
                                right_held = false;
                                break;
                            case SDLK_UP:
                                up_held = false;
                                break;
                            case SDLK_DOWN:
                                down_held = false;
                                break;
                            default:
                                break;
                        }
                        break;
                
                    
                        
                       
                       
                       
                        
                        
                    } // closing switchevent
             
            } // closing while pollevent
            
            
            
            
            
            






            
            //ADJUST CHART (=CHARACTER) VARIABLES
            
            //x-axis
            if (1)
            {
                if ((left_held == true) and (c.x < c.xold))
                {
                    c.x -= c.vx;
                }
                else if ((right_held == true) and (c.x > c.xold))
                {
                    c.x += c.vx;
                }
                else if ((down_held == true) and (c.y > c.yold))
                {
                    c.y += c.vy;
                }
                else if ((up_held == true) and (c.y < c.yold))
                {
                    c.y -= c.vy;
                }
                else
                {
                
                        if ((left_held == true))
                        {
                            cimg = cl;
                            c.x -= c.vx;
                        }
                        else if ((right_held == true))
                        {
                            cimg = cr;
                            c.x += c.vx;
                        }
                        else if ((down_held == true))
                        {
                            cimg = cd;
                            c.y += c.vy;
                        }
                        else if ((up_held == true))
                        {
                            cimg = cu;
                            c.y -= c.vy;
                        }
                
                }
            }
            
            
            
            
            
            
            
            //IS BEHIND SCREEN? LOAD NEXT SCREEN
            
            // TODO I only have one screen at the moment
            // use either array or a custom queue class for listing all blocks
            // and in that process, replace with absolute values
            // e.g. 100 on screen 2 -> 900 (also in loading below)
            
            
            
            
            
            
            
            
            
            
            
            
            
           
           
            
            //DETECT COLLISIONS
            
            
            
            
            
            //PROTOTYPE here:
            
            
            for (int j=0; j<11; j++)
            {
                for (int l=0; l<16; l++)
                {
                    if (curr_screen == 5050) int lint = a001[j][l];
                    if (curr_screen == 5051) int lint = a002[j][l];
                    if (lint == 1)
                    {
                        int lx = 16*l;
                        int ly = scr_dispos+16*j;
                        int lw = 16;
                        int lh = 16;
                        
                        if ((c.y < ly+lh) and (c.y+c.h > ly))
                        {
                                //std::cout << "bump 0" << std::endl;
                            if ((c.x < lx+lw) and (c.xold >= lx+lw))
                            {
                               c.x = lx+lw; // from left
                                std::cout << "bump 1" << std::endl;
                            }
                            else if ((c.x+c.w > lx) and (c.xold+c.w <= lx))
                            {
                               c.x = lx-c.w; // from right
                                std::cout << "bump 2" << std::endl;
                            }
                        }
                        if ((c.x < lx+lw) and (c.x+c.w > lx)) //CAREFUL! not an else!
                        {
                            if ((c.y < ly+lh) and (c.yold >= ly+lh))
                            {
                               c.y = ly+lh; // from bottom
                                std::cout << "bump 3" << std::endl;
                            }
                            else if ((c.y+c.h > ly) and (c.yold+c.h <= ly))
                            {
                               c.y = ly-c.h; // from top
                                std::cout << "bump 4" << std::endl;
                            }
                        }
                    }
                }
            }
            
            
            
            
            
            
            
            //Block *f;
            
            //TODO it currently only works if blocks align from screen to screen
            // also collision-detect left and right so you can fall into other screen
            //if (curr_screen == 1) f = blocks1;
            //if (curr_screen == 2) f = blocks2;
            //if (curr_screen == 3) f = blocks3;
            
            
            /*Screen *s
            
            for (int j=0; j<screens[curr_screen]; j++)
            {
            
            
            
                Block bl = f[j];*/
                /*std::cout << c.y << std::endl;
                std::cout << c.vy << std::endl;
                std::cout << c.yold << std::endl;
                std::cout << bl.y << std::endl;*/
            
            
            
            
            /*    
                // land safely on block
                // if in_or_on_block and above_block_before
                if ((c.y+c.h >= bl.y) and (c.yold+c.h < bl.y))
                {
                    // if not_left and not_right of block
                    if ((c.x+fuckslide*c.w > bl.x) and (c.x+(1-fuckslide)*c.w < bl.x+bl.w))
                    {
                        c.y = bl.y - c.h;
                        c.vy = 0;
                        jump = 0;
                        on_a_block = j;
                        std::cout << "hust" << std::endl; 
                    }   
                } 
                
                
                
                
                // hit block from below
                // TODO have oss contract a little bit so it looks more "natural"
                if ((c.y < bl.y+bl.h) and (c.yold >= bl.y+bl.h))
                {
                    // if not_left and not_right of block
                    if ((c.x+fuckslide*c.w > bl.x) and (c.x+(1-fuckslide)*c.w < bl.x+bl.w))
                    {
                        c.y = bl.y+bl.h;
                        std::cout << "bonk" << std::endl; 
                    }   
                } 
                
            } // end block-char interaction
            
            
            
            
            // TODO block-hitbox (sword, boomerang?, etc.)
            

            
            
            
            
            
            
            
            // scrolling TODO
            // TODO disable vollbild / stretching the window in any way!
            if (c.x > SCREEN_WIDTH)
            {
                if ((curr_screen > 0) and (curr_screen < no_of_screens-1) and (c.vx > 0))
                {
                    curr_screen += 1;
                    c.x = 0;
                    c.y -= 1; // so it collision detects
                    jump = 2;
                    on_a_block = -1;
                    on_a_wall = -1;
                    on_a_wall_side = -1;
                    std::cout << "scrollin'" << std::endl;
                }
            }
            else if ((c.x+c.w < 0) and (c.vx < 0))
            {
                if (curr_screen > 1)
                {
                    std::cout << curr_screen << std::endl;
                    curr_screen -= 1;
                    std::cout << curr_screen << std::endl;
                    c.x = SCREEN_WIDTH-c.w;
                    c.y -= 1; // so it collision detects
                    jump = 2;
                    on_a_block = -1;
                    on_a_wall = -1;
                    on_a_wall_side = -1;
                    std::cout << "nooooo" << std::endl;
                }
            }
            
            
            */
            
            
            
            
            
            


            //RENDER SCENE
            
            //don't redraw entire background, just bit where char just was? TODO
            
            //renderTexture(background_small, renderer, c.xold, c.yold, c.w, c.h);
            //renderTexture(background, renderer, 0, 0);
            
            //Block *bl = nullptr;
            //Block *blo;
            //if (curr_screen == 1) blo = blocks1;
            //if (curr_screen == 2) blo = blocks2;
            //if (curr_screen == 3) blo = blocks3;
            for (int j=0; j<11; j++)
            {
                for (int l=0; l<16; l++)
                {
                    if (curr_screen == 5050) int lint = a001[j][l];
                    if (curr_screen == 5051) int lint = a002[j][l];
                    if (lint == 0)
                        renderTexture(tground, renderer, 16*l, scr_dispos+16*j, 16, 16);
                    if (lint == 1)
                        renderTexture(trock, renderer, 16*l, scr_dispos+16*j, 16, 16);
                }
            }
            renderTexture(cimg, renderer, c.x, c.y);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000.0/24.0);
            //TODO add timer, so that it isnt =20ms+executiondelay, but =20ms
            
            i += 1;
                                std::cout << i << std::endl;
        }





        //Destroy the various items
        SDL_DestroyTexture(cu);
        SDL_DestroyTexture(cd);
        SDL_DestroyTexture(cr);
        SDL_DestroyTexture(cl);
        SDL_DestroyTexture(trock);
        SDL_DestroyTexture(tground);
        //TODO update destroyer
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
        IMG_Quit();


        return 0;
}
