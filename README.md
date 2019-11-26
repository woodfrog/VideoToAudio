# Video to Sound

----------------

This project is a video-to-sound converter application, aiming to help vision disabled people to interpret video contents through sound.

On launching this application, a UI is available to user to locate mp4 formatted videos on your computer, on selection of video, a corresponding converted audio will be played.

The program uses the OpenCV library for video manipulation, the SDL and SDL_Mixer library for audio producing. UI implementation is based on Qt.

Something interesting happened during development:

*  SDL conflicts with Qt on Windows platform. If SDL and Qt are applied at the same time, the linker complained about the **duplication of WinMain**. The reason is SDL defines a main macro to replace main with the following:


    ``` C
    #define main SDL_main
    extern C_LINKAGE int SDL_main(int argc, char *argv[]);

    ```
SDL performs initialization to ensure functionalities work correctly in its main scope. There is an [official explanation](https://wiki.libsdl.org/FAQWindows#I_get_.22Undefined_reference_to_.27SDL_main.27.22_...) of this behaviour. **The link error happens because Qt also uses WinMain for initializing jobs.** 
As a temporary work-around, the link error can be resolved if we **undefine the macro of SDL**.


## Notes

1. When creating a new thread using C++ thread in the standrard library, the template below should be followed:

    ``` cpp
        std::thread my_thread(bar)  // if the function bar has no parameter
        std::thread my_thread(foo, ...) // if function foo has parameters, the arguments should be specified 
    ```
    
    **When the function is a member function of a class, the first argument must be a pointer to an object of this class(serve as the default argument `"this"`)**


 
