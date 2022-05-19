#include "stdafx.h"
#include "Scene.h"
#include "Csv.h"
#include "Common.h"

#include "Framework.h"
#include "Framework/Text.h"

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

	Image_LoadImage(&data->TitleImage, "corridor_dark.png");

	Audio_LoadMusic(&data->TitleBGM, "space_bgm.mp3");
	Audio_PlayFadeIn(&data->TitleBGM, INFINITY_LOOP, 3000);
}

void update_title()
{
	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_DESCRIPTION);
	}

	if (Input_GetKeyDown(VK_RETURN))
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
typedef struct DescriptionSceneData
{
	Image DescriptionImage;
	Music DescriptionBGM;
} DescriptionSceneData;

void init_description()
{
	g_Scene.Data = malloc(sizeof(DescriptionSceneData));
	memset(g_Scene.Data, 0, sizeof(DescriptionSceneData));

	DescriptionSceneData* data = (DescriptionSceneData*)g_Scene.Data;

	Image_LoadImage(&data->DescriptionImage, "description.png");

	Audio_LoadMusic(&data->DescriptionBGM, "space_bgm.mp3");
	Audio_PlayFadeIn(&data->DescriptionBGM, INFINITY_LOOP, 3000);
}

void update_description()
{
	if (Input_GetKeyDown(VK_SPACE))
	{
		/*
			아마 다음 이미지가 있다면 그 이미지를 보여주는 것으로 해야함.
			이미지를 배열로 받아야할 수도 있음
		*/
	}

	if (Input_GetKeyDown(VK_RETURN))
	{
		Scene_SetNextScene(SCENE_STORY);
	}
}

void render_description()
{
	DescriptionSceneData* data = (DescriptionSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->DescriptionImage, 0, 0);
}

void release_description()
{
	DescriptionSceneData* data = (DescriptionSceneData*)g_Scene.Data;

	Audio_FreeMusic(&data->DescriptionBGM);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region STORY_SCENE
/*
	오로지 텍스트로만 진행되는 부분
	가끔 연출이 필요할 수도 있음
*/

#define SOLID 0
#define SHADED 1
#define BLENDED 2

CsvFile csvFile;
Text CsvText[500][500];
bool isCreated = false;

int32 sceneNumber = 1;

typedef struct MainSceneOption
{
	//선택지 1 / 선택지 1에 대한 씬 번호 / 선택지 2 / 선택지 2에 대한 씬 번호 / 선택지 3(타이머로 인한 선택지) / 선택지 3에 대한 씬 번호 / 엔딩 옵션
	int32 SceneOption;	// 씬 옵션
	bool TimerOption[4];	// 타이머 옵션
	Text StoryText;
} MainSceneOption;

typedef struct StorySceneData
{
	//int32	SceneNumber;	// 씬 번호
	Text	TestText;
	int32	FontSize;
	int32	RenderMode;
	Image	TestImage;
	Image	BackgroundImage;
	Music	BackgroundMusic;
} StorySceneData;

void init_story()
{
	if (!isCreated)
	{
		CreateCsvFile(&csvFile, "HumanAfterAll.csv");  // 희희 
		isCreated = true;
	}

	g_Scene.Data = malloc(sizeof(StorySceneData));
	memset(g_Scene.Data, 0, sizeof(StorySceneData));

	StorySceneData* data = (StorySceneData*)g_Scene.Data;

	for (int r = 0; r < csvFile.RowCount; ++r)
	{
		for (int c = 0; c < csvFile.ColumnCount; ++c)
		{
			wchar_t* str = ParseToUnicode(csvFile.Items[r][c]);
			Text_CreateText(&CsvText[r][c], "d2coding.ttf", 16, str, wcslen(str));
			free(str);
		}
	}

	/*wchar_t* str = ParseToUnicode(csvFile.Items[sceneNumber][1]);

	Text_CreateText(&CsvText[sceneNumber][1], "d2coding.ttf", 16, str, wcslen(str));
	free(str);*/

	/*for (int c = 0; c < csvFile.ColumnCount; ++c)
	{
		wchar_t* str = ParseToUnicode(csvFile.Items[c][1]);
		
		Text_CreateText("d2coding.ttf", 16, str, wcslen(str));
		free(str);
	}*/


	data->FontSize = 24;

	data->RenderMode = SOLID;


	Image_LoadImage(&data->BackgroundImage, "scene1.png");

	Audio_LoadMusic(&data->BackgroundMusic, "space_bgm.mp3");
	Audio_PlayFadeIn(&data->BackgroundMusic, INFINITY_LOOP, 3000);


}

void update_story()
{
	StorySceneData* data = (StorySceneData*)g_Scene.Data;


	if (Input_GetKeyDown(VK_SPACE))
	{
		/*
			텍스트 줄단위로 스킵.
			완전히 스킵이 되는 것이 아닌 텍스트가 출력되어있어야 함
		*/
	}

	if (Input_GetKeyDown(VK_RETURN))
	{
		++sceneNumber;
	}

}

void render_story()
{
	StorySceneData* data = (StorySceneData*)g_Scene.Data;
	SDL_Color color = { .a = 255 };

	//for (int r = 0; r < csvFile.RowCount; ++r)
	//{
	//	for (int c = 0; c < csvFile.ColumnCount; ++c)
	//	{
	//		Renderer_DrawTextSolid(&CsvText[c][r], 30 * c, 150 * r, color);
	//	}
	//}

	Renderer_DrawImage(&data->BackgroundImage, 0, 0);

	/*for (int r = 0; r < csvFile.RowCount; ++r)
	{
		Renderer_DrawTextSolid(&CsvText[1][r], 30 * 4, 150 * r, color);
	}*/

	//Renderer_DrawTextSolid(&CsvText[1][r], 30 * 4, 150 * r, color);
	Renderer_DrawTextSolid(&CsvText[sceneNumber][1], 30 * 2, 150 * 1, color);
	

	/*switch (data->RenderMode)
	{
	case SOLID:
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->TestText, 400, 400, color);
	}
	break;
	case SHADED:
	{
		SDL_Color bg = { .a = 255 };
		SDL_Color fg = { .r = 255, .g = 255, .a = 255 };
		Renderer_DrawTextShaded(&data->TestText, 400, 400, fg, bg);
	}
	break;
	case BLENDED:
	{
		Renderer_DrawImage(&data->TestImage, 400, 400);
		SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		Renderer_DrawTextBlended(&data->TestText, 400, 400, color);
	}
	break;
	}*/
}

void release_story()
{
	StorySceneData* data = (StorySceneData*)g_Scene.Data;

	Audio_FreeMusic(&data->BackgroundMusic);
	//Text_FreeText(&data->TestText);
	Text_FreeText(&data->TestText);
	SafeFree(g_Scene.Data);

	
}
#pragma endregion



#pragma region ENDING_SCENE
/*

	엔딩 A, B, C 그리고 배드엔딩 따로 열거형으로 만들어줘야할 것 같음

*/


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