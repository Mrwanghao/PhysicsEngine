#pragma once


class IWindow
{
	friend void CleanupMemory(IWindow* window);
private:
	IWindow(const IWindow& _window) {}
	IWindow& operator=(const IWindow& right) {}

protected:
	static IWindow* Singleton;
	bool quitFlag;
	bool fullFlag;
	int width;
	int height;
	bool visible;
	bool titleDirty;
	char* title;

	int targetFPS;
	int fixedFPS;

public:
	inline static IWindow* GetSingleton() { return Singleton; }

	IWindow();
	IWindow(const char* _title);
	IWindow(const char* _title, int _width, int _height);
	virtual ~IWindow();

	virtual void Initialize() {}
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void Render() {}
	virtual void Shutdown() {}

	virtual void Resize(int _width, int _height) {}

	virtual void MouseMove(int _x, int _y) {}
	virtual void MouseDown(int mousecode) {}
	virtual void MouseUp(int mousecode) {}

	virtual void KeyDown(int mousecode) {}
	virtual void KeyUp(int mousecode) {}

	void SetTitle(const char* _title);
	bool GetAndResetTitleDirtyFlag();
	const char* GetTitle();

	void SetFullScreen(bool value);
	bool GetFullScreen();

	void Resize(int _widht, int _height);
	int GetWidth();
	int GetHeight();

	void SetTargetFPS(int target);
	int GetTargetFPS();
	int GetFixedFPS();

	void MarkAsShown();
	bool WasWindowShown();
};

void CleanupMemory(IWindow* window);
int KeyIndex(int keyCode);