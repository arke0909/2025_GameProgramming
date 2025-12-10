#pragma once
#include "Enemy.h"
#include "Player.h"
#include "EntityStateMachine.h"
#include "PhaseData.h"
#include "BossWindow.h"
#include <vector>

class EnemyBoss : public Enemy
{
public:
    EnemyBoss();
    ~EnemyBoss() override = default;

    void CreateEnemyWindow();
    void Update() override;
    void Render(HDC hdc) override;

    void ChangeState(std::string state);
    void EnterCollision(Collider* _other);

    int GetCurrentPhase() const { return _currentPhase; }
    PhaseData GetCurrentPhaseData() const;

    void ExecuteCircleShot(const PatternData& pattern);
    void ExecuteLinearShot(const PatternData& pattern);
    void ExecuteBounceShot(const PatternData& pattern);
    void ExecuteTrackingShot(const PatternData& pattern);
    void ExecuteMoveSprayShot(const PatternData& pattern);
    void ExecuteCircularSector(const PatternData& pattern);
    void ExecuteDistanceMoveSkill();

    Player* GetTarget() const { return _player; }

private:
    void InitializePhases();
    void CheckPhaseTransition();
    void TransitionToPhase(int phase);

    BossWindow* _window;
    int _currentPhase;
    std::vector<PhaseData> _phases;

    const float _minDistance = 200.0f;
    const float _maxDistance = 390.0f;
    const float _moveStep = 80.0f;

    bool _isMoving = false;
    Vec2 _moveTarget;
    float _moveSpeed = 600.f;

    bool _isSprayMoving = false;
    float _sprayTime = 0.f;
    float _sprayDuration = 0.8f;
    float _sprayInterval = 0.1f;
    float _sprayAccTime = 0.f;
};