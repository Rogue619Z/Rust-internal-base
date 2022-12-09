inline bool PressedKeys[256] = {};
inline static UINT vps = 1;
Vector2 screen_size = { 0, 0 };
Vector2 screen_center = { 0, 0 };
D3D11_VIEWPORT viewport;

class Present
{
public:
	inline static HWND window{ };
	inline static WNDPROC o_wnd_proc;
	inline static ID3D11Device* device{ };
	inline static ID3D11DeviceContext* context{ };
	inline static ID3D11RenderTargetView* main_render_target_view;

	static auto __stdcall WndProc(const HWND hwnd, unsigned int msg, uintptr_t param, long long l_param) ->  long long;
public:
	inline static void* o_present;
	static auto PresentHk(IDXGISwapChain* swap_chain, unsigned int sync, unsigned int flags)->uintptr_t;
};
