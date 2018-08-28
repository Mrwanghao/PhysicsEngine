#pragma once


class IWindow
{
	friend void CleanupMemory(IWindow* window);
private://≤ª»√øΩ±¥
	IWindow(const IWindow& _window) {}
	IWindow& operator=(const IWindow& right) {}

protected:
	static IWindow* Singleton;
	int width;
	int height;
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

	virtual void OnInitialize() {}
	virtual void OnUpdate(float dt) {}
	virtual void OnFixedUpdate(float dt) {}
	virtual void OnRender() {}
	virtual void OnShutdown() {}
	virtual void OnResize(int _width, int _height) {}

public:
	void SetTitle(const char* _title);
	bool GetAndResetTitleDirtyFlag();

	inline const char* GetTitle() { return title; }
	inline int GetWidth() { return width; }
	inline int GetHeight() { return height; }
	inline void SetTargetFPS(int target) { targetFPS = target; }
	inline int GetTargetFPS() { return targetFPS; }
	inline int GetFixedFPS() { return fixedFPS; }
	
};

void CleanupMemory(IWindow* window);