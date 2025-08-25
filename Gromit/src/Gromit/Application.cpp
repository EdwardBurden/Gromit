#pragma once
#include "Application.h"
#include <typeinfo>

namespace Gromit
{
	bool Application::m_isRunning = true;

	bool Application::IsRunning()
	{
		return m_isRunning;
	}

	void Application::StartUp()
	{
		m_isRunning = true;
		ServiceLocator::RegisterService<Logging>();
		ServiceLocator::RegisterService<Renderer>();
		ServiceLocator::RegisterService<WindowManager>();
		ServiceLocator::RegisterService<AssetManager>();
		ServiceLocator::RegisterService<EventSystem>();
		ServiceLocator::StartUp();


		Context::SharedContext = Renderer::GetAPI()->CreateContext(); //temp
		auto w = Gromit::ServiceLocator::GetService<Gromit::WindowManager>();
		w->CreateWindow(100, 100, 400, 400, "DLL Test1");
		w->CreateWindow(100, 100, 400, 400, "DLL Test2");
		//CreateWindow(800, 900, 400, 400, "DLL Test3");
	/*	const auto& manager = ServiceLocator::GetService<AssetManager>();
		const auto& api = Renderer::GetAPI();
		manager->LoadAsset(545);
		manager->LoadAsset(123434);
		ShaderAsset* vert = manager->GetAsset<ShaderAsset>(545);
		ShaderAsset* frag = manager->GetAsset<ShaderAsset>(123434);
		const auto& windows = ServiceLocator::GetService<WindowManager>();
		float vertices[] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 0.5f, 0.2f , 0.9f,  // top right
			 0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.2f , 0.9f, // bottom right
			-0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 1.2f , 0.9f, // bottom left
			-0.5f,  0.5f, 0.0f, 0.0f, 0.5f, 0.2f , 0.9f, // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		BufferLayout* layout = api->CreateBufferLayout(
			{
				{ShaderDataType::Float3 , "position"},
				{ShaderDataType::Float4 , "color"}
			});
		m_tempShader = api->CreateShader(*vert, *frag);
		auto m_tempVB = api->CreateVertexBuffer(vertices, sizeof(vertices));
		m_tempVB->SetLayout(layout);
		auto m_tempIB = api->CreateIndexBuffer(indices, sizeof(indices));
		for (size_t i = 0; i < windows->WindowsCount(); i++)
		{
			windows->m_windows[i]->Activate();
			m_va[i] = api->CreateVertexArray();
			m_va[i]->Bind();
			m_va[i]->SetIndexBuffer(m_tempIB);
			m_va[i]->SetVertexBuffer(m_tempVB);
			m_va[i]->Unbind();
			//renderer->SetGlobalContext();
		}
		*/
		test = 	RenderCommands::CreateRenderObject(Context::SharedContext); //would pass in mesh and shaer assets here
	}

	void Application::Run()
	{
	/*	const auto& windows = ServiceLocator::GetService<WindowManager>();
		const auto& renderer = ServiceLocator::GetService<Renderer>();
		//Renderer::PreScene();
		for (size_t i = 0; i < 1; i++)
		{
			windows->m_windows[i]->PreUpdate();
			m_tempShader->Bind();
		//	m_va[i]->Bind();
		//	Renderer::Submit(m_va[i]);
			//renderer->OnUpdate();
			m_tempShader->Unbind();
			m_va[i]->Unbind();
			windows->m_windows[i]->PostUpdate();
		}
		//Renderer::PostScene();

		windows->OnUpdate();
		*/
		RenderCommands::DrawRenderObject(test);

		ServiceLocator::GetService<WindowManager>()->OnUpdate();
		ServiceLocator::GetService<EventSystem>()->OnUpdate();
		//ServiceLocator::GetService<Renderer>()->OnUpdate();


		//window/context start
		//render per window
		//window/context end

		//ServiceLocator::Update();
	}

	void Application::ShutDown()
	{
		ServiceLocator::ShutDown();
	}

	void Application::Stop()
	{
		m_isRunning = false;
	}
}