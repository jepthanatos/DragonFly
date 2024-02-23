#ifndef __SKILL_H__
#define __SKILL_H__

// System includes.
#include <string>

namespace df
{
    enum class SkillType
    {
        FIST,
        SWORD,
        AXE,
        CLUB
    };

    static std::string SkillToString(SkillType s) {
        switch (s) {
            case SkillType::FIST:
                return "FIST";
            case SkillType::SWORD:
                return "SWORD";
            case SkillType::AXE:
                return "AXE";
            case SkillType::CLUB:
                return "CLUB";
            default:
                return "";
        }
    };

    template <SkillType _skill>
    class Skill
    {

    private:
        // SkillType m_id;     // Unique game engine defined identifier.
        int m_min_value;    // Minimum value the skill can have.
        int m_max_value;    // Maximum value the skill can have.
        int m_tries_needed; // Number of tries needed before next level.

    public:
        Skill(int min_value, int max_value, int tries) : m_min_value{min_value}, m_max_value{max_value}, m_tries_needed{tries}
        {
        }

        virtual ~Skill() {};

        SkillType getType() { return _skill; }
    };

} // end of namespace df
#endif // __SKILL_H__
