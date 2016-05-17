//! \cond INTERNAL

#include "../include/mounts/MountWatcher.h"

/*!
 * \file MountWatcher.cpp
 * Contains MountWatcher implementation.
 */


#ifdef __linux__
#include "linux/MountWatcherImpl.h"
#else
#error This OS is not supported yet.
#endif

MountWatcher::MountWatcher()
    : Observable()
    , _impl(new Implementation(*this))
{
}

MountWatcher::~MountWatcher()
{
}

void MountWatcher::forcedUpdate() const
{
	_impl->forcedUpdate();
}

//! \endcond
