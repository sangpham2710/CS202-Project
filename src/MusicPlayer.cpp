#include "MusicPlayer.hpp"


MusicPlayer::MusicPlayer() : mMusic(), mFilenames(), mVolume(0) {
    mFilenames[Music::MenuTheme] = "./assets/music/8-bit/menu-theme.mp3";
    mFilenames[Music::MissionTheme] = "./assets/music/8-bit/mission-theme.mp3";
    mFilenames[Music::GameOverTheme] =
        "./assets/music/8-bit/game-over-theme.mp3";
    mFilenames[Music::LevelUpTheme] = "./assets/music/8-bit/level-up-theme.mp3";
}

void MusicPlayer::play(Music::ID theme) {
    std::string filename = mFilenames[theme];

    if (!mMusic.openFromFile(filename))
        throw std::runtime_error("Music " + filename + " could not be loaded.");

    mMusic.setVolume(mVolume);
    mMusic.setLoop(true);
    mMusic.play();
}

void MusicPlayer::stop() {
    mMusic.stop();
}

void MusicPlayer::setVolume(float volume) {
    mVolume = volume;
    mMusic.setVolume(mVolume);
}

void MusicPlayer::setPaused(bool paused) {
    if (paused)
        mMusic.pause();
    else
        mMusic.play();
}
