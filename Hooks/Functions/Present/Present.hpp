#include <codecvt>



extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM param, LPARAM l_param);


void DirectXShutdown() {
	// destroy everything
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	Present::device->Release();
}

auto __stdcall Present::WndProc(const HWND hwnd, unsigned int msg, uintptr_t param, long long l_param) -> long long
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, param, l_param))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (device != NULL && param != SIZE_MINIMIZED)
		{
			ImGui_ImplDX11_InvalidateDeviceObjects();
			ImGui_ImplDX11_CreateDeviceObjects();
		}
		break;

	case WM_DESTROY:
		DirectXShutdown();
		PostQuitMessage(0);
		return 0;
		break;

	case WM_LBUTTONDOWN:
		PressedKeys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		PressedKeys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		PressedKeys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		PressedKeys[VK_RBUTTON] = false;
		break;
	case WM_MBUTTONDOWN:
		PressedKeys[VK_MBUTTON] = true;
		break;
	case WM_MBUTTONUP:
		PressedKeys[VK_MBUTTON] = false;
		break;
	case WM_KEYDOWN:
		PressedKeys[param] = true;
		break;
	case WM_KEYUP:
		PressedKeys[param] = false;
		break;
	case WM_XBUTTONDOWN:
	{
		UINT button = GET_XBUTTON_WPARAM(param);
		if (button == XBUTTON1)
		{
			PressedKeys[VK_XBUTTON1] = true;
		}
		else if (button == XBUTTON2)
		{
			PressedKeys[VK_XBUTTON2] = true;
		}
		break;
	}
	case WM_XBUTTONUP:
	{
		UINT button = GET_XBUTTON_WPARAM(param);
		if (button == XBUTTON1)
		{
			PressedKeys[VK_XBUTTON1] = false;
		}
		else if (button == XBUTTON2)
		{
			PressedKeys[VK_XBUTTON2] = false;
		}
		break;
	}
	}

	return CallWindowProcA(o_wnd_proc, hwnd, msg, param, l_param);
}


bool present_init{ false };
auto Present::PresentHk(IDXGISwapChain* swap_chain, unsigned int sync, unsigned int flags) -> uintptr_t
{
	if (!present_init)
	{
		if (SUCCEEDED(swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&device)))
		{
			device->GetImmediateContext(&context);
			DXGI_SWAP_CHAIN_DESC sd;
			swap_chain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			device->CreateRenderTargetView(pBackBuffer, NULL, &main_render_target_view);
			pBackBuffer->Release();

			o_wnd_proc = (WNDPROC)SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(device, context);
		}
		else
			return reinterpret_cast<decltype (&PresentHk)> (o_present) (swap_chain, sync, flags);

		present_init = true;
	}

	context->OMSetRenderTargets(1, &main_render_target_view, nullptr);
	context->RSGetViewports(&vps, &viewport);
	screen_size = { viewport.Width, viewport.Height };
	screen_center = { viewport.Width / 2.0f, viewport.Height / 2.0f };

	auto begin_scene = [&]() {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	};

	auto end_scene = [&]() {
		ImGui::Render();
	};


	begin_scene();
	{

		if (LocalPlayer::Entity() != nullptr)
		{

			Drawing::player_loop(); //useless check here but whatever, doesn't hurt.
		}

	}
	end_scene();


	context->OMSetRenderTargets(1, &main_render_target_view, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	if (GetKeyState(VK_END) & 0x8000)
	{
		Hooks::Unhook();
	}

	return reinterpret_cast<decltype (&PresentHk)> (o_present) (swap_chain, sync, flags);
}