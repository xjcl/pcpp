// parts of this file have been copied from https://github.com/Twinklebear/TwinklebearDev-Lessons
// title is not determined yet, so "oss" is used as substitute
#include <iostream> // load basic input/output
#include <SDL2/SDL.h> // load simple directmedia layer 2
#include <SDL2/SDL_image.h> // load sdl2 image library
//#include "chart.h" // i have no idea how to include files. do i have to change the makefile?

const int SCREEN_WIDTH = 1280;//640;
const int SCREEN_HEIGHT = 720;//480;




















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
        double x, xold, y, yold, w, h, vx, vxmax, vy, vymax, ac, in_air;
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
    vx = 0;
    vxmax = 6;
    vy = 0;
    vymax = 18;
    ac = 1;
    //in_air is covered by the jump variable
    //of the main loop at the moment
    in_air = 0;
}

int Chart::update () {
    return 0;
}










class Block
{
    public:
        double x, y, w, h;
        Block(int, int, int, int);
        //void set_values (int, int);
        //int get_x (); etc.
        int update ();
};


Block::Block(int a, int b, int c, int d)
{
    x = a;
    y = b;
    w = c;
    h = d;
}

int Block::update () {
    return 0;
}









































































































int main(int argc, char** argv){
        //Start up SDL and make sure it went ok
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){logSDLError(std::cout, "SDL_Init");return 1;}

        //Setup our window and renderer
        SDL_Window *window = SDL_CreateWindow("Oss", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr){logSDLError(std::cout, "CreateWindow");return 2;}
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr){logSDLError(std::cout, "CreateRenderer");return 3;}

        //The textures we'll be using
        SDL_Texture *background = loadTexture("sprites/background.png", renderer);
        SDL_Texture *background_small = loadTexture("sprites/background_charsized.png", renderer);
        SDL_Texture *planet_bg = loadTexture("sprites/planet_bg_blurry.png", renderer);
        //SDL_Texture *cr = loadTexture("sprites/char_right.png", renderer);
        //SDL_Texture *cl = loadTexture("sprites/char_left.png", renderer);
        SDL_Texture *cr = loadTexture("sprites/char_right_small.png", renderer);
        SDL_Texture *cl = loadTexture("sprites/char_left_small.png", renderer);
        SDL_Texture *c_shadow = loadTexture("sprites/char_right_small_mask.png", renderer);
        SDL_Texture *white_block = loadTexture("sprites/white_block.png", renderer);
        SDL_Texture *cimg = cr; // start of facing the right side
        
        //Make sure they both loaded ok
        if (background == nullptr || cr == nullptr || white_block == nullptr || c_shadow == nullptr ||
            cl == nullptr || background_small == nullptr)return 4;

        //Clear the window
        SDL_RenderClear(renderer);






        //create character
        int chart_width = 14;
        int chart_height = 14;
        Chart c(1000, 0, chart_width, chart_height);
        //create blocks
        Block bl_left_bnd(-1, -100, 1, SCREEN_HEIGHT+200);
        Block bl_right_bnd(SCREEN_WIDTH, -100, 1, SCREEN_HEIGHT+200);
        Block bl_start1(-10, SCREEN_HEIGHT-60, 240, 60);
        Block bl_start2(300, SCREEN_HEIGHT-60, SCREEN_WIDTH-300+10, 60);
        Block bl0(-100, -1, SCREEN_WIDTH+200, 1);
        Block bl00(0, -100, 100, SCREEN_HEIGHT+200);
        Block bl1(0, 540, 700, 600);
        Block bl2(920, 200, 200, 200);
        Block bl3(1200, 200, 80, 100); 
        Block bl4(-100, 200, 200, 200);
        Block bl5(400, 80, 30, 400);
        Block bl000(SCREEN_WIDTH, -100, 1, SCREEN_HEIGHT+200);
        Block blocks0[] = {bl0, bl_left_bnd, bl_right_bnd, bl_start1, bl_start2};
        Block blocks1[] = {bl0, bl00, bl1, bl2, bl3};
        Block blocks2[] = {bl0, bl4, bl5};//, bl000};
        Block blocks3[] = {bl0};
        int block_nos[] = {5, 5, 3, 1};
        int no_of_screens = 4;
        //Block meta_blocks[][] = {blocks, blocks2}; // sigh. stupid c++. i hate you.

        //used to temporarily store events into
        SDL_Event e;
        
        bool quit = false;
        int i = 0;
        int jump = 1;
        int curr_screen = 0; // 0 = start screen on top? TODO
        int on_a_block = -1;
        int on_a_wall = -1;
        int on_a_wall_side = 0;
        double dx = 0;
        bool up_held = false;
        bool right_held = false;
        bool left_held = false;
        // "fuckslide" value determines how much of the char
        // have to be over a ledge for him to fall / not hang on to
        // 1 = looks like char is hovering
        // 0.75 = you can fall through blocks
        // TODO: solution: have an extra check for if_inside_block
        double fuckslide = 1;
        
        
        while (!quit)
        {
            /*std::cout << i << std::endl;
            std::cout << c.x << std::endl;
            std::cout << c.y << std::endl;
            std::cout << c.vx << std::endl;
            std::cout << c.vy << std::endl;*/
            
            //clear the screen, init some variables
            SDL_RenderClear(renderer);
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
                                //nothing to do here
                                //TODO maybe c.a*=2?
                                //but I don't see how
                                //this could be any fun
                                break;
                            case SDLK_r:
                                //TODO  reset timer etc.
                                c.x = 1000;
                                c.y = 0;
                                c.vx = 0;
                                c.vy = 0;
                                c.xold = 20;
                                c.yold = 0;
                                jump = 1;
                                on_a_block = -1;
                                on_a_wall = -1;
                                on_a_wall_side = 0;
                                curr_screen = 0;
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
                                // later
                                up_held = false;
                                break;
                            case SDLK_DOWN:
                                // nothing for now
                                break;
                            default:
                                break;
                        }
                        break;
                
                    
                        
                       
                       
                       
                        
                        
                    } // closing switchevent
             
            } // closing while pollevent
            
            
            
            
            
            






            
            //ADJUST CHART (=CHARACTER) VARIABLES
            
            //x-axis
            
                // TODO while hitting block from below and having hold left and right and then
                //   releasing left you don't go right (after wall jump)
                
                
            if (on_a_wall == -1)
            {
                dx = 0.8;
                if (left_held == true)
                {
                    //TODO you can't change direction that fast
                    // if you are jump!=0-ing
                    dx = 1;
                    cimg = cl;
                    //c.vx = -c.vxmax;
                    if (c.vx > -c.vxmax)
                        c.vx -= c.ac;
                    else c.vx = -c.vxmax;
                }
                else if (right_held == true)
                {
                    dx = 1;
                    cimg = cr;
                    //c.vx = c.vxmax;
                    if (c.vx < c.vxmax)
                        c.vx += c.ac;
                    else c.vx = c.vxmax;
                }
                c.vx = dx*c.vx;
                c.x += c.vx;
            }
            
            
            
            //y-axis
            //falling:
            if (jump != 0)
            { 
                if (on_a_wall == -1)
                {
                    c.vy += c.ac;
                    c.y += c.vy;
                }
            }
            //jump:
            if ((jump == 0) and (up_held == true))
            {
                std::cout << "keyup jump = 0" << std::endl; 
                c.vy = -c.vymax; 
                on_a_block = -1;
                jump = 1;
            }
            //double jump:
            if ((jump == 1) and (up_held == true) and (c.vy > 0))
            {
                std::cout << "keyup jump = 1" << std::endl; 
                c.vy = -3*c.vymax/4;
                jump = 2;
            }
            /*std::cout << jump << std::endl;
            std::cout << c.ac << std::endl;
            std::cout << c.vy << std::endl;
            std::cout << c.y << std::endl;*/
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            //IS BEHIND SCREEN? LOAD NEXT SCREEN
            
            // TODO I only have one screen at the moment
            // use either array or a custom queue class for listing all blocks
            // and in that process, replace with absolute values
            // e.g. 100 on screen 2 -> 900 (also in loading below)
            
            
            
            
            
            
            
            
            
            
            
            
            
           
           
            
            //DETECT COLLISIONS
            
            Block *f;
            
            //TODO it currently only works if blocks align from screen to screen
            // also collision-detect left and right so you can fall into other screen
            if (curr_screen == 0) f = blocks0;
            if (curr_screen == 1) f = blocks1;
            if (curr_screen == 2) f = blocks2;
            if (curr_screen == 3) f = blocks3;
            
            //TODO sizeof f is ALWAYS 4.
            for (int j=0; j<block_nos[curr_screen]; j++)
            {
                Block bl = f[j];
                /*std::cout << c.y << std::endl;
                std::cout << c.vy << std::endl;
                std::cout << c.yold << std::endl;
                std::cout << bl.y << std::endl;*/
                
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
                        c.y = bl.y+bl.h+1;
                        std::cout << "bonk" << std::endl; 
                    }   
                } 
                
                
                
                
                
                
                // keep to / hang on a ledge
                // TODO and enable wall jumps
                
                // if sliding into a wall from the left
                if ((c.x+c.w >= bl.x) and (c.xold+c.w < bl.x))
                {
                    // check height
                    if ((c.y+fuckslide*c.h > bl.y) and (c.y+(1-fuckslide)*c.h < bl.y+bl.h))
                    {
                        c.x = bl.x - c.w;
                        c.vx = 0;
                        c.vy = 0;
                        on_a_wall = j;
                        on_a_wall_side = 1; //1 = left, 2 = right
                        std::cout << "wuff" << std::endl; 
                    }   
                } 
                
                
                if ((on_a_wall != -1) and (on_a_wall_side == 1) and (right_held != true))
                {
                    jump = 2;
                    on_a_wall = -1;
                    on_a_wall_side = -1;
                    //left_held = false; // needed so that it doesn't move
                        // left eternally (see c.vx = -c.vxmax;)
                    if (up_held == true)
                    {
                        c.x -= 1;
                        c.vx = -c.vxmax;
                        c.vy = -3.0/4.0*c.vymax;
                        std::cout << "wuff jump" << std::endl; 
                    }
                    else
                    {
                        c.x -= 1;
                        c.y -= 1;
                        std::cout << "wuff fall" << std::endl; 
                    }
                
                
                }
                
                
                
                // same from the right
                if ((c.x <= bl.x + bl.w) and (c.xold > bl.x + bl.w))
                {
                    // check height //TODO is this the correct height?
                    if ((c.y+fuckslide*c.h > bl.y) and (c.y+(1-fuckslide)*c.h < bl.y+bl.h))
                    {
                        c.x = bl.x + bl.w;
                        c.vx = 0;
                        c.vy = 0;
                        on_a_wall = j;
                        on_a_wall_side = 2; //1 = left, 2 = right
                        std::cout << "wuff" << std::endl; 
                    }   
                } 
                
                
                if ((on_a_wall != -1) and (on_a_wall_side == 2) and (left_held != true))
                {
                    jump = 2;
                    on_a_wall = -1;
                    on_a_wall_side = -1;
                    right_held = false;
                    if (up_held == true)
                    {
                        c.x += 1;
                        c.vx = c.vxmax;
                        c.vy = -3.0/4.0*c.vymax;
                        std::cout << "wuff jump" << std::endl; 
                    }
                    else
                    {
                        c.x += 1;
                        c.y -= 1;
                        std::cout << "wuff fall" << std::endl; 
                    }
                
                
                }
                
               
               
                // fall off a ledge
                // if on block (y)
                if (on_a_block == j)
                {
                    // if left or right of block
                    if ((c.x+fuckslide*c.w < bl.x) or (c.x+(1-fuckslide)*c.w > bl.x+bl.w))
                    {
                        // and if on block the frame before
                        if ((c.xold+fuckslide*c.w >= bl.x) and (c.xold+(1-fuckslide)*c.w <= bl.x+bl.w))
                        {
                            //fall off a ledge
                            //if was on ledge the screen before
                            std::cout << "fall off ledge" << std::endl;
                            jump = 1;
                            on_a_block = -1;
                        }
                    }
                }
                
            } // end block-char interaction
            
            
            
            
            
            // check if died (bottom of screen) and then respawn
            // top of screen is handled by extra block!
            if (c.y > SCREEN_HEIGHT)
            {
                if (curr_screen != 0)
                {
                    c.x = 60;
                    c.y = 0;
                    c.xold = 60;
                    c.yold = 0;
                    jump = 2;
                    c.vx = 0;
                    c.vy = 0;
                    on_a_block = -1;
                    on_a_wall = -1;
                    on_a_wall_side = -1;
                }
                if (curr_screen == 1) // single exception to rule
                {
                    c.x = 120;
                    c.xold = 120;
                }
                if (curr_screen == 0)
                {
                    curr_screen = 1;
                    c.y -= SCREEN_HEIGHT;
                    c.yold -= SCREEN_HEIGHT;
                }
                
            }
            
            
            
            
            
            
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
            
            
            
            
            
            
            
            
            


            //RENDER SCENE
            //don't redraw entire background, just bit where char just was
            //doesn't work
            //renderTexture(background_small, renderer, c.xold, c.yold, c.w, c.h);
            
            //Block *bl = nullptr;
            Block *blo;
            if (curr_screen == 0)
            {
                blo = blocks0;//{};
                renderTexture(planet_bg, renderer, 0, 0);
                renderTexture(c_shadow, renderer, c.x-3, c.y-3);
            }
            else
            {
                renderTexture(background, renderer, 0, 0);
                renderTexture(c_shadow, renderer, c.x-3, c.y-3);
            }
            if (curr_screen == 1) blo = blocks1;
            if (curr_screen == 2) blo = blocks2;
            if (curr_screen == 3) blo = blocks3;
            for (int j=0; j<block_nos[curr_screen]; j++)
            {
                Block blop = blo[j];
                renderTexture(white_block, renderer, blop.x, blop.y, blop.w, blop.h);
            }
            renderTexture(cimg, renderer, c.x, c.y);
            SDL_RenderPresent(renderer);
            SDL_Delay(10); //20 in debug, 10~15 in game
            //TODO add timer, so that it isnt =20ms+executiondelay, but =20ms
            
            i += 1;
        }









        //Destroy the various items
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(background_small);
        SDL_DestroyTexture(planet_bg);
        SDL_DestroyTexture(cr);
        SDL_DestroyTexture(cl);
        SDL_DestroyTexture(c_shadow);
        SDL_DestroyTexture(white_block);
        //TODO update destroyer
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
        IMG_Quit();
        
        return 0;
}
