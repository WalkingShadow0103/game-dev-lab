#include "Unit.h"

#include <iostream>

Unit::Unit()
    : m_name("Unknown")
    , m_hp(100)
    , m_maxHp(100)
{
    std::cout << "[Created] " << m_name << "\n";
}

Unit::Unit(const std::string& name, int maxHp)
    : m_name(name)
    , m_hp(maxHp)
    , m_maxHp(maxHp)
{
    if (m_maxHp <= 0)
    {
        m_maxHp = 1;
        m_hp = 1;
    }

    std::cout << "[Created] " << m_name << "\n";
}

Unit::~Unit()
{
    std::cout << "[Destroyed] " << m_name << "\n";
}

void Unit::TakeDamage(int damage)
{
    if (damage < 0)
    {
        std::cout << "Damage cannot be negative.\n";
        return;
	}

    m_hp -= damage;

    if (m_hp < 0)
    {
        m_hp = 0;
    }

	std::cout << m_name << " took " << damage << " damage. HP: " << m_hp << "\n";
}

void Unit::Heal(int amount)
{
    if (amount < 0)
    {
        std::cout << "Heal amount cannot be negative.\n";
        return;
	}

    if (IsDead())
    {
        std::cout << "Dead unit cannot be healed: " << m_name << "\n";
        return;
	}

    m_hp += amount;

    if (m_hp > m_maxHp)
    {
        m_hp = m_maxHp;
	}

	std::cout << m_name << " healed " << amount << ". HP: " << m_hp << "\n";
}

void Unit::Print() const
{
    std::cout << m_name
        << " | HP: " << m_hp << "/" << m_maxHp
        << " | Dead: " << (IsDead() ? "Yes" : "No")
        << "\n";
}

const std::string& Unit::GetName() const
{
    return m_name;
}

int Unit::GetHp() const
{
    return m_hp;
}

int Unit::GetMaxHp() const
{
    return m_maxHp;
}

bool Unit::IsDead() const
{
    return m_hp <= 0;
}

std::unique_ptr<Unit> CreateUnit(const std::string& name, int maxHp)
{
    return std::make_unique<Unit>(name, maxHp);
}

void RunStackLifetimeDemo()
{
    std::cout << "=== Stack Lifetime Demo ===\n";

    {
        Unit localUnit("LocalKnight", 100);
        localUnit.Print();
        std::cout << "Leaving inner scope soon.\n";
    }

    std::cout << "Inner scope ended.\n";
}

void RunUniquePtrDemo()
{
    std::cout << "=== unique_ptr Demo ===\n";

    std::unique_ptr<Unit> unit = std::make_unique<Unit>("UniqueKnight", 120);
    unit->Print();

    std::cout << "unit owns UniqueKnight.\n";

    std::unique_ptr<Unit> movedUnit = std::move(unit);

    if (unit == nullptr)
    {
        std::cout << "unit is now nullptr after move.\n";
    }

    movedUnit->Print();

    std::cout << "Leaving unique_ptr demo.\n";
}

void RunSharedPtrDemo()
{
    std::cout << "=== shared_ptr Demo ===\n";

    std::shared_ptr<Unit> boss = std::make_shared<Unit>("SharedBoss", 300);

    std::cout << "use_count: " << boss.use_count() << "\n";

    {
        std::shared_ptr<Unit> anotherOwner = boss;
        std::cout << "use_count after copy: " << boss.use_count() << "\n";
        anotherOwner->Print();
    }

    std::cout << "use_count after inner scope: " << boss.use_count() << "\n";
    std::cout << "Leaving shared_ptr demo.\n";
}

void RunWeakPtrDemo()
{
    std::cout << "=== weak_ptr Demo ===\n";

    std::weak_ptr<Unit> observer;

    {
        std::shared_ptr<Unit> boss = std::make_shared<Unit>("WeakBoss", 250);
        observer = boss;

        std::cout << "Inside scope. expired: "
            << (observer.expired() ? "Yes" : "No")
            << "\n";

        std::shared_ptr<Unit> locked = observer.lock();

        if (locked != nullptr)
        {
            locked->Print();
        }
    }

    std::cout << "After scope. expired: "
        << (observer.expired() ? "Yes" : "No")
        << "\n";

    std::shared_ptr<Unit> locked = observer.lock();

    if (locked == nullptr)
    {
        std::cout << "Weak pointer cannot lock. Object is gone.\n";
    }
}

void PrintParty(const std::vector<std::unique_ptr<Unit>>& party)
{
    std::cout << "=== Party ===\n";

    if (party.empty())
    {
        std::cout << "Party is empty.\n";
        return;
    }

    for (std::size_t i = 0; i < party.size(); ++i)
    {
        std::cout << i << ". ";

        if (party[i] == nullptr)
        {
            std::cout << "null unit\n";
            continue;
        }

        party[i]->Print();
    }
}

Unit* FindUnitByName(
    std::vector<std::unique_ptr<Unit>>& party,
    const std::string& name
)
{
    for (std::unique_ptr<Unit>& unit : party)
    {
        if (unit == nullptr)
        {
            continue;
        }
        if (unit->GetName() == name)
        {
            return unit.get();
        }
	}

    return nullptr;
}

// 도전 1: 죽은 유닛 제거
// HP 0인 Unit있으면 party에서 제거.
// 제거된 Unit이 있으면 소멸자 로그 출력.
// 생존 Unit이 있으면 유지.
// 제거 후 몇명 제거했는지 출력.
void RemoveDeadUnits(std::vector<std::unique_ptr<Unit>>& party)
{
    for (auto iterator = party.begin(); iterator != party.end();)
    {
        if ((*iterator)->IsDead())
        {
            iterator = party.erase(iterator);
        }
        else
        {
            ++iterator;
        }
    }
}

// 도전 2: 소유권 이전 실험
// 이름을 찾으면 해당 Unit 소유권을 vector 밖으로 이동.
// vector에서 제거하면 슬롯에서 사라짐.
// 반환값은 찾은 Unit의 unique_ptr. 찾는 이름이 없으면 nullptr 반환.
std::unique_ptr<Unit> ExtractUnitByName(
    std::vector<std::unique_ptr<Unit>>& party,
    const std::string& name
)
{
    for (auto iterator = party.begin(); iterator != party.end();)
    {
        if ((*iterator)->GetName() == name)
        {
            std::unique_ptr<Unit> extracted = std::move(*iterator);
            party.erase(iterator);
            std::cout << "Extracted. Type 1 to check.\n";
            return extracted;
        }
        else
        {
            ++iterator;
        }
    }
    std::cout << "No matching name.\n";
    return nullptr;    
}
