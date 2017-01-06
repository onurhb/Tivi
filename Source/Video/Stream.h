#ifndef PROJECT_STREAM_H
#define PROJECT_STREAM_H
// -------------- INCLUDES
#include "../Graphics/Texture.h"
#include "../Graphics/Shader.h"
#include <vlc/vlc.h>
#include <string>
#include <mutex>
#include <stb_image.h>

class Stream {

    struct CTX {
        unsigned char *pixeldata;
        std::mutex imagemutex;
    } ctx;


    // - VLC
    libvlc_media_player_t *mediaPlayer;
    libvlc_instance_t *instance;
    libvlc_media_t *media;

    // - Other
    unsigned int screenWidth, screenHeight;
    bool streamPlaying = false;

    // - Graphics
    Texture texture;
    Shader shader;
    GLuint VAO, VBO, EBO;

    // - Settings
private:
    void createQuad();
    void initializeVLC();
    void initializeShader();

public:
    Stream(unsigned int screenWidth, unsigned int screenHeight);
    ~Stream();
    void openFile(std::string path);
    void openExternal(std::string URL);
    bool play();
    bool pause();
    bool resume();
    bool destroy();
    void render();
    // -------------------------------------------------- CALLBACKS
    friend void *lock(void *data, void **p_pixels);
    friend void unlock(void *data, void *id, void *const *p_pixels);
    // ----------------------------- GETTERS
    unsigned char *getPixels();
    bool isStreamPlaying() const;
};


#endif //PROJECT_STREAM_H
