#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <stdio.h>
#include <time.h>
#include <libpad.h>
#include <assert.h>
#include <gsKit.h>
#include <dmaKit.h>
#include <pad.h>
#include <audsrv.h>
#include <SDL2/SDL_mixer.h>
#include <malloc.h>
#include <appman.hpp>
#include <simple_gui.hpp>
#define BUFFER_SIZE 2048

void loadModules(void){
    int ret;

    ret = SifLoadModule("rom0:SIO2MAN", 0, NULL);
    if (ret < 0) {
        printf("sifLoadModule sio failed: %d\n", ret);
        SleepThread();
    }

    ret = SifLoadModule("rom0:PADMAN", 0, NULL);
    if (ret < 0) {
        printf("sifLoadModule pad failed: %d\n", ret);
        SleepThread();
    }
    ret = SifLoadModule("rom0:LIBSD", 0, NULL);
    if (ret < 0) {
        printf("sifLoadModule LIBSD failed: %d\n", ret);
        SleepThread();
    }

    ret = SifLoadModule("cdrom0:\\IRX\\AUDSRV.IRX;1", 0, NULL);
    if (ret < 0) {
        printf("sifLoadModule AUDSRV failed: %d\n", ret);
        SleepThread();
    }
    printf("ALL MODULES DONE\n");
}

void all_inits(){
    SifInitRpc(0);
    SifLoadFileInit();
    loadModules();
    padInit(0);
    audsrv_init();
    init_pad_port();
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3);
    printf("INITler UGURLU!\n");
}

void init_GS(){
    // Initialize the GS (Graphics Synthesizer) and set it to 720p
    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
		    D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    GSGLOBAL *gsGlobal = gsKit_init_global();
    gsGlobal->Mode = GS_MODE_DTV_720P;
    gsGlobal->Width = 1280;
    gsGlobal->Height = 720;
    gsGlobal->PSM = GS_PSM_CT32;
    gsGlobal->Interlace = GS_NONINTERLACED;
    gsGlobal->Field = GS_FRAME;
    gsGlobal->DoubleBuffering = GS_SETTING_OFF;
    gsGlobal->ZBuffering = GS_SETTING_OFF;
    

    gsKit_init_screen(gsGlobal);
    gsKit_mode_switch(gsGlobal, GS_ONESHOT);
}

int main(int argc, char *argv[]){
    all_inits();
    init_GS();
    SDL_Window* window = NULL;
    //SDL_Renderer* renderer = NULL;
    //SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);
    window = SDL_CreateWindow("PS2 SDL2 WINDOW",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN);
    Simple::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | 
                                        SDL_RENDERER_TARGETTEXTURE);

    
    Simple::font = TTF_OpenFont("FONT.OTF", 100);
    if(Simple::font == NULL) printf("Font load olmadi!\n");
    SDL_Color color = {255, 0, 0, 255};
    SDL_Surface* temp = TTF_RenderUTF8_Blended(Simple::font, "Azərbaycan!", color);
    SDL_Texture* textImage = SDL_CreateTextureFromSurface(Simple::renderer, temp);
    SDL_Rect pos = {320 - 100 + 20, 240 - 50, 240, 100};
    SDL_FreeSurface(temp);

    SDL_Rect rect;
    rect.h = 100;
    rect.w = 400;
    rect.x = 100;
    rect.y = 240 - 50;

    int qirmizi = 120, goy = 120;

    printf("\nSDL VERSIYASI: %d.%d\n", SDL_MAJOR_VERSION, SDL_MINOR_VERSION);

    ApplicationManager &Appman = ApplicationManager::get_instance();
    App app = {
        1, // ID
        1, // CAT
        "APP NAME", // NAME
        "./", "./", ""
    };
    Appman.pushApp(&app);

    Button button;
    button.setTag("Ilk Button");
    button.setText("ILK BUTTON YAZISI!");
    SDL_Rect button_rect = {200, 20, 50, 400};

    // ------------------------- MUSIC ----------------------- //
    /* initialize SDL_mixer */
	Mix_Music *music;
	SDL_RWops *rw;
	if(Mix_OpenAudio(44100, AUDIO_F32, 2, 4096) < 0){
		printf("Couldn't open audio: %s\n", SDL_GetError());
		SleepThread();
	}

    rw = SDL_RWFromFile("MUSIC.MP3", "rb");
    if(!rw){
        printf("rw NULL QAYTARDI!\n");
    }

    music = Mix_LoadMUS_RW(rw, 1);  // 1 means freesrc will close rwops
    if(!music){
        printf("music NULL QAYTARDI!\n");
    }
    
    Mix_PlayMusic(music, 0);
    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_LOW);
    unsigned int sonuncu_duyme = 0;
    int is_app_still_up = 1;
    while(is_app_still_up){
        // ------------------------- PAD INPUT ----------------------- //
        unsigned int new_pad = read_pad(0, 0);
        
        if((new_pad ^ sonuncu_duyme) & PAD_UP){
            printf("YUXARI\n");
            if(qirmizi < 255) qirmizi++;
        }
        if((new_pad ^ sonuncu_duyme) & PAD_LEFT){
            printf("SOL\n");
            if(goy > 0) goy--;
        }
        if((new_pad ^ sonuncu_duyme) & PAD_RIGHT){
            printf("SAG\n");
            if(goy < 255) goy++;
        }
        if((new_pad ^ sonuncu_duyme) & PAD_DOWN){
            printf("ASAGI\n");
            if(qirmizi > 0) qirmizi--;
            Appman.listApps();
        }
        sonuncu_duyme = new_pad;
        
        // ------------------------- RENDER ----------------------- //

        SDL_SetRenderDrawColor(Simple::renderer, 255, 255, 255, 255);
        SDL_RenderClear(Simple::renderer);

        SDL_SetRenderDrawColor(Simple::renderer, 0, 0, 255, 255);
        SDL_RenderDrawRect(Simple::renderer, &rect);
        SDL_RenderFillRect(Simple::renderer, &rect);

        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char s[64];
        size_t ret = strftime(s, sizeof(s), "%c", tm);
        assert(ret);

        SDL_Color Yazicolor = {(Uint8)qirmizi, 0, (Uint8)goy, 255};
        SDL_Surface* temp = TTF_RenderUTF8_Blended(Simple::font, s, Yazicolor);
        SDL_Texture* timeImage = SDL_CreateTextureFromSurface(Simple::renderer, temp);
        SDL_Rect posTime = {10, 10, 150, 50};
        SDL_RenderCopy(Simple::renderer, textImage, NULL, &pos);
        SDL_RenderCopy(Simple::renderer, timeImage, NULL, &posTime);
        button.render(button_rect);
        SDL_RenderPresent(Simple::renderer);

        SDL_FreeSurface(temp); // Free the surface
        SDL_DestroyTexture(timeImage); // Destroy the texture

        SDL_Delay(16);
    }

    // Clean up and quit SDL
    Mix_FreeMusic(music);
    SDL_DestroyRenderer(Simple::renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(textImage);
    TTF_Quit();
    SDL_Quit();
    return 0;
}