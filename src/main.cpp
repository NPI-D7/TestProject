#include "renderd7.hpp"
#include "TEX.h"
#include "Game.hpp"

int main()
{
    RenderD7::Init::Main("TestProject");
    RenderD7::Scene::Load(std::make_unique<Game>());
    while (RenderD7::MainLoop())
    {
        if (d7_hDown & KEY_START)
        {
            RenderD7::ExitApp();
        }
        RenderD7::FrameEnd();
    }
    RenderD7::Exit::Main();
    
    return 0;
}
