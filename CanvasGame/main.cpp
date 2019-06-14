#include "Managers.h"
#include <windows.h>
#include <memory>
#include "Vector4.h"
#include "Systems.h"
#include "Components.h"
#include "Matrix4.h"
#include "KodeBoldsMath.h"
#include "GameScene.h"
#include "RayCubeCollisionSystem.h"
#include "NetworkUpdateSystem.h"

#pragma comment(lib, "CanvasEngine.lib")

using namespace KodeBoldsMath;

HINSTANCE hInst = nullptr;
HWND hWnd = nullptr;

HRESULT InitWindow(HINSTANCE pHInstance, int pNCmdShow);

/// <summary>
/// Entry point to the program. Initializes everything and goes into a message processing loop.
/// </summary>
/// <param name="pHInstance"></param>
/// <param name="pHPrevInstance"></param>
/// <param name="pLpCmdLine"></param>
/// <param name="pNCmdShow"></param>
/// <returns></returns>
int WINAPI wWinMain(_In_ const HINSTANCE pHInstance, _In_opt_ const HINSTANCE pHPrevInstance, _In_ const LPWSTR pLpCmdLine, _In_ const int pNCmdShow)
{
	UNREFERENCED_PARAMETER(pHPrevInstance);
	UNREFERENCED_PARAMETER(pLpCmdLine);

	if (FAILED(InitWindow(pHInstance, pNCmdShow)))
	{
		return 0;
	}

	RECT rc;
	GetClientRect(hWnd, &rc);
	const auto width = static_cast<float>(rc.right - rc.left);
	const auto height = static_cast<float>(rc.bottom - rc.top);

	auto ecsManager = ECSManager::Instance();
	auto threadManager = ThreadManager::Instance();
	threadManager->CreateThreads();

	auto antTweakManager = AntTweakManager::Instance();

#ifdef DIRECTX
	const std::shared_ptr<ISystem> renderer = std::make_shared<RenderSystem_DX>(hWnd);
#elif OPENGL
	const std::shared_ptr<ISystem> renderer = std::make_shared<RenderSystem_GL>();
#endif

	ecsManager->AddRenderSystem(renderer);

	auto networkManager = NetworkManager::Instance();
	networkManager->Init();

	const std::shared_ptr<ISystem> networkUpdateSystem = std::make_shared<NetworkUpdateSystem>();
	ecsManager->AddUpdateSystem(networkUpdateSystem);

	auto sceneManager = SceneManager::Instance();

	const std::shared_ptr<ISystem> rayCubeCollisionSystem = std::make_shared<RayCubeCollisionSystem>();
	ecsManager->AddUpdateSystem(rayCubeCollisionSystem);

	sceneManager->SetWindowSize(width, height);
	//Set start scene
	sceneManager->LoadScene<GameScene>();

	//Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//Testing scene manager
			sceneManager->Update();
			//sceneManager->Render();

			//double dt = sceneManager->DeltaTime();
			//int fps = sceneManager->Fps();
			//double time = sceneManager->Time();
		}
	}

	return static_cast<int>(msg.wParam);
}

/// <summary>
/// Register class and create window
/// </summary>
/// <param name="pHInstance"></param>
/// <param name="pNCmdShow"></param>
/// <returns></returns>
HRESULT InitWindow(const HINSTANCE pHInstance, const int pNCmdShow)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = InputManager_DX::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = pHInstance;
	wcex.hIcon = LoadIcon(pHInstance, nullptr);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Canvas Game";
	wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);
	if (!RegisterClassEx(&wcex))
	{
		return static_cast<HRESULT>(0x80004005L);
	}

	// Create window
	hInst = pHInstance;
	//RECT rc = { 0, 0, 1920, 1080 };
	RECT rc = { 0, 0, 500, 300 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindow(L"Canvas Game", L"Canvas Game",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, pHInstance,
		nullptr);
	if (!hWnd)
	{
		return static_cast<HRESULT>(0x80004005L);
	}

	ShowWindow(hWnd, pNCmdShow);

	return static_cast<HRESULT>(0L);
}