#pragma once


#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <memory.h>
#include <map>
#include <mutex>
#include <vector>
#include <atomic>
#include <array>

#include <d3d11.h>
#include <dxgi.h>
#include <string>
#include <format>

#include "Include/Xorstr.hpp"

#define ConsoleLOG( format, ... ) printf( _("[ DEUBG ] " format "\n"), ##__VA_ARGS__ );

#include "Rust/Il2Cpp/Il2Cpp.hpp"

#include <Rust/Il2Cpp/pattern.hpp>

#include <Rust/Il2Cpp/misc/lazy_importer.hpp>


#include "Rust/Utils/Math/Vector/Vector2.hpp"
#include "Rust/Utils/Math/Vector/Vector3.hpp"
#include "Rust/Utils/Math/Vector/Vector4.hpp"
#include "Rust/Utils/Math/Vector/Matrix.hpp"

#include "Rust/Utils/Math/Hash.hpp"

#include "Include/ImGui/imgui.h"
#include "Include/ImGui/imgui_internal.h"
#include "Include/ImGui/imgui_impl_dx11.h"
#include "Include/ImGui/imgui_impl_win32.h"



#include "Rust/Utils/Math/Structs/RustStructs.hpp"

#include "Rust/Classes/Unity.hpp"
#include "Rust/Classes/GUI/OnGUI.hpp"
#include "Rust/Classes/GUI/Shader.hpp"
#include "Rust/Classes/GUI/Material.hpp"
#include "Rust/Classes/GUI/GL.hpp"
#include "Rust/Classes/GUI/GUIStyle.hpp"
#include "Rust/Classes/GUI/GUIContent.hpp"
#include "Rust/Classes/GUI/GUI.hpp"
#include "Rust/Classes/GUI/Label.hpp"
#include "Rust/Classes/GUI/Event.hpp"
#include "Rust/Classes/Screen.hpp"
#include "Rust/Classes/Camera.hpp"


#include "Rust/Utils/Enums/Enums.hpp"

#include "Rust/Classes/Matrix4x4.hpp"
#include "Rust/Classes/Transform.hpp"
#include "Rust/Classes/GameObject.hpp"
#include "Rust/Classes/Component.hpp"


#include "Rust/Classes/AimConeUtil.hpp"
#include "Rust/Classes/PlayerModel.hpp"
#include "Rust/Classes/Physics.hpp"
#include "Rust/Classes/Time.hpp"

#include "Rust/Classes/Input.hpp"

#include "Rust/Classes/TerrainCollision.hpp"
#include "Rust/Classes/TerrainHeightMap.hpp"
#include "Rust/Classes/Terrain.hpp"
#include "Rust/Classes/TerrainMeta.hpp"


#include "Rust/Classes/BaseNetworkable.hpp"
#include "Rust/Classes/Connection.hpp"
#include "Rust/Classes/Client.hpp"
#include "Rust/Classes/Networkable.hpp"
#include "Rust/Classes/ItemModProjectile.hpp"
#include "Rust/Classes/HitTest.hpp"
#include "Rust/Classes/Projectile.hpp"
#include "Rust/Classes/ItemDefinition.hpp"
#include "Rust/Classes/BaseProjectile.hpp"
#include "Rust/Classes/Item.hpp"
#include "Rust/Classes/ItemContainer.hpp"
#include "Rust/Classes/PlayerInventory.hpp"
#include "Rust/Classes/PlayerTick.hpp"
#include "Rust/Classes/Audio.hpp"
#include "Rust/Classes/PlayerEyes.hpp"
#include "Rust/Classes/Network.hpp"
#include "Rust/Classes/BaseEntity.hpp"

BaseEntity* cargo_ship_entity = nullptr;

#include "Rust/Classes/BaseCombatEntity.hpp"
#include "Rust/Classes/BasePlayer.hpp"
#include "Rust/Classes/LocalPlayer.hpp"
#include "Rust/Classes/GamePhysics.hpp"
#include "Rust/Classes/WaterLevel.hpp"

#include "Rust/Hooks/Functions/Present/PresentInit.hpp"
#include "Rust/Utils/Math/Math.hpp"

#include "Rust/Features/Drawing/Rendering/caching.hpp"



namespace rust {
	namespace globals {
		//BasePlayer* local = nullptr;
		//BaseProjectile* heldEntity = nullptr;

		inline bool initalized;

		inline Camera* camera;

		inline BasePlayer* target{ nullptr };

		inline box_bounds bounds;

		float max_spoofed_eye_distance = 0.0f;

		float last_tick_time = 0.0f;
		float desyncTime = 0.0f;

		Vector3 spoofed_eye_pos = Vector3().Zero();
	}
}
#include "Rust/Hooks/Hooks.hpp"

#include "Rust/Features/AntiHack/AntiHackVars.hpp"

#include "Rust/Features/AntiHack/Noclip.hpp"
#include "Rust/Features/AntiHack/EyeSpoof.hpp"
#include "Rust/Features/AntiHack/Flyhack.hpp"


#include "Rust/Features/Combat/Prediction.hpp"
#include "Rust/Features/Combat/Silent.hpp"

#include "Rust/Features/Drawing/Rendering/Rendering.hpp"
#include "Rust/Features/Drawing/Players.hpp"


#include "Rust/Hooks/Functions/Present/Present.hpp"

#include "Rust/Hooks/Functions/ClientUpdate.hpp"
#include "Rust/Hooks/Functions/ClientInput.hpp"
#include "Rust/Hooks/Functions/OnGUI.hpp"
#include "Rust/Hooks/Functions/SendClientTick.hpp"
#include "Rust/Hooks/Functions/ClientCycle.hpp"
#include "Rust/Hooks/Functions/DoHit.hpp"
#include "Rust/Hooks/Functions/TraceAll.hpp"
#include "Rust/Hooks/Functions/DoMovement.hpp"
#include "Rust/Hooks/Functions/PerformanceUpdate.hpp"
#include "Rust/Hooks/Functions/OnDisconnected.hpp"
