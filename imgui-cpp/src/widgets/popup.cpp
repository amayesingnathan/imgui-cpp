module imcpp.widgets.popup;

import <imgui.h>;

namespace imcpp::ui {

	PopUp::~PopUp()
	{
		if (!ImGui::BeginPopup(mStrID.data()))
			return;

		auto selectedPopups = mPopUpItems;// |
			//std::views::filter([](const auto& item) { return ImGui::MenuItem(item.label.data()); });

		for (const PopUpItem& item : selectedPopups)
		{
			item.action();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	void PopUp::addPopUpItem(std::string_view label, Action<> action)
	{
		mPopUpItems.emplace_back(label, action);
	}

	PopUpContext::~PopUpContext()
	{
		if (!ImGui::BeginPopupContextItem())
			return;

		auto selectedPopups = mPopUpItems;// |
			//std::views::filter([](const auto& item) { return ImGui::MenuItem(item.label.data()); });

		for (const PopUpItem& item : selectedPopups)
			item.action();

		ImGui::EndPopup();
	}

	void PopUpContext::addPopUpItem(std::string_view label, Action<> action)
	{
		mPopUpItems.emplace_back(label, action);
	}
}