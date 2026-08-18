#pragma once

enum class CameraMode : uint8
{
    Perspective = 0,
    Orthographic,
};

class Camera : public Component
{
    using Super = Component;
public:
    Camera();
    ~Camera();

    virtual void Awake() override;
    virtual void Start() override;
    virtual void FixedUpdate() override;
    virtual void LateUpdate() override;
    virtual void Update() override;

    CameraMode GetMode() const { return _mode; }
    void SetMode(CameraMode mode) { _mode = mode; }

    // 실제 뷰 행렬을 업데이트하는 함수
    void UpdateMatrix();

    static Matrix S_MatView;
    static Matrix S_MatProjection;

private:
    CameraMode _mode = CameraMode::Orthographic;
};