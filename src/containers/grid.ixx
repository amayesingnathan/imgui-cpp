export module imcpp.containers.grid;

import imcpp.std;

export namespace imcpp {

	template<std::integral T>
	struct Coordinate
	{
		static constexpr T NullCoord = std::numeric_limits<T>::max();
		T x = NullCoord, y = NullCoord;

		Coordinate() = default;
		constexpr Coordinate(T _x, T _y) : x(_x), y(_y) {}

		bool operator==(const Coordinate& other) const { return (x == other.x && y == other.y); }
		bool operator<(const Coordinate& other) const
		{
			if (y == other.y)
				return x < other.x;
			return y < other.y;
		}

		bool valid() const { return x != NullCoord && y != NullCoord; }
	};

	using GridPosition = Coordinate<uint32_t>;

	template<typename T, std::integral TPos = uint32_t>
	class Grid
	{
	public:
		using Bool = uint8_t;
		static constexpr Bool True = 1;
		static constexpr Bool False = 0;

		using ValType = std::conditional_t<std::same_as<T, bool>, Bool, T>; // std::vector<bool> has special storage, use uint8_t instead. 
		using Position = Coordinate<TPos>;

	public:
		Grid() = default;
		Grid(size_t width, size_t height)
			: mWidth(width), mHeight(height), mData(width* height)
		{}

		ValType& operator()(TPos x, TPos y) { return mData[x + (mWidth * y)]; }
		const ValType& operator()(TPos x, TPos y) const { return mData[x + (mWidth * y)]; }

		ValType& operator()(const Position& pos) { return mData[pos.x + (mWidth * pos.y)]; }
		const ValType& operator()(const Position& pos) const { return mData[pos.x + (mWidth * pos.y)]; }

		void set(size_t index, const ValType& data) { mData[index] = data; }

		size_t getWidth() const { return mWidth; }
		size_t getHeight() const { return mHeight; }

		void resize(size_t width, size_t height) { mData.clear(); mData.resize(width * height); }

		auto begin() { return mData.begin(); }
		auto begin() const { return mData.cbegin(); }
		auto end() { return mData.end(); }
		auto end() const { return mData.cend(); }

	protected:
		ValType& At(TPos x, TPos y) { return mData[x + (mWidth * y)]; }
		const ValType& At(TPos x, TPos y) const { return mData[x + (mWidth * y)]; }

		ValType& At(const Position& pos) { return mData[pos.x + (mWidth * pos.y)]; }
		const ValType& At(const Position& pos) const { return mData[pos.x + (mWidth * pos.y)]; }

	protected:
		size_t mWidth = 0, mHeight = 0;

	private:
		std::vector<ValType> mData;
	};
}

namespace std {
	template<typename T> struct hash;

	template<typename T>
	struct hash<imcpp::Coordinate<T>>
	{
		std::size_t operator()(const imcpp::Coordinate<T>& pos) const
		{
			uint64_t combo = (uint64_t)pos.x | (uint64_t)pos.y << 32;
			return std::hash<uint64_t>()(combo);
		}
	};
}