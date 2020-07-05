#ifndef _ANIMATOR_COMPONENT_H_
#define _ANIMATOR_COMPONENT_H

#include "../Component.h"

#include <vector>
#include <map>

#include "../../Maths/Rect.h"
#include "../../Maths/Vector2.h"
#include "../ComponentType.h"

class GameObject;
struct SpritesheetDef;
class AnimatorComponentCreate;

struct Animation
{
	Animation() 
	:m_Filename(nullptr)
	,m_CurrentFrame(0)
	,m_fps(0)
	,m_CurrentTime(0.0f)
	,m_TimePerFrame(0.0f)
	,m_bLoop(false)
	,m_bPaused(false)
	,m_bFinished(false)
	{
	}

	const char* m_Filename;
	unsigned int m_CurrentFrame;
	int m_fps;
	std::vector<Rect> m_Frames;
	std::vector<Vector2> m_Origins;
	float m_CurrentTime;
	float m_TimePerFrame;
	bool m_bLoop;
	bool HasFinished() { return m_bFinished; }
	bool m_bPaused;
	bool m_bFinished;
	void Reset() { m_CurrentFrame = 0; m_CurrentTime = 0; m_bFinished = false; m_bPaused = false; }

private:
};




class AnimatorComponent : public Component
{
public:
	AnimatorComponent(const AnimatorComponentCreate* pCreationData, GameObject* pOwner);
	virtual ~AnimatorComponent();

	void Initialise(const AnimatorComponentCreate* pCreationData);
	virtual void Update(float delta);


	void SetCurrentAnimation(int animationId);
	int GetCurrentAnimation() { return m_CurrentAnimation; }

	bool AnimationFinished();

	void Animate(float delta);

	int GetCurrentFrame();

	void SetVisible(bool visibility);

	void Pause();
	void Play();

	void AddAnimation(int animationId, const char* filename, std::vector<Rect>& frames, std::vector<Vector2>& origins, int fps, bool loop = true);
	void AddAnimationFromSpriteSheetDef(int animationId, SpritesheetDef* pSpritesheetDef, const char* animationName, int fps, bool loop = true);

	Animation& CurrentAnimation();

	std::map<int, Animation> m_Animations;
	int m_CurrentAnimation;

	bool m_bInitialised;
};

#endif
