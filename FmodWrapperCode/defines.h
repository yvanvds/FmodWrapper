#pragma once


#ifdef FW_DLL_BUILD
#define API __declspec (dllexport)
#define EXTERN
#pragma warning (disable: 4251)
#elif defined (FW_DLL)
#define API __declspec (dllimport)
#define EXTERN extern
#pragma warning (disable: 4251)
#endif

#ifndef API
#define API   /**< This macro is added to all public class declarations. */
#define EXTERN
#endif

#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)