#include <iostream>
using namespace std;

class MediaFiles {
    string path;
    int size;
public:
    MediaFiles(string path, int size) : path(path), size(size) {}

    string getPath() const { return path; }
    int getSize() const { return size; }

    virtual void play() {
        cout << "Playing media..." << endl;
    }

    virtual void stop() {
        cout << "Stopping media..." << endl;
    }
};

class VisualMedia : virtual public MediaFiles {
public:
    VisualMedia(string path, int size) : MediaFiles(path, size) {}
};

class AudioMedia : virtual public MediaFiles {
public:
    AudioMedia(string path, int size) : MediaFiles(path, size) {}
};

class VideoFile : public VisualMedia, public AudioMedia {
public:
    VideoFile(string path, int size)
        : MediaFiles(path, size), VisualMedia(path, size), AudioMedia(path, size) {}

    void play() override {
        cout << "Playing Video File: " << getPath() << endl;
    }

    void stop() override {
        cout << "Stopped Video Playback: " << getPath() << endl;
    }
};

class ImageFile : public VisualMedia {
public:
    ImageFile(string path, int size) : MediaFiles(path, size), VisualMedia(path, size) {}

    void play() override {
        cout << "Displaying Image: " << getPath() << endl;
    }

    void stop() override {
        cout << "Closing Image Display: " << getPath() << endl;
    }
};

class AudioFile : public AudioMedia {
public:
    AudioFile(string path, int size) : MediaFiles(path, size), AudioMedia(path, size) {}

    void play() override {
        cout << "Playing Audio: " << getPath() << endl;
    }

    void stop() override {
        cout << "Stopped Audio Playback: " << getPath() << endl;
    }
};

int main() {
    MediaFiles* files[] = {
        new VideoFile("movie.mp4", 1024),
        new ImageFile("photo.jpg", 500),
        new AudioFile("song.mp3", 300)
    };

    for (int i = 0; i < 3; ++i) {
        cout << "File: " << files[i]->getPath() << ", Size: " << files[i]->getSize() << " MB" << endl;
        files[i]->play();
        files[i]->stop();
        delete files[i];
    }

    return 0;
}
