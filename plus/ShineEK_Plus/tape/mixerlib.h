#ifndef DAGEXING_MIX_MIXER_DLL_H_
#define DAGEXING_MIX_MIXER_DLL_H_

namespace dagexing {

void* CreateHandle(bool disable_mixer=false);

bool LoadNoiseFile(void* handle, char const* noise_filename);

bool StartSong(void* handle,
  char const* voice_wav_filename,
  char const* out_mp3_file,
  char const* out_mp3_second_file,
  unsigned int music_sample_rate = 44100,
  double finish_time_rate = 0.8);

bool MusicSample(void* handle,
  short* ch0,
  short* ch1,
  unsigned int sample_num);

bool FinishSong(void* handle);

void DestroyHandle(void* handle);

char const* GetMp3FileName(void* handle,
  char const* song_time,
  char const* song_id,
  char const* ktv_room,
  char const* passwd,
  int song_second,
  int score);

char const* GetMp3SecondFileName(void* handle,
  char const* song_time,
  char const* song_id,
  char const* ktv_room,
  char const* passwd,
  int song_second,
  int score);

char const* GetPassword(void* handle, short ktv_id, unsigned char ktv_room_id,
  char const* open_time);

char const* GetKtvRoomOpenFileName(void* handle, char const* ktv_room,
  char const* open_time, char const* passwd);

char const* GetKtvRoomClosedFileName(void* handle, char const* ktv_room, 
  char const* open_time, char const* closed_time, char const* passwd);

char const* GetErrMsg(void* handle);

bool DumpDefaultConf(void* handle, char const* path);


}  // dagexing

#endif
