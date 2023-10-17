#ifndef VPNCORE_GLOBAL_H
#define VPNCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VPNCORE_LIBRARY)
#  define VPNCORE_EXPORT Q_DECL_EXPORT
#else
#  define VPNCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // VPNCORE_GLOBAL_H
