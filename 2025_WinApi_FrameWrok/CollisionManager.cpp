#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
void CollisionManager::Update()
{
	for (UINT Row = 0; Row < (UINT)Layer::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)Layer::END; ++Col)
		{
			if (m_objectLayer[Row] & (1 << Col))
			{
				//int a = 0;
				CollisionLayerUpdate((Layer)Row, (Layer)Col);
			}
		}
	}
}

void CollisionManager::CheckLayer(Layer _left, Layer _right)
{
	// 작은쪽을 행으로 씁시다.
	// 작은 값을 LAYER의 행으로, 큰 값을 열
	UINT Row = (UINT)_left;
	UINT Col = (UINT)_right;
	//Row = min(Row, Col);
	if (Row > Col)
		std::swap(Row, Col);
	//m_arrLayer[Row];
	//Col;

	//// 비트 연산
	// 체크가 되어있다면
	if (m_objectLayer[Row] & (1 << Col))
	{
		// 체크 풀기
		m_objectLayer[Row] &= ~(1 << Col);
	}
	// 체크가 안되어있다면r
	else
	{
		m_objectLayer[Row] |= (1 << Col);
	}
	int a = 0;
}

void CollisionManager::CheckReset()
{
	// 메모리 초기화
	memset(m_objectLayer, 0, sizeof(UINT) * (UINT)Layer::END);
}

void CollisionManager::CollisionLayerUpdate(Layer _left, Layer _right)
{
	std::shared_ptr<Scene> pCurrentScene = GET_SINGLE(SceneManager)->GetCurScene();
	const vector<Object*>& vecLeftLayer = pCurrentScene->GetLayerObjects(_left);
	const vector<Object*>& vecRightLayer = pCurrentScene->GetLayerObjects(_right);
	std::unordered_map<ULONGLONG, bool>::iterator iter;
	for (size_t i = 0; i < vecLeftLayer.size(); ++i)
	{
		Collider* pLeftCollider = vecLeftLayer[i]->GetComponent<Collider>();
		// 충돌체 없는 경우
		if (nullptr == pLeftCollider)
			continue;
		for (size_t j = 0; j < vecRightLayer.size(); j++)
		{
			Collider* pRightCollider = vecRightLayer[j]->GetComponent<Collider>();
			// 충돌체가 없거나, 자기자신과의 충돌인 경우
			if (nullptr == pRightCollider || vecLeftLayer[i] == vecRightLayer[j])
				continue;

			// 두 충돌체로만 만들 수 있는 ID
			ULONGLONG colliderID = MakePairKey(pLeftCollider->GetID(), pRightCollider->GetID());

			iter = m_mapCollisionInfo.find(colliderID);
			// 이전 프레임 충돌한 적 없다.
			if (iter == m_mapCollisionInfo.end())
			{
				// 충돌 정보가 미등록된 상태인 경우 등록(충돌하지 않았다로)
				m_mapCollisionInfo.insert({ colliderID, false });
				//m_mapCollisionInfo[colliderID.ID] = false;
				iter = m_mapCollisionInfo.find(colliderID);
			}

			// 충돌여부 확인
			if (IsCollision(pLeftCollider, pRightCollider))
			{
				// 이전에도 충돌중
				if (iter->second)
				{
					if (vecLeftLayer[i]->GetIsDead() || vecRightLayer[j]->GetIsDead())
					{
						pLeftCollider->ExitCollision(pRightCollider);
						pRightCollider->ExitCollision(pLeftCollider);
						iter->second = false;
					}
					else
					{
						pLeftCollider->StayCollision(pRightCollider);
						pRightCollider->StayCollision(pLeftCollider);
					}
				}
				else // 이전에 충돌 x
				{
					if (!vecLeftLayer[i]->GetIsDead() && !vecRightLayer[j]->GetIsDead())
					{
						pLeftCollider->EnterCollision(pRightCollider);
						pRightCollider->EnterCollision(pLeftCollider);
						iter->second = true;
					}
				}
			}
			else // 충돌 안하네?
			{
				if (iter->second) // 근데 이전에 충돌중
				{
					pLeftCollider->ExitCollision(pRightCollider);
					pRightCollider->ExitCollision(pLeftCollider);
					iter->second = false;
				}
			}
		}
	}

}

bool CollisionManager::IsCollision(Collider* _left, Collider* _right)
{
	auto* circle1 = dynamic_cast<CircleCollider*>(_left);
	auto* circle2 = dynamic_cast<CircleCollider*>(_right);

	if (circle1 && circle2)
		return IsCircleCircle(circle1, circle2);

	if (circle1 && !circle2)
		return IsCircleAABB((BoxCollider*)_right, circle1);

	if(!circle1 && circle2)
		return IsCircleAABB((BoxCollider*)_left, circle2);

	return IsAABBAABB((BoxCollider*)_left, (BoxCollider*)_right);
}

bool CollisionManager::IsAABBAABB(BoxCollider* _left, BoxCollider* _right)
{
	Vec2 leftPos = _left->GetUpdatedPos();
	Vec2 rightPos = _right->GetUpdatedPos();
	Vec2 leftSize = _left->GetSize();
	Vec2 rightSize = _right->GetSize();

	return (fabsf(rightPos.x - leftPos.x) < (leftSize.x + rightSize.x) / 2.f
		&& fabsf(rightPos.y - leftPos.y) < (leftSize.y + rightSize.y) / 2.f);
}

bool CollisionManager::IsCircleAABB(BoxCollider* aabb, CircleCollider* circle)
{
	Vec2 circlePos = circle->GetUpdatedPos();
	float radius = circle->GetRadius();

	Vec2 boxPos = aabb->GetUpdatedPos();
	Vec2 boxSize = aabb->GetSize();

	float boxX1 = boxPos.x - (boxSize.x / 2);
	float boxX2 = boxPos.x + (boxSize.x / 2);
	float boxY1 = boxPos.y + (boxSize.y / 2);
	float boxY2 = boxPos.y - (boxSize.y / 2);

	float closestX = std::clamp(circlePos.x, boxX1, boxX2);
	float closestY = std::clamp(circlePos.y, boxY1, boxY2);

	float x = circlePos.x - closestX;
	float y = circlePos.y - closestY;

	float dist = sqrt((x * x) + (y * y));

	return dist < radius;
}

bool CollisionManager::IsCircleCircle(CircleCollider* _left, CircleCollider* _right)
{
	// 반지름 반지름 원의 거리 반지름보다 작으면 충돌

	Vec2 leftPos = _left->GetUpdatedPos();
	Vec2 rightPos = _right->GetUpdatedPos();
	float leftRadius = _left->GetRadius();
	float rightRadius = _right->GetRadius();
	float dist = (leftPos - rightPos).Length();

	return dist <= leftRadius + rightRadius;
}

ULONGLONG CollisionManager::MakePairKey(UINT a, UINT b)
{
	// 좌우 순서를 무의미하게: 작은 값을 lo, 큰 값을 hi
	COLLIDER_ID id = {};
	id.lo_ID = (a < b) ? a : b;
	id.hi_ID = (a < b) ? b : a;
	return id.ID;
}
