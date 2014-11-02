/** MainMenuUI.h - This widget implements all of the root level main menu items. 
*
* For a basic tutorial on creating menus with Slate, visit http://minalien.com/unreal-engine-4-creating-menus-with-slatec-part-1/
*
*/

#pragma once

#include "Slate.h"

/**
* Lays out and controls the Main Menu UI.
**/
class SMainMenuUI : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SMainMenuUI)
		: _MenuHUD()
	{
	}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMainMenuHUD>, MenuHUD);

	SLATE_END_ARGS()

public:
	/**
	* Constructs and lays out the Main Menu UI Widget.
	*
	* \args Arguments structure that contains widget-specific setup information.
	**/
	void Construct(const FArguments& args);

private:
	/** Click handler for the Host button - Calls MenuHUD's HostClicked() event. */
	FReply HostClicked();

	/** Click handler for the Options button - Calls MenuHUD's OptionsClicked() event. */
	FReply OptionsClicked();

	/** Click handler for the Quit button - Calls MenuHUD's QuitClicked() event. */
	FReply QuitClicked();

	/**
	* Stores a weak reference to the HUD controlling this class.
	**/
	TWeakObjectPtr<class AMainMenuHUD> MenuHUD;
};