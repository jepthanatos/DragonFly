#ifndef __SKILL_MANAGER_H__
#define __SKILL_MANAGER_H__

#include "Singleton.h"
#include "Manager.h"
#include "Skill.h"
#include "Player.h"
#include "LogManager.h"

// System includes.
#include <vector>
#include <algorithm>
#include "spdlog/sinks/basic_file_sink.h"

// Two-letter acronym for easier access to manager.
#define RM_SWORD df::RankManager<SkillType::SWORD>::getInstance()

namespace df
{
    template <SkillType _skill>
    class RankManager : public Manager, public Singleton<RankManager<_skill>>
    {

    private:
        std::vector<Player> m_players_list;

    public:
        int startUp()
        {
            Manager::setType("RankManager-" + SkillToString(_skill));
            LM.getLogger()->debug("{} RankManager::startUp", SkillToString(_skill));
            return Manager::startUp();
        }

        void shutDown()
        {
            m_players_list.clear();
            Manager::shutDown();
            LM.getLogger()->debug("RankManager::shutDown");
        }

        void updateRanking()
        {
            std::sort(m_players_list.begin(), m_players_list.end(), [](Player a, Player b)
                      { return a.getSkill(_skill) > b.getSkill(_skill); });
        }

        void addPlayer(const Player &player)
        {
            m_players_list.emplace_back(std::move(player));
            updateRanking();
        }

        std::vector<Player> getRanking() const
        {
            return m_players_list;
        }

        short getPlayerRanking(std::string playerId)
        {
            for (int i = 0; i < m_players_list.size(); i++)
            {
                if (m_players_list[i].getName() == playerId)
                {
                    return i;
                }
            }
            return -1;
        }

        void printRanking()
        {
            auto ranking_logger = spdlog::basic_logger_mt("ranking_logger", "log/ranking.txt", true);
            ranking_logger->set_level(spdlog::level::debug);
            ranking_logger->set_pattern("[%H:%M:%S %z] [%^%L%$] [thread %t] %v");
            ranking_logger->debug("Ranking of: {}", SkillToString(_skill));
            for (auto player : m_players_list)
            {
                ranking_logger->debug("{} {}", player.getName(), player.getSkill(_skill));
            }
        }
    };

} // end of namespace df
#endif // __SKILL_MANAGER_H__
