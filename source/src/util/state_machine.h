//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004 - 2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 12-18-2004
//! \file ./util/state_machine.h
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PIRANHA_UTIL_STATE_MACHINE_H__
#define __PIRANHA_UTIL_STATE_MACHINE_H__

#include "./singleton.h"
#include "./timer_global.h"
#include "../file/texture_mipmaps2d.h"
#include "../file/texture_rectangle.h"
#include "../file/texture_texture2d.h"

namespace util {

typedef enum
{
    STATE_NULL = 0,
    STATE_TEXTURE_TEXTURE2D,
    STATE_TEXTURE_MIPMAPS2D,
    STATE_TEXTURE_RECTANGLE,
    STATE_PAUSE,
    STATE_MAX
} EState;

typedef enum
{
    CONFIG_NULL = 0,
    CONFIG_NONE,
    CONFIG_DONE,
    CONFIG_FAIL
} EConfigured;

typedef enum
{
    ENABLED_NULL = 0,
    ENABLED_PAUSE,
} EEnabled;

class CStateMachine : public CSingleton<CStateMachine>
{
    friend class CSingleton<CStateMachine>;
    // 12-18-2004 - BUG : Under MinGW this declaration make fail the compilation ... but it is a better solution.
    //friend static void file::CTexture2D::Config ();
    friend class file::CTexture2D;
    friend class file::CMipmaps2D;
    friend class file::CRectangle;
    friend class util::CTimerGlobal;

    EConfigured m_Configured[STATE_MAX];
    bool m_Enabled[STATE_MAX];

private:
    CStateMachine ();
    ~CStateMachine ();

    void SetConfigured (const EState & State, const EConfigured & Configured);
    void Enable (const EEnabled & Enabled);
    void Disable (const EEnabled & Enabled);

public:
    EConfigured GetConfigured (const EState & State) const;
    bool Enabled (const EEnabled & Enabled) const;
    void Init ();
    void Log ();
    bool IsError ();
};

}; // util

#endif //__PIRANHA_UTIL_STATE_MACHINE_H__
