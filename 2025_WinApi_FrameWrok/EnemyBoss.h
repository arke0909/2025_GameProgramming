#pragma once
#include "Entity.h"
#include "Player.h"
#include "EntityStateMachine.h"
#include "PhaseData.h"
#include <vector>

class EnemyBoss :
    public Entity
{
public:
    EnemyBoss();
    ~EnemyBoss();

    void CreateEnemyWindow();
    void SetTarget(Player* player);
    void Update() override;
    void Render(HDC hdc) override;

    void ChangeState(std::string state);
    void UpdateHP(int value);
    int GetHP();
    void EnterCollision(Collider* _other);

    int GetCurrentPhase() const { return _currentPhase; } // 현재 페이지
    PhaseData GetCurrentPhaseData() const; // 현재 페이지의 데이터

    //스킬들
    void ExecuteCircleShot(const PatternData& pattern);
    void ExecuteLinearShot(const PatternData& pattern);
    void ExecuteBounceShot(const PatternData& pattern);
    void ExecuteTrackingShot(const PatternData& pattern);

    Player* GetTarget() const { return _player; }

private:
    void InitializePhases();
    void CheckPhaseTransition();
    void TransitionToPhase(int phase);

    EntityStateMachine* _stateMachine;
    Window* _window;
    Player* _player;

    int _hp;
    int _maxHP;
    int _currentPhase;

    std::vector<PhaseData> _phases;
};