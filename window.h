#pragma once
class window
{
public:
	window();

	bool init();

	SDL_Renderer* createRenderer();

	void handleEvent(SDL_Event& e);

	void focus();

	void render();

	void free();

	int getWidth();
	int getHeight();

	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	bool isShown();

	SDL_Renderer* getRenderer();
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	int mWindowID;

	int mWidth;
	int mHeight;

	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
	bool mShown;
};

