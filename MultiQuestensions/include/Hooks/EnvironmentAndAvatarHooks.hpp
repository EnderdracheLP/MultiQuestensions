#pragma once
#include "GlobalNamespace/IConnectedPlayer.hpp"
#include "UnityEngine/Color.hpp"

namespace MultiQuestensions {
    extern void SetPlayerPlaceColor(GlobalNamespace::IConnectedPlayer* player, const UnityEngine::Color& color, bool priority);
    extern void UpdateNameTagIcons();
}

#include "GlobalNamespace/MultiplayerSessionManager.hpp"
namespace MultiplayerCore {
    extern GlobalNamespace::MultiplayerSessionManager* _multiplayerSessionManager;
}