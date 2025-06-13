#pragma once

#ifdef GROMIT_PLATFORM_WINDOWS
#ifdef GROMIT_EXPORTS
#define GROMIT_API __declspec(dllexport)
#else
#define GROMIT_API __declspec(dllimport)
#endif
#else
#define GROMIT_API
#endif