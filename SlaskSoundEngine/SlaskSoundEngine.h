#pragma once

#ifdef SLASKSOUNDENGINE_EXPORTS 
#define SLASKSOUNDENGINE_API __declspec(dllexport)
#else
#define SLASKSOUNDENGINE_API __declspec(dllimport)
#endif

extern "C" SLASKSOUNDENGINE_API void InitializeEngine();
extern "C" SLASKSOUNDENGINE_API void LoadSGAF(const char* path);
extern "C" SLASKSOUNDENGINE_API void PlayAudio();
extern "C" SLASKSOUNDENGINE_API void StopAudio();