/**
 * Appcelerator Titanium License
 * This source code and all modifications done by Appcelerator
 * are licensed under the Apache Public License (version 2) and
 * are Copyright (c) 2009-2014 by Appcelerator, Inc.
 */

/*
 *  Copyright (C) 1999-2001 Harri Porten (porten@kde.org)
 *  Copyright (C) 2001 Peter Kelly (pmk@post.com)
 *  Copyright (C) 2003, 2004, 2005, 2007, 2008 Apple Inc. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 *
 */

#ifndef JSAPIValueWrapper_h
#define JSAPIValueWrapper_h

#include "JSCTiValue.h"
#include "JSCell.h"
#include "CallFrame.h"
#include "Structure.h"

namespace TI {

    class JSAPIValueWrapper : public JSCell {
        friend TiValue jsAPIValueWrapper(ExecState*, TiValue);
    public:
        typedef JSCell Base;

        TiValue value() const { return m_value.get(); }

        static Structure* createStructure(VM& vm, JSGlobalObject* globalObject, TiValue prototype)
        {
            return Structure::create(vm, globalObject, prototype, TypeInfo(APIValueWrapperType, OverridesVisitChildren | OverridesGetPropertyNames), info());
        }
        
        DECLARE_EXPORT_INFO;
        
        static JSAPIValueWrapper* create(ExecState* exec, TiValue value) 
        {
            VM& vm = exec->vm();
            JSAPIValueWrapper* wrapper = new (NotNull, allocateCell<JSAPIValueWrapper>(vm.heap)) JSAPIValueWrapper(exec);
            wrapper->finishCreation(vm, value);
            return wrapper;
        }

    protected:
        void finishCreation(VM& vm, TiValue value)
        {
            Base::finishCreation(vm);
            m_value.set(vm, this, value);
            ASSERT(!value.isCell());
        }

    private:
        JSAPIValueWrapper(ExecState* exec)
            : JSCell(exec->vm(), exec->vm().apiWrapperStructure.get())
        {
        }

        WriteBarrier<Unknown> m_value;
    };

    inline TiValue jsAPIValueWrapper(ExecState* exec, TiValue value)
    {
        return JSAPIValueWrapper::create(exec, value);
    }

} // namespace TI

#endif // JSAPIValueWrapper_h
