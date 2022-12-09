#pragma once


class Camera;
namespace unity
{
	


	inline auto viewMatrix() -> mat4x4_t
	{
		if (!camera) {
			camera = Camera::main();
			ConsoleLOG("Camera Set");
		}
		auto camera_ = *reinterpret_cast<std::uintptr_t*>(camera + 0x10);
		if (!camera_ ) {
			return {};
		}

		auto matrix = *reinterpret_cast<mat4x4_t*>(camera_ + 0x2e4);
		if (!matrix.m) {
			return {};
		}
		return matrix;
	}
	inline bool w2s(const Vector3& EntityPos, Vector2& ScreenPos)
	{
		auto matrix = viewMatrix();
		if (!memory::valid_pointer(matrix.m))
			return false;

		const auto temp = matrix.transpose();

		auto translation_vector = Vector3{ temp[3][0], temp[3][1], temp[3][2] };
		auto up = Vector3{ temp[1][0], temp[1][1], temp[1][2] };
		auto right = Vector3{ temp[0][0], temp[0][1], temp[0][2] };

		float w = translation_vector.Dot(EntityPos) + temp[3][3];

		if (w < 0.098f) {
			return false;
		}

		float x = up.Dot(EntityPos) + temp._24;
		float y = right.Dot(EntityPos) + temp._14;

		ScreenPos.x = (static_cast<float>(screen_size.x) / 2) * (1 + y / w);
		ScreenPos.y = (static_cast<float>(screen_size.y) / 2) * (1 - x / w);

		//ScreenPos = out;

		return true;
	}
}
