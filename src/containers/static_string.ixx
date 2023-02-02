export module imcpp.containers.static_string;

import imcpp.std;
import imcpp.containers.static_buffer;

export namespace imcpp {

	template<size_t TSize>
	class StaticString : public StaticBuffer<TSize>
	{
	public:
		StaticString(const std::string& string)
		{
			memset(this->mData, 0, TSize);
			memcpy(this->mData, string.c_str(), string.size() <= TSize ? string.size() : TSize - 1);;
		}

		constexpr size_t length() const { return TSize; }

		operator char* ()
		{
			if (this->mData[TSize - 1] != 0)
				return nullptr;

			return (char*)this->mData;
		}

		std::string toString() const
		{
			if (this->mData[TSize - 1] != 0)
				return {};

			return (const char*)this->mData;
		}
	};
}