#include "pch.h"
#include "Animation.h"

Animation::Animation() : Super(ResourceType::Animation)
{
}

Animation::~Animation()
{
}

void Animation::Load(const wstring& path)
{
    ResourceBase::Load(path);

    tinyxml2::XMLDocument doc;
    string pathStr(path.begin(), path.end());
    XMLError result = doc.LoadFile(pathStr.c_str());
    assert(result == XML_SUCCESS);

    XMLElement* root = doc.FirstChildElement();
    string nameStr = root->Attribute("Name");
    _name = wstring(nameStr.begin(), nameStr.end());
    _loop = root->BoolAttribute("Loop");
    _path = path;

    XMLElement* node = root->FirstChildElement();
    while (node)
    {
        Keyframe keyframe;

        keyframe.offset.x = node->FloatAttribute("OffsetX");
        keyframe.offset.y = node->FloatAttribute("OffsetY");
        keyframe.size.x = node->FloatAttribute("SizeX");
        keyframe.size.y = node->FloatAttribute("SizeY");
        keyframe.time = node->FloatAttribute("Time");

        AddKeyframe(keyframe);
        node = node->NextSiblingElement();
    }
}

void Animation::Save(const wstring& path)
{
    ResourceBase::Save(path);

    tinyxml2::XMLDocument doc;
    XMLElement* root = doc.NewElement("Animation");
    doc.LinkEndChild(root);

    string nameStr(GetName().begin(), GetName().end());
    root->SetAttribute("Name", nameStr.c_str());
    root->SetAttribute("Loop", _loop);
    root->SetAttribute("TexturePath", "TODO");

    for (const auto& keyframe : _keyframes)
    {
        XMLElement* elem = doc.NewElement("Keyframe");
        root->LinkEndChild(elem);

        elem->SetAttribute("OffsetX", keyframe.offset.x);
        elem->SetAttribute("OffsetY", keyframe.offset.y);
        elem->SetAttribute("SizeX", keyframe.size.x);
        elem->SetAttribute("SizeY", keyframe.size.y);
        elem->SetAttribute("Time", keyframe.time);
    }

    string pathStr(path.begin(), path.end());
    auto result = doc.SaveFile(pathStr.c_str());
}

const Keyframe& Animation::GetKeyframe(int32 index)
{
    return _keyframes[index];
}

void Animation::AddKeyframe(const Keyframe& keyframe)
{
    _keyframes.push_back(keyframe);
}

Vector2 Animation::GetTextureSize()
{
    return _texture->GetSize();
}