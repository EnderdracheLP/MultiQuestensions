#include "Extensions/ExtendedPlayer.hpp"
#include "CodegenExtensions/ColorUtility.hpp"

DEFINE_TYPE(MultiQuestensions::Extensions, ExtendedPlayer)

DEFINE_TYPE(MultiQuestensions::Extensions, ExtendedPlayerPacket)

namespace MultiQuestensions::Extensions {

    static constexpr Il2CppString* const MQE_Protocol() {
        return il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>(MPEX_PROTOCOL);
    }

#pragma region ExtendedPlayer
    void ExtendedPlayer::ExtendedPlayer_ctor(GlobalNamespace::IConnectedPlayer* player, Il2CppString* platformID, int platform, UnityEngine::Color playerColor, Il2CppString* mpexVersion) {
        getLogger().debug("Creating ExtendedPlayer");
        _connectedPlayer = player;
        if (mpexVersion) this->mpexVersion = mpexVersion;
        else this->mpexVersion = MQE_Protocol();
        if (platformID) {
            this->platformID = platformID;
            this->platform = (Platform)platform;
            this->playerColor = playerColor;
        }
        getLogger().debug("Finished Creating ExtendedPlayer");
    }

    ExtendedPlayer* ExtendedPlayer::CS_ctor(GlobalNamespace::IConnectedPlayer* player) {
        return THROW_UNLESS(il2cpp_utils::New<ExtendedPlayer*, il2cpp_utils::CreationType::Manual>(player, static_cast<Il2CppString*>(nullptr), 3, DefaultColor, static_cast<Il2CppString*>(nullptr)));
    }
    ExtendedPlayer* ExtendedPlayer::CS_ctor(GlobalNamespace::IConnectedPlayer* player, Il2CppString* platformID, Platform platform, UnityEngine::Color playerColor) {
        return THROW_UNLESS(il2cpp_utils::New<ExtendedPlayer*>(player, platformID, (int)platform, playerColor, static_cast<Il2CppString*>(nullptr)));
    }
    ExtendedPlayer* ExtendedPlayer::CS_ctor(GlobalNamespace::IConnectedPlayer* player, Il2CppString* platformID, Platform platform, Il2CppString* mpexVersion, UnityEngine::Color playerColor) {
        return THROW_UNLESS(il2cpp_utils::New<ExtendedPlayer*>(player, platformID, (int)platform, playerColor, mpexVersion));
    }
#pragma endregion

#pragma region Getters
    Il2CppString* ExtendedPlayer::get_platformID() {
        return platformID;
    }
    Platform ExtendedPlayer::get_platform() {
        return platform;
    }
    Il2CppString* ExtendedPlayer::get_mpexVersion() {
        return mpexVersion;
    }
#pragma endregion

#pragma region ExtendedPlayerPacket
    void ExtendedPlayerPacket::New() {}

    void ExtendedPlayerPacket::Release() {
        getLogger().debug("ExtendedPlayerPacket::Release");
        GlobalNamespace::ThreadStaticPacketPool_1<ExtendedPlayerPacket*>::get_pool()->Release(this);
    }

    void ExtendedPlayerPacket::Serialize(LiteNetLib::Utils::NetDataWriter* writer) {
        getLogger().debug("ExtendedPlayerPacket::Serialize");

        writer->Put(platformID);
        writer->Put(mpexVersion);
        writer->Put(UnityEngine::ColorUtility::ToHtmlStringRGB(playerColor));
        //writer->Put(Il2CppString::Concat(il2cpp_utils::newcsstr("#"), UnityEngine::ColorUtility::ToHtmlStringRGB(playerColor)));
        writer->Put((int)platform);
        getLogger().debug("Serialize ExtendedPlayerPacket done");
    }

    void ExtendedPlayerPacket::Deserialize(LiteNetLib::Utils::NetDataReader* reader) {
        getLogger().debug("ExtendedPlayerPacket::Deserialize");

        platformID = reader->GetString();
        mpexVersion = reader->GetString();
        if (!UnityEngine::ColorUtility::TryParseHtmlString(reader->GetString(), playerColor))
            this->playerColor = ExtendedPlayer::DefaultColor;
        if (reader->get_AvailableBytes() >= 4) // Verify this works when the platform int exists.
            this->platform = (Platform)reader->GetInt();
        else
            this->platform = Platform::Unknown;
        getLogger().debug("Deserialize ExtendedPlayerPacket done");
    }

    ExtendedPlayerPacket* ExtendedPlayerPacket::Init(Il2CppString* platformID, Platform platform, UnityEngine::Color playerColor)
    {
        auto extendedPlayer = THROW_UNLESS(il2cpp_utils::New<ExtendedPlayerPacket*>());
        
        extendedPlayer->platformID = platformID;
        extendedPlayer->platform = (Platform)platform;
        extendedPlayer->playerColor = playerColor;
        extendedPlayer->mpexVersion = MQE_Protocol();
        return extendedPlayer;
    }
#pragma endregion
}