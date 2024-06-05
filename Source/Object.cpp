#include "Object.h"
#include <unordered_map>

Object::Object(int mX, int mY, std::string mPath)
{
    mPosX = mX;
    mPosY = mY;
    objPath = mPath;
}

Object::~Object() {}

void Object::OnCollisionEnter() {}

void Object::Update(void)
{
    mVelY = 4 * DOT_VEL;
    mPosY += mVelY;
}

void Object::handleEvent(SDL_Event& e)
{
    // If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        // Adjust the velocity
        switch (e.key.keysym.sym)
        {
            case SDLK_UP: mVelY -= 4 * DOT_VEL; break;
            case SDLK_DOWN: mVelY += 4 * DOT_VEL; break;
            case SDLK_LEFT: mVelX -= 4 * DOT_VEL; break;
            case SDLK_RIGHT: mVelX += 4 * DOT_VEL; break;
        }
    }
    // If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        // Adjust the velocity
        switch (e.key.keysym.sym)
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Object::move()
{
    // Move the object left or right
    mPosX += mVelX;

    // If the object went too far to the left or right
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH))
    {
        // Move back
        mPosX -= mVelX;
    }

    // Move the object up or down
    mPosY += mVelY;

    // If the object went too far up or down
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT))
    {
        // Move back
        mPosY -= mVelY;
    }
}

void Object::render()
{
    // Map to store textures associated with object paths
    static std::unordered_map<std::string, Texture*> textureMap = {
        { "../../media/sand.png", GraphicManager::GetInstance().gSandTexture },
        { "../../media/water.png", GraphicManager::GetInstance().gWaterTexture },
        { "../../media/wood.png", GraphicManager::GetInstance().gWoodTexture },
        { "../../media/lava.png", GraphicManager::GetInstance().gLavaTexture },
        { "../../media/frame.png", GraphicManager::GetInstance().gFrameTexture },
        { "../../media/smoke.png", GraphicManager::GetInstance().gSmokeTexture }
    };

    // Find the texture associated with the object path
    auto it = textureMap.find(objPath);
    if (it != textureMap.end())
    {
        // Render the texture if found
        it->second->render(mPosX, mPosY);
    }
}