#include <list>

template<typename type>
class List
{
public:
    type get(std::uint32_t idx)
    {
        const auto internal_list = reinterpret_cast<std::uintptr_t>(this + 0x20);
        return *reinterpret_cast<type*>(internal_list + idx * sizeof(type));
    }

    type value(std::uint32_t idx)
    {
        const auto list = *reinterpret_cast<std::uintptr_t*>(this + 0x10);
        const auto internal_list = list + 0x20;
        return *reinterpret_cast<type*>(internal_list + idx * sizeof(type));
    }

    auto size() -> const std::uint32_t { return *reinterpret_cast<std::uint32_t*>(this + 0x18); }
};
struct Ray {
public:
	Vector3 m_Origin;
	Vector3 m_Direction;

	Ray() {
		this->m_Origin = Vector3(0, 0, 0);
		this->m_Direction = Vector3(0, 0, 0);
	}

	Ray(Vector3 origin, Vector3 direction) {
		this->m_Origin = origin;
		this->m_Direction = direction;
	}

	Vector3 ClosestPoint(Vector3 pos) {
		return this->m_Origin + this->m_Direction * (pos - this->m_Origin).dot_product(this->m_Direction);
	}
};
class CornerBox
{
public:
	Vector3 left;
	Vector3 right;
	Vector3 top;
	Vector3 bottom;
	bool Valid = true;
	ImColor Color;
};
struct box_bounds {
	float left, right, top, bottom;

	bool empty() {
		if (this->left == 0 && this->right == 0 && this->top == 0 && this->bottom == 0)
			return true;

		if (this->left == FLT_MAX || this->right == FLT_MIN || this->top == FLT_MAX || this->bottom == FLT_MIN)
			return true;

		return false;
	}
	static box_bounds null() {
		return { 0, 0, 0, 0 };
	}
};
class ILine
{
public:
	ILine(Vector3 position1, Vector3 position2, ImColor lineColor)
	{
		this->Start = position1;
		this->End = position2;
		this->Color = lineColor;
	};

	Vector3 Start;
	Vector3 End;
	ImColor Color;
};

inline std::list<ILine> ILines; inline std::list<ILine> TempILines;