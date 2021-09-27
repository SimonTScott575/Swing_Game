add_library(Game_Engine
	ECS/geComponent.c
	ECS/geEntity.c
	ECS/geSystem.c

	Graphics/Graphics.c
	Graphics/grMesh.c
	Graphics/grModel.c
	Graphics/grRenderer.c
	Graphics/grScreen.c
	Graphics/grShader.c
	Graphics/grTexture.c
	Graphics/grImage.c
	Graphics/grText_Renderer.c
	Graphics/Formats/grColours.c
	Graphics/Formats/grTypes.c
	Graphics/Defaults/grCamera.c
	Graphics/Defaults/grColour_Render.c
	Graphics/Defaults/grRendering_System.c
	Graphics/Defaults/grSprite.c

	Physics/phCollider.c
	Physics/phCollision_Solver.c
	Physics/phJoint.c
	Physics/phRB_System.c
	Physics/phRigid_Body.c

	UI/geButton_UI.c
	UI/geUI_Element.c
	UI/geUI_Renderer.c
	UI/Defaults/geUI_Manager.c

	Game_Engine.c
	geGame.c
	geInput.c
	geInput_States.c
	geScene.c
	geWindow.c
)