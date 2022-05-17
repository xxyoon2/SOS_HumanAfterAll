#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TITLE_SCENE

/*
	이미지 출력하고 만약 스페이스바를 누른다면 다음 씬으로 넘어감
	별다른 버튼은 없을듯?
*/

typedef struct TitleSceneData
{
	Image TitleImage;
	Music TitleBGM;
	//SoundEffect TitleSound;
} TitleSceneData;

void init_title()
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Image_LoadImage(&data->TitleImage, "corridor_bright.jpg");

	Audio_LoadMusic(&data->TitleBGM, "space_bgm.mp3");
	Audio_PlayFadeIn(&data->TitleBGM, INFINITY_LOOP, 3000);
}

void update_title()
{
	//TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_DESCRIPTION);
	}
}

void render_title()
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->TitleImage, 0, 0);
}

void release_title()
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Audio_FreeMusic(&data->TitleBGM);

	SafeFree(g_Scene.Data);
}

#pragma endregion

#pragma region DESCRIPTION_SCENE
void init_description()
{

}

void update_description()
{
	if (Input_GetKeyDown(VK_SPACE))
	{

	}

	if (Input_GetKeyDown(VK_RETURN))
	{

	}
}

void render_description()
{

}

void release_description()
{

}
#pragma endregion

#pragma region STORY_SCENE
void init_story()
{

}

void update_story()
{
	if (Input_GetKeyDown(VK_SPACE))
	{

	}

	if (Input_GetKeyDown(VK_RETURN))
	{

	}
}

void render_story()
{

}

void release_story()
{

}
#pragma endregion

#pragma region CHOICE_SCENE
void init_choice()
{

}

void update_choice()
{
	if (Input_GetKeyDown(VK_SPACE))
	{

	}

	if (Input_GetKeyDown(VK_RETURN))
	{

	}

	if (Input_GetKeyDown(VK_NUMPAD1))
	{

	}

	if (Input_GetKeyDown(VK_NUMPAD2))
	{

	}

	if (Input_GetKeyDown(VK_NUMPAD3))
	{

	}
}

void render_choice()
{

}

void release_choice()
{

}
#pragma endregion

#pragma region ENDING_SCENE
void init_ending()
{

}

void update_ending()
{

}

void render_ending()
{

}

void release_ending()
{

}
#pragma endregion

bool Scene_IsSetNextScene(void)
{
	if (SCENE_NULL == s_nextScene)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Scene_SetNextScene(ESceneType scene)
{
	assert(s_nextScene == SCENE_NULL);
	assert(SCENE_NULL < scene&& scene < SCENE_MAX);

	s_nextScene = scene;
}

void Scene_Change(void)
{
	assert(s_nextScene != SCENE_NULL);

	if (g_Scene.Release)
	{
		g_Scene.Release();
	}

	switch (s_nextScene)
	{
	case SCENE_TITLE:
		g_Scene.Init = init_title;
		g_Scene.Update = update_title;
		g_Scene.Render = render_title;
		g_Scene.Release = release_title;
		break;
	case SCENE_DESCRIPTION:
		g_Scene.Init = init_description;
		g_Scene.Update = update_description;
		g_Scene.Render = render_description;
		g_Scene.Release = release_description;
		break;
	case SCENE_STORY:
		g_Scene.Init = init_story;
		g_Scene.Update = update_story;
		g_Scene.Render = render_story;
		g_Scene.Release = release_story;
		break;
	case SCENE_CHOICE:
		g_Scene.Init = init_choice;
		g_Scene.Update = update_choice;
		g_Scene.Render = render_choice;
		g_Scene.Release = release_choice;
		break;
	case SCENE_ENDING:
		g_Scene.Init = init_ending;
		g_Scene.Update = update_ending;
		g_Scene.Render = render_ending;
		g_Scene.Release = release_ending;
		break;

	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}