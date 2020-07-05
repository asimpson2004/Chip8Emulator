#include "AnimatorComponent.h"

#include "../../Assets/AssetManager.h"
#include "../../Assets/SpritesheetDef.h"

#include "../../Messages/SetSpriteRectMessage.h"
#include "../../Messages/SetSpriteTextureMessage.h"

#include "../../GameDatabase/CreationData/AnimatorComponentCreate.h"
#include "../../GameDatabase/DatabaseTypes.h"

AnimatorComponent::AnimatorComponent(const AnimatorComponentCreate* pCreationData, GameObject* pOwner)
	:Component(pCreationData, pOwner)
{
	Initialise(pCreationData);
}

AnimatorComponent::~AnimatorComponent()
{
}

void AnimatorComponent::Initialise(const AnimatorComponentCreate* pCreationData)
{
	if (pCreationData)
	{
		for (unsigned int i = 0; i < pCreationData->m_AnimationSet.GetItem()->m_Animations.size(); i++)
		{
			AssetManager* pAssetManager = AssetManager::Instance();
			SpritesheetDef* pSpritesheetDef = pAssetManager->GetSpritesheetDef(pCreationData->m_AnimationSet.GetItem()->m_Animations[i].m_Spritesheet);

			if (pSpritesheetDef)
			{
				AddAnimationFromSpriteSheetDef(pCreationData->m_AnimationSet.GetItem()->m_Animations[i].m_AnimationId, pSpritesheetDef, pCreationData->m_AnimationSet.GetItem()->m_Animations[i].m_AnimationName, pCreationData->m_AnimationSet.GetItem()->m_Animations[i].m_FPS, pCreationData->m_AnimationSet.GetItem()->m_Animations[i].m_bLoop);
			}
		}

		SetCurrentAnimation(pCreationData->m_DefaultAnimation);
	}
}

void AnimatorComponent::Update(float delta)
{
	Animate(delta);
}

void AnimatorComponent::SetVisible(bool visibility)
{
	UNUSED_VARIABLE(visibility);
}

void AnimatorComponent::AddAnimation(int animationId, const char* filename, std::vector<Rect>& frames, std::vector<Vector2>& origins, int fps, bool loop)
{
	Animation animation;

	animation.m_Filename = filename;
	animation.m_Frames = frames;
	animation.m_Origins = origins;
	animation.m_fps = fps;
	animation.m_TimePerFrame = 1.0f / (float)animation.m_fps;
	animation.m_bLoop = loop;

	m_Animations[animationId] = animation;
}

void AnimatorComponent::AddAnimationFromSpriteSheetDef(int animationId, SpritesheetDef* pSpritesheetDef, const char* animationName, int fps, bool loop)
{
	if (!pSpritesheetDef)
		return;

	std::vector<Rect> frames;
	std::vector<Vector2> origins;

	for (std::vector<SpritesheetSpriteDef>::iterator iter = pSpritesheetDef->m_pSpriteDefs.begin(); iter != pSpritesheetDef->m_pSpriteDefs.end(); iter++)
	{
		//remove the frame number from the end of the sprite name
		std::string spriteNameFull = (*iter).m_Name;
		std::size_t found = spriteNameFull.find_last_of("_");
		std::string spriteName = spriteNameFull.substr(0, found);

		//if this is a frame that we are looking for add it to the list
		if (spriteName.compare(animationName) == 0)
		{
			Rect rect( (float)(*iter).m_PosX, (float)(*iter).m_PosY, (float)(*iter).m_Width, (float)(*iter).m_Height );
			frames.push_back(rect);

			Vector2 origin((*iter).m_PivotX * (*iter).m_Width, (*iter).m_PivotY * (*iter).m_Height);
			origins.push_back(origin);
		}
	}

	AddAnimation(animationId, pSpritesheetDef->m_Filename.c_str(), frames, origins, fps, loop);
}

void AnimatorComponent::SetCurrentAnimation(int animationId)
{
	std::map<int, Animation>::iterator iter = m_Animations.find(animationId);

	if (iter != m_Animations.end())
	{
		if (m_bInitialised)
		{
			CurrentAnimation().Reset();
		}

		m_CurrentAnimation = animationId;


		SetSpriteTextureMessage setSpriteTextureMessage;
		setSpriteTextureMessage.TextureFilename = CurrentAnimation().m_Filename;

		if (CurrentAnimation().m_CurrentFrame < CurrentAnimation().m_Frames.size())
		{
			setSpriteTextureMessage.SpriteRect = CurrentAnimation().m_Frames[CurrentAnimation().m_CurrentFrame];
			setSpriteTextureMessage.SpriteOrigin = CurrentAnimation().m_Origins[CurrentAnimation().m_CurrentFrame];
		}

		BroadcastMessageToGameObject(&setSpriteTextureMessage);

		m_bInitialised = true;
	}
}

void AnimatorComponent::Animate(float delta)
{
	if (!m_bInitialised)
		return;


	//TODO: Move this inside the animation

	if (CurrentAnimation().m_bPaused)
		return;

	CurrentAnimation().m_CurrentTime += delta;

	if (CurrentAnimation().m_CurrentTime >= CurrentAnimation().m_TimePerFrame)
	{
		CurrentAnimation().m_CurrentFrame++;
		CurrentAnimation().m_CurrentTime = 0;

		if (CurrentAnimation().m_CurrentFrame >= CurrentAnimation().m_Frames.size())
		{
			if (CurrentAnimation().m_bLoop)
			{
				CurrentAnimation().m_CurrentFrame = 0;
			}
			else
			{
				CurrentAnimation().m_CurrentFrame = CurrentAnimation().m_Frames.size() - 1;
				CurrentAnimation().m_bFinished = true;
			}
		}
	}

	if (CurrentAnimation().m_CurrentFrame < CurrentAnimation().m_Frames.size())
	{
		SetSpriteRectMessage setSpriteRectMessage;
		setSpriteRectMessage.SpriteRect = CurrentAnimation().m_Frames[CurrentAnimation().m_CurrentFrame];
		setSpriteRectMessage.SpriteOrigin = CurrentAnimation().m_Origins[CurrentAnimation().m_CurrentFrame];
	
		BroadcastMessageToGameObject(&setSpriteRectMessage);
	}

	//TODO: sort out repeat
}

int AnimatorComponent::GetCurrentFrame()
{
	if (!m_bInitialised)
		return -1;

	return CurrentAnimation().m_CurrentFrame;
}

Animation& AnimatorComponent::CurrentAnimation()
{
	return m_Animations[m_CurrentAnimation];
}

bool AnimatorComponent::AnimationFinished()
{
	if (CurrentAnimation().HasFinished())
	{
		return true;
	}

	return false;
}

void AnimatorComponent::Pause()
{
	CurrentAnimation().m_bPaused = true;
}

void AnimatorComponent::Play()
{
	CurrentAnimation().m_bPaused = false;
}
