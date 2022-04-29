#include "renderd7.hpp"

class Game : public RenderD7::Scene
{
    public:
    void Draw(void) const override;
    void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) override;
    Game();
    ~Game();
    private:
    
    std::vector<RenderD7::DirContent> dircontent;
    int dirsel = 0;
    bool changeddir = false;
};