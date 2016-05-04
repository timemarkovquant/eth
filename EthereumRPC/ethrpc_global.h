#ifndef ETHRPC_GLOBAL_H
#define ETHRPC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ETHRPC_LIBRARY)
#  define ETHRPCSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ETHRPCSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ETHRPC_GLOBAL_H
