/**
 * (C) LGPL-3
 *
 * Tasteful Framework <https://github.com/scheibel/tasteful-framework>
 *
 * Copyright: 2012-2014 Lux, Scheibel
 * Authors:
 *     Roland Lux <rollux2000@googlemail.com>
 *     Willy Scheibel <willyscheibel@gmx.de>
 *
 * This file is part of Tasteful Framework.
 *
 * Tasteful Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tasteful Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Tasteful Framework.  If not, see <http://www.gnu.org/licenses/>.
 **/

#pragma once

#include <tasteful-framework/IdentityMap.h>

namespace tastefulframework {

template <class T, typename Identity>
IdentityMap<T, Identity>::IdentityMap()
{
}

template <class T, typename Identity>
Identity IdentityMap<T, Identity>::idOf(T * model) const
{
    m_lock.lockForRead();
    Identity id = m_identities.key(model);
    m_lock.unlock();

    return id;
}

template <class T, typename Identity>
bool IdentityMap<T, Identity>::hasModel(Identity id) const
{
    m_lock.lockForRead();
    bool has = m_identities.contains(id);
    m_lock.unlock();

    return has;
}

template <class T, typename Identity>
T * IdentityMap<T, Identity>::getModel(Identity id) const
{
    m_lock.lockForRead();
    T * model = hasModel(id) ? m_identities[id] : nullptr;
    m_lock.unlock();

    return model;
}

template <class T, typename Identity>
void IdentityMap<T, Identity>::registerModel(Identity id, T * model)
{
    m_lock.lockForWrite();
    m_identities[id] = model;
    m_lock.unlock();
}

} // namespace tastefulframework
