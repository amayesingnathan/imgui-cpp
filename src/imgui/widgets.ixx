export module imcpp.widgets;

import <imgui.h>;

import imcpp.def;
import imcpp.utils;
import imcpp.containers;

import imcpp.widgets.combobox;
import imcpp.widgets.payload;
import imcpp.widgets.menubar;
import imcpp.widgets.popup;

namespace imcpp {
	
	export class Widgets
	{
	public:
		static void NewLine();
		static void SameLine(float xOffset = 0.0f);
		static void Separator();

		static void Disable(bool disable = true);
		static void EndDisable();

		static void SetXPosition(float pos);
		static void SetYPosition(float pos);

		using GridFunction = std::function<void(const GridPosition&, const ImVec2&)>;
		static void GridControl(const ImVec2& pos, const ImVec2& size, size_t width, size_t height, GridFunction func);
		static void GridControl(const ImVec2& size, size_t width, size_t height, GridFunction func);

		static void BeginColumns(int count, bool border = false);
		static void NextColumn();
		static void EndColumns();

		static void BeginChild(std::string_view strID, const ImVec2& size = { 0.0f, 0.0f }, bool border = true);
		static void EndChild();

		static void BeginGroup();
		static void EndGroup();

		static void TreeNode(void* id, std::string_view text, bool selected, Action<> whileOpen);

		static void Selectable(std::string_view label, bool selected, Action<> action);

		static void BeginMenuBar();
		static void AddMenuBarHeading(std::string_view heading);
		static void AddMenuBarItem(std::string_view heading, Action<> action);
		static void AddMenuBarItem(std::string_view heading, std::string_view shortcut, Action<> action);
		static void AddMenuBarItem(std::string_view heading, bool& displayed);
		static void AddMenuBarSeparator();
		static void EndMenuBar();

		static void OpenPopup(std::string_view popupName);
		static void BeginPopup(std::string_view popupName);
		static void AddPopupItem(std::string_view heading, Action<> action);
		static void EndPopup();

		static void BeginContextPopup();
		static void AddContextItem(std::string_view heading, Action<> action);
		static void EndContextPopup();

		static void Label(std::string_view fmt);
		static void LabelWrapped(std::string_view fmt);

		static void StringEdit(std::string_view label, std::string& field);
		static void PathEdit(std::string_view label, fs::path& field);

		template<typename T> requires std::signed_integral<T>
		static void IntEdit(std::string_view label, T& field)
		{
			int64_t result = ScalarEdit(label, field);
			if (result < Limits<T>::Min)
				result = Limits<T>::Min;
			else if (result > Limits<T>::Max)
				result = Limits<T>::Max;

			field = (T)result;
		}
		template<typename T> requires std::signed_integral<T>
		static void IntEdit(std::string_view label, T field, Action<T> onEdit)
		{
			int64_t result = ScalarEdit(label, field);
			if (result < Limits<T>::Min)
				result = Limits<T>::Min;
			else if (result > Limits<T>::Max)
				result = Limits<T>::Max;

			field = (T)result;
			onEdit(field);
		}

		template<typename T> requires std::unsigned_integral<T>
		static void UIntEdit(std::string_view label, T& field)
		{
			uint64_t result = UScalarEdit(label, field);
			if (result < Limits<T>::Min)
				result = Limits<T>::Min;
			else if (result > Limits<T>::Max)
				result = Limits<T>::Max;

			field = (T)result;
		}
		template<typename T> requires std::unsigned_integral<T>
		static void UIntEdit(std::string_view label, T field, Action<T> onEdit)
		{
			uint64_t result = UScalarEdit(label, field);
			if (result < Limits<T>::Min)
				result = Limits<T>::Min;
			else if (result > Limits<T>::Max)
				result = Limits<T>::Max;

			field = (T)result;
			onEdit(field);
		}

		static void FloatEdit(std::string_view label, float& field, float speed = 1.0f, float mix = 0.0f, float max = 0.0f);
		static void FloatEdit(std::string_view label, float field, Action<float> onEdit, float speed = 1.0f, float mix = 0.0f, float max = 0.0f);
		static void DoubleEdit(std::string_view label, double& field, float speed = 1.0f, float mix = 0.0f, float max = 0.0f);
		static void DoubleEdit(std::string_view label, double field, Action<double> onEdit, float speed = 1.0f, float mix = 0.0f, float max = 0.0f);

