/************************************************************************************
** Simple Media Player, allows to watch videos with simple and uncluttered interface.
** Copyright (C) 2011 Stanislav Ionascu
**
** Contact: Stanislav Ionascu <stanislav.ionascu@gmail.com>
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************************/

#ifndef SMPVIEW_P_H
#define SMPVIEW_P_H

#include <QtGlobal>

class SMPView;

class SMPViewPrivate
{
public:
    SMPViewPrivate();
    ~SMPViewPrivate();

private:
    Q_DECLARE_PUBLIC(SMPView)
    SMPView *q_ptr;

    bool forceAspectRatio;
    qreal aspectRatio;
};

#endif // SMPVIEW_P_H
