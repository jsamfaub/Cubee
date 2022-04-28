#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

extern int screenwidth;
extern int screenheight;
extern SDL_Renderer* mRenderer;
window windows[3];

window::window()
{
	mWindow = NULL;
	mMouseFocus = 0;
	mKeyboardFocus = 0;
	mFullScreen = 0;
	mMinimized = 0;
	mWidth = 0;
	mHeight = 0;
}

bool window::init()
{
	mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenwidth, screenheight,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if (mWindow != NULL)
	{
		mMouseFocus = 1;
		mKeyboardFocus = 1;
		mWidth = screenwidth;
		mHeight = screenheight;

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (mRenderer == NULL)
		{
			SDL_DestroyWindow(mWindow);
			mWindow = NULL;
		}
		else
		{
			SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			mWindowID = SDL_GetWindowID(mWindow);

			mShown = true;
		}
	}
	else
	{
		cout << "cant create window lol" << endl;
	}

	return mWindow != NULL && mRenderer != NULL;
}

SDL_Renderer* window::createRenderer()
{
	return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void window::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID)
	{

		bool updateCaption = 0;
		switch (e.window.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			mShown = 1;
			break;
			
		case SDL_WINDOWEVENT_HIDDEN:
			mShown = false;
			break;

		case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			SDL_RenderPresent(mRenderer);
			break;

		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(mRenderer);
			break;
		case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = 1;
			updateCaption = 1;
			break;

		case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = 0;
			updateCaption = 1;
			break;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = 1;
			updateCaption = 1;
			break;

		case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			updateCaption = true;
			break;

		case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = 1;
			break;

		case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = 0;
			break;

		case SDL_WINDOWEVENT_RESTORED:
			mMinimized = 0;
			break;

		case SDL_WINDOWEVENT_CLOSE:
			SDL_HideWindow(mWindow);
			break;
		}
		if (updateCaption)
		{
			stringstream caption;
			caption << "SDL Tutorial - MouseFocus:" << ((mMouseFocus) ? "On" : "Off") << " KeyboardFocus:" << ((mKeyboardFocus) ? "On" : "Off");
			SDL_SetWindowTitle(mWindow, caption.str().c_str());
		}
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
	{
		if (mFullScreen)
		{
			SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
			mFullScreen = 0;
		}
		else
		{
			SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
			mFullScreen = 1;
			mMinimized = 0;
		}
	}
}

int window::getWidth()
{
	return mWidth;
}

int window::getHeight()
{
	return mHeight;
}

bool window::hasMouseFocus()
{
	return mMouseFocus;
}

bool window::hasKeyboardFocus()
{
	return mKeyboardFocus;
}

bool window::isMinimized()
{
	return mMinimized;
}

void window::free()
{
	SDL_DestroyWindow(mWindow);
}

void window::focus()
{
	if (!mShown)
	{
		SDL_ShowWindow(mWindow);
	}

	SDL_RaiseWindow(mWindow);
}

void window::render()
{
	if (!mMinimized)
	{
		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(mRenderer);

		SDL_RenderPresent(mRenderer);
	}
}

bool window::isShown()
{
	return mShown;
}

SDL_Renderer* window::getRenderer()
{
	return mRenderer;
}
