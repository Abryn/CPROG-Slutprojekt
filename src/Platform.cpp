#include <SDL2/SDL_image.h>

class Platform : public Sprite {
public:
    // Tar in koordinater samt sökväg till bild och anropar sedan sprite-konstruktorn med de värdena
    Platform(int x, int y, int w, int h, const std::string& imagePath) : Sprite(x, y, w, h), texture(nullptr){ 
        texture = IMG_LoadTexture(sys.get_ren(), imagePath.c_str());
    } 
    
    ~Platform() {
        if (texture) {
            SDL_DestroyTexture(texture); //Frigör texture
        }
    }

    void draw const() {
        if (texture) {
            SDL_RenderCopy(sys.get_ren(), texture, nullptr, &rect); //Rita ut texture
        } else {
        SDL_SetRenderDrawColour(sys.get_ren(), 255, 0, 0, 0) //Standard röd färg
        SDL_RenderFillRect(sys.get_ren(), &rect) //Skapar en "backup"rektangel (ifall inte en texture laddas)

        //eventuellt lägga till att plattformar rör sig?
    }

private:
    SDL_Texture* texture;
}

}