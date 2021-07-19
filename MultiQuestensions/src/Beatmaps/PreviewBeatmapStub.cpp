#include "Beatmaps/PreviewBeatmapStub.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "System/Threading/Tasks/TaskStatus.hpp"
#include "UnityEngine/ImageConversion.hpp"

DEFINE_TYPE(MultiQuestensions::Beatmaps, PreviewBeatmapStub);

namespace MultiQuestensions::Beatmaps {
	void PreviewBeatmapStub::FromPreview(Il2CppString* levelHashStr, GlobalNamespace::IPreviewBeatmapLevel* preview) {
		getLogger().debug("PreviewBeatmapStub::FromPreview");

		_preview = preview;
		isDownloaded = true;
		_downloadable = DownloadableState::Unchecked;

		levelID = preview->get_levelID();
		levelHash = levelHashStr;
		getLogger().debug("levelID: %s, levelHash: %s", to_utf8(csstrtostr(levelID)).c_str(), to_utf8(csstrtostr(levelHash)).c_str());

		songName = preview->get_songName();
		songSubName = preview->get_songSubName();
		songAuthorName = preview->get_songAuthorName();
		levelAuthorName = preview->get_levelAuthorName();
		getLogger().debug("songName: %s, songSubName: %s, songAuthorName: %s, levelAuthorName: %s", to_utf8(csstrtostr(songName)).c_str(), to_utf8(csstrtostr(songSubName)).c_str(), to_utf8(csstrtostr(songAuthorName)).c_str(), to_utf8(csstrtostr(levelAuthorName)).c_str());
		
		beatsPerMinute = preview->get_beatsPerMinute();
		songDuration = preview->get_songDuration();
		getLogger().debug("beatsPerMinute: %f, songDuration: %f", beatsPerMinute, songDuration);
	}

	void PreviewBeatmapStub::FromPacket(MultiQuestensions::Beatmaps::PreviewBeatmapPacket* packet) {
		getLogger().debug("PreviewBeatmapStub::FromPacket");

		isDownloaded = false;
		_downloadable = DownloadableState::Unchecked;
		
		levelID = packet->levelId;
		levelHash = LevelIdToHash(levelID)/*packet->levelHash*/;

		songName = packet->songName;
		songSubName = packet->songSubName;
		songAuthorName = packet->songAuthorName;
		levelAuthorName = packet->levelAuthorName;

		beatsPerMinute = packet->beatsPerMinute;
		songDuration = packet->songDuration;
	}

	System::Threading::Tasks::Task_1<UnityEngine::Sprite*>* PreviewBeatmapStub::GetCoverImageAsync(System::Threading::CancellationToken cancellationToken) {
		return _preview->GetCoverImageAsync(cancellationToken);
	}

	System::Threading::Tasks::Task_1<UnityEngine::AudioClip*>* PreviewBeatmapStub::GetPreviewAudioClipAsync(System::Threading::CancellationToken cancellationToken) {
		return _preview->GetPreviewAudioClipAsync(cancellationToken);
	}

	MultiQuestensions::Beatmaps::PreviewBeatmapPacket* PreviewBeatmapStub::GetPacket(Il2CppString* characteristic, GlobalNamespace::BeatmapDifficulty difficulty) {
		getLogger().debug("Start PreviewBeatmapStub::GetPacket");
		MultiQuestensions::Beatmaps::PreviewBeatmapPacket* packet = THROW_UNLESS(il2cpp_utils::New<MultiQuestensions::Beatmaps::PreviewBeatmapPacket*>());

		packet->levelId = levelID;
		packet->levelHash = levelHash;

		packet->songName = songName;
		packet->songSubName = songSubName;
		packet->songAuthorName = songAuthorName;
		packet->levelAuthorName = levelAuthorName;

		packet->beatsPerMinute = beatsPerMinute;
		packet->songDuration = songDuration;

		packet->characteristic = characteristic;
		packet->difficulty = difficulty;
		return packet;
	}

#pragma region All the pain in form of getter functions

	Il2CppString* PreviewBeatmapStub::get_levelID() {
		return levelID;
	}

	Il2CppString* PreviewBeatmapStub::get_songName() {
		return songName;
	}

	Il2CppString* PreviewBeatmapStub::get_songSubName() {
		return songSubName;
	}

	Il2CppString* PreviewBeatmapStub::get_songAuthorName() {
		return songAuthorName;
	}

	Il2CppString* PreviewBeatmapStub::get_levelAuthorName() {
		return levelAuthorName;
	}

	float PreviewBeatmapStub::get_beatsPerMinute() {
		return beatsPerMinute;
	}

	float PreviewBeatmapStub::get_songDuration() {
		return songDuration;
	}

	float PreviewBeatmapStub::get_songTimeOffset() {
		return songTimeOffset;
	}

	float PreviewBeatmapStub::get_previewDuration() {
		return previewDuration;
	}

	float PreviewBeatmapStub::get_previewStartTime() {
		return previewStartTime;
	}

	float PreviewBeatmapStub::get_shuffle() {
		return shuffle;
	}

	float PreviewBeatmapStub::get_shufflePeriod() {
		return shufflePeriod;
	}

	GlobalNamespace::EnvironmentInfoSO* PreviewBeatmapStub::get_allDirectionsEnvironmentInfo() {
		return allDirectionsEnvironmentInfo;
	}

	GlobalNamespace::EnvironmentInfoSO* PreviewBeatmapStub::get_environmentInfo() {
		return environmentInfo;
	}

	Array<GlobalNamespace::PreviewDifficultyBeatmapSet*>* PreviewBeatmapStub::get_previewDifficultyBeatmapSets() {
		return previewDifficultyBeatmapSets;
	}

#pragma endregion

}