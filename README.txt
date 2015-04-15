1- Install the following dependencies by using:
sudo apt-get install -y libavformat-dev libfaac-dev libfaad-dev libmp3lame-dev libbz2-dev libtheora-dev libvorbis-dev zlib1g-dev libxvidcore-dev
2- Type the command sudo make to compile the files.
3- Usage: ./segmenter <input MPEG-TS file> <segment duration in seconds> <cuepoints comma seperated, use [] to skip input> <output MPEG-TS file prefix> <output m3u8 index file> <http prefix> [<segment window size>]
