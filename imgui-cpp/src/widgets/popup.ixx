export module imcpp.widgets.popup;

import imcpp.std;
import imcpp.def;

namespace imcpp::ui {

	struct PopUpItem
	{
		std::string_view label;
		Action<> action;

		PopUpItem(std::string_view heading, Action<> delegate)
			: label(heading), action(delegate) {}
	};

	export class PopUp
	{
	public:
		PopUp(std::string_view strID) : mStrID(strID) {}
		~PopUp();

		void addPopUpItem(std::string_view label, Action<> action);

	private:
		std::string_view mStrID;
		std::vector<PopUpItem> mPopUpItems;
	};

	export class PopUpContext
	{
	public:
		~PopUpContext();

		void addPopUpItem(std::string_view label, Action<> action);

	private:
		std::vector<PopUpItem> mPopUpItems;
	};
}