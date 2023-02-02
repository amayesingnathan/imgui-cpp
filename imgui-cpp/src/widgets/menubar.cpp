module imcpp.widgets.menubar;

import <imgui.h>;

namespace imcpp::ui {

	MenuBar::~MenuBar()
	{
		if (!ImGui::BeginMenuBar())
			return;

		auto openMenus = mMenuItems | 
			std::views::filter([](const auto& heading) { return ImGui::BeginMenu(heading.label.data()); });

		for (const MenuHeading& heading : openMenus)
		{
			for (const MenuItem& item : heading.menu)
			{
				switch (item.type)
				{
				case MenuItemType::Action:
					if (ImGui::MenuItem(item.label.data(), item.shortcut.data()))
						item.action();
					break;

				case MenuItemType::Switch:
					ImGui::MenuItem(item.label.data(), item.shortcut.data(), item.display);
					break;

				case MenuItemType::Separator:
					ImGui::Separator();
					break;
				}
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	void MenuBar::addHeading(std::string_view heading)
	{
		mMenuItems.emplace_back(heading);
	}

	void MenuBar::addMenuItemAction(std::string_view label, std::string_view shortcut, Action<> action)
	{
		MenuHeading& lastMenu = mMenuItems.back();
		lastMenu.menu.emplace_back(MenuItemType::Action, label, shortcut, action);
	}

	void MenuBar::addMenuItemSwitch(std::string_view label, std::string_view shortcut, bool& show)
	{
		MenuHeading& lastMenu = mMenuItems.back();
		lastMenu.menu.emplace_back(MenuItemType::Switch, label, shortcut, show);
	}

	void MenuBar::addSeparator()
	{
		MenuHeading& lastMenu = mMenuItems.back();
		lastMenu.menu.emplace_back(MenuItemType::Separator);
	}
}