#pragma once

#ifdef SLASKSOUNDENGINE_EXPORTS 
#define SLASKSOUNDENGINE_API __declspec(dllexport)
#else
#define SLASKSOUNDENGINE_API __declspec(dllimport)
#endif

typedef void(__stdcall* Callback)(const char*);

extern "C" SLASKSOUNDENGINE_API void InitializeEngine();
extern "C" SLASKSOUNDENGINE_API void LoadSGAF(const char* path);
extern "C" SLASKSOUNDENGINE_API void PlayAudio();
extern "C" SLASKSOUNDENGINE_API void StopAudio();
extern "C" SLASKSOUNDENGINE_API void RegisterErrorLogger(Callback func);