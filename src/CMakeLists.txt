add_library(GameL 

	Scenes.c

	Components/Camera_Controller.c
	Components/Gem_Controller.c
	Components/Player_Controller.c
	Components/Rope_Controller.c
	Components/Portal_Catcher.c
	Components/Level_Transitioner.c
	Components/Level_Select_Navigator.c
	Components/Level_Select_Camera_Controller.c
	Components/Portal_Renderer.c
	Components/Timer_Clock.c
	Components/Score_Counter.c
	Components/Display_Time.c
	Components/Level_Title.c

	Entities/Camera.c
	Entities/Gem.c
	Entities/Hook_Surface.c
	Entities/Player.c
	Entities/Rope.c
	Entities/UI_Camera.c
	Entities/Portal.c
	Entities/UI_Manager.c
	Entities/Menu_Button.c
	Entities/Level_Selector.c
	Entities/Level_Select_Camera.c
	Entities/Menu_Camera.c
	Entities/Background.c
	Entities/Menu_Text.c
	Entities/Timer.c
	Entities/Score.c

	Scenes/Level_1.c
	Scenes/Level_2.c
	Scenes/Main_Menu.c
	Scenes/Level_Select_Menu.c

	Builders/End_Level_Menu_Build.c
	Builders/Level_UI_Build.c
	Builders/Level_1_Surfaces_Build.c
	Builders/Level_2_Basic_Build.c

)