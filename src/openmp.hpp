#pragma once

#if defined(_OPENMP)
  #define _OPENMP_PRAGMA(all) _Pragma(all)

  #include <omp.h>

  #ifndef GPU_LIMIT
    #define GPU_LIMIT 10000
  #endif

  #ifndef CPU_LIMIT
    #define CPU_LIMIT 500
  #endif
#else
  #define _OPENMP_PRAGMA(all)
#endif

#if defined(_OPENMP) && defined(TARGET)
  #define _OPENMP_GPU_PRAGMA(gpu) _Pragma(gpu)
#else
  #define _OPENMP_GPU_PRAGMA(gpu)
#endif
