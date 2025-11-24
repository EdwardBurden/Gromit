#pragma once
#include "Application.h"
#include <typeinfo>
#include "Core/LinearAllocator.h"

namespace Gromit
{
	const size_t TextureAllocationSize = 32 * 1024 * 1024;
	LinearAllocator textureAllocator;

	Context* SharedContext = nullptr;
	struct TestData
	{
		uint16_t first;
		uint32_t second;
		char third;
	};

	struct BestData
	{
		char third;
		uint16_t first;
		uint32_t second;
	};

	struct Breaker {
		char a;         // 1 byte
		__m128 simd;    // 16 bytes, 16-byte aligned
	};


	bool Application::m_isRunning = true;

	bool Application::IsRunning()
	{
		return m_isRunning;
	}

	void Application::StartUp()
	{
		textureAllocator.Create(TextureAllocationSize);
		m_isRunning = true;
		ServiceLocator::RegisterService<Logging>();
		ServiceLocator::RegisterService<Renderer>();
		ServiceLocator::RegisterService<WindowManager>();
		ServiceLocator::RegisterService<AssetManager>();
		ServiceLocator::RegisterService<EventSystem>();
		ServiceLocator::RegisterService<SceneManager>();
		ServiceLocator::StartUp();


		SharedContext = Renderer::GetAPI()->CreateContext(); //temp
		//auto w = ServiceLocator::GetService<WindowManager>();
		//w->CreateWindow(100, 100, 400, 400, "DLL Test1");
	}

	void Application::Run()
	{
		m_isRunning = false;
		return;
		auto renderer = ServiceLocator::GetService<Renderer>();
		//	renderer->AddDrawObject(testRender); //temp will be set from the scene/world manager

		FrameTime::SetDelta();
		ServiceLocator::GetService<WindowManager>()->OnUpdate(); // use the update
		//hack must fix
		if (!m_isRunning)
			return;
		//ServiceLocator::GetService<EventSystem>()->OnUpdate();
		const auto& sceneManger = ServiceLocator::GetService<SceneManager>();
		ServiceLocator::GetService<Renderer>()->OnUpdate(sceneManger->m_activeScene);
		//ServiceLocator::Update();
		//m_isRunning = false;

	}

	void Application::ShutDown()
	{
		ServiceLocator::ShutDown();
		delete SharedContext;
	}

	void Application::Stop()
	{
		m_isRunning = false;
	}
}