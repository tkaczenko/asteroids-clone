#pragma once

class Drawable
{
public:
    virtual void trace() = 0;
    virtual void updatePosition(const float& dT) = 0;
    virtual void interpolate(const float& dT, const float& i) = 0;
    virtual void draw(SDL_Renderer *r) = 0;
};
