#pragma once

struct Keyframe
{
    Vector2 offset = Vector2{0.f, 0.f};
    Vector2 size = Vector2{0.f, 0.f};
    float time = 0.f;
};

class Animation : public ResourceBase
{
    using Super = ResourceBase;
public:
    Animation();
    virtual ~Animation();

    virtual void Load(const wstring& path) override;
    virtual void Save(const wstring& path) override;

    void SetLoop(bool loop) { _loop = loop; }
    bool IsLoop() const { return _loop; }

    void SetTexture(shared_ptr<Texture> texture) { _texture = texture; }
    shared_ptr<Texture> GetTexture() const { return _texture; }

    Vector2 GetTextureSize();

    const Keyframe& GetKeyframe(int32 index);
    int32 GetKeyframeCount() const { return _keyframes.size(); }
    void AddKeyframe(const Keyframe& keyframe);

private:
    bool _loop = false;
    shared_ptr<Texture> _texture;
    vector<Keyframe> _keyframes;
};