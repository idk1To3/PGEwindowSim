#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define PGEWS_APPLICATION
#include "PGEwindowsim.h"

enum ids
{
        left0,
        right0,
        right1,
        menu,
        number
};

class LeftWindow : public PGEws::Window
{
public:
	LeftWindow(olc::PixelGameEngine* pge, unsigned int id, std::string name, int width, int height, int posX, int posY, int permissions = -1) : Window(pge, id, name, width, height, posX, posY, permissions)
	{ }

        int x = 8;

public:
	bool wOnUserCreate() override
	{
		return true;
	};

	bool wOnUserUpdate(float fElapsedTime) override
	{
                if(!inFocus)
                        return true;
                
		for (int x = 0; x < WindowWidth(); x++)
			for (int y = 0; y < WindowHeight(); y++)
			{
				pge->Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
			}
		pge->DrawString(0, 0, std::to_string(1.0f / fElapsedTime), olc::BLACK);
		pge->FillCircle(20, 20, 5, olc::MAGENTA);
		return true;
	};
};

class RightWindow : public PGEws::Window
{
public:
	RightWindow(olc::PixelGameEngine* pge, unsigned int id, std::string name, int width, int height, int posX, int posY, int permissions = -1) : Window(pge, id, name, width, height, posX, posY, permissions)
	{ }

public:
	bool wOnUserCreate() override
	{
		return true;
	};

	bool wOnUserUpdate(float fElapsedTime) override
	{
		pge->Clear(olc::BLUE);
		pge->FillTriangle(-18, -49, rand() % WindowWidth(), rand() % WindowHeight(), rand() % WindowWidth(), rand() % WindowHeight(), olc::RED);
		pge->DrawString(0, 0, std::to_string(1.0f / fElapsedTime), olc::BLACK);

                Window* w = getWindow(left0);

                olc::vi2d pos = (w != nullptr ? w->lGetMousePos() * w->scale : olc::vi2d{0,0});

                pge->FillCircle(pos, 5, olc::GREEN);

		return true;
	};
};

class WindowMenu : public PGEws::Window
{
public:
	WindowMenu(olc::PixelGameEngine* pge, unsigned int id, std::string name, int width, int height, int posX, int posY, int permissions = -1) : Window(pge, id, name, width, height, posX, posY, permissions)
	{ }

	bool wOnUserCreate() override
	{
		return true;
	};

	bool wOnUserUpdate(float fElapsedTime) override
	{
		shouldBeFocused = -1;

		if (hidden)
			return true;

		pge->FillCircle(20, 10, 10, olc::WHITE);
		pge->FillCircle(20, 30, 10, olc::WHITE);
		pge->FillCircle(20, 50, 10, olc::WHITE);
		pge->DrawString(20, 10, "0", olc::BLACK);
		pge->DrawString(20, 30, "1", olc::BLACK);
		pge->DrawString(20, 50, "2", olc::BLACK);

		if (!inFocus)
			return true;

		if (!pge->GetMouse(0).bPressed)
			return true;

		float mouseX = lGetMouseX();
		float mouseY = lGetMouseY();

		std::cout << mouseX << " " << mouseY << "\n";

		if (sqrtf((mouseX - 20) * (mouseX - 20) + (mouseY - 10) * (mouseY - 10)) < 10.0f)
			shouldBeFocused = 0;
		else if (sqrtf((mouseX - 20) * (mouseX - 20) + (mouseY - 30) * (mouseY - 30)) < 10.0f)
			shouldBeFocused = 1;
		if (sqrtf((mouseX - 20) * (mouseX - 20) + (mouseY - 50) * (mouseY - 50)) < 10.0f)
			shouldBeFocused = 2;

		if (shouldBeFocused != -1)
			parentWindowList->changeFocusedWindow(shouldBeFocused);

		return true;
	};

	int shouldBeFocused;
};


class Application : public olc::PixelGameEngine
{
public:
	Application() : win(this)
	{
		sAppName = "Application";
	}

private:
        PGEws::WindowList win;

	int id = number;

public:
	bool OnUserCreate() override
	{
		win.addNewWindow(new LeftWindow(this,  left0, "Can do all", 20, 10, 0, 0));
		win.addNewWindow(new RightWindow(this, right0, "can move and close", 300, 300, 200, 0, PGEws::CanMove | PGEws::CanClose));
		win.addNewWindow(new RightWindow(this, right1, "cant move", 200, 300, 500, 0, ~(PGEws::CanMove)));
		win.addNewWindow(new WindowMenu(this, menu, "window menu", 40, 60, 400, 400, ~(PGEws::CanResizeY)));

		win.setMaxFPS(left0, 1.0f);
		win.setMaxFPS(right0, 10.0f);
		win.setScale(left0, 7);
		win.setScale(menu, 1);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

//                for(int x = 0; x < ScreenWidth(); x++)
//                        for(int y = 0; y < ScreenHeight(); y++)
//                        {
//                                Draw(x,y,((x+y) % 2 == 0 ? olc::BLACK : olc::WHITE));
//                                if(x % 8 == 0 || y % 8 == 0)
//                                        Draw(x,y,olc::RED);
//                        }

		win.updateAll(fElapsedTime);

//		int windowMenuIndex = win.getIndexOfId(menu);
//		int whichWindowToFocus = ((WindowMenu*)win.windowList[windowMenuIndex])->shouldBeFocused;
//		if (whichWindowToFocus != -1)
//			win.changeFocusedWindow(whichWindowToFocus);
//
//		if (GetKey(olc::Key::A).bPressed)
//			win.addNewWindow(new LeftWindow(this, id++, "added window", 50, 50, 400, 400));
//
//		if (GetKey(olc::Key::DEL).bPressed)
//			win.deleteWindow(win.getFocusedId());
//
//		if (GetKey(olc::Key::F).bPressed)
//			win.changeFocusedWindow(1);
//
//		if (GetKey(olc::Key::O).bPressed)
//			win.setHidden(win.getFocusedId(), true);
//
//		if (GetKey(olc::Key::P).bPressed)
//			win.setHidden(win.getFocusedId(), false);

		return true;
	}

	bool OnUserDestroy() override
	{
		win.destroyAll();

		return true;
	}
};

int main()
{
	Application demo;
	if (demo.Construct(800, 550, 1, 1))
//	if (demo.Construct(80, 80, 8, 8)) 
		demo.Start();

	return 0;
}