		static void Vector2Edit(std::string_view label, ImVec2& values, float resetVal = 0.0f, float colWidth = 100.0f);
		static void Vector3Edit(std::string_view label, ImVec3& values, float resetVal = 0.0f, float colWidth = 100.0f);
		static void Vector4Edit(std::string_view label, ImVec4& values, float resetVal = 0.0f, float colWidth = 100.0f);
		static void Vector2Edit(std::string_view label, ImVec2 values, Action<const ImVec2&> onEdit, float resetVal = 0.0f, float colWidth = 100.0f);
		static void Vector3Edit(std::string_view label, ImVec3 values, Action<const ImVec3&> onEdit, float resetVal = 0.0f, float colWidth = 100.0f);
		static void Vector4Edit(std::string_view label, ImVec4 values, Action<const ImVec4&> onEdit, float resetVal = 0.0f, float colWidth = 100.0f);

		static void ColourEdit(std::string_view label, ImVec4& colour);

		static void Image(ImTextureID image, const ImVec2& size, float rotation = 0.0f, const ImVec2& uv0= { 0.0f, 0.0f }, const ImVec2& uv1= { 1.0f, 1.0f });
		static void ImageButton(ImTextureID image, const ImVec2& size, Action<> action = {}, const ImVec2& uv0 = { 0.0f, 0.0f }, const ImVec2& uv1 = { 1.0f, 1.0f }, int padding = -1);

		template<typename T>
		static void AddDragDropSource(std::string_view strID, const T& data)
		{
			DragDropSourceInternal(strID, [&]() { sCurrentPayload = MakeSingle<Payload<T>>(data); });
		}
		template<typename T>
		static void AddDragDropTarget(std::string_view strID, Action<const T&> response)
		{
			void* imguiPayload = DragDropTargetInternal(strID);
			if (!imguiPayload)
				return;

			const T& payload = *(T*)imguiPayload;
			response(payload);
		}

		static void OnWidgetSelected(Action<> action);
		static void OnWidgetHovered(Action<> action);

		static void Checkbox(std::string_view label, bool& value, Action<> action = {});
		static void Button(std::string_view label, Action<> action = {});
		static void Button(std::string_view label, const ImVec2& size, Action<> action = {});

		template<typename T>
		static void Combobox(std::string_view label, std::string_view preview, T& value, std::span<const ComboEntry<T>> table)
		{
			if (!BeginCombo(label, preview))
				return;

			// Convert span of entries to base class view and display each entry and return value if item selected.
			const IComboEntry* comboEntry = nullptr;
			std::ranges::for_each(table | std::views::transform([](const ComboEntry<T>& entry) { return dynamic_cast<const IComboEntry*>(&entry); }),
				[=, &comboEntry](const IComboEntry* entry)
				{
					const IComboEntry* result = Widgets::ComboboxEntry(preview, entry);
			comboEntry = result ? result : comboEntry;
				});

			EndCombo();

			if (!comboEntry)
				return;

			const void* comboValue = comboEntry->getVal();
			if (!comboValue)
				return;

			value = T(*(const T*)comboValue);
		}

		template<typename T, typename Func>
		static void Combobox(std::string_view label, std::string_view preview, T value, std::span<const ComboEntry<T>> table, Func onEdit)
		{
			if (!BeginCombo(label, preview))
				return;

			// Convert span of entries to base class view and display each entry and return value if item selected.
			const IComboEntry* comboEntry = nullptr;
			std::ranges::for_each(table | std::views::transform([](const ComboEntry<T>& entry) { return dynamic_cast<const IComboEntry*>(&entry); }),
			[=, &comboEntry](const IComboEntry* entry)
			{
				const IComboEntry* result = Widgets::ComboboxEntry(preview, entry);
				comboEntry = result ? result : comboEntry;
			});

			EndCombo();

			if (!comboEntry)
				return;

			const void* comboValue = comboEntry->getVal();
			if (!comboValue)
				return;

			onEdit(comboEntry->key, *(const T*)comboValue);
		}

	private:
		static int64_t ScalarEdit(std::string_view label, int64_t field);
		static void ScalarEdit(std::string_view label, int64_t field, Action<int64_t> onEdit);
		static uint64_t UScalarEdit(std::string_view label, uint64_t field);
		static void UScalarEdit(std::string_view label, uint64_t field, Action<uint64_t> onEdit);

		static void TreeNodeInternal(void* id, std::string_view text, bool selected, ImGuiTreeNodeFlags flags, Action<> whileOpen);

		static void DragDropSourceInternal(std::string_view strID, Action<> createPayload);
		static void* DragDropTargetInternal(std::string_view strID);

		static bool BeginCombo(std::string_view label, std::string_view preview);
		static const IComboEntry* ComboboxEntry(std::string_view preview, const IComboEntry* entry);
		static void EndCombo();

	private:
		inline static std::unique_ptr<IPayload>			sCurrentPayload  = nullptr;
		inline static std::unique_ptr<ui::MenuBar>		sCurrentMenuBar  = nullptr;
		inline static std::unique_ptr<ui::PopUp>		sCurrentPopup    = nullptr;
		inline static std::unique_ptr<ui::PopUpContext> sCurrentPopupCtx = nullptr;
	};
}