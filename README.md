# Video to Sound

----------------

This is a simple video -> sound converter program. 

It uses OpenCV for video manipulation, SDL&SDL_Mixer for audio producing and finally Qt for making a simple UI.

Some interesting things happen during the programming process:

1. SDL and Qt has some conflicts on Windows. When I tried to use both of them, the linker complained about the ** duplication of WinMain **. The reason is SDL defines a main macro to replace main, like this:


    ``` C
    #define main SDL_main
    extern C_LINKAGE int SDL_main(int argc, char *argv[]);

    ```
And then SDL does some initialization to make its functionalities work properly in its own main. There is some [official explanation](https://wiki.libsdl.org/FAQWindows#I_get_.22Undefined_reference_to_.27SDL_main.27.22_...). ** The link error happens because Qt also uses WinMain to do its initial jobs. ** 
However, sometimes we just **undef the macro of SDL** and our program works fine too.  
 