#include <Jolt/Jolt.h>
#include <iostream>

#include <Application/Application.h>
#include <Renderer/Renderer.h>
using String = std::basic_string<char, std::char_traits<char>, STLAllocator<char>>;


int main(int argc, char **argv) {
    Application debugRenderApplication("ContatoComChao", String());
    debugRenderApplication.Run();
    
    while(true){
        // do nothing
    }

    return 0;
}
