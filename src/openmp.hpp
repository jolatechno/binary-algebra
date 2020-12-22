#ifndef _OPENMP_PRAGMA
  #if defined(_OPENMP)
    #define _OPENMP_PRAGMA(all) _Pragma(all)

    #if defined(TARGET)
      #define _OPENMP_GPU_PRAGMA(cpu, gpu) _Pragma(gpu)

    #else
      #define _OPENMP_GPU_PRAGMA(cpu, gpu) _Pragma(cpu)

    #endif

  #else
    #define _OPENMP_PRAGMA(all)
    #define _OPENMP_GPU_PRAGMA(cpu, gpu)

  #endif

  #if defined(_OPENMP) && defined(TARGET)
    #define _OPENMP_GPU(gpu) _Pragma(gpu)

  #else
    #define _OPENMP_GPU(gpu)
    
  #endif
#endif
