//////////////////////////////////////////////////////////////////////////////
// Piranha, Copyright (c) 2004-2005 G-Truc Creation (www.g-truc.net)
// Under LGPL licence 
//////////////////////////////////////////////////////////////////////////////
//! \author Groove (groove@g-truc.net)
//! \date 11-15-2004
//! \file ./scene/element_fade.cpp
//! \brief 
//////////////////////////////////////////////////////////////////////////////

#include "./element_fade.h"
#include "../window/index.h"

using namespace scene;

static const float      TIME =                  1.f;

CFade::CFade ()
{

}

CFade::~CFade ()
{

}

bool CFade::Load ()
{
    return true;
}

void CFade::Begin ()
{
    m_fTimeStart = util::CTimerGlobal::Instance ()->Time ();

    glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

void CFade::End ()
{

}

void CFade::Update ()
{

}

void CFade::Render () const
{
    glClear (GL_COLOR_BUFFER_BIT);

    window::CHUD::Instance ()->Update ();
    window::CHUD::Instance ()->Render ();

    glPushMatrix ();
        glMatrixMode (GL_PROJECTION);
	    glPushMatrix ();
            glViewport (0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
            glMatrixMode (GL_PROJECTION);
		    glLoadIdentity ();
		    glOrtho (0, 640, 0, 480, -1, 1);
		    glMatrixMode (GL_MODELVIEW);
		    glLoadIdentity ();

            glEnable (GL_BLEND);
                glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glColor4f (1.0f, 1.0f, 1.0f, 1.f - (util::CTimerGlobal::Instance ()->Time () - m_fTimeStart) / TIME);
                glBegin (GL_QUADS);
                    glVertex2f (0, 0);
                    glVertex2f (640, 0);
                    glVertex2f (640, 480);
                    glVertex2f (0, 480);
                glEnd ();
            glDisable (GL_BLEND);

		    glMatrixMode (GL_PROJECTION);
	    glPopMatrix ();
	    glMatrixMode (GL_MODELVIEW);
    glPopMatrix ();
}

bool CFade::IsEnd ()
{
    return util::CTimerGlobal::Instance ()->Time () - m_fTimeStart > TIME;
}

EType CFade::Type ()
{
    return TYPE_FADE;
}

bool CFade::HUD ()
{
    return false;
}
