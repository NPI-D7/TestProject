#include "Game.hpp"
#include <time.h>

Game::Game()
{
    consoleInit(GFX_TOP, NULL);
    this->dircontent.clear();
    chdir("sdmc:/");
    std::vector<RenderD7::DirContent> temp;
    RenderD7::GetDirContentsExt(temp, {"bcstm"});
    for (uint i = 0; i < temp.size(); i++)
    {
        this->dircontent.push_back(temp[i]);
    } 
    this->changeddir = false;
}
Game::~Game()
{
    
}
void Game::Draw(void) const
{
    consoleClear();
    std::string dirs;
    dirs.clear();
    int contentsss;
    contentsss = (int)dircontent.size();
    for (int i = this->dirsel < 9 ? 0 : this->dirsel - 9; (int)dircontent.size() && i < ((this->dirsel < 9) ? 10 : this->dirsel + 1); i++)
    {
        if (i == dirsel)
        {
            dirs += "> " + dircontent[i].name + "\n";
        }
        else
        {
            dirs += dircontent[i].name + "\n";
        } 
    }
    for (uint i = 0; i < ((dircontent.size() < 10) ? 10 - dircontent.size() : 0); i++) {
		dirs += "\n\n";
	}
    std::cout << dirs << std::endl;
}
void Game::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
     if (this->changeddir) {
        //RenderD7::Msg::Display("BCSTM-Player", "Loading Directory", Top);
        
		this->dircontent.clear();
		std::vector<RenderD7::DirContent> temp;
		RenderD7::GetDirContentsExt(temp, {"bcstm"});

		for(uint i = 0; i < temp.size(); i++) {
			this->dircontent.push_back(temp[i]);
		}

		this->changeddir = false;
	}
    if (hDown & KEY_A)
    {
        char path[PATH_MAX];
		getcwd(path, PATH_MAX);
        if (this->dircontent.size() > 0) 
        {
			if (this->dircontent[dirsel].isDir) 
            {
				chdir(this->dircontent[this->dirsel].name.c_str());
                this->dircontent.clear();
				this->dirsel = 0;
				this->changeddir = true;
			} 
            else 
            {
                if (RenderD7::NameIsEndingWith(this->dircontent[this->dirsel].name, {"bcstm"}) && RenderD7::IsNdspInit())
                {
                    playing = false;
                    player.stop();
                    player.openFromFile(this->dircontent[this->dirsel].name);
                    player.play();
                    currentlypl = this->dircontent[this->dirsel].name;
                    playing = true;
                }
                else
                {
                    //RenderD7::Error::DisplayError("BCSTM-Player", "Ndsp is not initialisized.\nPress Start to exit!");
                }
			}
		}
        else if (this->dircontent.size() == 0)
        {
            //RenderD7::Msg::Display("BCSTM_Player->Error", "What are you trying to do?\nThis Directory is empty.", Top);
        }
    }
    if (hDown & KEY_B)
    {
        char path[PATH_MAX];
		getcwd(path, PATH_MAX);

		if (strcmp(path, "sdmc:/") == 0 || strcmp(path, "/") == 0) 
        {
			RenderD7::Scene::Back();
		} 
        else 
        {
			chdir("..");
			dirsel = 0;
			changeddir = true;
		}
    }
    if (hDown & KEY_X)
    {

    }
    if (hDown & KEY_UP && dirsel > 0)
    {
        dirsel--;
    }
    if (hDown & KEY_DOWN && dirsel < (int)dircontent.size() - 1)
    {
        dirsel++;
    }
    if (hDown & KEY_LEFT && dirsel - 6 > 0)
    {
        dirsel -= 6;
    }
    if (hDown & KEY_RIGHT && dirsel + 6 < (int)dircontent.size() - 1)
    {
        dirsel += 6;
    }
}
