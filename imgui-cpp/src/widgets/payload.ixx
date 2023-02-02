export module imcpp.widgets.payload;

export import imcpp.std;

export namespace imcpp {

	struct IPayload
	{
		virtual void* data() = 0;
		virtual size_t size() const = 0;
	};

	template<typename T>
	struct Payload : public IPayload
	{
		using Type = std::decay_t<T>;

		Payload(const Type& data) : mData(data) {}

		void* data() override { return &mData; }
		size_t size() const override { return sizeof(T); }

	private:
		Type mData;
	};
}