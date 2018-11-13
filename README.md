# Video to Sound

----------------

This project contains a video to sound converter program. 

The program uses OpenCV for video manipulation, SDL and SDL_Mixer for audio producing, and Qt for UI implementation.

Something interesting happened during development:

*  SDL conflicts with Qt on Windows platform. In a situation of using SDL and Qt together, the linker complained about the **duplication of WinMain**. The reason is that SDL defines a main macro to replace main as follows:


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


 
