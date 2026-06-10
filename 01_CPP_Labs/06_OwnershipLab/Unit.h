#pragma once

#include <memory>
#include <string>
#include <vector>

class Unit
{
public:
    Unit();
    Unit(const std::string& name, int maxHp);
    ~Unit();

    void TakeDamage(int damage);
    void Heal(int amount);
    void Print() const;

    const std::string& GetName() const;
    int GetHp() const;
    int GetMaxHp() const;
    bool IsDead() const;

private:
    std::string m_name;
    int m_hp;
    int m_maxHp;
};

std::unique_ptr<Unit> CreateUnit(const std::string& name, int maxHp);

void RunStackLifetimeDemo();
void RunUniquePtrDemo();
void RunSharedPtrDemo();
void RunWeakPtrDemo();

void PrintParty(const std::vector<std::unique_ptr<Unit>>& party);

Unit* FindUnitByName(
    std::vector<std::unique_ptr<Unit>>& party,
    const std::string& name
);

// 도전 1: 죽은 유닛 제거
// HP 0인 Unit있으면 party에서 제거.
// 제거된 Unit이 있으면 소멸자 로그 출력.
// 생존 Unit이 있으면 유지.
// 제거 후 몇명 제거했는지 출력.
void RemoveDeadUnits(std::vector<std::unique_ptr<Unit>>& party);

// 도전 2: 소유권 이전 실험
// 이름을 찾으면 해당 Unit 소유권을 vector 밖으로 이동.
// vector에서 제거하면 슬롯에서 사라짐.
// 반환값은 찾은 Unit의 unique_ptr. 찾는 이름이 없으면 nullptr 반환.
std::unique_ptr<Unit> ExtractUnitByName(
    std::vector<std::unique_ptr<Unit>>& party,
    const std::string& name
);

