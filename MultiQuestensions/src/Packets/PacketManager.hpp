#pragma once
#include "main.hpp"
#include "PacketSerializer.hpp"

template <class T>
using PacketCallback = void (*)(T, GlobalNamespace::IConnectedPlayer*);

namespace MultiQuestensions {
	class PacketManager {
	private:
		GlobalNamespace::MultiplayerSessionManager* _sessionManager;
		PacketSerializer* packetSerializer;

	public:
		PacketManager(GlobalNamespace::MultiplayerSessionManager* sessionManager);
		void Send(LiteNetLib::Utils::INetSerializable* message);
		void SendUnreliable(LiteNetLib::Utils::INetSerializable* message);

		template <class TPacket>
		void RegisterCallback(PacketCallback<TPacket> callback) {
			System::Type* packetType = typeof(TPacket);
			Il2CppString* identifier = packetType->ToString();

			auto* newCallback = il2cpp_utils::MakeDelegate<CallbackAction*>(classof(CallbackAction*), &callback, *[](PacketCallback<TPacket> context, LiteNetLib::Utils::NetDataReader* reader, int size, GlobalNamespace::IConnectedPlayer* player) {
				TPacket packet = GlobalNamespace::ThreadStaticPacketPool_1<TPacket>::get_pool()->Obtain();
				if (packet == nullptr) {
					reader->SkipBytes(size);
				}
				else {
					packet->Deserialize(reader);
				}

				(*context)(packet, player);
			});

			packetSerializer->RegisterCallback(identifier, newCallback);
		}
	};
}