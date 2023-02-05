export module imcpp.containers.dummy;

export namespace imcpp {

	struct ImCppVec2 
	{ 
		float x, y; 
		constexpr ImCppVec2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
	};

	struct ImCppVec3
	{
		float x, y, z;
		constexpr ImCppVec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
	};

	struct ImCppVec4
	{
		float x, y, z, w;
		constexpr ImCppVec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : x(x), y(y), z(z), w(w) {}
	};
}